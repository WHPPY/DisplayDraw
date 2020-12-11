/********************************************************************************
** Form generated from reading UI file 'form.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORM_H
#define UI_FORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Form
{
public:
    QPushButton *sendBtn;
    QPushButton *closeBtn;
    QLabel *label;
    QLineEdit *lineEdit_waistline;
    QLabel *label_2;
    QLineEdit *lineEdit_hipline;
    QLabel *label_3;
    QLineEdit *lineEdit_crotchdepth;
    QLabel *label_4;
    QLineEdit *lineEdit_TrouserLength;
    QLabel *label_5;
    QLineEdit *lineEdit_SweepBottom;

    void setupUi(QWidget *Form)
    {
        if (Form->objectName().isEmpty())
            Form->setObjectName(QStringLiteral("Form"));
        Form->resize(276, 289);
        sendBtn = new QPushButton(Form);
        sendBtn->setObjectName(QStringLiteral("sendBtn"));
        sendBtn->setGeometry(QRect(40, 240, 75, 23));
        closeBtn = new QPushButton(Form);
        closeBtn->setObjectName(QStringLiteral("closeBtn"));
        closeBtn->setGeometry(QRect(150, 240, 75, 23));
        label = new QLabel(Form);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(30, 30, 71, 16));
        lineEdit_waistline = new QLineEdit(Form);
        lineEdit_waistline->setObjectName(QStringLiteral("lineEdit_waistline"));
        lineEdit_waistline->setGeometry(QRect(110, 30, 113, 20));
        label_2 = new QLabel(Form);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(40, 70, 54, 12));
        lineEdit_hipline = new QLineEdit(Form);
        lineEdit_hipline->setObjectName(QStringLiteral("lineEdit_hipline"));
        lineEdit_hipline->setGeometry(QRect(110, 70, 113, 20));
        label_3 = new QLabel(Form);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(30, 110, 81, 16));
        lineEdit_crotchdepth = new QLineEdit(Form);
        lineEdit_crotchdepth->setObjectName(QStringLiteral("lineEdit_crotchdepth"));
        lineEdit_crotchdepth->setGeometry(QRect(110, 110, 113, 20));
        label_4 = new QLabel(Form);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(20, 150, 91, 16));
        lineEdit_TrouserLength = new QLineEdit(Form);
        lineEdit_TrouserLength->setObjectName(QStringLiteral("lineEdit_TrouserLength"));
        lineEdit_TrouserLength->setGeometry(QRect(110, 150, 113, 20));
        label_5 = new QLabel(Form);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(30, 190, 81, 16));
        lineEdit_SweepBottom = new QLineEdit(Form);
        lineEdit_SweepBottom->setObjectName(QStringLiteral("lineEdit_SweepBottom"));
        lineEdit_SweepBottom->setGeometry(QRect(110, 190, 113, 20));

        retranslateUi(Form);

        QMetaObject::connectSlotsByName(Form);
    } // setupUi

    void retranslateUi(QWidget *Form)
    {
        Form->setWindowTitle(QApplication::translate("Form", "Measuring items", 0));
        sendBtn->setText(QApplication::translate("Form", "OK", 0));
        closeBtn->setText(QApplication::translate("Form", "Cancel", 0));
        label->setText(QApplication::translate("Form", "Waist Girth", 0));
        lineEdit_waistline->setText(QApplication::translate("Form", "68", 0));
        label_2->setText(QApplication::translate("Form", "Hip Girth:", 0));
        lineEdit_hipline->setText(QApplication::translate("Form", "98", 0));
        label_3->setText(QApplication::translate("Form", "Crotch Depth", 0));
        lineEdit_crotchdepth->setText(QApplication::translate("Form", "28", 0));
        label_4->setText(QApplication::translate("Form", "Trouser Length", 0));
        lineEdit_TrouserLength->setText(QApplication::translate("Form", "104", 0));
        label_5->setText(QApplication::translate("Form", "Slack Bottom", 0));
        lineEdit_SweepBottom->setText(QApplication::translate("Form", "20", 0));
    } // retranslateUi

};

namespace Ui {
    class Form: public Ui_Form {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORM_H
