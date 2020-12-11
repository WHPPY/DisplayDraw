#include "form.h"
#include "ui_form.h"

#include <QDebug>


Form::Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);

	connect(ui->sendBtn, SIGNAL(clicked()), this, SLOT(OKProc()));
	connect(ui->closeBtn, SIGNAL(clicked()), this, SLOT(close()));
}

Form::~Form()
{
    delete ui;
}

void Form::OKProc()
{
	//获取文本框的信息
	QString t_waistGirth = ui->lineEdit_waistline->text();
	QString t_hipGirth = ui->lineEdit_hipline->text();
	QString t_crotchDepth = ui->lineEdit_crotchdepth->text();
	QString t_trousersLength = ui->lineEdit_TrouserLength->text();
	QString t_sweepBottom = ui->lineEdit_SweepBottom->text();

	if (t_waistGirth.isEmpty() || t_hipGirth.isEmpty() || t_crotchDepth.isEmpty() || t_trousersLength.isEmpty() || t_sweepBottom.isEmpty())
	{
		QMessageBox::information(this,"Information","The information in the text box cannot be empty!",QMessageBox::Ok);
		qDebug() << "The information in the text box cannot be empty!" << endl;
		return;
	}

	qDebug() << QString::fromLocal8Bit("Send Information：");
	qDebug() << QString::fromLocal8Bit("waist_girth:") << t_waistGirth << QString::fromLocal8Bit("hio girth:") << t_hipGirth 
		<< QString::fromLocal8Bit("crotch depth:") << t_crotchDepth << QString::fromLocal8Bit("trouser length:") << t_trousersLength << QString::fromLocal8Bit("sweep bottom:") << t_sweepBottom << endl;

	//发送信息
	emit sendInfo(t_waistGirth, t_hipGirth, t_crotchDepth, t_trousersLength, t_sweepBottom);
	
	this->close();

}