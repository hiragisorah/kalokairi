#include "hierarchy-animation-editor.h"
#include <QtWidgets/qfiledialog.h>

unsigned int ItemData::cnt = 0;
unsigned int AnimData::cnt = 0;

hierarchyanimationeditor::hierarchyanimationeditor(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	//New、Openの各tiriggeredシグナルを捕捉
	connect(ui.actionImport, SIGNAL(triggered()), this, SLOT(actionImport()));
	connect(ui.actionExport, SIGNAL(triggered()), this, SLOT(actionExport()));

	connect(ui.actionImport2, SIGNAL(triggered()), this, SLOT(actionImport2()));
	connect(ui.actionExport2, SIGNAL(triggered()), this, SLOT(actionExport2()));

	timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(Update()));
	timer->start(1000/60);

	current_data = 0;

	play = false;
	loop = false;

	copy_data = nullptr;
	copy_frame_data = nullptr;
	copy_frame_data2 = nullptr;

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

	this->wire_primitive_ = graphics.CreatePlane(1, 1, { 10.f, 10.f });

	graphics.SetProjection(DirectX::Matrix::CreatePerspectiveFieldOfView(DirectX::XM_PIDIV4,
		static_cast<float>(graphics.width()) / static_cast<float>(graphics.height()), 0.3f, 1000.f));
	graphics.SetViewPort(this->vp_);
}

void hierarchyanimationeditor::paintEvent(QPaintEvent * ev)
{

}

void hierarchyanimationeditor::closeEvent(QCloseEvent * ev)
{
	if (copy_data != nullptr)
		delete copy_data;

	if (copy_frame_data != nullptr)
		delete copy_frame_data;

	if (copy_frame_data2 != nullptr)
		delete copy_frame_data2;
}

ItemData & hierarchyanimationeditor::GetData(int no)
{
	auto & anim = anim_data[ui.animation_list->currentRow()];
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
	graphics.SetEye(wvp.eye);
	graphics.SetView(DirectX::Matrix::CreateLookAt(wvp.eye, DirectX::Vector3::Zero, DirectX::Vector3(0, 1, 0)));

	if (ui.animation_list->currentItem() == nullptr) return;

	int anim_cnt = 0;

	if (play)
	{
		auto & anim = anim_data[ui.animation_list->currentRow()];

		anim_cnt = anim.frames.size();

		current_data += anim.speed[(static_cast<int>(current_data) + 1) % (anim_cnt)];
		if (loop)
		{
			if(current_data > static_cast<float>(anim_cnt))
			{
				current_data -= static_cast<float>(anim_cnt);
			}
		}
		else
		{
			if (current_data > static_cast<float>(anim_cnt - 1))
			{
				current_data = static_cast<float>(anim_cnt - 1);
			}
		}
	}
		
	if (play)
	{
		auto & anim = anim_data[ui.animation_list->currentRow()];
		auto value = static_cast<int>(current_data) % anim_cnt;

		for (auto & frame : anim.frames[value])
		{
			play_data[frame.first] = Linear(frame.second, anim.frames[(value + 1) % anim_cnt][frame.first], current_data - static_cast<int>(current_data));
		}
	}
	graphics.ClearTarget({ this->backbuffer_, this->col_map_, this->pos_map_, this->nor_map_, this->dep_map_ }, { this->dsv_ });
	graphics.SetTarget({ this->col_map_, this->pos_map_, this->nor_map_, this->dep_map_ }, this->dsv_);

	graphics.SetDirectionLight(this->dir_light_);

	graphics.SetShader(this->shader_deffered_);

	graphics.UpdateMainConstantBuffer();

	graphics.EnableWireFrame(this->wire_frame_);
	
	graphics.SetWorld(DirectX::XMMatrixIdentity());

	graphics.UpdateModelConstantBuffer();

	graphics.Draw(this->wire_primitive_);

	if (ui.animation_list->currentItem() != nullptr)
	{
		for (int i = 0; i < ui.parts_list->count(); ++i)
		{
			auto item = GetData(i);

			if (play)
			{
				if (!anim_data[ui.animation_list->currentRow()].unuse_[item_no[i]])
					item = GetPlayData(i);
			}

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
					auto p = anim_data[ui.animation_list->currentRow()].frames[ui.anim_slider->value()][parent];

					if (play)
						p = play_data[parent];

					auto p_world
						= DirectX::XMMatrixScaling(p.scale.x, p.scale.y, p.scale.z)
						* DirectX::XMMatrixRotationRollPitchYaw(p.rotation.x, p.rotation.y, p.rotation.z)
						* DirectX::XMMatrixTranslation(p.position.x, p.position.y, p.position.z);

					world *= p_world;

					parent = p.parent;
				}
				if (i == ui.parts_list->currentRow())
					graphics.SetDiffuse(DirectX::Vector4(1, .8f, .8f, 1));
				else
					graphics.SetDiffuse(DirectX::Vector4(1, 1, 1, 0.5f));

				graphics.SetWorld(offset * world);

				graphics.UpdateModelConstantBuffer();

				graphics.Draw(item.primitive_id);
			}
		}
	}

	graphics.EnableWireFrame(false);

	graphics.SetTarget({ this->backbuffer_ }, this->dsv_);

	graphics.SetShader(this->shader_backbuffer_);

	graphics.DrawScreen({ this->col_map_, this->pos_map_, this->nor_map_, this->dep_map_ });

	graphics.Run();
}

void hierarchyanimationeditor::on_delete_button_pressed(void)
{
	anim_data.erase(ui.animation_list->currentRow());
	delete ui.animation_list->currentItem();
}

void hierarchyanimationeditor::on_copy_pressed(void)
{
	if(copy_data == nullptr)
		delete copy_data;

	auto & anim = anim_data[ui.animation_list->currentRow()];
	auto value = ui.anim_slider->value();

	copy_data = new AnimData(anim);
}

void hierarchyanimationeditor::on_paste_pressed(void)
{
	if (copy_data != nullptr)
	{
		auto & anim = anim_data[ui.animation_list->currentRow()];
		auto value = ui.anim_slider->value();
		anim = *copy_data;
	}
}

void hierarchyanimationeditor::on_copy_frame_pressed(void)
{
	if (copy_frame_data == nullptr)
		delete copy_frame_data;

	if (copy_frame_data2 == nullptr)
		delete copy_frame_data2;

	auto & anim = anim_data[ui.animation_list->currentRow()];
	auto value = ui.anim_slider->value();

	copy_frame_data = new std::unordered_map<int, ItemData>(anim.frames[value]);
	copy_frame_data2 = new float(anim.speed[value]);
}

void hierarchyanimationeditor::on_paste_frame_pressed(void)
{
	if (copy_frame_data)
	{
		auto & anim = anim_data[ui.animation_list->currentRow()];
		auto value = ui.anim_slider->value();

		anim.frames[value] = *copy_frame_data;
		anim.speed[value] = *copy_frame_data2;
	}
}

void hierarchyanimationeditor::on_rename_button_pressed(void)
{
	ui.animation_list->currentItem()->setText(ui.rename_box->text());

	anim_data[ui.animation_list->currentRow()].name = ui.rename_box->text().toStdString();
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
			if (ui.animation_list->currentItem() != nullptr)
			{
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

		{ // Une
			ui.use->setChecked(!anim_data[ui.animation_list->currentRow()].unuse_[item_no[ui.parts_list->currentRow()]]);
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

void hierarchyanimationeditor::on_eye_x_valueChanged(double value)
{
	wvp.eye.x = value;
}

void hierarchyanimationeditor::on_eye_y_valueChanged(double value)
{
	wvp.eye.y = value;
}

void hierarchyanimationeditor::on_eye_z_valueChanged(double value)
{
	wvp.eye.z = value;
}

void hierarchyanimationeditor::on_speed_valueChanged(double value)
{
	if (ui.animation_list->currentItem())
	{
		auto & anim = anim_data[ui.animation_list->currentRow()];
		auto slider_value = ui.anim_slider->value();
		
		anim.speed[slider_value] = value;
	}
}

void hierarchyanimationeditor::on_anim_max_valueChanged(int value)
{
	ui.anim_slider->setMaximum(value - 1);

	auto & anim = anim_data[ui.animation_list->currentRow()];
	
	auto frame_cnt = anim.frames.size();
	if (value < frame_cnt)
	{
		anim.frames.resize(value);
		anim.speed.resize(value);
	}
	if (value > frame_cnt)
	{
		auto dif = value - frame_cnt;
		for (int n = 0; n < dif; ++n)
		{
			auto & frames = anim.frames;
			frames.emplace_back(frames[frames.size() - 1]);
			anim.speed.emplace_back(0.01f);
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
		auto & anim = anim_data[ui.animation_list->currentRow()];
		auto value = ui.anim_slider->value();
		ui.speed->setValue(static_cast<double>(anim.speed[value]));
	}
}

void hierarchyanimationeditor::on_wire_mode_check_toggled(bool toggle)
{
	this->wire_frame_ = toggle;
}

void hierarchyanimationeditor::on_loop_check_toggled(bool toggle)
{
	loop = toggle;
}

void hierarchyanimationeditor::on_use_toggled(bool toggle)
{
	anim_data[ui.animation_list->currentRow()].unuse_[item_no[ui.parts_list->currentRow()]] = !toggle;
}

void hierarchyanimationeditor::actionImport(void)
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

void hierarchyanimationeditor::actionExport(void)
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

void hierarchyanimationeditor::actionImport2(void)
{
	QString sel_filter = tr("Hierarchy Animation(*.hanim)");
	QString file_name = QFileDialog::getOpenFileName(
		this,
		tr("ファイルを開く"),
		".",
		tr("Hierarchy Animation(*.hanim)"),
		&sel_filter,
		QFileDialog::DontUseCustomDirectoryIcons
	);
	if (!file_name.isEmpty()) {
		Load2(file_name.toStdString());
	}
}

void hierarchyanimationeditor::actionExport2(void)
{
	QString sel_filter = tr("Hierarchy Animation(*.hanim)");
	QString file_name = QFileDialog::getSaveFileName(
		this,
		tr("名前を付けて保存"),
		".",
		tr("Hierarchy Animation(*.hanim)"),
		&sel_filter,
		QFileDialog::DontUseCustomDirectoryIcons
	);
	if (!file_name.isEmpty())
	{
		Save2(file_name.toStdString());
	}
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
}

void hierarchyanimationeditor::Save(std::string file_name)
{
	std::ofstream os(file_name, std::ios::binary);
	cereal::BinaryOutputArchive on(os);
	on(ItemData::cnt, main_data);

	os.close();
}

void hierarchyanimationeditor::Load(std::string file_name)
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

	UpdatePrimitive();

	play_data = main_data;

	for (auto & data : anim_data)
	{
		auto & sdata = data.second;

		for (auto & frame : sdata.frames)
			for (auto & mdata : main_data)
				frame[mdata.first].primitive_id = mdata.second.primitive_id;
	}
}

void hierarchyanimationeditor::Save2(std::string file_name)
{
	std::ofstream os(file_name, std::ios::binary);
	cereal::BinaryOutputArchive on(os);
	on(AnimData::cnt, anim_data, main_data);

	os.close();
}

void hierarchyanimationeditor::Load2(std::string file_name)
{
	anim_data.clear();
	main_data.clear();
	play_data.clear();
	item_no.clear();
	ui.parts_list->clear();
	ui.animation_list->clear();

	std::ifstream is(file_name, std::ios::binary);
	cereal::BinaryInputArchive in(is);
	in(AnimData::cnt, anim_data, main_data);

	is.close();

	for (auto & data : main_data)
	{
		auto & sdata = data.second;

		ui.parts_list->addItem(sdata.name.c_str());
		item_no.emplace_back(sdata.self);
	}

	UpdatePrimitive();

	play_data = main_data;

	std::vector<int> del_list;

	for (auto & data : anim_data)
	{
		if (data.second.self < 0)
			del_list.emplace_back(data.first);
	}

	for (auto & del : del_list)
		anim_data.erase(del);

	for (auto & data : anim_data)
	{
		auto & sdata = data.second;

		ui.animation_list->addItem("");

		for (auto & frame : sdata.frames)
			for (auto & mdata : main_data)
				frame[mdata.first].primitive_id = mdata.second.primitive_id;
	}

	for (auto & data : anim_data)
	{
		ui.animation_list->item(data.first)->setText(data.second.name.c_str());
	}
}

void hierarchyanimationeditor::on_add_button_pressed(void)
{
	char str[80];
	sprintf(str, "%3d: %s", AnimData::cnt, "Empty Animation");
	ui.animation_list->addItem(str);
	anim_data[AnimData::cnt].name = str;

	for (auto & frame : anim_data[AnimData::cnt].frames)
		frame = main_data;

	AnimData::cnt++;
}