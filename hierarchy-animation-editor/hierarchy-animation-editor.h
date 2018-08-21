#pragma once

#include <DirectXMath.h>

#include <QtWidgets/QMainWindow>
#include <qtimer.h>
#include <unordered_map>

#include "ui_hierarchy-animation-editor.h"
#include "..\graphics\graphics.h"

#include "..\QtGui\item.h"

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

	AnimData * copy_data;
	std::unordered_map<int, ItemData> * copy_frame_data;
	float * copy_frame_data2;

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

	void on_copy_frame_pressed(void);
	void on_paste_frame_pressed(void);

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

	void on_use_toggled(bool toggle);

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
