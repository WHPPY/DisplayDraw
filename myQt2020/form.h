#ifndef FORM_H
#define FORM_H

#include <QWidget>
#include <QMessageBox>
#include <QLabel>

namespace Ui {
class Form;
}

class Form : public QWidget
{
    Q_OBJECT

public:
    explicit Form(QWidget *parent = 0);
    ~Form();
	
public slots:
	void OKProc();
signals:
	void sendInfo(const QString &t_waistGirth, const QString &t_hipGirth, 
		const QString &t_crotchDepth, const QString &t_trousersLength, const QString &t_sweepBottom);

private:
    Ui::Form *ui;

//private:
//	void createInterface();
//
//private:
//	QLabel *m_nameLabel;
};

#endif // FORM_H
