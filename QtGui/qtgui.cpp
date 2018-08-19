#include "qtgui.h"
#include <QtWidgets/qfiledialog.h>

bool break_flag_1 = false;

QtGui::QtGui(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	//New、Openの各tiriggeredシグナルを捕捉
	connect(ui.actionImport, SIGNAL(triggered()), this, SLOT(actionImport()));
	connect(ui.actionExport, SIGNAL(triggered()), this, SLOT(actionExport()));

	this->wire_frame_ = false;

	auto & widget = ui.widget;
	auto handle = reinterpret_cast<void*>(widget->winId());
	auto width = widget->width();
	auto height = widget->height();

	graphics.Initialize(handle, width, height);

	this->dir_light_ = DirectX::Vector3(0, -100, 50);

	this->backbuffer_ = graphics.CreateBackBuffer();

	this->col_map_ = graphics.CreateColorMap(graphics.width(), graphics.height());
	this->pos_map_ = graphics.CreatePositionMap(graphics.width(), graphics.height());
	this->nor_map_ = graphics.CreateNormalMap(graphics.width(), graphics.height());
	this->dep_map_ = graphics.CreateNormalMap(graphics.width(), graphics.height());

	this->dsv_ = graphics.CreateDepthStencil(graphics.width(), graphics.height());
	this->vp_ = graphics.CreateViewPort(graphics.width(), graphics.height());

	this->shader_backbuffer_ = graphics.CreateShader("../backbuffer3d.hlsl");
	this->shader_deffered_ = graphics.CreateShader("../deffered3d.hlsl");

	graphics.SetEye(DirectX::Vector3(0, 5, -5));
	graphics.SetView(DirectX::Matrix::CreateLookAt(DirectX::Vector3(0, 5, -5), DirectX::Vector3::Zero, DirectX::Vector3(0, 1, 0)));
	graphics.SetProjection(DirectX::Matrix::CreatePerspectiveFieldOfView(DirectX::XM_PIDIV4,
		static_cast<float>(graphics.width()) / static_cast<float>(graphics.height()), 0.3f, 1000.f));
	graphics.SetViewPort(this->vp_);
}

void QtGui::paintEvent(QPaintEvent * ev)
{
	graphics.ClearTarget({ this->backbuffer_, this->col_map_, this->pos_map_, this->nor_map_, this->dep_map_ }, { this->dsv_ });
	graphics.SetTarget({ this->col_map_, this->pos_map_, this->nor_map_, this->dep_map_ }, this->dsv_);

	graphics.SetDirectionLight(this->dir_light_);

	graphics.SetShader(this->shader_deffered_);

	graphics.UpdateMainConstantBuffer();

	graphics.EnableWireFrame(this->wire_frame_);

	for (int i = 0; i < ui.parts_list->count(); ++i)
	{
		auto & item = main_data[item_no[i]];

		if (item.primitive_id != -1)
		{
			auto offset
				= DirectX::XMMatrixScaling(item.offset_scale.x, item.offset_scale.y, item.offset_scale.z)
				* DirectX::XMMatrixRotationRollPitchYaw(item.offset_rotation.x, item.offset_rotation.y, item.offset_rotation.z)
				* DirectX::XMMatrixTranslation(item.offset_position.x, item.offset_position.y, item.offset_position.z);

			auto world
				= DirectX::XMMatrixScaling(item.scale.x, item.scale.y, item.scale.z)
				* DirectX::XMMatrixRotationRollPitchYaw(item.rotation.x, item.rotation.y, item.rotation.z)
				* DirectX::XMMatrixTranslation(item.position.x, item.position.y, item.position.z);

			auto parent = item.parent;
			
			while (parent != -1)
			{
				auto & p = main_data[parent];

				auto p_world
					= DirectX::XMMatrixScaling(p.scale.x, p.scale.y, p.scale.z)
					* DirectX::XMMatrixRotationRollPitchYaw(p.rotation.x, p.rotation.y, p.rotation.z)
					* DirectX::XMMatrixTranslation(p.position.x, p.position.y, p.position.z);

				world *= p_world;

				parent = p.parent;
			}

			graphics.SetWorld(offset * world);

			graphics.UpdateModelConstantBuffer();

			graphics.Draw(item.primitive_id);
		}
	}

	graphics.EnableWireFrame(false);

	graphics.SetTarget({ this->backbuffer_ }, this->dsv_);

	graphics.SetShader(this->shader_backbuffer_);

	graphics.DrawScreen({ this->col_map_, this->pos_map_, this->nor_map_, this->dep_map_ });

	graphics.Run();
}

ItemData & QtGui::GetData(int no)
{
	return main_data[item_no[no]];
}

void QtGui::on_delete_button_pressed(void)
{
	auto row = ui.parts_list->currentRow();
	auto no = item_no[row];
	main_data.erase(no);
	delete ui.parts_list->currentItem();
	item_no.erase(item_no.begin() + row);
}

void QtGui::on_clear_button_pressed(void)
{
	ui.parts_list->clear();
	main_data.clear();
	item_no.clear();
	ItemData::cnt = 0;
}

void QtGui::on_rename_button_pressed(void)
{
	ui.parts_list->currentItem()->setText(ui.rename_box->text());

	auto row = ui.parts_list->currentRow();
	auto no = item_no[row];

	main_data[no].name = ui.rename_box->text().toStdString();
}

void QtGui::on_parent_combo_currentIndexChanged(int row)
{
	if(!break_flag_1) return;

	auto mrow = ui.parts_list->currentRow();
	auto no = item_no[mrow];

	if (mrow == row)
		main_data[no].parent = -1;
	else
		main_data[no].parent = item_no[row];
}

void QtGui::on_parts_list_currentRowChanged(int row)
{
	auto this_item = ui.parts_list->currentItem();

	if (this_item == nullptr)
	{
		ui.rename_box->setText("");

		ui.rename_group->setDisabled(true);
		ui.transform_type->setDisabled(true);
		ui.primitive_type->setDisabled(true);
		ui.delete_button->setDisabled(true);
	}
	else
	{
		ui.rename_group->setEnabled(true);
		ui.transform_type->setEnabled(true);
		ui.primitive_type->setEnabled(true);
		ui.delete_button->setEnabled(true);

		ui.rename_box->setText(this_item->text());

		{ // Parent Combo
			break_flag_1 = false;

			ui.parent_combo->clear();

			bool parent_finded = false;

			for (int i = 0; i < ui.parts_list->count(); ++i)
			{
				auto this_no = item_no[ui.parts_list->currentRow()];
				auto target_no = item_no[i];

				if (this_no != target_no)
				{
					ui.parent_combo->addItem(ui.parts_list->item(i)->text());
					if (target_no == main_data[this_no].parent)
					{
						parent_finded = true;
						ui.parent_combo->setCurrentIndex(i);
					}
				}
				else
				{
					ui.parent_combo->addItem("(none)");
					if (main_data[this_no].parent == -1)
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
					auto this_no = item_no[ui.parts_list->currentRow()];
					auto target_no = item_no[i];

					if (this_no == target_no)
					{
						main_data[this_no].parent = -1;
						ui.parent_combo->setCurrentIndex(i);
					}
				}
			}
		}

		{ // Transform Box
			ui.position_x->setValue(static_cast<double>(GetData(row).position.x));
			ui.position_y->setValue(static_cast<double>(GetData(row).position.y));
			ui.position_z->setValue(static_cast<double>(GetData(row).position.z));

			ui.rotation_x->setValue(static_cast<double>(GetData(row).rotation.x));
			ui.rotation_y->setValue(static_cast<double>(GetData(row).rotation.y));
			ui.rotation_z->setValue(static_cast<double>(GetData(row).rotation.z));

			ui.scale_x->setValue(static_cast<double>(GetData(row).scale.x));
			ui.scale_y->setValue(static_cast<double>(GetData(row).scale.y));
			ui.scale_z->setValue(static_cast<double>(GetData(row).scale.z));
		}

		{ // Offset Box
			ui.offset_position_x->setValue(static_cast<double>(GetData(row).offset_position.x));
			ui.offset_position_y->setValue(static_cast<double>(GetData(row).offset_position.y));
			ui.offset_position_z->setValue(static_cast<double>(GetData(row).offset_position.z));

			ui.offset_rotation_x->setValue(static_cast<double>(GetData(row).offset_rotation.x));
			ui.offset_rotation_y->setValue(static_cast<double>(GetData(row).offset_rotation.y));
			ui.offset_rotation_z->setValue(static_cast<double>(GetData(row).offset_rotation.z));

			ui.offset_scale_x->setValue(static_cast<double>(GetData(row).offset_scale.x));
			ui.offset_scale_y->setValue(static_cast<double>(GetData(row).offset_scale.y));
			ui.offset_scale_z->setValue(static_cast<double>(GetData(row).offset_scale.z));
		}

		{ // Primitive Type
			ui.primitive_type->setCurrentIndex(GetData(row).primitive_type);
			
			ui.plane_div_x->setValue(GetData(row).plane_div_x);
			ui.plane_div_y->setValue(GetData(row).plane_div_y);
			ui.plane_size_x->setValue(GetData(row).plane_size.x);
			ui.plane_size_y->setValue(GetData(row).plane_size.y);

			ui.box_size_x->setValue(GetData(row).box_size.x);
			ui.box_size_y->setValue(GetData(row).box_size.y);
			ui.box_size_z->setValue(GetData(row).box_size.z);

			ui.sphere_diameter->setValue(GetData(row).sphere_diameter);
			ui.sphere_tessellation->setValue(GetData(row).sphere_tessellation);

			ui.geosphere_diameter->setValue(GetData(row).geosphere_diameter);
			ui.geosphere_tessellation->setValue(GetData(row).geosphere_tessellation);

			ui.capsule_diameter->setValue(GetData(row).capsule_diameter);
			ui.capsule_tessellation->setValue(GetData(row).capsule_tessellation);

			ui.caps_size_x->setValue(GetData(row).capsule_p2.x);
			ui.caps_size_y->setValue(GetData(row).capsule_p2.y);
			ui.caps_size_z->setValue(GetData(row).capsule_p2.z);
		}

		break_flag_1 = true;
	}
}

void QtGui::on_position_x_valueChanged(double value)
{
	GetData(ui.parts_list->currentRow()).position.x = static_cast<float>(value);
}

void QtGui::on_position_y_valueChanged(double value)
{
	GetData(ui.parts_list->currentRow()).position.y = static_cast<float>(value);
}

void QtGui::on_position_z_valueChanged(double value)
{
	GetData(ui.parts_list->currentRow()).position.z = static_cast<float>(value);
}

void QtGui::on_rotation_x_valueChanged(double value)
{
	GetData(ui.parts_list->currentRow()).rotation.x = static_cast<float>(value);
}

void QtGui::on_rotation_y_valueChanged(double value)
{
	GetData(ui.parts_list->currentRow()).rotation.y = static_cast<float>(value);
}

void QtGui::on_rotation_z_valueChanged(double value)
{
	GetData(ui.parts_list->currentRow()).rotation.z = static_cast<float>(value);
}

void QtGui::on_scale_x_valueChanged(double value)
{
	GetData(ui.parts_list->currentRow()).scale.x = static_cast<float>(value);
}

void QtGui::on_scale_y_valueChanged(double value)
{
	GetData(ui.parts_list->currentRow()).scale.y = static_cast<float>(value);
}

void QtGui::on_scale_z_valueChanged(double value)
{
	GetData(ui.parts_list->currentRow()).scale.z = static_cast<float>(value);
}

void QtGui::on_offset_position_x_valueChanged(double value)
{
	GetData(ui.parts_list->currentRow()).offset_position.x = static_cast<float>(value);
}

void QtGui::on_offset_position_y_valueChanged(double value)
{
	GetData(ui.parts_list->currentRow()).offset_position.y = static_cast<float>(value);
}

void QtGui::on_offset_position_z_valueChanged(double value)
{
	GetData(ui.parts_list->currentRow()).offset_position.z = static_cast<float>(value);
}

void QtGui::on_offset_rotation_x_valueChanged(double value)
{
	GetData(ui.parts_list->currentRow()).offset_rotation.x = static_cast<float>(value);
}

void QtGui::on_offset_rotation_y_valueChanged(double value)
{
	GetData(ui.parts_list->currentRow()).offset_rotation.y = static_cast<float>(value);
}

void QtGui::on_offset_rotation_z_valueChanged(double value)
{
	GetData(ui.parts_list->currentRow()).offset_rotation.z = static_cast<float>(value);
}

void QtGui::on_offset_scale_x_valueChanged(double value)
{
	GetData(ui.parts_list->currentRow()).offset_scale.x = static_cast<float>(value);
}

void QtGui::on_offset_scale_y_valueChanged(double value)
{
	GetData(ui.parts_list->currentRow()).offset_scale.y = static_cast<float>(value);
}

void QtGui::on_offset_scale_z_valueChanged(double value)
{
	GetData(ui.parts_list->currentRow()).offset_scale.z = static_cast<float>(value);
}

void QtGui::on_primitive_type_currentChanged(int value)
{
	GetData(ui.parts_list->currentRow()).primitive_type = value;

	this->UpdatePrimitive(ui.parts_list->currentRow());
}

void QtGui::on_plane_div_x_valueChanged(int value)
{
	GetData(ui.parts_list->currentRow()).plane_div_x = value;

	this->UpdatePrimitive(ui.parts_list->currentRow());
}

void QtGui::on_plane_div_y_valueChanged(int value)
{
	GetData(ui.parts_list->currentRow()).plane_div_y = value;

	this->UpdatePrimitive(ui.parts_list->currentRow());
}

void QtGui::on_plane_size_x_valueChanged(double value)
{
	GetData(ui.parts_list->currentRow()).plane_size.x = value;

	this->UpdatePrimitive(ui.parts_list->currentRow());
}

void QtGui::on_plane_size_y_valueChanged(double value)
{
	GetData(ui.parts_list->currentRow()).plane_size.y = value;

	this->UpdatePrimitive(ui.parts_list->currentRow());
}

void QtGui::on_box_size_x_valueChanged(double value)
{
	GetData(ui.parts_list->currentRow()).box_size.x = value;

	this->UpdatePrimitive(ui.parts_list->currentRow());
}

void QtGui::on_box_size_y_valueChanged(double value)
{
	GetData(ui.parts_list->currentRow()).box_size.y = value;

	this->UpdatePrimitive(ui.parts_list->currentRow());
}

void QtGui::on_box_size_z_valueChanged(double value)
{
	GetData(ui.parts_list->currentRow()).box_size.z = value;

	this->UpdatePrimitive(ui.parts_list->currentRow());
}

void QtGui::on_sphere_diameter_valueChanged(double value)
{
	GetData(ui.parts_list->currentRow()).sphere_diameter = value;

	this->UpdatePrimitive(ui.parts_list->currentRow());
}

void QtGui::on_sphere_tessellation_valueChanged(int value)
{
	GetData(ui.parts_list->currentRow()).sphere_tessellation = value;

	this->UpdatePrimitive(ui.parts_list->currentRow());
}

void QtGui::on_geosphere_diameter_valueChanged(double value)
{
	GetData(ui.parts_list->currentRow()).geosphere_diameter = value;

	this->UpdatePrimitive(ui.parts_list->currentRow());
}

void QtGui::on_geosphere_tessellation_valueChanged(int value)
{
	GetData(ui.parts_list->currentRow()).geosphere_tessellation = value;

	this->UpdatePrimitive(ui.parts_list->currentRow());
}

void QtGui::on_capsule_diameter_valueChanged(double value)
{
	GetData(ui.parts_list->currentRow()).capsule_diameter = value;

	this->UpdatePrimitive(ui.parts_list->currentRow());
}

void QtGui::on_capsule_tessellation_valueChanged(int value)
{
	GetData(ui.parts_list->currentRow()).capsule_tessellation = value;

	this->UpdatePrimitive(ui.parts_list->currentRow());
}

void QtGui::on_caps_size_x_valueChanged(double value)
{
	GetData(ui.parts_list->currentRow()).capsule_p1.x = -value;
	GetData(ui.parts_list->currentRow()).capsule_p2.x = +value;

	this->UpdatePrimitive(ui.parts_list->currentRow());
}

void QtGui::on_caps_size_y_valueChanged(double value)
{
	GetData(ui.parts_list->currentRow()).capsule_p1.y = -value;
	GetData(ui.parts_list->currentRow()).capsule_p2.y = +value;

	this->UpdatePrimitive(ui.parts_list->currentRow());
}

void QtGui::on_caps_size_z_valueChanged(double value)
{
	GetData(ui.parts_list->currentRow()).capsule_p1.z = -value;
	GetData(ui.parts_list->currentRow()).capsule_p2.z = +value;

	this->UpdatePrimitive(ui.parts_list->currentRow());
}

void QtGui::on_wire_mode_check_toggled(bool toggle)
{
	this->wire_frame_ = toggle;
}

void QtGui::actionImport(void)
{
	QString sel_filter = tr("Hierarchy Model(*.hmodel)");
	QString file_name = QFileDialog::getOpenFileName(
		this,
		tr("ファイルを開く"),
		".",
		tr("Hierarchy Model(*.hmodel)"),
		&sel_filter,
		QFileDialog::DontUseCustomDirectoryIcons
	);
	if (!file_name.isEmpty()) {
		Load(file_name.toStdString());
	}
}

void QtGui::actionExport(void)
{
	QString sel_filter = tr("Hierarchy Model(*.hmodel)");
	QString file_name = QFileDialog::getSaveFileName(
		this,
		tr("名前を付けて保存"),
		".",
		tr("Hierarchy Model(*.hmodel)"),
		&sel_filter,
		QFileDialog::DontUseCustomDirectoryIcons
	);
	if (!file_name.isEmpty())
	{
		Save(file_name.toStdString());
	}
}

void QtGui::UpdatePrimitive(int row)
{
	auto & item = GetData(row);

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
		primitive_id = graphics.CreateSphere(item.sphere_diameter, item.sphere_tessellation);
	}
	else if (primitive_type == 4)
	{
		primitive_id = graphics.CreateGeoSphere(item.geosphere_diameter, item.geosphere_tessellation);
	}
	else if (primitive_type == 5)
	{
		primitive_id = graphics.CreateCapsule(item.capsule_p1, item.capsule_p2, item.capsule_diameter, item.capsule_tessellation);
	}
}

void QtGui::Save(std::string file_name)
{
	std::ofstream os(file_name, std::ios::binary);
	cereal::BinaryOutputArchive on(os);
	on(ItemData::cnt, main_data);

	os.close();
}

void QtGui::Load(std::string file_name)
{
	main_data.clear();
	item_no.clear();
	ui.parts_list->clear();

	std::ifstream is(file_name, std::ios::binary);
	cereal::BinaryInputArchive in(is);
	in(ItemData::cnt, main_data);

	is.close();

	for (auto & data : main_data)
	{
		auto & sdata = data.second;

		ui.parts_list->addItem(sdata.name.c_str());
		item_no.emplace_back(sdata.self);
	}

	for (int n = 0; n < ui.parts_list->count(); ++n)
	{
		UpdatePrimitive(n);
	}
}

void QtGui::on_add_button_pressed(void)
{
	char str[80];
	sprintf(str, "%3d: %s", ItemData::cnt, "Empty Object");
	ui.parts_list->addItem(str);
	item_no.emplace_back(ItemData::cnt);
	main_data[ItemData::cnt].name = str;

	ItemData::cnt++;
}