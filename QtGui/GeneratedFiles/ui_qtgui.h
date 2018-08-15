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
    QPushButton *clear_button;
    QGroupBox *rename_group;
    QLineEdit *rename_box;
    QPushButton *rename_button;
    QGroupBox *groupBox_12;
    QComboBox *material_combo;
    QTabWidget *transform_type;
    QWidget *tab_4;
    QGroupBox *groupBox_6;
    QWidget *horizontalLayoutWidget_4;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_10;
    QDoubleSpinBox *scale_x;
    QLabel *label_11;
    QDoubleSpinBox *scale_y;
    QLabel *label_12;
    QDoubleSpinBox *scale_z;
    QGroupBox *groupBox_4;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_3;
    QDoubleSpinBox *position_x;
    QLabel *label_2;
    QDoubleSpinBox *position_y;
    QLabel *label;
    QDoubleSpinBox *position_z;
    QGroupBox *groupBox_8;
    QComboBox *parent_combo;
    QGroupBox *groupBox_5;
    QWidget *horizontalLayoutWidget_2;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_4;
    QDoubleSpinBox *rotation_x;
    QLabel *label_5;
    QDoubleSpinBox *rotation_y;
    QLabel *label_6;
    QDoubleSpinBox *rotation_z;
    QWidget *tab_8;
    QGroupBox *groupBox_16;
    QWidget *horizontalLayoutWidget_17;
    QHBoxLayout *horizontalLayout_18;
    QLabel *label_29;
    QDoubleSpinBox *offset_position_x;
    QLabel *label_30;
    QDoubleSpinBox *offset_position_y;
    QLabel *label_31;
    QDoubleSpinBox *offset_position_z;
    QGroupBox *groupBox_17;
    QWidget *horizontalLayoutWidget_18;
    QHBoxLayout *horizontalLayout_19;
    QLabel *label_32;
    QDoubleSpinBox *offset_rotation_x;
    QLabel *label_33;
    QDoubleSpinBox *offset_rotation_y;
    QLabel *label_34;
    QDoubleSpinBox *offset_rotation_z;
    QGroupBox *groupBox_18;
    QWidget *horizontalLayoutWidget_19;
    QHBoxLayout *horizontalLayout_20;
    QLabel *label_35;
    QDoubleSpinBox *offset_scale_x;
    QLabel *label_36;
    QDoubleSpinBox *offset_scale_y;
    QLabel *label_37;
    QDoubleSpinBox *offset_scale_z;
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
    QSpinBox *sphere_tessellation;
    QWidget *tab_6;
    QGroupBox *egsdge_2;
    QWidget *horizontalLayoutWidget_11;
    QHBoxLayout *horizontalLayout_12;
    QSpinBox *geosphere_tessellation;
    QGroupBox *groupBox_13;
    QWidget *horizontalLayoutWidget_9;
    QHBoxLayout *horizontalLayout_10;
    QDoubleSpinBox *geosphere_diameter;
    QWidget *tab_7;
    QGroupBox *egsdge_3;
    QWidget *horizontalLayoutWidget_12;
    QHBoxLayout *horizontalLayout_13;
    QSpinBox *capsule_tessellation;
    QGroupBox *groupBox_14;
    QWidget *horizontalLayoutWidget_13;
    QHBoxLayout *horizontalLayout_14;
    QDoubleSpinBox *capsule_diameter;
    QGroupBox *groupBox_15;
    QWidget *horizontalLayoutWidget_14;
    QHBoxLayout *horizontalLayout_15;
    QLabel *label_20;
    QDoubleSpinBox *caps_size_x;
    QLabel *label_21;
    QDoubleSpinBox *caps_size_y;
    QLabel *label_22;
    QDoubleSpinBox *caps_size_z;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *QtGuiClass)
    {
        if (QtGuiClass->objectName().isEmpty())
            QtGuiClass->setObjectName(QStringLiteral("QtGuiClass"));
        QtGuiClass->resize(1360, 706);
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
        wire_mode_check->setGeometry(QRect(30, 609, 141, 31));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\343\203\241\343\202\244\343\203\252\343\202\252"));
        font1.setPointSize(12);
        font1.setBold(false);
        font1.setWeight(50);
        wire_mode_check->setFont(font1);
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(210, 0, 821, 641));
        groupBox->setFont(font);
        widget = new QWidget(groupBox);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(10, 30, 800, 600));
        groupBox_2 = new QGroupBox(centralWidget);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(10, 0, 191, 601));
        groupBox_2->setFont(font);
        parts_list = new QListWidget(groupBox_2);
        parts_list->setObjectName(QStringLiteral("parts_list"));
        parts_list->setGeometry(QRect(10, 30, 171, 441));
        add_button = new QPushButton(groupBox_2);
        add_button->setObjectName(QStringLiteral("add_button"));
        add_button->setGeometry(QRect(10, 480, 171, 31));
        add_button->setFont(font);
        delete_button = new QPushButton(groupBox_2);
        delete_button->setObjectName(QStringLiteral("delete_button"));
        delete_button->setEnabled(false);
        delete_button->setGeometry(QRect(10, 520, 171, 31));
        delete_button->setFont(font);
        clear_button = new QPushButton(groupBox_2);
        clear_button->setObjectName(QStringLiteral("clear_button"));
        clear_button->setGeometry(QRect(10, 560, 171, 31));
        clear_button->setFont(font);
        rename_group = new QGroupBox(centralWidget);
        rename_group->setObjectName(QStringLiteral("rename_group"));
        rename_group->setEnabled(false);
        rename_group->setGeometry(QRect(1040, 0, 311, 61));
        rename_group->setFont(font);
        rename_box = new QLineEdit(rename_group);
        rename_box->setObjectName(QStringLiteral("rename_box"));
        rename_box->setGeometry(QRect(10, 20, 211, 31));
        rename_button = new QPushButton(rename_group);
        rename_button->setObjectName(QStringLiteral("rename_button"));
        rename_button->setGeometry(QRect(230, 19, 71, 31));
        groupBox_12 = new QGroupBox(centralWidget);
        groupBox_12->setObjectName(QStringLiteral("groupBox_12"));
        groupBox_12->setGeometry(QRect(1040, 580, 311, 61));
        material_combo = new QComboBox(groupBox_12);
        material_combo->setObjectName(QStringLiteral("material_combo"));
        material_combo->setGeometry(QRect(10, 20, 291, 31));
        transform_type = new QTabWidget(centralWidget);
        transform_type->setObjectName(QStringLiteral("transform_type"));
        transform_type->setGeometry(QRect(1040, 60, 311, 281));
        tab_4 = new QWidget();
        tab_4->setObjectName(QStringLiteral("tab_4"));
        groupBox_6 = new QGroupBox(tab_4);
        groupBox_6->setObjectName(QStringLiteral("groupBox_6"));
        groupBox_6->setGeometry(QRect(10, 180, 291, 61));
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
        scale_x->setMinimum(-5);
        scale_x->setMaximum(5);
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
        scale_y->setMinimum(-5);
        scale_y->setMaximum(5);
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
        scale_z->setMinimum(-5);
        scale_z->setMaximum(5);
        scale_z->setSingleStep(0.01);

        horizontalLayout_5->addWidget(scale_z);

        groupBox_4 = new QGroupBox(tab_4);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        groupBox_4->setGeometry(QRect(10, 60, 291, 61));
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
        position_x->setMinimum(-5);
        position_x->setMaximum(5);
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
        position_y->setMinimum(-5);
        position_y->setMaximum(5);
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
        position_z->setMinimum(-5);
        position_z->setMaximum(5);
        position_z->setSingleStep(0.01);

        horizontalLayout_2->addWidget(position_z);

        groupBox_8 = new QGroupBox(tab_4);
        groupBox_8->setObjectName(QStringLiteral("groupBox_8"));
        groupBox_8->setGeometry(QRect(10, 0, 291, 61));
        parent_combo = new QComboBox(groupBox_8);
        parent_combo->setObjectName(QStringLiteral("parent_combo"));
        parent_combo->setGeometry(QRect(10, 20, 271, 31));
        groupBox_5 = new QGroupBox(tab_4);
        groupBox_5->setObjectName(QStringLiteral("groupBox_5"));
        groupBox_5->setGeometry(QRect(10, 120, 291, 61));
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
        rotation_x->setMinimum(-5);
        rotation_x->setMaximum(5);
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
        rotation_y->setMinimum(-5);
        rotation_y->setMaximum(5);
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
        rotation_z->setMinimum(-5);
        rotation_z->setMaximum(5);
        rotation_z->setSingleStep(0.01);

        horizontalLayout_3->addWidget(rotation_z);

        transform_type->addTab(tab_4, QString());
        tab_8 = new QWidget();
        tab_8->setObjectName(QStringLiteral("tab_8"));
        groupBox_16 = new QGroupBox(tab_8);
        groupBox_16->setObjectName(QStringLiteral("groupBox_16"));
        groupBox_16->setGeometry(QRect(10, 0, 291, 61));
        horizontalLayoutWidget_17 = new QWidget(groupBox_16);
        horizontalLayoutWidget_17->setObjectName(QStringLiteral("horizontalLayoutWidget_17"));
        horizontalLayoutWidget_17->setGeometry(QRect(10, 20, 271, 31));
        horizontalLayout_18 = new QHBoxLayout(horizontalLayoutWidget_17);
        horizontalLayout_18->setSpacing(6);
        horizontalLayout_18->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_18->setObjectName(QStringLiteral("horizontalLayout_18"));
        horizontalLayout_18->setContentsMargins(0, 0, 0, 0);
        label_29 = new QLabel(horizontalLayoutWidget_17);
        label_29->setObjectName(QStringLiteral("label_29"));

        horizontalLayout_18->addWidget(label_29);

        offset_position_x = new QDoubleSpinBox(horizontalLayoutWidget_17);
        offset_position_x->setObjectName(QStringLiteral("offset_position_x"));
        offset_position_x->setWrapping(false);
        offset_position_x->setProperty("showGroupSeparator", QVariant(false));
        offset_position_x->setDecimals(2);
        offset_position_x->setMinimum(-5);
        offset_position_x->setMaximum(5);
        offset_position_x->setSingleStep(0.01);

        horizontalLayout_18->addWidget(offset_position_x);

        label_30 = new QLabel(horizontalLayoutWidget_17);
        label_30->setObjectName(QStringLiteral("label_30"));

        horizontalLayout_18->addWidget(label_30);

        offset_position_y = new QDoubleSpinBox(horizontalLayoutWidget_17);
        offset_position_y->setObjectName(QStringLiteral("offset_position_y"));
        offset_position_y->setWrapping(false);
        offset_position_y->setProperty("showGroupSeparator", QVariant(false));
        offset_position_y->setDecimals(2);
        offset_position_y->setMinimum(-5);
        offset_position_y->setMaximum(5);
        offset_position_y->setSingleStep(0.01);

        horizontalLayout_18->addWidget(offset_position_y);

        label_31 = new QLabel(horizontalLayoutWidget_17);
        label_31->setObjectName(QStringLiteral("label_31"));

        horizontalLayout_18->addWidget(label_31);

        offset_position_z = new QDoubleSpinBox(horizontalLayoutWidget_17);
        offset_position_z->setObjectName(QStringLiteral("offset_position_z"));
        offset_position_z->setWrapping(false);
        offset_position_z->setProperty("showGroupSeparator", QVariant(false));
        offset_position_z->setDecimals(2);
        offset_position_z->setMinimum(-5);
        offset_position_z->setMaximum(5);
        offset_position_z->setSingleStep(0.01);

        horizontalLayout_18->addWidget(offset_position_z);

        groupBox_17 = new QGroupBox(tab_8);
        groupBox_17->setObjectName(QStringLiteral("groupBox_17"));
        groupBox_17->setGeometry(QRect(10, 60, 291, 61));
        horizontalLayoutWidget_18 = new QWidget(groupBox_17);
        horizontalLayoutWidget_18->setObjectName(QStringLiteral("horizontalLayoutWidget_18"));
        horizontalLayoutWidget_18->setGeometry(QRect(10, 20, 270, 31));
        horizontalLayout_19 = new QHBoxLayout(horizontalLayoutWidget_18);
        horizontalLayout_19->setSpacing(6);
        horizontalLayout_19->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_19->setObjectName(QStringLiteral("horizontalLayout_19"));
        horizontalLayout_19->setContentsMargins(0, 0, 0, 0);
        label_32 = new QLabel(horizontalLayoutWidget_18);
        label_32->setObjectName(QStringLiteral("label_32"));

        horizontalLayout_19->addWidget(label_32);

        offset_rotation_x = new QDoubleSpinBox(horizontalLayoutWidget_18);
        offset_rotation_x->setObjectName(QStringLiteral("offset_rotation_x"));
        offset_rotation_x->setWrapping(false);
        offset_rotation_x->setProperty("showGroupSeparator", QVariant(false));
        offset_rotation_x->setDecimals(2);
        offset_rotation_x->setMinimum(-5);
        offset_rotation_x->setMaximum(5);
        offset_rotation_x->setSingleStep(0.01);

        horizontalLayout_19->addWidget(offset_rotation_x);

        label_33 = new QLabel(horizontalLayoutWidget_18);
        label_33->setObjectName(QStringLiteral("label_33"));

        horizontalLayout_19->addWidget(label_33);

        offset_rotation_y = new QDoubleSpinBox(horizontalLayoutWidget_18);
        offset_rotation_y->setObjectName(QStringLiteral("offset_rotation_y"));
        offset_rotation_y->setWrapping(false);
        offset_rotation_y->setProperty("showGroupSeparator", QVariant(false));
        offset_rotation_y->setDecimals(2);
        offset_rotation_y->setMinimum(-5);
        offset_rotation_y->setMaximum(5);
        offset_rotation_y->setSingleStep(0.01);

        horizontalLayout_19->addWidget(offset_rotation_y);

        label_34 = new QLabel(horizontalLayoutWidget_18);
        label_34->setObjectName(QStringLiteral("label_34"));

        horizontalLayout_19->addWidget(label_34);

        offset_rotation_z = new QDoubleSpinBox(horizontalLayoutWidget_18);
        offset_rotation_z->setObjectName(QStringLiteral("offset_rotation_z"));
        offset_rotation_z->setWrapping(false);
        offset_rotation_z->setProperty("showGroupSeparator", QVariant(false));
        offset_rotation_z->setDecimals(2);
        offset_rotation_z->setMinimum(-5);
        offset_rotation_z->setMaximum(5);
        offset_rotation_z->setSingleStep(0.01);

        horizontalLayout_19->addWidget(offset_rotation_z);

        groupBox_18 = new QGroupBox(tab_8);
        groupBox_18->setObjectName(QStringLiteral("groupBox_18"));
        groupBox_18->setGeometry(QRect(10, 120, 291, 61));
        horizontalLayoutWidget_19 = new QWidget(groupBox_18);
        horizontalLayoutWidget_19->setObjectName(QStringLiteral("horizontalLayoutWidget_19"));
        horizontalLayoutWidget_19->setGeometry(QRect(10, 20, 270, 31));
        horizontalLayout_20 = new QHBoxLayout(horizontalLayoutWidget_19);
        horizontalLayout_20->setSpacing(6);
        horizontalLayout_20->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_20->setObjectName(QStringLiteral("horizontalLayout_20"));
        horizontalLayout_20->setContentsMargins(0, 0, 0, 0);
        label_35 = new QLabel(horizontalLayoutWidget_19);
        label_35->setObjectName(QStringLiteral("label_35"));

        horizontalLayout_20->addWidget(label_35);

        offset_scale_x = new QDoubleSpinBox(horizontalLayoutWidget_19);
        offset_scale_x->setObjectName(QStringLiteral("offset_scale_x"));
        offset_scale_x->setWrapping(false);
        offset_scale_x->setProperty("showGroupSeparator", QVariant(false));
        offset_scale_x->setDecimals(2);
        offset_scale_x->setMinimum(-5);
        offset_scale_x->setMaximum(5);
        offset_scale_x->setSingleStep(0.01);

        horizontalLayout_20->addWidget(offset_scale_x);

        label_36 = new QLabel(horizontalLayoutWidget_19);
        label_36->setObjectName(QStringLiteral("label_36"));

        horizontalLayout_20->addWidget(label_36);

        offset_scale_y = new QDoubleSpinBox(horizontalLayoutWidget_19);
        offset_scale_y->setObjectName(QStringLiteral("offset_scale_y"));
        offset_scale_y->setWrapping(false);
        offset_scale_y->setProperty("showGroupSeparator", QVariant(false));
        offset_scale_y->setDecimals(2);
        offset_scale_y->setMinimum(-5);
        offset_scale_y->setMaximum(5);
        offset_scale_y->setSingleStep(0.01);

        horizontalLayout_20->addWidget(offset_scale_y);

        label_37 = new QLabel(horizontalLayoutWidget_19);
        label_37->setObjectName(QStringLiteral("label_37"));

        horizontalLayout_20->addWidget(label_37);

        offset_scale_z = new QDoubleSpinBox(horizontalLayoutWidget_19);
        offset_scale_z->setObjectName(QStringLiteral("offset_scale_z"));
        offset_scale_z->setWrapping(false);
        offset_scale_z->setProperty("showGroupSeparator", QVariant(false));
        offset_scale_z->setDecimals(2);
        offset_scale_z->setMinimum(-5);
        offset_scale_z->setMaximum(5);
        offset_scale_z->setSingleStep(0.01);

        horizontalLayout_20->addWidget(offset_scale_z);

        transform_type->addTab(tab_8, QString());
        primitive_type = new QTabWidget(centralWidget);
        primitive_type->setObjectName(QStringLiteral("primitive_type"));
        primitive_type->setGeometry(QRect(1040, 350, 311, 231));
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
        groupBox_10->setGeometry(QRect(10, 10, 291, 61));
        horizontalLayoutWidget_7 = new QWidget(groupBox_10);
        horizontalLayoutWidget_7->setObjectName(QStringLiteral("horizontalLayoutWidget_7"));
        horizontalLayoutWidget_7->setGeometry(QRect(10, 20, 293, 31));
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
        box_size_x->setDecimals(3);
        box_size_x->setMinimum(-5);
        box_size_x->setMaximum(5);
        box_size_x->setSingleStep(0.01);

        horizontalLayout_8->addWidget(box_size_x);

        label_18 = new QLabel(horizontalLayoutWidget_7);
        label_18->setObjectName(QStringLiteral("label_18"));

        horizontalLayout_8->addWidget(label_18);

        box_size_y = new QDoubleSpinBox(horizontalLayoutWidget_7);
        box_size_y->setObjectName(QStringLiteral("box_size_y"));
        box_size_y->setWrapping(false);
        box_size_y->setProperty("showGroupSeparator", QVariant(false));
        box_size_y->setDecimals(3);
        box_size_y->setMinimum(-5);
        box_size_y->setMaximum(5);
        box_size_y->setSingleStep(0.01);

        horizontalLayout_8->addWidget(box_size_y);

        label_19 = new QLabel(horizontalLayoutWidget_7);
        label_19->setObjectName(QStringLiteral("label_19"));

        horizontalLayout_8->addWidget(label_19);

        box_size_z = new QDoubleSpinBox(horizontalLayoutWidget_7);
        box_size_z->setObjectName(QStringLiteral("box_size_z"));
        box_size_z->setWrapping(false);
        box_size_z->setProperty("showGroupSeparator", QVariant(false));
        box_size_z->setDecimals(3);
        box_size_z->setMinimum(-5);
        box_size_z->setMaximum(5);
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
        sphere_diameter->setDecimals(3);
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
        sphere_tessellation = new QSpinBox(horizontalLayoutWidget_10);
        sphere_tessellation->setObjectName(QStringLiteral("sphere_tessellation"));
        sphere_tessellation->setWrapping(false);
        sphere_tessellation->setProperty("showGroupSeparator", QVariant(false));
        sphere_tessellation->setMinimum(3);
        sphere_tessellation->setValue(16);

        horizontalLayout_11->addWidget(sphere_tessellation);

        primitive_type->addTab(tab_3, QString());
        tab_6 = new QWidget();
        tab_6->setObjectName(QStringLiteral("tab_6"));
        egsdge_2 = new QGroupBox(tab_6);
        egsdge_2->setObjectName(QStringLiteral("egsdge_2"));
        egsdge_2->setGeometry(QRect(10, 70, 271, 61));
        horizontalLayoutWidget_11 = new QWidget(egsdge_2);
        horizontalLayoutWidget_11->setObjectName(QStringLiteral("horizontalLayoutWidget_11"));
        horizontalLayoutWidget_11->setGeometry(QRect(10, 20, 251, 31));
        horizontalLayout_12 = new QHBoxLayout(horizontalLayoutWidget_11);
        horizontalLayout_12->setSpacing(6);
        horizontalLayout_12->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_12->setObjectName(QStringLiteral("horizontalLayout_12"));
        horizontalLayout_12->setContentsMargins(0, 0, 0, 0);
        geosphere_tessellation = new QSpinBox(horizontalLayoutWidget_11);
        geosphere_tessellation->setObjectName(QStringLiteral("geosphere_tessellation"));
        geosphere_tessellation->setWrapping(false);
        geosphere_tessellation->setProperty("showGroupSeparator", QVariant(false));
        geosphere_tessellation->setMinimum(3);
        geosphere_tessellation->setMaximum(7);
        geosphere_tessellation->setValue(5);

        horizontalLayout_12->addWidget(geosphere_tessellation);

        groupBox_13 = new QGroupBox(tab_6);
        groupBox_13->setObjectName(QStringLiteral("groupBox_13"));
        groupBox_13->setGeometry(QRect(10, 10, 271, 61));
        horizontalLayoutWidget_9 = new QWidget(groupBox_13);
        horizontalLayoutWidget_9->setObjectName(QStringLiteral("horizontalLayoutWidget_9"));
        horizontalLayoutWidget_9->setGeometry(QRect(10, 20, 251, 31));
        horizontalLayout_10 = new QHBoxLayout(horizontalLayoutWidget_9);
        horizontalLayout_10->setSpacing(6);
        horizontalLayout_10->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_10->setObjectName(QStringLiteral("horizontalLayout_10"));
        horizontalLayout_10->setContentsMargins(0, 0, 0, 0);
        geosphere_diameter = new QDoubleSpinBox(horizontalLayoutWidget_9);
        geosphere_diameter->setObjectName(QStringLiteral("geosphere_diameter"));
        geosphere_diameter->setWrapping(false);
        geosphere_diameter->setProperty("showGroupSeparator", QVariant(false));
        geosphere_diameter->setDecimals(3);
        geosphere_diameter->setMaximum(10);
        geosphere_diameter->setSingleStep(0.01);
        geosphere_diameter->setValue(1);

        horizontalLayout_10->addWidget(geosphere_diameter);

        primitive_type->addTab(tab_6, QString());
        tab_7 = new QWidget();
        tab_7->setObjectName(QStringLiteral("tab_7"));
        egsdge_3 = new QGroupBox(tab_7);
        egsdge_3->setObjectName(QStringLiteral("egsdge_3"));
        egsdge_3->setGeometry(QRect(10, 120, 271, 61));
        horizontalLayoutWidget_12 = new QWidget(egsdge_3);
        horizontalLayoutWidget_12->setObjectName(QStringLiteral("horizontalLayoutWidget_12"));
        horizontalLayoutWidget_12->setGeometry(QRect(10, 20, 251, 31));
        horizontalLayout_13 = new QHBoxLayout(horizontalLayoutWidget_12);
        horizontalLayout_13->setSpacing(6);
        horizontalLayout_13->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_13->setObjectName(QStringLiteral("horizontalLayout_13"));
        horizontalLayout_13->setContentsMargins(0, 0, 0, 0);
        capsule_tessellation = new QSpinBox(horizontalLayoutWidget_12);
        capsule_tessellation->setObjectName(QStringLiteral("capsule_tessellation"));
        capsule_tessellation->setWrapping(false);
        capsule_tessellation->setProperty("showGroupSeparator", QVariant(false));
        capsule_tessellation->setMinimum(3);
        capsule_tessellation->setValue(18);

        horizontalLayout_13->addWidget(capsule_tessellation);

        groupBox_14 = new QGroupBox(tab_7);
        groupBox_14->setObjectName(QStringLiteral("groupBox_14"));
        groupBox_14->setGeometry(QRect(10, 60, 271, 61));
        horizontalLayoutWidget_13 = new QWidget(groupBox_14);
        horizontalLayoutWidget_13->setObjectName(QStringLiteral("horizontalLayoutWidget_13"));
        horizontalLayoutWidget_13->setGeometry(QRect(10, 20, 251, 31));
        horizontalLayout_14 = new QHBoxLayout(horizontalLayoutWidget_13);
        horizontalLayout_14->setSpacing(6);
        horizontalLayout_14->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_14->setObjectName(QStringLiteral("horizontalLayout_14"));
        horizontalLayout_14->setContentsMargins(0, 0, 0, 0);
        capsule_diameter = new QDoubleSpinBox(horizontalLayoutWidget_13);
        capsule_diameter->setObjectName(QStringLiteral("capsule_diameter"));
        capsule_diameter->setWrapping(false);
        capsule_diameter->setProperty("showGroupSeparator", QVariant(false));
        capsule_diameter->setDecimals(2);
        capsule_diameter->setMaximum(10);
        capsule_diameter->setSingleStep(0.01);
        capsule_diameter->setValue(1);

        horizontalLayout_14->addWidget(capsule_diameter);

        groupBox_15 = new QGroupBox(tab_7);
        groupBox_15->setObjectName(QStringLiteral("groupBox_15"));
        groupBox_15->setGeometry(QRect(10, 0, 291, 61));
        horizontalLayoutWidget_14 = new QWidget(groupBox_15);
        horizontalLayoutWidget_14->setObjectName(QStringLiteral("horizontalLayoutWidget_14"));
        horizontalLayoutWidget_14->setGeometry(QRect(10, 20, 297, 31));
        horizontalLayout_15 = new QHBoxLayout(horizontalLayoutWidget_14);
        horizontalLayout_15->setSpacing(6);
        horizontalLayout_15->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_15->setObjectName(QStringLiteral("horizontalLayout_15"));
        horizontalLayout_15->setContentsMargins(0, 0, 0, 0);
        label_20 = new QLabel(horizontalLayoutWidget_14);
        label_20->setObjectName(QStringLiteral("label_20"));

        horizontalLayout_15->addWidget(label_20);

        caps_size_x = new QDoubleSpinBox(horizontalLayoutWidget_14);
        caps_size_x->setObjectName(QStringLiteral("caps_size_x"));
        caps_size_x->setWrapping(false);
        caps_size_x->setProperty("showGroupSeparator", QVariant(false));
        caps_size_x->setDecimals(3);
        caps_size_x->setMinimum(-5);
        caps_size_x->setMaximum(5);
        caps_size_x->setSingleStep(0.01);

        horizontalLayout_15->addWidget(caps_size_x);

        label_21 = new QLabel(horizontalLayoutWidget_14);
        label_21->setObjectName(QStringLiteral("label_21"));

        horizontalLayout_15->addWidget(label_21);

        caps_size_y = new QDoubleSpinBox(horizontalLayoutWidget_14);
        caps_size_y->setObjectName(QStringLiteral("caps_size_y"));
        caps_size_y->setWrapping(false);
        caps_size_y->setProperty("showGroupSeparator", QVariant(false));
        caps_size_y->setDecimals(3);
        caps_size_y->setMinimum(-5);
        caps_size_y->setMaximum(5);
        caps_size_y->setSingleStep(0.01);

        horizontalLayout_15->addWidget(caps_size_y);

        label_22 = new QLabel(horizontalLayoutWidget_14);
        label_22->setObjectName(QStringLiteral("label_22"));

        horizontalLayout_15->addWidget(label_22);

        caps_size_z = new QDoubleSpinBox(horizontalLayoutWidget_14);
        caps_size_z->setObjectName(QStringLiteral("caps_size_z"));
        caps_size_z->setWrapping(false);
        caps_size_z->setProperty("showGroupSeparator", QVariant(false));
        caps_size_z->setDecimals(3);
        caps_size_z->setMinimum(-5);
        caps_size_z->setMaximum(5);
        caps_size_z->setSingleStep(0.01);

        horizontalLayout_15->addWidget(caps_size_z);

        primitive_type->addTab(tab_7, QString());
        QtGuiClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(QtGuiClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1360, 26));
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

        transform_type->setCurrentIndex(0);
        primitive_type->setCurrentIndex(3);


        QMetaObject::connectSlotsByName(QtGuiClass);
    } // setupUi

    void retranslateUi(QMainWindow *QtGuiClass)
    {
        QtGuiClass->setWindowTitle(QApplication::translate("QtGuiClass", "Hierarchy Model Editor", nullptr));
        actionImport->setText(QApplication::translate("QtGuiClass", "Import", nullptr));
        actionExport->setText(QApplication::translate("QtGuiClass", "Export", nullptr));
        wire_mode_check->setText(QApplication::translate("QtGuiClass", "WireMode", nullptr));
        groupBox->setTitle(QApplication::translate("QtGuiClass", "Game Screen", nullptr));
        groupBox_2->setTitle(QApplication::translate("QtGuiClass", "Parts", nullptr));
        add_button->setText(QApplication::translate("QtGuiClass", "Add", nullptr));
        delete_button->setText(QApplication::translate("QtGuiClass", "Delete", nullptr));
        clear_button->setText(QApplication::translate("QtGuiClass", "Clear", nullptr));
        rename_group->setTitle(QApplication::translate("QtGuiClass", "Name", nullptr));
        rename_button->setText(QApplication::translate("QtGuiClass", "Rename", nullptr));
        groupBox_12->setTitle(QApplication::translate("QtGuiClass", "Material", nullptr));
        groupBox_6->setTitle(QApplication::translate("QtGuiClass", "Scale", nullptr));
        label_10->setText(QApplication::translate("QtGuiClass", "X", nullptr));
        label_11->setText(QApplication::translate("QtGuiClass", "Y", nullptr));
        label_12->setText(QApplication::translate("QtGuiClass", "Z", nullptr));
        groupBox_4->setTitle(QApplication::translate("QtGuiClass", "Position", nullptr));
        label_3->setText(QApplication::translate("QtGuiClass", "X", nullptr));
        label_2->setText(QApplication::translate("QtGuiClass", "Y", nullptr));
        label->setText(QApplication::translate("QtGuiClass", "Z", nullptr));
        groupBox_8->setTitle(QApplication::translate("QtGuiClass", "Parent", nullptr));
        groupBox_5->setTitle(QApplication::translate("QtGuiClass", "Rotation", nullptr));
        label_4->setText(QApplication::translate("QtGuiClass", "X", nullptr));
        label_5->setText(QApplication::translate("QtGuiClass", "Y", nullptr));
        label_6->setText(QApplication::translate("QtGuiClass", "Z", nullptr));
        transform_type->setTabText(transform_type->indexOf(tab_4), QApplication::translate("QtGuiClass", "Transform", nullptr));
        groupBox_16->setTitle(QApplication::translate("QtGuiClass", "Position", nullptr));
        label_29->setText(QApplication::translate("QtGuiClass", "X", nullptr));
        label_30->setText(QApplication::translate("QtGuiClass", "Y", nullptr));
        label_31->setText(QApplication::translate("QtGuiClass", "Z", nullptr));
        groupBox_17->setTitle(QApplication::translate("QtGuiClass", "Rotation", nullptr));
        label_32->setText(QApplication::translate("QtGuiClass", "X", nullptr));
        label_33->setText(QApplication::translate("QtGuiClass", "Y", nullptr));
        label_34->setText(QApplication::translate("QtGuiClass", "Z", nullptr));
        groupBox_18->setTitle(QApplication::translate("QtGuiClass", "Scale", nullptr));
        label_35->setText(QApplication::translate("QtGuiClass", "X", nullptr));
        label_36->setText(QApplication::translate("QtGuiClass", "Y", nullptr));
        label_37->setText(QApplication::translate("QtGuiClass", "Z", nullptr));
        transform_type->setTabText(transform_type->indexOf(tab_8), QApplication::translate("QtGuiClass", "Offset", nullptr));
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
        egsdge->setTitle(QApplication::translate("QtGuiClass", "Tessellation", nullptr));
        primitive_type->setTabText(primitive_type->indexOf(tab_3), QApplication::translate("QtGuiClass", "Sphere", nullptr));
        egsdge_2->setTitle(QApplication::translate("QtGuiClass", "Tessellation", nullptr));
        groupBox_13->setTitle(QApplication::translate("QtGuiClass", "Diameter", nullptr));
        primitive_type->setTabText(primitive_type->indexOf(tab_6), QApplication::translate("QtGuiClass", "GeoSphere", nullptr));
        egsdge_3->setTitle(QApplication::translate("QtGuiClass", "Tessellation", nullptr));
        groupBox_14->setTitle(QApplication::translate("QtGuiClass", "Diameter", nullptr));
        groupBox_15->setTitle(QApplication::translate("QtGuiClass", "Size", nullptr));
        label_20->setText(QApplication::translate("QtGuiClass", "X", nullptr));
        label_21->setText(QApplication::translate("QtGuiClass", "Y", nullptr));
        label_22->setText(QApplication::translate("QtGuiClass", "Z", nullptr));
        primitive_type->setTabText(primitive_type->indexOf(tab_7), QApplication::translate("QtGuiClass", "Capsule", nullptr));
        menuFile->setTitle(QApplication::translate("QtGuiClass", "File", nullptr));
    } // retranslateUi

};

namespace Ui {
    class QtGuiClass: public Ui_QtGuiClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTGUI_H
