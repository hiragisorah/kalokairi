#pragma once

#include <DirectXMath.h>

#include <QtWidgets/QMainWindow>
#include <qtimer.h>
#include <unordered_map>

#include "ui_hierarchy-animation-editor.h"
#include "..\graphics\graphics.h"

#include <cereal/types/string.hpp>
#include <cereal/archives/binary.hpp>
#include <cereal/types/unordered_map.hpp>
#include <cereal/types/vector.hpp>
#include <fstream>

struct ItemData
{
	static unsigned int cnt;

	ItemData(void)
		: self(cnt)
		, parent(-1)
		, position({ 0,0,0 })
		, rotation({ 0,0,0 })
		, scale({ 1,1,1 })
		, offset_position({ 0,0,0 })
		, offset_rotation({ 0,0,0 })
		, offset_scale({ 1,1,1 })
		, primitive_id(-1)
		, primitive_type(0)
		, plane_div_x(1)
		, plane_div_y(1)
		, plane_size({ 0.5f, 0.5f })
		, box_size({ .1f,.1f,.1f })
		, sphere_tessellation(16)
		, sphere_diameter(1.f)
		, geosphere_tessellation(3)
		, geosphere_diameter(1.f)
		, capsule_tessellation(18)
		, capsule_diameter(1.f)
		, capsule_p1({ 0,-.5f,0 })
		, capsule_p2({ 0,+.5f,0 })
	{}

	int self;

	int parent;

	DirectX::XMFLOAT3 position;
	DirectX::XMFLOAT3 rotation;
	DirectX::XMFLOAT3 scale;

	DirectX::XMFLOAT3 offset_position;
	DirectX::XMFLOAT3 offset_rotation;
	DirectX::XMFLOAT3 offset_scale;

	int primitive_id;

	unsigned int primitive_type;

	unsigned int plane_div_x;
	unsigned int plane_div_y;

	DirectX::XMFLOAT2 plane_size;

	DirectX::XMFLOAT3 box_size;

	unsigned int sphere_tessellation;
	float sphere_diameter;

	unsigned int geosphere_tessellation;
	float geosphere_diameter;

	DirectX::XMFLOAT3 capsule_p1;
	DirectX::XMFLOAT3 capsule_p2;

	unsigned int capsule_tessellation;
	float capsule_diameter;

	std::string name;

	template <class Archive>
	void serialize(Archive & ar)
	{
		ar(self, parent,
			position.x, position.y, position.z, rotation.x, rotation.y, rotation.z, scale.x, scale.y, scale.z,
			offset_position.x, offset_position.y, offset_position.z, offset_rotation.x, offset_rotation.y, offset_rotation.z, offset_scale.x, offset_scale.y, offset_scale.z,
			-1, primitive_type, plane_div_x, plane_div_y, plane_size.x, plane_size.y, box_size.x, box_size.y,
			sphere_tessellation, sphere_diameter, geosphere_tessellation, geosphere_diameter,
			capsule_p1.x, capsule_p1.y, capsule_p1.z, capsule_p2.x, capsule_p2.y, capsule_p2.z,
			capsule_tessellation, capsule_diameter, name);
	}
};

struct AnimData
{
	AnimData(void)
		: self(cnt)
	{
		frames.resize(5);
		speed.resize(5);

		for (auto & sp : speed)
			sp = 0.01f;
	}

	static unsigned int cnt;

	int self;

	std::string name;

	std::vector<std::unordered_map<int, ItemData>> frames;
	std::vector<float> speed;

	template <class Archive>
	void serialize(Archive & ar)
	{
		ar(self, name, frames, speed);
	}
};

class hierarchyanimationeditor : public QMainWindow
{
	Q_OBJECT

public:
	hierarchyanimationeditor(QWidget *parent = Q_NULLPTR);

public:
	Ui::hierarchyanimationeditorClass ui;

private:
	Seed::Graphics graphics;

protected:
	void paintEvent(QPaintEvent * ev);
	void closeEvent(QCloseEvent * ev);

private:
	struct WVP
	{
		DirectX::XMMATRIX world;
		DirectX::XMMATRIX view;
		DirectX::XMMATRIX projection;
		DirectX::XMFLOAT3A eye;
	} wvp;

private:
	std::unordered_map<int, ItemData> main_data;
	std::vector<int> item_no;

	std::unordered_map<int, AnimData> anim_data;
	std::vector<int> anim_no;

	AnimData * copy_data;

	std::unordered_map<int, ItemData> play_data;
	float current_data;
	bool play;
	bool loop;

private:
	ItemData & GetData(int no);
	ItemData & GetPlayData(int no);

private:
	QTimer * timer;

private slots:
	void Update(void);

	void on_add_button_pressed(void);

	void on_delete_button_pressed(void);

	void on_copy_pressed(void);
	void on_paste_pressed(void);

	void on_rename_button_pressed(void);

	void on_play_button_pressed(void);

	void on_pause_button_pressed(void);

	void on_animation_list_currentRowChanged(int row);
	void on_parts_list_currentRowChanged(int row);

	void on_position_x_valueChanged(double value);
	void on_position_y_valueChanged(double value);
	void on_position_z_valueChanged(double value);

	void on_rotation_x_valueChanged(double value);
	void on_rotation_y_valueChanged(double value);
	void on_rotation_z_valueChanged(double value);

	void on_scale_x_valueChanged(double value);
	void on_scale_y_valueChanged(double value);
	void on_scale_z_valueChanged(double value);

	void on_eye_x_valueChanged(double value);
	void on_eye_y_valueChanged(double value);
	void on_eye_z_valueChanged(double value);

	void on_speed_valueChanged(double value);

	void on_anim_max_valueChanged(int value);

	void on_anim_slider_valueChanged(int value);

	void on_wire_mode_check_toggled(bool toggle);

	void on_loop_check_toggled(bool toggle);

	void actionImport(void);
	void actionExport(void);
	void actionImport2(void);
	void actionExport2(void);

private:
	unsigned int shader_backbuffer_;
	unsigned int shader_deffered_;

	unsigned int backbuffer_;

	unsigned int col_map_;
	unsigned int pos_map_;
	unsigned int nor_map_;
	unsigned int dep_map_;

	unsigned int dsv_;
	unsigned int vp_;

	bool wire_frame_;

private:
	DirectX::Vector3 dir_light_;

public:
	unsigned int wire_primitive_;

private:
	void UpdatePrimitive(void);

	void Save(std::string file_name);
	void Load(std::string file_name);
	void Save2(std::string file_name);
	void Load2(std::string file_name);
};
