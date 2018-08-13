/********************************************************************************
** Form generated from reading UI file 'qtgui.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTGUI_H
#define UI_QTGUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QtGuiClass
{
public:
    QAction *actionImport;
    QAction *actionExport;
    QWidget *centralWidget;
    QCheckBox *wire_mode_check;
    QGroupBox *groupBox;
    QWidget *widget;
    QGroupBox *groupBox_2;
    QListWidget *parts_list;
    QPushButton *add_button;
    QPushButton *delete_button;
    QGroupBox *transform_group;
    QGroupBox *groupBox_4;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_3;
    QDoubleSpinBox *position_x;
    QLabel *label_2;
    QDoubleSpinBox *position_y;
    QLabel *label;
    QDoubleSpinBox *position_z;
    QGroupBox *groupBox_5;
    QWidget *horizontalLayoutWidget_2;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_4;
    QDoubleSpinBox *rotation_x;
    QLabel *label_5;
    QDoubleSpinBox *rotation_y;
    QLabel *label_6;
    QDoubleSpinBox *rotation_z;
    QGroupBox *groupBox_6;
    QWidget *horizontalLayoutWidget_4;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_10;
    QDoubleSpinBox *scale_x;
    QLabel *label_11;
    QDoubleSpinBox *scale_y;
    QLabel *label_12;
    QDoubleSpinBox *scale_z;
    QGroupBox *groupBox_8;
    QComboBox *parent_combo;
    QGroupBox *rename_group;
    QLineEdit *rename_box;
    QPushButton *rename_button;
    QGroupBox *primitive_group;
    QTabWidget *primitive_type;
    QWidget *tab_5;
    QWidget *tab;
    QGroupBox *groupBox_7;
    QWidget *horizontalLayoutWidget_5;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_13;
    QDoubleSpinBox *plane_size_x;
    QLabel *label_14;
    QDoubleSpinBox *plane_size_y;
    QGroupBox *groupBox_9;
    QWidget *horizontalLayoutWidget_6;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_15;
    QSpinBox *plane_div_x;
    QLabel *label_16;
    QSpinBox *plane_div_y;
    QWidget *tab_2;
    QGroupBox *groupBox_10;
    QWidget *horizontalLayoutWidget_7;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_17;
    QDoubleSpinBox *box_size_x;
    QLabel *label_18;
    QDoubleSpinBox *box_size_y;
    QLabel *label_19;
    QDoubleSpinBox *box_size_z;
    QWidget *tab_3;
    QGroupBox *groupBox_11;
    QWidget *horizontalLayoutWidget_8;
    QHBoxLayout *horizontalLayout_9;
    QDoubleSpinBox *sphere_diameter;
    QGroupBox *egsdge;
    QWidget *horizontalLayoutWidget_10;
    QHBoxLayout *horizontalLayout_11;
    QSpinBox *sphere_tesselation;
    QWidget *tab_4;
    QGroupBox *groupBox_12;
    QComboBox *material_combo;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *QtGuiClass)
    {
        if (QtGuiClass->objectName().isEmpty())
            QtGuiClass->setObjectName(QStringLiteral("QtGuiClass"));
        QtGuiClass->resize(1361, 731);
        QFont font;
        font.setFamily(QString::fromUtf8("\343\203\241\343\202\244\343\203\252\343\202\252"));
        QtGuiClass->setFont(font);
        actionImport = new QAction(QtGuiClass);
        actionImport->setObjectName(QStringLiteral("actionImport"));
        actionExport = new QAction(QtGuiClass);
        actionExport->setObjectName(QStringLiteral("actionExport"));
        centralWidget = new QWidget(QtGuiClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        wire_mode_check = new QCheckBox(centralWidget);
        wire_mode_check->setObjectName(QStringLiteral("wire_mode_check"));
        wire_mode_check->setGeometry(QRect(30, 619, 141, 31));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\343\203\241\343\202\244\343\203\252\343\202\252"));
        font1.setPointSize(12);
        font1.setBold(false);
        font1.setWeight(50);
        wire_mode_check->setFont(font1);
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(210, 10, 821, 641));
        groupBox->setFont(font);
        widget = new QWidget(groupBox);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(10, 30, 800, 600));
        groupBox_2 = new QGroupBox(centralWidget);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(10, 10, 191, 601));
        groupBox_2->setFont(font);
        parts_list = new QListWidget(groupBox_2);
        parts_list->setObjectName(QStringLiteral("parts_list"));
        parts_list->setGeometry(QRect(10, 30, 171, 481));
        add_button = new QPushButton(groupBox_2);
        add_button->setObjectName(QStringLiteral("add_button"));
        add_button->setGeometry(QRect(10, 520, 171, 31));
        add_button->setFont(font);
        delete_button = new QPushButton(groupBox_2);
        delete_button->setObjectName(QStringLiteral("delete_button"));
        delete_button->setEnabled(false);
        delete_button->setGeometry(QRect(10, 560, 171, 31));
        delete_button->setFont(font);
        transform_group = new QGroupBox(centralWidget);
        transform_group->setObjectName(QStringLiteral("transform_group"));
        transform_group->setEnabled(false);
        transform_group->setGeometry(QRect(1040, 70, 311, 271));
        transform_group->setFont(font);
        groupBox_4 = new QGroupBox(transform_group);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        groupBox_4->setGeometry(QRect(10, 80, 291, 61));
        horizontalLayoutWidget = new QWidget(groupBox_4);
        horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(10, 20, 271, 31));
        horizontalLayout_2 = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        label_3 = new QLabel(horizontalLayoutWidget);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout_2->addWidget(label_3);

        position_x = new QDoubleSpinBox(horizontalLayoutWidget);
        position_x->setObjectName(QStringLiteral("position_x"));
        position_x->setWrapping(false);
        position_x->setProperty("showGroupSeparator", QVariant(false));
        position_x->setDecimals(2);
        position_x->setMaximum(10);
        position_x->setSingleStep(0.01);

        horizontalLayout_2->addWidget(position_x);

        label_2 = new QLabel(horizontalLayoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_2->addWidget(label_2);

        position_y = new QDoubleSpinBox(horizontalLayoutWidget);
        position_y->setObjectName(QStringLiteral("position_y"));
        position_y->setWrapping(false);
        position_y->setProperty("showGroupSeparator", QVariant(false));
        position_y->setDecimals(2);
        position_y->setMaximum(10);
        position_y->setSingleStep(0.01);

        horizontalLayout_2->addWidget(position_y);

        label = new QLabel(horizontalLayoutWidget);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout_2->addWidget(label);

        position_z = new QDoubleSpinBox(horizontalLayoutWidget);
        position_z->setObjectName(QStringLiteral("position_z"));
        position_z->setWrapping(false);
        position_z->setProperty("showGroupSeparator", QVariant(false));
        position_z->setDecimals(2);
        position_z->setMaximum(10);
        position_z->setSingleStep(0.01);

        horizontalLayout_2->addWidget(position_z);

        groupBox_5 = new QGroupBox(transform_group);
        groupBox_5->setObjectName(QStringLiteral("groupBox_5"));
        groupBox_5->setGeometry(QRect(10, 140, 291, 61));
        horizontalLayoutWidget_2 = new QWidget(groupBox_5);
        horizontalLayoutWidget_2->setObjectName(QStringLiteral("horizontalLayoutWidget_2"));
        horizontalLayoutWidget_2->setGeometry(QRect(10, 20, 270, 31));
        horizontalLayout_3 = new QHBoxLayout(horizontalLayoutWidget_2);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        label_4 = new QLabel(horizontalLayoutWidget_2);
        label_4->setObjectName(QStringLiteral("label_4"));

        horizontalLayout_3->addWidget(label_4);

        rotation_x = new QDoubleSpinBox(horizontalLayoutWidget_2);
        rotation_x->setObjectName(QStringLiteral("rotation_x"));
        rotation_x->setWrapping(false);
        rotation_x->setProperty("showGroupSeparator", QVariant(false));
        rotation_x->setDecimals(2);
        rotation_x->setMaximum(10);
        rotation_x->setSingleStep(0.01);

        horizontalLayout_3->addWidget(rotation_x);

        label_5 = new QLabel(horizontalLayoutWidget_2);
        label_5->setObjectName(QStringLiteral("label_5"));

        horizontalLayout_3->addWidget(label_5);

        rotation_y = new QDoubleSpinBox(horizontalLayoutWidget_2);
        rotation_y->setObjectName(QStringLiteral("rotation_y"));
        rotation_y->setWrapping(false);
        rotation_y->setProperty("showGroupSeparator", QVariant(false));
        rotation_y->setDecimals(2);
        rotation_y->setMaximum(10);
        rotation_y->setSingleStep(0.01);

        horizontalLayout_3->addWidget(rotation_y);

        label_6 = new QLabel(horizontalLayoutWidget_2);
        label_6->setObjectName(QStringLiteral("label_6"));

        horizontalLayout_3->addWidget(label_6);

        rotation_z = new QDoubleSpinBox(horizontalLayoutWidget_2);
        rotation_z->setObjectName(QStringLiteral("rotation_z"));
        rotation_z->setWrapping(false);
        rotation_z->setProperty("showGroupSeparator", QVariant(false));
        rotation_z->setDecimals(2);
        rotation_z->setMaximum(10);
        rotation_z->setSingleStep(0.01);

        horizontalLayout_3->addWidget(rotation_z);

        groupBox_6 = new QGroupBox(transform_group);
        groupBox_6->setObjectName(QStringLiteral("groupBox_6"));
        groupBox_6->setGeometry(QRect(10, 200, 291, 61));
        horizontalLayoutWidget_4 = new QWidget(groupBox_6);
        horizontalLayoutWidget_4->setObjectName(QStringLiteral("horizontalLayoutWidget_4"));
        horizontalLayoutWidget_4->setGeometry(QRect(10, 20, 270, 31));
        horizontalLayout_5 = new QHBoxLayout(horizontalLayoutWidget_4);
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(0, 0, 0, 0);
        label_10 = new QLabel(horizontalLayoutWidget_4);
        label_10->setObjectName(QStringLiteral("label_10"));

        horizontalLayout_5->addWidget(label_10);

        scale_x = new QDoubleSpinBox(horizontalLayoutWidget_4);
        scale_x->setObjectName(QStringLiteral("scale_x"));
        scale_x->setWrapping(false);
        scale_x->setProperty("showGroupSeparator", QVariant(false));
        scale_x->setDecimals(2);
        scale_x->setMaximum(10);
        scale_x->setSingleStep(0.01);

        horizontalLayout_5->addWidget(scale_x);

        label_11 = new QLabel(horizontalLayoutWidget_4);
        label_11->setObjectName(QStringLiteral("label_11"));

        horizontalLayout_5->addWidget(label_11);

        scale_y = new QDoubleSpinBox(horizontalLayoutWidget_4);
        scale_y->setObjectName(QStringLiteral("scale_y"));
        scale_y->setWrapping(false);
        scale_y->setProperty("showGroupSeparator", QVariant(false));
        scale_y->setDecimals(2);
        scale_y->setMaximum(10);
        scale_y->setSingleStep(0.01);

        horizontalLayout_5->addWidget(scale_y);

        label_12 = new QLabel(horizontalLayoutWidget_4);
        label_12->setObjectName(QStringLiteral("label_12"));

        horizontalLayout_5->addWidget(label_12);

        scale_z = new QDoubleSpinBox(horizontalLayoutWidget_4);
        scale_z->setObjectName(QStringLiteral("scale_z"));
        scale_z->setWrapping(false);
        scale_z->setProperty("showGroupSeparator", QVariant(false));
        scale_z->setDecimals(2);
        scale_z->setMaximum(10);
        scale_z->setSingleStep(0.01);

        horizontalLayout_5->addWidget(scale_z);

        groupBox_8 = new QGroupBox(transform_group);
        groupBox_8->setObjectName(QStringLiteral("groupBox_8"));
        groupBox_8->setGeometry(QRect(10, 20, 291, 61));
        parent_combo = new QComboBox(groupBox_8);
        parent_combo->setObjectName(QStringLiteral("parent_combo"));
        parent_combo->setGeometry(QRect(10, 20, 271, 31));
        rename_group = new QGroupBox(centralWidget);
        rename_group->setObjectName(QStringLiteral("rename_group"));
        rename_group->setEnabled(false);
        rename_group->setGeometry(QRect(1040, 10, 311, 61));
        rename_group->setFont(font);
        rename_box = new QLineEdit(rename_group);
        rename_box->setObjectName(QStringLiteral("rename_box"));
        rename_box->setGeometry(QRect(10, 20, 211, 31));
        rename_button = new QPushButton(rename_group);
        rename_button->setObjectName(QStringLiteral("rename_button"));
        rename_button->setGeometry(QRect(230, 19, 71, 31));
        primitive_group = new QGroupBox(centralWidget);
        primitive_group->setObjectName(QStringLiteral("primitive_group"));
        primitive_group->setEnabled(false);
        primitive_group->setGeometry(QRect(1040, 340, 311, 231));
        primitive_group->setFont(font);
        primitive_type = new QTabWidget(primitive_group);
        primitive_type->setObjectName(QStringLiteral("primitive_type"));
        primitive_type->setGeometry(QRect(10, 30, 291, 191));
        tab_5 = new QWidget();
        tab_5->setObjectName(QStringLiteral("tab_5"));
        primitive_type->addTab(tab_5, QString());
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        groupBox_7 = new QGroupBox(tab);
        groupBox_7->setObjectName(QStringLiteral("groupBox_7"));
        groupBox_7->setGeometry(QRect(10, 10, 271, 61));
        horizontalLayoutWidget_5 = new QWidget(groupBox_7);
        horizontalLayoutWidget_5->setObjectName(QStringLiteral("horizontalLayoutWidget_5"));
        horizontalLayoutWidget_5->setGeometry(QRect(10, 20, 251, 31));
        horizontalLayout_6 = new QHBoxLayout(horizontalLayoutWidget_5);
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        horizontalLayout_6->setContentsMargins(0, 0, 0, 0);
        label_13 = new QLabel(horizontalLayoutWidget_5);
        label_13->setObjectName(QStringLiteral("label_13"));

        horizontalLayout_6->addWidget(label_13);

        plane_size_x = new QDoubleSpinBox(horizontalLayoutWidget_5);
        plane_size_x->setObjectName(QStringLiteral("plane_size_x"));
        plane_size_x->setWrapping(false);
        plane_size_x->setProperty("showGroupSeparator", QVariant(false));
        plane_size_x->setDecimals(2);
        plane_size_x->setMaximum(10);
        plane_size_x->setSingleStep(0.01);

        horizontalLayout_6->addWidget(plane_size_x);

        label_14 = new QLabel(horizontalLayoutWidget_5);
        label_14->setObjectName(QStringLiteral("label_14"));

        horizontalLayout_6->addWidget(label_14);

        plane_size_y = new QDoubleSpinBox(horizontalLayoutWidget_5);
        plane_size_y->setObjectName(QStringLiteral("plane_size_y"));
        plane_size_y->setWrapping(false);
        plane_size_y->setProperty("showGroupSeparator", QVariant(false));
        plane_size_y->setDecimals(2);
        plane_size_y->setMaximum(10);
        plane_size_y->setSingleStep(0.01);

        horizontalLayout_6->addWidget(plane_size_y);

        groupBox_9 = new QGroupBox(tab);
        groupBox_9->setObjectName(QStringLiteral("groupBox_9"));
        groupBox_9->setGeometry(QRect(10, 80, 271, 61));
        horizontalLayoutWidget_6 = new QWidget(groupBox_9);
        horizontalLayoutWidget_6->setObjectName(QStringLiteral("horizontalLayoutWidget_6"));
        horizontalLayoutWidget_6->setGeometry(QRect(10, 20, 251, 31));
        horizontalLayout_7 = new QHBoxLayout(horizontalLayoutWidget_6);
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        horizontalLayout_7->setContentsMargins(0, 0, 0, 0);
        label_15 = new QLabel(horizontalLayoutWidget_6);
        label_15->setObjectName(QStringLiteral("label_15"));

        horizontalLayout_7->addWidget(label_15);

        plane_div_x = new QSpinBox(horizontalLayoutWidget_6);
        plane_div_x->setObjectName(QStringLiteral("plane_div_x"));
        plane_div_x->setWrapping(false);
        plane_div_x->setProperty("showGroupSeparator", QVariant(false));
        plane_div_x->setMinimum(1);

        horizontalLayout_7->addWidget(plane_div_x);

        label_16 = new QLabel(horizontalLayoutWidget_6);
        label_16->setObjectName(QStringLiteral("label_16"));

        horizontalLayout_7->addWidget(label_16);

        plane_div_y = new QSpinBox(horizontalLayoutWidget_6);
        plane_div_y->setObjectName(QStringLiteral("plane_div_y"));
        plane_div_y->setWrapping(false);
        plane_div_y->setProperty("showGroupSeparator", QVariant(false));
        plane_div_y->setMinimum(1);

        horizontalLayout_7->addWidget(plane_div_y);

        primitive_type->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        groupBox_10 = new QGroupBox(tab_2);
        groupBox_10->setObjectName(QStringLiteral("groupBox_10"));
        groupBox_10->setGeometry(QRect(10, 10, 271, 61));
        horizontalLayoutWidget_7 = new QWidget(groupBox_10);
        horizontalLayoutWidget_7->setObjectName(QStringLiteral("horizontalLayoutWidget_7"));
        horizontalLayoutWidget_7->setGeometry(QRect(10, 20, 251, 31));
        horizontalLayout_8 = new QHBoxLayout(horizontalLayoutWidget_7);
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        horizontalLayout_8->setContentsMargins(0, 0, 0, 0);
        label_17 = new QLabel(horizontalLayoutWidget_7);
        label_17->setObjectName(QStringLiteral("label_17"));

        horizontalLayout_8->addWidget(label_17);

        box_size_x = new QDoubleSpinBox(horizontalLayoutWidget_7);
        box_size_x->setObjectName(QStringLiteral("box_size_x"));
        box_size_x->setWrapping(false);
        box_size_x->setProperty("showGroupSeparator", QVariant(false));
        box_size_x->setDecimals(2);
        box_size_x->setMaximum(10);
        box_size_x->setSingleStep(0.01);

        horizontalLayout_8->addWidget(box_size_x);

        label_18 = new QLabel(horizontalLayoutWidget_7);
        label_18->setObjectName(QStringLiteral("label_18"));

        horizontalLayout_8->addWidget(label_18);

        box_size_y = new QDoubleSpinBox(horizontalLayoutWidget_7);
        box_size_y->setObjectName(QStringLiteral("box_size_y"));
        box_size_y->setWrapping(false);
        box_size_y->setProperty("showGroupSeparator", QVariant(false));
        box_size_y->setDecimals(2);
        box_size_y->setMaximum(10);
        box_size_y->setSingleStep(0.01);

        horizontalLayout_8->addWidget(box_size_y);

        label_19 = new QLabel(horizontalLayoutWidget_7);
        label_19->setObjectName(QStringLiteral("label_19"));

        horizontalLayout_8->addWidget(label_19);

        box_size_z = new QDoubleSpinBox(horizontalLayoutWidget_7);
        box_size_z->setObjectName(QStringLiteral("box_size_z"));
        box_size_z->setWrapping(false);
        box_size_z->setProperty("showGroupSeparator", QVariant(false));
        box_size_z->setDecimals(2);
        box_size_z->setMaximum(10);
        box_size_z->setSingleStep(0.01);

        horizontalLayout_8->addWidget(box_size_z);

        primitive_type->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QStringLiteral("tab_3"));
        groupBox_11 = new QGroupBox(tab_3);
        groupBox_11->setObjectName(QStringLiteral("groupBox_11"));
        groupBox_11->setGeometry(QRect(10, 10, 271, 61));
        horizontalLayoutWidget_8 = new QWidget(groupBox_11);
        horizontalLayoutWidget_8->setObjectName(QStringLiteral("horizontalLayoutWidget_8"));
        horizontalLayoutWidget_8->setGeometry(QRect(10, 20, 251, 31));
        horizontalLayout_9 = new QHBoxLayout(horizontalLayoutWidget_8);
        horizontalLayout_9->setSpacing(6);
        horizontalLayout_9->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        horizontalLayout_9->setContentsMargins(0, 0, 0, 0);
        sphere_diameter = new QDoubleSpinBox(horizontalLayoutWidget_8);
        sphere_diameter->setObjectName(QStringLiteral("sphere_diameter"));
        sphere_diameter->setWrapping(false);
        sphere_diameter->setProperty("showGroupSeparator", QVariant(false));
        sphere_diameter->setDecimals(2);
        sphere_diameter->setMaximum(10);
        sphere_diameter->setSingleStep(0.01);
        sphere_diameter->setValue(1);

        horizontalLayout_9->addWidget(sphere_diameter);

        egsdge = new QGroupBox(tab_3);
        egsdge->setObjectName(QStringLiteral("egsdge"));
        egsdge->setGeometry(QRect(10, 70, 271, 61));
        horizontalLayoutWidget_10 = new QWidget(egsdge);
        horizontalLayoutWidget_10->setObjectName(QStringLiteral("horizontalLayoutWidget_10"));
        horizontalLayoutWidget_10->setGeometry(QRect(10, 20, 251, 31));
        horizontalLayout_11 = new QHBoxLayout(horizontalLayoutWidget_10);
        horizontalLayout_11->setSpacing(6);
        horizontalLayout_11->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_11->setObjectName(QStringLiteral("horizontalLayout_11"));
        horizontalLayout_11->setContentsMargins(0, 0, 0, 0);
        sphere_tesselation = new QSpinBox(horizontalLayoutWidget_10);
        sphere_tesselation->setObjectName(QStringLiteral("sphere_tesselation"));
        sphere_tesselation->setWrapping(false);
        sphere_tesselation->setProperty("showGroupSeparator", QVariant(false));
        sphere_tesselation->setMinimum(3);
        sphere_tesselation->setValue(16);

        horizontalLayout_11->addWidget(sphere_tesselation);

        primitive_type->addTab(tab_3, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName(QStringLiteral("tab_4"));
        primitive_type->addTab(tab_4, QString());
        groupBox_12 = new QGroupBox(centralWidget);
        groupBox_12->setObjectName(QStringLiteral("groupBox_12"));
        groupBox_12->setGeometry(QRect(1040, 570, 311, 81));
        material_combo = new QComboBox(groupBox_12);
        material_combo->setObjectName(QStringLiteral("material_combo"));
        material_combo->setGeometry(QRect(10, 30, 291, 31));
        QtGuiClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(QtGuiClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1361, 29));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        QtGuiClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(QtGuiClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        QtGuiClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(QtGuiClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        QtGuiClass->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuFile->addAction(actionImport);
        menuFile->addAction(actionExport);

        retranslateUi(QtGuiClass);

        primitive_type->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(QtGuiClass);
    } // setupUi

    void retranslateUi(QMainWindow *QtGuiClass)
    {
        QtGuiClass->setWindowTitle(QApplication::translate("QtGuiClass", "Model Editor", nullptr));
        actionImport->setText(QApplication::translate("QtGuiClass", "Import", nullptr));
        actionExport->setText(QApplication::translate("QtGuiClass", "Export", nullptr));
        wire_mode_check->setText(QApplication::translate("QtGuiClass", "WireMode", nullptr));
        groupBox->setTitle(QApplication::translate("QtGuiClass", "Game Screen", nullptr));
        groupBox_2->setTitle(QApplication::translate("QtGuiClass", "Parts", nullptr));
        add_button->setText(QApplication::translate("QtGuiClass", "Add", nullptr));
        delete_button->setText(QApplication::translate("QtGuiClass", "Delete", nullptr));
        transform_group->setTitle(QApplication::translate("QtGuiClass", "Transform", nullptr));
        groupBox_4->setTitle(QApplication::translate("QtGuiClass", "Position", nullptr));
        label_3->setText(QApplication::translate("QtGuiClass", "X", nullptr));
        label_2->setText(QApplication::translate("QtGuiClass", "Y", nullptr));
        label->setText(QApplication::translate("QtGuiClass", "Z", nullptr));
        groupBox_5->setTitle(QApplication::translate("QtGuiClass", "Rotation", nullptr));
        label_4->setText(QApplication::translate("QtGuiClass", "X", nullptr));
        label_5->setText(QApplication::translate("QtGuiClass", "Y", nullptr));
        label_6->setText(QApplication::translate("QtGuiClass", "Z", nullptr));
        groupBox_6->setTitle(QApplication::translate("QtGuiClass", "Scale", nullptr));
        label_10->setText(QApplication::translate("QtGuiClass", "X", nullptr));
        label_11->setText(QApplication::translate("QtGuiClass", "Y", nullptr));
        label_12->setText(QApplication::translate("QtGuiClass", "Z", nullptr));
        groupBox_8->setTitle(QApplication::translate("QtGuiClass", "Parent", nullptr));
        rename_group->setTitle(QApplication::translate("QtGuiClass", "Name", nullptr));
        rename_button->setText(QApplication::translate("QtGuiClass", "Rename", nullptr));
        primitive_group->setTitle(QApplication::translate("QtGuiClass", "Primitive", nullptr));
        primitive_type->setTabText(primitive_type->indexOf(tab_5), QApplication::translate("QtGuiClass", "none", nullptr));
        groupBox_7->setTitle(QApplication::translate("QtGuiClass", "Size", nullptr));
        label_13->setText(QApplication::translate("QtGuiClass", "Width", nullptr));
        label_14->setText(QApplication::translate("QtGuiClass", "Height", nullptr));
        groupBox_9->setTitle(QApplication::translate("QtGuiClass", "Div", nullptr));
        label_15->setText(QApplication::translate("QtGuiClass", "X", nullptr));
        label_16->setText(QApplication::translate("QtGuiClass", "Y", nullptr));
        primitive_type->setTabText(primitive_type->indexOf(tab), QApplication::translate("QtGuiClass", "Plane", nullptr));
        groupBox_10->setTitle(QApplication::translate("QtGuiClass", "Size", nullptr));
        label_17->setText(QApplication::translate("QtGuiClass", "X", nullptr));
        label_18->setText(QApplication::translate("QtGuiClass", "Y", nullptr));
        label_19->setText(QApplication::translate("QtGuiClass", "Z", nullptr));
        primitive_type->setTabText(primitive_type->indexOf(tab_2), QApplication::translate("QtGuiClass", "Box", nullptr));
        groupBox_11->setTitle(QApplication::translate("QtGuiClass", "Diameter", nullptr));
        egsdge->setTitle(QApplication::translate("QtGuiClass", "Tesselation", nullptr));
        primitive_type->setTabText(primitive_type->indexOf(tab_3), QApplication::translate("QtGuiClass", "Sphere", nullptr));
        primitive_type->setTabText(primitive_type->indexOf(tab_4), QApplication::translate("QtGuiClass", "Capsule", nullptr));
        groupBox_12->setTitle(QApplication::translate("QtGuiClass", "Material", nullptr));
        menuFile->setTitle(QApplication::translate("QtGuiClass", "File", nullptr));
    } // retranslateUi

};

namespace Ui {
    class QtGuiClass: public Ui_QtGuiClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTGUI_H
