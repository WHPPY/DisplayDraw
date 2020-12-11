/********************************************************************************
** Form generated from reading UI file 'myqt2020.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MYQT2020_H
#define UI_MYQT2020_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_myQt2020Class
{
public:
    QAction *actionNew_N;
    QAction *actionOpen_O;
    QAction *actionSave_S;
    QAction *actionLine_Edit;
    QAction *actionCurve_Edit;
    QWidget *centralWidget;
    QMenuBar *menuBar;
    QMenu *menuFile_F;
    QMenu *menuEdit;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *myQt2020Class)
    {
        if (myQt2020Class->objectName().isEmpty())
            myQt2020Class->setObjectName(QStringLiteral("myQt2020Class"));
        myQt2020Class->resize(800, 650);
        actionNew_N = new QAction(myQt2020Class);
        actionNew_N->setObjectName(QStringLiteral("actionNew_N"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/myQt2020/images/new.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionNew_N->setIcon(icon);
        actionOpen_O = new QAction(myQt2020Class);
        actionOpen_O->setObjectName(QStringLiteral("actionOpen_O"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/myQt2020/images/open.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionOpen_O->setIcon(icon1);
        actionSave_S = new QAction(myQt2020Class);
        actionSave_S->setObjectName(QStringLiteral("actionSave_S"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/myQt2020/images/save.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSave_S->setIcon(icon2);
        actionLine_Edit = new QAction(myQt2020Class);
        actionLine_Edit->setObjectName(QStringLiteral("actionLine_Edit"));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/myQt2020/images/tool.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionLine_Edit->setIcon(icon3);
        actionCurve_Edit = new QAction(myQt2020Class);
        actionCurve_Edit->setObjectName(QStringLiteral("actionCurve_Edit"));
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/myQt2020/images/rotate.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionCurve_Edit->setIcon(icon4);
        centralWidget = new QWidget(myQt2020Class);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        myQt2020Class->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(myQt2020Class);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 800, 23));
        menuFile_F = new QMenu(menuBar);
        menuFile_F->setObjectName(QStringLiteral("menuFile_F"));
        menuEdit = new QMenu(menuBar);
        menuEdit->setObjectName(QStringLiteral("menuEdit"));
        myQt2020Class->setMenuBar(menuBar);
        mainToolBar = new QToolBar(myQt2020Class);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        myQt2020Class->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(myQt2020Class);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        statusBar->setAutoFillBackground(false);
        myQt2020Class->setStatusBar(statusBar);

        menuBar->addAction(menuFile_F->menuAction());
        menuBar->addAction(menuEdit->menuAction());
        menuFile_F->addAction(actionNew_N);
        menuFile_F->addAction(actionOpen_O);
        menuFile_F->addSeparator();
        menuFile_F->addAction(actionSave_S);
        menuEdit->addAction(actionLine_Edit);
        menuEdit->addSeparator();
        menuEdit->addAction(actionCurve_Edit);

        retranslateUi(myQt2020Class);

        QMetaObject::connectSlotsByName(myQt2020Class);
    } // setupUi

    void retranslateUi(QMainWindow *myQt2020Class)
    {
        myQt2020Class->setWindowTitle(QApplication::translate("myQt2020Class", "myQt2020", 0));
        actionNew_N->setText(QApplication::translate("myQt2020Class", "New(N)", 0));
        actionOpen_O->setText(QApplication::translate("myQt2020Class", "Open(O)", 0));
        actionSave_S->setText(QApplication::translate("myQt2020Class", "Save(S)", 0));
        actionLine_Edit->setText(QApplication::translate("myQt2020Class", "Line Edit", 0));
        actionCurve_Edit->setText(QApplication::translate("myQt2020Class", "Curve Edit", 0));
        menuFile_F->setTitle(QApplication::translate("myQt2020Class", "File(F)", 0));
        menuEdit->setTitle(QApplication::translate("myQt2020Class", "Edit(E)", 0));
    } // retranslateUi

};

namespace Ui {
    class myQt2020Class: public Ui_myQt2020Class {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MYQT2020_H
