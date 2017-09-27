/********************************************************************************
** Form generated from reading UI file 'paint.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PAINT_H
#define UI_PAINT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PaintClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *PaintClass)
    {
        if (PaintClass->objectName().isEmpty())
            PaintClass->setObjectName(QStringLiteral("PaintClass"));
        PaintClass->resize(600, 400);
        menuBar = new QMenuBar(PaintClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        PaintClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(PaintClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        PaintClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(PaintClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        PaintClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(PaintClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        PaintClass->setStatusBar(statusBar);

        retranslateUi(PaintClass);

        QMetaObject::connectSlotsByName(PaintClass);
    } // setupUi

    void retranslateUi(QMainWindow *PaintClass)
    {
        PaintClass->setWindowTitle(QApplication::translate("PaintClass", "Paint", 0));
    } // retranslateUi

};

namespace Ui {
    class PaintClass: public Ui_PaintClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PAINT_H
