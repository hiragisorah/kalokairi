#pragma once

#include <DirectXMath.h>

#include <QtWidgets/QMainWindow>
#include <QTimer>
#include <unordered_map>

#include "ui_qtgui.h"
#include "..\graphics\graphics.h"

#include "item.h"

class QtGui : public QMainWindow
{
	Q_OBJECT

public:
	QtGui(QWidget *parent = Q_NULLPTR);

public:
	Ui::QtGuiClass ui;
	
private:
	Seed::Graphics graphics;
	QTimer * timer;

private:
	std::unordered_map<int, ItemData> main_data;
	std::vector<int> item_no;

private:
	ItemData & GetData(int no);

private slots:
	void Update(void);

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

	void on_offset_position_x_valueChanged(double value);
	void on_offset_position_y_valueChanged(double value);
	void on_offset_position_z_valueChanged(double value);

	void on_offset_rotation_x_valueChanged(double value);
	void on_offset_rotation_y_valueChanged(double value);
	void on_offset_rotation_z_valueChanged(double value);

	void on_offset_scale_x_valueChanged(double value);
	void on_offset_scale_y_valueChanged(double value);
	void on_offset_scale_z_valueChanged(double value);

	void on_primitive_type_currentChanged(int value);

	void on_plane_div_x_valueChanged(int value);
	void on_plane_div_y_valueChanged(int value);
	void on_plane_size_x_valueChanged(double value);
	void on_plane_size_y_valueChanged(double value);

	void on_box_size_x_valueChanged(double value);
	void on_box_size_y_valueChanged(double value);
	void on_box_size_z_valueChanged(double value);

	void on_sphere_diameter_valueChanged(double value);
	void on_sphere_tessellation_valueChanged(int value);

	void on_geosphere_diameter_valueChanged(double value);
	void on_geosphere_tessellation_valueChanged(int value);

	void on_capsule_diameter_valueChanged(double value);
	void on_capsule_tessellation_valueChanged(int value);

	void on_caps_size_x_valueChanged(double value);
	void on_caps_size_y_valueChanged(double value);
	void on_caps_size_z_valueChanged(double value);

	void on_wire_mode_check_toggled(bool toggle);

	void actionImport(void);
	void actionExport(void);

private:
	unsigned int shader_post_effects_;
	unsigned int shader_backbuffer_;
	unsigned int shader_deffered_;
	unsigned int shader_shadow_;

	unsigned int backbuffer_;

	unsigned int col_map_;
	unsigned int pos_map_;
	unsigned int nor_map_;
	unsigned int dep_map_;
	unsigned int sha_map_;

	unsigned int dsv_;
	unsigned int vp_;

	bool wire_frame_;

private:
	DirectX::Vector3 dir_light_;

private:
	void UpdatePrimitive(int row);

	void Save(std::string file_name);
	void Load(std::string file_name);
};
