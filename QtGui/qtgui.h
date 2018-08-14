#pragma once

#include <DirectXMath.h>

#include <QtWidgets/QMainWindow>
#include <unordered_map>

#include "ui_qtgui.h"
#include "..\graphics\graphics.h"

#include <cereal/types/string.hpp>
#include <cereal/archives/binary.hpp>
#include <cereal/types/unordered_map.hpp>
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
		, primitive_id(-1)
		, primitive_type(0)
		, plane_div_x(1)
		, plane_div_y(1)
		, plane_size({ 0.5f, 0.5f })
		, box_size({ .1f,.1f,.1f })
		, sphere_tesselation(16)
		, sphere_diameter(1.f)
	{}

	int self;

	int parent;
	
	DirectX::XMFLOAT3 position;
	DirectX::XMFLOAT3 rotation;
	DirectX::XMFLOAT3 scale;

	int primitive_id;

	unsigned int primitive_type;
	
	unsigned int plane_div_x;
	unsigned int plane_div_y;
	
	DirectX::XMFLOAT2 plane_size;

	DirectX::XMFLOAT3 box_size;

	unsigned int sphere_tesselation;
	float sphere_diameter;

	std::string name;

	template <class Archive>
	void serialize(Archive & ar)
	{
		ar(self, parent, position.x, position.y, position.z, rotation.x, rotation.y, rotation.z, scale.x, scale.y, scale.z,
			-1, primitive_type, plane_div_x, plane_size.x, plane_size.y, box_size.x, box_size.y,
			sphere_tesselation, sphere_diameter, name);
	}
};

class QtGui : public QMainWindow
{
	Q_OBJECT

public:
	QtGui(QWidget *parent = Q_NULLPTR);

public:
	Ui::QtGuiClass ui;
	
private:
	Seed::Graphics graphics;

protected:
	void paintEvent(QPaintEvent * ev);

private:
	struct WVP
	{
		DirectX::XMMATRIX world;
		DirectX::XMMATRIX view;
		DirectX::XMMATRIX projection;
	} wvp;

private:
	std::unordered_map<int, ItemData> main_data;
	std::vector<int> item_no;

private:
	ItemData & GetData(int no);

private slots:
	void on_add_button_pressed(void);

	void on_delete_button_pressed(void);

	void on_clear_button_pressed(void);

	void on_rename_button_pressed(void);

	void on_parent_combo_currentIndexChanged(int row);

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

	void on_primitive_type_currentChanged(int value);

	void on_plane_div_x_valueChanged(int value);
	void on_plane_div_y_valueChanged(int value);
	void on_plane_size_x_valueChanged(double value);
	void on_plane_size_y_valueChanged(double value);

	void on_box_size_x_valueChanged(double value);
	void on_box_size_y_valueChanged(double value);
	void on_box_size_z_valueChanged(double value);

	void on_sphere_diameter_valueChanged(double value);
	void on_sphere_tesselation_valueChanged(int value);

	void on_wire_mode_check_toggled(bool toggle);

	void actionImport(void);
	void actionExport(void);

private:
	unsigned int rtv;
	unsigned int dsv;
	unsigned int vp;
	unsigned int shader;

private:
	void UpdatePrimitive(int row);

	void Save(void);
	void Load(void);
};
