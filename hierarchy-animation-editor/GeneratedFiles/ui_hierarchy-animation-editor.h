/********************************************************************************
** Form generated from reading UI file 'hierarchy-animation-editor.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HIERARCHY_2D_ANIMATION_2D_EDITOR_H
#define UI_HIERARCHY_2D_ANIMATION_2D_EDITOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
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
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_hierarchyanimationeditorClass
{
public:
    QAction *actionImport;
    QAction *actionExport;
    QWidget *centralWidget;
    QGroupBox *groupBox_2;
    QListWidget *parts_list;
    QCheckBox *wire_mode_check;
    QGroupBox *groupBox;
    QWidget *widget;
    QSlider *anim_slider;
    QWidget *horizontalLayoutWidget_3;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_8;
    QDoubleSpinBox *delta_time;
    QGroupBox *groupBox_3;
    QListWidget *animation_list;
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
    QWidget *horizontalLayoutWidget_5;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_9;
    QDoubleSpinBox *speed;
    QWidget *horizontalLayoutWidget_6;
    QHBoxLayout *horizontalLayout;
    QLabel *label_7;
    QSpinBox *anim_max;
    QGroupBox *rename_group;
    QLineEdit *rename_box;
    QPushButton *rename_button;
    QPushButton *play_button;
    QPushButton *pause_button;
    QCheckBox *loop_check;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *hierarchyanimationeditorClass)
    {
        if (hierarchyanimationeditorClass->objectName().isEmpty())
            hierarchyanimationeditorClass->setObjectName(QStringLiteral("hierarchyanimationeditorClass"));
        hierarchyanimationeditorClass->resize(1366, 781);
        actionImport = new QAction(hierarchyanimationeditorClass);
        actionImport->setObjectName(QStringLiteral("actionImport"));
        actionExport = new QAction(hierarchyanimationeditorClass);
        actionExport->setObjectName(QStringLiteral("actionExport"));
        centralWidget = new QWidget(hierarchyanimationeditorClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        groupBox_2 = new QGroupBox(centralWidget);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setEnabled(true);
        groupBox_2->setGeometry(QRect(1040, 70, 311, 321));
        QFont font;
        font.setFamily(QString::fromUtf8("\343\203\241\343\202\244\343\203\252\343\202\252"));
        groupBox_2->setFont(font);
        parts_list = new QListWidget(groupBox_2);
        parts_list->setObjectName(QStringLiteral("parts_list"));
        parts_list->setGeometry(QRect(10, 30, 291, 281));
        wire_mode_check = new QCheckBox(centralWidget);
        wire_mode_check->setObjectName(QStringLiteral("wire_mode_check"));
        wire_mode_check->setGeometry(QRect(30, 600, 141, 31));
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
        anim_slider = new QSlider(centralWidget);
        anim_slider->setObjectName(QStringLiteral("anim_slider"));
        anim_slider->setGeometry(QRect(220, 670, 641, 22));
        anim_slider->setMaximum(4);
        anim_slider->setPageStep(1);
        anim_slider->setTracking(true);
        anim_slider->setOrientation(Qt::Horizontal);
        anim_slider->setInvertedAppearance(false);
        anim_slider->setInvertedControls(false);
        anim_slider->setTickPosition(QSlider::TicksBelow);
        anim_slider->setTickInterval(0);
        horizontalLayoutWidget_3 = new QWidget(centralWidget);
        horizontalLayoutWidget_3->setObjectName(QStringLiteral("horizontalLayoutWidget_3"));
        horizontalLayoutWidget_3->setGeometry(QRect(30, 560, 151, 32));
        horizontalLayout_4 = new QHBoxLayout(horizontalLayoutWidget_3);
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        label_8 = new QLabel(horizontalLayoutWidget_3);
        label_8->setObjectName(QStringLiteral("label_8"));
        QFont font2;
        font2.setFamily(QString::fromUtf8("\343\203\241\343\202\244\343\203\252\343\202\252"));
        font2.setPointSize(9);
        label_8->setFont(font2);

        horizontalLayout_4->addWidget(label_8);

        delta_time = new QDoubleSpinBox(horizontalLayoutWidget_3);
        delta_time->setObjectName(QStringLiteral("delta_time"));
        delta_time->setWrapping(false);
        delta_time->setProperty("showGroupSeparator", QVariant(false));
        delta_time->setDecimals(2);
        delta_time->setMaximum(10);
        delta_time->setSingleStep(0.01);

        horizontalLayout_4->addWidget(delta_time);

        groupBox_3 = new QGroupBox(centralWidget);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        groupBox_3->setGeometry(QRect(10, 10, 191, 541));
        groupBox_3->setFont(font);
        animation_list = new QListWidget(groupBox_3);
        animation_list->setObjectName(QStringLiteral("animation_list"));
        animation_list->setGeometry(QRect(10, 30, 171, 421));
        add_button = new QPushButton(groupBox_3);
        add_button->setObjectName(QStringLiteral("add_button"));
        add_button->setGeometry(QRect(10, 460, 171, 31));
        add_button->setFont(font);
        delete_button = new QPushButton(groupBox_3);
        delete_button->setObjectName(QStringLiteral("delete_button"));
        delete_button->setEnabled(false);
        delete_button->setGeometry(QRect(10, 500, 171, 31));
        delete_button->setFont(font);
        transform_group = new QGroupBox(centralWidget);
        transform_group->setObjectName(QStringLiteral("transform_group"));
        transform_group->setEnabled(false);
        transform_group->setGeometry(QRect(1040, 400, 311, 211));
        transform_group->setFont(font);
        groupBox_4 = new QGroupBox(transform_group);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        groupBox_4->setGeometry(QRect(10, 20, 291, 61));
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
        groupBox_5->setGeometry(QRect(10, 80, 291, 61));
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
        groupBox_6->setGeometry(QRect(10, 140, 291, 61));
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

        horizontalLayoutWidget_5 = new QWidget(centralWidget);
        horizontalLayoutWidget_5->setObjectName(QStringLiteral("horizontalLayoutWidget_5"));
        horizontalLayoutWidget_5->setGeometry(QRect(1040, 620, 141, 32));
        horizontalLayout_6 = new QHBoxLayout(horizontalLayoutWidget_5);
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        horizontalLayout_6->setContentsMargins(0, 0, 0, 0);
        label_9 = new QLabel(horizontalLayoutWidget_5);
        label_9->setObjectName(QStringLiteral("label_9"));
        QFont font3;
        font3.setFamily(QString::fromUtf8("\343\203\241\343\202\244\343\203\252\343\202\252"));
        font3.setPointSize(12);
        label_9->setFont(font3);

        horizontalLayout_6->addWidget(label_9);

        speed = new QDoubleSpinBox(horizontalLayoutWidget_5);
        speed->setObjectName(QStringLiteral("speed"));
        speed->setEnabled(false);
        speed->setWrapping(false);
        speed->setProperty("showGroupSeparator", QVariant(false));
        speed->setDecimals(3);
        speed->setMaximum(1);
        speed->setSingleStep(0.01);
        speed->setValue(0.01);

        horizontalLayout_6->addWidget(speed);

        horizontalLayoutWidget_6 = new QWidget(centralWidget);
        horizontalLayoutWidget_6->setObjectName(QStringLiteral("horizontalLayoutWidget_6"));
        horizontalLayoutWidget_6->setGeometry(QRect(890, 660, 131, 32));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget_6);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label_7 = new QLabel(horizontalLayoutWidget_6);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setEnabled(true);
        label_7->setFont(font3);

        horizontalLayout->addWidget(label_7);

        anim_max = new QSpinBox(horizontalLayoutWidget_6);
        anim_max->setObjectName(QStringLiteral("anim_max"));
        anim_max->setEnabled(false);
        anim_max->setMinimum(2);
        anim_max->setValue(5);

        horizontalLayout->addWidget(anim_max);

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
        play_button = new QPushButton(centralWidget);
        play_button->setObjectName(QStringLiteral("play_button"));
        play_button->setGeometry(QRect(20, 670, 41, 28));
        pause_button = new QPushButton(centralWidget);
        pause_button->setObjectName(QStringLiteral("pause_button"));
        pause_button->setEnabled(false);
        pause_button->setGeometry(QRect(70, 670, 51, 28));
        loop_check = new QCheckBox(centralWidget);
        loop_check->setObjectName(QStringLiteral("loop_check"));
        loop_check->setGeometry(QRect(130, 670, 61, 31));
        QFont font4;
        font4.setFamily(QString::fromUtf8("\343\203\241\343\202\244\343\203\252\343\202\252"));
        font4.setPointSize(9);
        font4.setBold(false);
        font4.setWeight(50);
        loop_check->setFont(font4);
        hierarchyanimationeditorClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(hierarchyanimationeditorClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1366, 26));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        hierarchyanimationeditorClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(hierarchyanimationeditorClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        hierarchyanimationeditorClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(hierarchyanimationeditorClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        hierarchyanimationeditorClass->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuFile->addAction(actionImport);
        menuFile->addAction(actionExport);

        retranslateUi(hierarchyanimationeditorClass);

        QMetaObject::connectSlotsByName(hierarchyanimationeditorClass);
    } // setupUi

    void retranslateUi(QMainWindow *hierarchyanimationeditorClass)
    {
        hierarchyanimationeditorClass->setWindowTitle(QApplication::translate("hierarchyanimationeditorClass", "Hierarchy Animation Editor", nullptr));
        actionImport->setText(QApplication::translate("hierarchyanimationeditorClass", "Import", nullptr));
        actionExport->setText(QApplication::translate("hierarchyanimationeditorClass", "Export", nullptr));
        groupBox_2->setTitle(QApplication::translate("hierarchyanimationeditorClass", "Parts", nullptr));
        wire_mode_check->setText(QApplication::translate("hierarchyanimationeditorClass", "WireMode", nullptr));
        groupBox->setTitle(QApplication::translate("hierarchyanimationeditorClass", "Game Screen", nullptr));
        label_8->setText(QApplication::translate("hierarchyanimationeditorClass", "DeltaTime", nullptr));
        groupBox_3->setTitle(QApplication::translate("hierarchyanimationeditorClass", "Animation", nullptr));
        add_button->setText(QApplication::translate("hierarchyanimationeditorClass", "Add", nullptr));
        delete_button->setText(QApplication::translate("hierarchyanimationeditorClass", "Delete", nullptr));
        transform_group->setTitle(QApplication::translate("hierarchyanimationeditorClass", "Transform", nullptr));
        groupBox_4->setTitle(QApplication::translate("hierarchyanimationeditorClass", "Position", nullptr));
        label_3->setText(QApplication::translate("hierarchyanimationeditorClass", "X", nullptr));
        label_2->setText(QApplication::translate("hierarchyanimationeditorClass", "Y", nullptr));
        label->setText(QApplication::translate("hierarchyanimationeditorClass", "Z", nullptr));
        groupBox_5->setTitle(QApplication::translate("hierarchyanimationeditorClass", "Rotation", nullptr));
        label_4->setText(QApplication::translate("hierarchyanimationeditorClass", "X", nullptr));
        label_5->setText(QApplication::translate("hierarchyanimationeditorClass", "Y", nullptr));
        label_6->setText(QApplication::translate("hierarchyanimationeditorClass", "Z", nullptr));
        groupBox_6->setTitle(QApplication::translate("hierarchyanimationeditorClass", "Scale", nullptr));
        label_10->setText(QApplication::translate("hierarchyanimationeditorClass", "X", nullptr));
        label_11->setText(QApplication::translate("hierarchyanimationeditorClass", "Y", nullptr));
        label_12->setText(QApplication::translate("hierarchyanimationeditorClass", "Z", nullptr));
        label_9->setText(QApplication::translate("hierarchyanimationeditorClass", "Speed", nullptr));
        label_7->setText(QApplication::translate("hierarchyanimationeditorClass", "Max:", nullptr));
        rename_group->setTitle(QApplication::translate("hierarchyanimationeditorClass", "Name", nullptr));
        rename_button->setText(QApplication::translate("hierarchyanimationeditorClass", "Rename", nullptr));
        play_button->setText(QApplication::translate("hierarchyanimationeditorClass", "Play", nullptr));
        pause_button->setText(QApplication::translate("hierarchyanimationeditorClass", "Pause", nullptr));
        loop_check->setText(QApplication::translate("hierarchyanimationeditorClass", "Loop", nullptr));
        menuFile->setTitle(QApplication::translate("hierarchyanimationeditorClass", "File", nullptr));
    } // retranslateUi

};

namespace Ui {
    class hierarchyanimationeditorClass: public Ui_hierarchyanimationeditorClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HIERARCHY_2D_ANIMATION_2D_EDITOR_H
