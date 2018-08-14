#include "hierarchy-animation-editor.h"

unsigned int ItemData::cnt = 0;
unsigned int AnimData::cnt = 0;

hierarchyanimationeditor::hierarchyanimationeditor(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	//New、Openの各tiriggeredシグナルを捕捉
	connect(ui.actionImport, SIGNAL(triggered()), this, SLOT(actionImport()));
	connect(ui.actionExport, SIGNAL(triggered()), this, SLOT(actionExport()));

	timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(Update()));
	timer->start(1000/60);

	current_data = 0;
	play = false;

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

void hierarchyanimationeditor::paintEvent(QPaintEvent * ev)
{
	/*graphics.ClearTarget({ rtv }, { dsv });

	if (ui.animation_list->currentItem() != nullptr)
	{
		for (int i = 0; i < ui.parts_list->count(); ++i)
		{
			auto item = GetData(i);

			if (play)
				item = GetPlayData(i);

			if (item.primitive_id != -1)
			{
				auto world
					= DirectX::XMMatrixScaling(item.scale.x, item.scale.y, item.scale.z)
					* DirectX::XMMatrixRotationRollPitchYaw(item.rotation.x, item.rotation.y, item.rotation.z)
					* DirectX::XMMatrixTranslation(item.position.x, item.position.y, item.position.z);

				auto parent = item.parent;

				while (parent != -1)
				{
					auto p = anim_data[anim_no[ui.animation_list->currentRow()]].frames[ui.anim_slider->value()][parent];

					if (play)
						p = play_data[parent];

					auto p_world
						= DirectX::XMMatrixScaling(p.scale.x, p.scale.y, p.scale.z)
						* DirectX::XMMatrixRotationRollPitchYaw(p.rotation.x, p.rotation.y, p.rotation.z)
						* DirectX::XMMatrixTranslation(p.position.x, p.position.y, p.position.z);

					world *= p_world;

					parent = p.parent;
				}

				wvp.world = world;

				graphics.SetShader(shader, &wvp);

				graphics.Draw(item.primitive_id);
			}
		}
	}

	graphics.Run();*/
}

ItemData & hierarchyanimationeditor::GetData(int no)
{
	auto row = anim_no[ui.animation_list->currentRow()];
	auto & anim = anim_data[row];
	auto value = ui.anim_slider->value();
	return anim.frames[value][item_no[no]];
}

ItemData & hierarchyanimationeditor::GetPlayData(int no)
{
	return play_data[item_no[no]];
}

ItemData Linear(ItemData & a, ItemData & b, float progress)
{
	ItemData ret = a;

	ret.position.x = a.position.x + (b.position.x - a.position.x) * progress;
	ret.position.y = a.position.y + (b.position.y - a.position.y) * progress;
	ret.position.z = a.position.z + (b.position.z - a.position.z) * progress;

	ret.rotation.x = a.rotation.x + (b.rotation.x - a.rotation.x) * progress;
	ret.rotation.y = a.rotation.y + (b.rotation.y - a.rotation.y) * progress;
	ret.rotation.z = a.rotation.z + (b.rotation.z - a.rotation.z) * progress;

	ret.scale.x = a.scale.x + (b.scale.x - a.scale.x) * progress;
	ret.scale.y = a.scale.y + (b.scale.y - a.scale.y) * progress;
	ret.scale.z = a.scale.z + (b.scale.z - a.scale.z) * progress;

	return ret;
}

void hierarchyanimationeditor::Update(void)
{
	if (ui.animation_list->currentItem() == nullptr) return;

	int anim_cnt = 0;

	if (play)
	{
		auto row = anim_no[ui.animation_list->currentRow()];
		auto & anim = anim_data[row];

		anim_cnt = anim.frames.size() - 1;

		current_data += anim.speed[static_cast<int>(current_data)];
		if (current_data > static_cast<float>(anim_cnt))
		{
			current_data = static_cast<float>(anim_cnt);
		}
	}
		
	auto row = anim_no[ui.animation_list->currentRow()];
	auto & anim = anim_data[row];
	auto value = static_cast<int>(current_data);

	for (auto & frame : anim.frames[value])
	{
		play_data[frame.first] = Linear(frame.second, anim.frames[std::min(value + 1, anim_cnt)][frame.first], current_data - value);
	}

	graphics.ClearTarget({ rtv }, { dsv });

	if (ui.animation_list->currentItem() != nullptr)
	{
		for (int i = 0; i < ui.parts_list->count(); ++i)
		{
			auto item = GetData(i);

			if (play)
				item = GetPlayData(i);

			if (item.primitive_id != -1)
			{
				auto world
					= DirectX::XMMatrixScaling(item.scale.x, item.scale.y, item.scale.z)
					* DirectX::XMMatrixRotationRollPitchYaw(item.rotation.x, item.rotation.y, item.rotation.z)
					* DirectX::XMMatrixTranslation(item.position.x, item.position.y, item.position.z);

				auto parent = item.parent;

				while (parent != -1)
				{
					auto p = anim_data[anim_no[ui.animation_list->currentRow()]].frames[ui.anim_slider->value()][parent];

					if (play)
						p = play_data[parent];

					auto p_world
						= DirectX::XMMatrixScaling(p.scale.x, p.scale.y, p.scale.z)
						* DirectX::XMMatrixRotationRollPitchYaw(p.rotation.x, p.rotation.y, p.rotation.z)
						* DirectX::XMMatrixTranslation(p.position.x, p.position.y, p.position.z);

					world *= p_world;

					parent = p.parent;
				}

				wvp.world = world;

				graphics.SetShader(shader, &wvp);

				graphics.Draw(item.primitive_id);
			}
		}
	}

	graphics.Run();
}

void hierarchyanimationeditor::on_delete_button_pressed(void)
{
	auto row = ui.animation_list->currentRow();
	auto no = anim_no[row];
	anim_data.erase(no);
	delete ui.animation_list->currentItem();
	anim_no.erase(anim_no.begin() + row);
}

void hierarchyanimationeditor::on_rename_button_pressed(void)
{
	ui.animation_list->currentItem()->setText(ui.rename_box->text());

	auto row = ui.animation_list->currentRow();
	auto no = anim_no[row];

	anim_data[no].name = ui.rename_box->text().toStdString();
}

void hierarchyanimationeditor::on_play_button_pressed(void)
{
	this->play = true;
	this->current_data = 0;

	ui.play_button->setDisabled(true);
	ui.pause_button->setEnabled(true);
}

void hierarchyanimationeditor::on_pause_button_pressed(void)
{
	this->play = false;
	this->current_data = 0;

	ui.pause_button->setDisabled(true);
	ui.play_button->setEnabled(true);
}

void hierarchyanimationeditor::on_animation_list_currentRowChanged(int row)
{
	auto this_item = ui.animation_list->currentItem();

	if (this_item == nullptr)
	{
		ui.rename_box->setText("");

		ui.rename_group->setDisabled(true);
		ui.parts_list->setDisabled(true);
		ui.delete_button->setDisabled(true);
		ui.anim_max->setDisabled(true);
		ui.anim_slider->setDisabled(true);
		ui.speed->setDisabled(true);
		ui.play_button->setDisabled(true);
	}
	else
	{
		ui.rename_box->setText(this_item->text());

		ui.rename_group->setEnabled(true);
		ui.parts_list->setEnabled(true);
		ui.delete_button->setEnabled(true);
		ui.anim_max->setEnabled(true);
		ui.anim_slider->setEnabled(true);
		ui.speed->setEnabled(true);
		ui.play_button->setEnabled(true);

		ui.anim_max->setValue(anim_data[row].frames.size());
		ui.speed->setValue(anim_data[row].speed[ui.anim_slider->value()]);
	}
}

void hierarchyanimationeditor::on_parts_list_currentRowChanged(int row)
{
	auto this_item = ui.parts_list->currentItem();

	if (this_item == nullptr)
	{
		ui.transform_group->setDisabled(true);
	}
	else
	{
		ui.transform_group->setEnabled(true);

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
	}
}

void hierarchyanimationeditor::on_position_x_valueChanged(double value)
{
	if(ui.animation_list->currentItem())
		GetData(ui.parts_list->currentRow()).position.x = static_cast<float>(value);
}

void hierarchyanimationeditor::on_position_y_valueChanged(double value)
{
	if (ui.animation_list->currentItem())
		GetData(ui.parts_list->currentRow()).position.y = static_cast<float>(value);
}

void hierarchyanimationeditor::on_position_z_valueChanged(double value)
{
	if (ui.animation_list->currentItem())
		GetData(ui.parts_list->currentRow()).position.z = static_cast<float>(value);
}

void hierarchyanimationeditor::on_rotation_x_valueChanged(double value)
{
	if (ui.animation_list->currentItem())
		GetData(ui.parts_list->currentRow()).rotation.x = static_cast<float>(value);
}

void hierarchyanimationeditor::on_rotation_y_valueChanged(double value)
{
	if (ui.animation_list->currentItem())
		GetData(ui.parts_list->currentRow()).rotation.y = static_cast<float>(value);
}

void hierarchyanimationeditor::on_rotation_z_valueChanged(double value)
{
	if (ui.animation_list->currentItem())
		GetData(ui.parts_list->currentRow()).rotation.z = static_cast<float>(value);
}

void hierarchyanimationeditor::on_scale_x_valueChanged(double value)
{
	if (ui.animation_list->currentItem())
		GetData(ui.parts_list->currentRow()).scale.x = static_cast<float>(value);
}

void hierarchyanimationeditor::on_scale_y_valueChanged(double value)
{
	if (ui.animation_list->currentItem())
		GetData(ui.parts_list->currentRow()).scale.y = static_cast<float>(value);
}

void hierarchyanimationeditor::on_scale_z_valueChanged(double value)
{
	if (ui.animation_list->currentItem())
		GetData(ui.parts_list->currentRow()).scale.z = static_cast<float>(value);
}

void hierarchyanimationeditor::on_anim_max_valueChanged(int value)
{
	ui.anim_slider->setMaximum(value - 1);
	auto frame_cnt = anim_data[ui.animation_list->currentRow()].frames.size();
	if (value < frame_cnt)
	{
		anim_data[ui.animation_list->currentRow()].frames.resize(value);
		anim_data[ui.animation_list->currentRow()].speed.resize(value);
	}
	if (value > frame_cnt)
	{
		auto dif = value - frame_cnt;
		for (int n = 0; n < dif; ++n)
		{
			auto & frames = anim_data[ui.animation_list->currentRow()].frames;
			frames.emplace_back(frames[frames.size() - 1]);
			anim_data[ui.animation_list->currentRow()].speed.emplace_back(0.01f);
		}
	}
}

void hierarchyanimationeditor::on_anim_slider_valueChanged(int value)
{
	{ // Transform Box
		ui.position_x->setValue(static_cast<double>(GetData(ui.parts_list->currentRow()).position.x));
		ui.position_y->setValue(static_cast<double>(GetData(ui.parts_list->currentRow()).position.y));
		ui.position_z->setValue(static_cast<double>(GetData(ui.parts_list->currentRow()).position.z));

		ui.rotation_x->setValue(static_cast<double>(GetData(ui.parts_list->currentRow()).rotation.x));
		ui.rotation_y->setValue(static_cast<double>(GetData(ui.parts_list->currentRow()).rotation.y));
		ui.rotation_z->setValue(static_cast<double>(GetData(ui.parts_list->currentRow()).rotation.z));

		ui.scale_x->setValue(static_cast<double>(GetData(ui.parts_list->currentRow()).scale.x));
		ui.scale_y->setValue(static_cast<double>(GetData(ui.parts_list->currentRow()).scale.y));
		ui.scale_z->setValue(static_cast<double>(GetData(ui.parts_list->currentRow()).scale.z));
	}
}

void hierarchyanimationeditor::on_wire_mode_check_toggled(bool toggle)
{
	graphics.EnableWireFrame(toggle);
}

void hierarchyanimationeditor::actionImport(void)
{
	Save();
}

void hierarchyanimationeditor::actionExport(void)
{
	Load();
}

void hierarchyanimationeditor::UpdatePrimitive(void)
{
	for (auto & data : main_data)
	{
		auto & item = data.second;
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
}

void hierarchyanimationeditor::Save(void)
{
	std::ofstream os("../save.bin", std::ios::binary);
	cereal::BinaryOutputArchive on(os);
	on(ItemData::cnt, main_data);

	os.close();
}

void hierarchyanimationeditor::Load(void)
{
	main_data.clear();
	item_no.clear();
	ui.parts_list->clear();

	std::ifstream is("../save.bin", std::ios::binary);
	cereal::BinaryInputArchive in(is);
	in(ItemData::cnt, main_data);

	is.close();

	for (auto & data : main_data)
	{
		auto & sdata = data.second;

		ui.parts_list->addItem(sdata.name.c_str());
		item_no.emplace_back(sdata.self);
	}

	UpdatePrimitive();

	play_data = main_data;
}

void hierarchyanimationeditor::on_add_button_pressed(void)
{
	char str[80];
	sprintf(str, "%3d: %s", AnimData::cnt, "Empty Animation");
	ui.animation_list->addItem(str);
	anim_no.emplace_back(AnimData::cnt);
	anim_data[AnimData::cnt].name = str;

	for (auto & frame : anim_data[AnimData::cnt].frames)
		frame = main_data;

	AnimData::cnt++;
}