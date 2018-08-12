#pragma once

#include <DirectXMath.h>

#include <QtWidgets/QMainWindow>
#include <unordered_map>

#include "ui_qtgui.h"
#include "..\graphics\graphics.h"

struct ItemData
{
	ItemData(void)
		: parent(nullptr)
		, position({0,0,0})
		, rotation({0,0,0})
		, scale({1,1,1})
		, primitive_id(-1)
		, primitive_type(0)
		, plane_div_x(1)
		, plane_div_y(1)
		, plane_size({ 0.5f, 0.5f })
		, box_size({.1f,.1f,.1f})
		, sphere_tesselation(16)
		, sphere_diameter(1.f)
	{}

	QListWidgetItem * parent;
	
	DirectX::XMFLOAT3 position;
	DirectX::XMFLOAT3 rotation;
	DirectX::XMFLOAT3 scale;

	signed int primitive_id;

	unsigned int primitive_type;
	
	unsigned int plane_div_x;
	unsigned int plane_div_y;
	
	DirectX::XMFLOAT2 plane_size;

	DirectX::XMFLOAT3 box_size;

	unsigned int sphere_tesselation;
	float sphere_diameter;
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
	std::unordered_map<QListWidgetItem*, ItemData> saved_data;

private slots:
	void on_add_button_pressed(void);

	void on_delete_button_pressed(void);

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

private:
	unsigned int rtv;
	unsigned int dsv;
	unsigned int vp;
	unsigned int shader;

private:
	void UpdatePrimitive(void);
};
