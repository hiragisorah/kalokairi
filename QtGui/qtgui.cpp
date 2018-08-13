#include "qtgui.h"

bool break_flag_1 = false;

unsigned int ItemData::cnt = 0;

QtGui::QtGui(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	//New、Openの各tiriggeredシグナルを捕捉
	connect(ui.actionImport, SIGNAL(triggered()), this, SLOT(actionImport()));
	connect(ui.actionExport, SIGNAL(triggered()), this, SLOT(actionExport()));

	auto & widget = ui.widget;
	auto handle = reinterpret_cast<void*>(widget->winId());
	auto width = widget->width();
	auto height = widget->height();

	graphics.Initialize(handle, width, height);

	rtv = graphics.CreateBackBuffer();
	dsv = graphics.CreateDepthStencil(width, height);
	vp = graphics.CreateViewPort(width, height);
	//box = graphics.CreatePlane(10, 10, { 0.5f, 0.5f });
	//box = graphics.CreateBox();
	//box = graphics.CreateSphere();
	shader = graphics.CreateShader("../default3d.hlsl");

	wvp.world = DirectX::XMMatrixIdentity();
	wvp.view = DirectX::XMMatrixLookAtLH(DirectX::XMVectorSet(0, 5.f, -5.f, 0.f), DirectX::XMVectorZero(), DirectX::XMVectorSet(0, 1, 0, 0));
	wvp.projection = DirectX::XMMatrixPerspectiveFovLH(DirectX::XM_PIDIV4, static_cast<float>(width) / static_cast<float>(height), 0.1f, 100.f);

	graphics.ClearTarget({ rtv }, { dsv });
	graphics.SetTarget({ rtv }, { dsv });
	graphics.SetViewPort(vp);
	graphics.SetShader(shader, &wvp);
}

void QtGui::paintEvent(QPaintEvent * ev)
{
	graphics.ClearTarget({ rtv }, { dsv });

	for (int i = 0; i < ui.parts_list->count(); ++i)
	{
		auto & item = GetData(ui.parts_list->item(i));

		if (item.primitive_id != -1)
		{
			auto world
				= DirectX::XMMatrixScaling(item.scale.x, item.scale.y, item.scale.z)
				* DirectX::XMMatrixRotationRollPitchYaw(item.rotation.x, item.rotation.y, item.rotation.z)
				* DirectX::XMMatrixTranslation(item.position.x, item.position.y, item.position.z);

			auto parent = no_to_item[item.parent];
			
			while (parent != nullptr)
			{
				auto & p = GetData(parent);

				auto p_world
					= DirectX::XMMatrixScaling(p.scale.x, p.scale.y, p.scale.z)
					* DirectX::XMMatrixRotationRollPitchYaw(p.rotation.x, p.rotation.y, p.rotation.z)
					* DirectX::XMMatrixTranslation(p.position.x, p.position.y, p.position.z);

				world *= p_world;

				parent = no_to_item[p.parent];
			}

			wvp.world = world;

			graphics.SetShader(shader, &wvp);

			graphics.Draw(item.primitive_id);
		}
	}

	graphics.Run();
}

ItemData & QtGui::GetData(unsigned int no)
{
	return main_data[no];
}

ItemData & QtGui::GetData(QListWidgetItem * item)
{
	return main_data[item_to_no[item]];
}

void QtGui::on_delete_button_pressed(void)
{
	auto current_item = ui.parts_list->currentItem();
	main_data.erase(item_to_no[current_item]);
	no_to_item.erase(item_to_no[current_item]);
	item_to_no.erase(current_item);
	delete current_item;
}

void QtGui::on_rename_button_pressed(void)
{
	ui.parts_list->currentItem()->setText(ui.rename_box->text());

	main_data[item_to_no[ui.parts_list->currentItem()]].name = ui.rename_box->text().toStdString();
}

void QtGui::on_parent_combo_currentIndexChanged(int row)
{
	if(!break_flag_1) return;

	auto this_item = ui.parts_list->currentItem();
	auto parent_item = ui.parts_list->item(row);
	
	if (parent_item == this_item)
		parent_item = nullptr;

	GetData(this_item).parent = item_to_no[parent_item];
	GetData(parent_item).self = item_to_no[parent_item];
}

void QtGui::on_parts_list_currentRowChanged(int row)
{
	auto this_item = ui.parts_list->currentItem();
	if (this_item == nullptr)
	{
		ui.rename_box->setText("");

		ui.rename_group->setDisabled(true);
		ui.transform_group->setDisabled(true);
		ui.primitive_group->setDisabled(true);
		ui.delete_button->setDisabled(true);
	}
	else
	{
		ui.rename_group->setEnabled(true);
		ui.transform_group->setEnabled(true);
		ui.primitive_group->setEnabled(true);
		ui.delete_button->setEnabled(true);

		ui.rename_box->setText(this_item->text());

		{ // Parent Combo
			break_flag_1 = false;

			ui.parent_combo->clear();

			bool parent_finded = false;

			for (int i = 0; i < ui.parts_list->count(); ++i)
			{
				auto target_item = ui.parts_list->item(i);

				if (this_item != target_item)
				{
					ui.parent_combo->addItem(ui.parts_list->item(i)->text());
					if (target_item == no_to_item[GetData(this_item).parent])
					{
						parent_finded = true;
						ui.parent_combo->setCurrentIndex(i);
					}
				}
				else
				{
					ui.parent_combo->addItem("(none)");
					if (no_to_item[GetData(this_item).parent] == nullptr)
					{
						parent_finded = true;
						ui.parent_combo->setCurrentIndex(i);
					}
				}
			}
			if (!parent_finded)
			{
				for (int i = 0; i < ui.parts_list->count(); ++i)
				{
					auto target_item = ui.parts_list->item(i);

					if (this_item == target_item)
					{
						no_to_item[GetData(this_item).parent] = nullptr;
						ui.parent_combo->setCurrentIndex(i);
					}
				}
			}
		}

		{ // Transform Box
			ui.position_x->setValue(static_cast<double>(GetData(this_item).position.x));
			ui.position_y->setValue(static_cast<double>(GetData(this_item).position.y));
			ui.position_z->setValue(static_cast<double>(GetData(this_item).position.z));

			ui.rotation_x->setValue(static_cast<double>(GetData(this_item).rotation.x));
			ui.rotation_y->setValue(static_cast<double>(GetData(this_item).rotation.y));
			ui.rotation_z->setValue(static_cast<double>(GetData(this_item).rotation.z));

			ui.scale_x->setValue(static_cast<double>(GetData(this_item).scale.x));
			ui.scale_y->setValue(static_cast<double>(GetData(this_item).scale.y));
			ui.scale_z->setValue(static_cast<double>(GetData(this_item).scale.z));
		}

		{ // Primitive Type
			ui.primitive_type->setCurrentIndex(GetData(this_item).primitive_type);
			
			ui.plane_div_x->setValue(GetData(this_item).plane_div_x);
			ui.plane_div_y->setValue(GetData(this_item).plane_div_y);
			ui.plane_size_x->setValue(GetData(this_item).plane_size.x);
			ui.plane_size_y->setValue(GetData(this_item).plane_size.y);

			ui.box_size_x->setValue(GetData(this_item).box_size.x);
			ui.box_size_y->setValue(GetData(this_item).box_size.y);
			ui.box_size_z->setValue(GetData(this_item).box_size.z);

			ui.sphere_diameter->setValue(GetData(this_item).sphere_diameter);
			ui.sphere_tesselation->setValue(GetData(this_item).sphere_tesselation);
		}

		break_flag_1 = true;
	}
}

void QtGui::on_position_x_valueChanged(double value)
{
	GetData(ui.parts_list->currentItem()).position.x = static_cast<float>(value);
}

void QtGui::on_position_y_valueChanged(double value)
{
	GetData(ui.parts_list->currentItem()).position.y = static_cast<float>(value);
}

void QtGui::on_position_z_valueChanged(double value)
{
	GetData(ui.parts_list->currentItem()).position.z = static_cast<float>(value);
}

void QtGui::on_rotation_x_valueChanged(double value)
{
	GetData(ui.parts_list->currentItem()).rotation.x = static_cast<float>(value);
}

void QtGui::on_rotation_y_valueChanged(double value)
{
	GetData(ui.parts_list->currentItem()).rotation.y = static_cast<float>(value);
}

void QtGui::on_rotation_z_valueChanged(double value)
{
	GetData(ui.parts_list->currentItem()).rotation.z = static_cast<float>(value);
}

void QtGui::on_scale_x_valueChanged(double value)
{
	GetData(ui.parts_list->currentItem()).scale.x = static_cast<float>(value);
}

void QtGui::on_scale_y_valueChanged(double value)
{
	GetData(ui.parts_list->currentItem()).scale.y = static_cast<float>(value);
}

void QtGui::on_scale_z_valueChanged(double value)
{
	GetData(ui.parts_list->currentItem()).scale.z = static_cast<float>(value);
}

void QtGui::on_primitive_type_currentChanged(int value)
{
	GetData(ui.parts_list->currentItem()).primitive_type = value;

	this->UpdatePrimitive();
}

void QtGui::on_plane_div_x_valueChanged(int value)
{
	GetData(ui.parts_list->currentItem()).plane_div_x = value;

	this->UpdatePrimitive();
}

void QtGui::on_plane_div_y_valueChanged(int value)
{
	GetData(ui.parts_list->currentItem()).plane_div_y = value;

	this->UpdatePrimitive();
}

void QtGui::on_plane_size_x_valueChanged(double value)
{
	GetData(ui.parts_list->currentItem()).plane_size.x = value;

	this->UpdatePrimitive();
}

void QtGui::on_plane_size_y_valueChanged(double value)
{
	GetData(ui.parts_list->currentItem()).plane_size.y = value;

	this->UpdatePrimitive();
}

void QtGui::on_box_size_x_valueChanged(double value)
{
	GetData(ui.parts_list->currentItem()).box_size.x = value;

	this->UpdatePrimitive();
}

void QtGui::on_box_size_y_valueChanged(double value)
{
	GetData(ui.parts_list->currentItem()).box_size.y = value;

	this->UpdatePrimitive();
}

void QtGui::on_box_size_z_valueChanged(double value)
{
	GetData(ui.parts_list->currentItem()).box_size.z = value;

	this->UpdatePrimitive();
}

void QtGui::on_sphere_diameter_valueChanged(double value)
{
	GetData(ui.parts_list->currentItem()).sphere_diameter = value;

	this->UpdatePrimitive();
}

void QtGui::on_sphere_tesselation_valueChanged(int value)
{
	GetData(ui.parts_list->currentItem()).sphere_tesselation = value;

	this->UpdatePrimitive();
}

void QtGui::on_wire_mode_check_toggled(bool toggle)
{
	graphics.EnableWireFrame(toggle);
}

void QtGui::actionImport(void)
{
	Save();
}

void QtGui::actionExport(void)
{
	Load();
}

void QtGui::UpdatePrimitive(void)
{
	auto & item = GetData(ui.parts_list->currentItem());

	auto & primitive_id = item.primitive_id;
	auto & primitive_type = item.primitive_type;

	if (primitive_id != -1)
		graphics.UnloadGeometry(primitive_id);

	if (primitive_type == 0)
	{
		primitive_id = -1;
	}
	else if (primitive_type == 1)
	{
		primitive_id = graphics.CreatePlane(item.plane_div_x, item.plane_div_y, item.plane_size);
	}
	else if (primitive_type == 2)
	{
		primitive_id = graphics.CreateBox(item.box_size);
	}
	else if (primitive_type == 3)
	{
		primitive_id = graphics.CreateSphere(item.sphere_diameter, item.sphere_tesselation);
	}
}

void QtGui::Save(void)
{
	save_data = main_data;
	saved_cnt = ItemData::cnt;
}

void QtGui::Load(void)
{
	ItemData::cnt = saved_cnt;

	ui.parts_list->clear();

	main_data = save_data;

	item_to_no.clear();
	no_to_item.clear();

	for (auto & data : main_data)
	{
		auto & sdata = data.second;

		ui.parts_list->addItem(sdata.name.c_str());
		auto item = ui.parts_list->item(ui.parts_list->count() - 1);
		item_to_no[item] = sdata.self;
		no_to_item[sdata.self] = item;
	}
}

void QtGui::on_add_button_pressed(void)
{
	char str[80];
	sprintf(str, "%3d: %s", ItemData::cnt, "Empty Object");
	ui.parts_list->addItem(str);
	auto item = ui.parts_list->item(ui.parts_list->count() - 1);
	item_to_no[item] = ItemData::cnt;
	no_to_item[ItemData::cnt] = item;
	main_data[item_to_no[item]].name = str;

	ItemData::cnt++;
}
