/********************************************************************************
** Form generated from reading UI file 'kalokairi.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_KALOKAIRI_H
#define UI_KALOKAIRI_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_KalokairiClass
{
public:
    QAction *actionLaunch;
    QAction *actionReset;
    QAction *actionShutdown;
    QWidget *centralWidget;

    void setupUi(QMainWindow *KalokairiClass)
    {
        if (KalokairiClass->objectName().isEmpty())
            KalokairiClass->setObjectName(QStringLiteral("KalokairiClass"));
        KalokairiClass->setWindowModality(Qt::ApplicationModal);
        KalokairiClass->resize(1280, 746);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(KalokairiClass->sizePolicy().hasHeightForWidth());
        KalokairiClass->setSizePolicy(sizePolicy);
        KalokairiClass->setWindowOpacity(1);
        KalokairiClass->setDockOptions(QMainWindow::AllowTabbedDocks|QMainWindow::AnimatedDocks);
        actionLaunch = new QAction(KalokairiClass);
        actionLaunch->setObjectName(QStringLiteral("actionLaunch"));
        actionReset = new QAction(KalokairiClass);
        actionReset->setObjectName(QStringLiteral("actionReset"));
        actionShutdown = new QAction(KalokairiClass);
        actionShutdown->setObjectName(QStringLiteral("actionShutdown"));
        centralWidget = new QWidget(KalokairiClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        sizePolicy.setHeightForWidth(centralWidget->sizePolicy().hasHeightForWidth());
        centralWidget->setSizePolicy(sizePolicy);
        KalokairiClass->setCentralWidget(centralWidget);

        retranslateUi(KalokairiClass);

        QMetaObject::connectSlotsByName(KalokairiClass);
    } // setupUi

    void retranslateUi(QMainWindow *KalokairiClass)
    {
        KalokairiClass->setWindowTitle(QApplication::translate("KalokairiClass", "Kalokairi", nullptr));
        actionLaunch->setText(QApplication::translate("KalokairiClass", "Launch", nullptr));
        actionReset->setText(QApplication::translate("KalokairiClass", "Reset", nullptr));
        actionShutdown->setText(QApplication::translate("KalokairiClass", "Shutdown", nullptr));
    } // retranslateUi

};

namespace Ui {
    class KalokairiClass: public Ui_KalokairiClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_KALOKAIRI_H
