#ifndef SCREENWIDGET_H
#define SCREENWIDGET_H

#include <QWidget>
#include <QMenu>
#include <QPoint>
#include <QSize>
#include <QScrollArea>

//����������
class Screen
{
public:
	enum STATUS { SELECT, MOV, SET_W_H };
	Screen() {}
	Screen(QSize size);

	void setStart(QPoint pos);
	void setEnd(QPoint pos);
	QPoint getStart();
	QPoint getEnd();

	QPoint getLeftUp();
	QPoint getRightDown();

	STATUS getStatus();
	void setStatus(STATUS status);

	int width();
	int height();
	bool isInArea(QPoint pos);          // ���pos�Ƿ��ڽ�ͼ������
	void move(QPoint p);                // �� p �ƶ���ͼ����

private:
	QPoint leftUpPos, rightDownPos;     //��¼ ��ͼ���� ���Ͻǡ����½�
	QPoint startPos, endPos;            //��¼ ��꿪ʼλ�á�����λ��
	int maxWidth, maxHeight;            //��¼��Ļ��С
	STATUS status;                      //����״̬: ѡ�������ƶ���������width height

	void cmpPoint(QPoint &s, QPoint &e);//�Ƚ���λ�ã��ж����Ͻǡ����½�
};

class QMouseEvent;
class QPaintEvent;
//����������
class ScreenWidget : public QWidget
{
	Q_OBJECT
public:
	static ScreenWidget *Instance();
	explicit ScreenWidget(QWidget *parent = 0);

private:
	static QScopedPointer<ScreenWidget> self;
	QMenu *menu;            //�Ҽ��˵�����
	Screen *screen;         //��������
	QPixmap *fullScreen;    //����ȫ��ͼ��
	QPixmap *bgScreen;      //ģ������ͼ
	QPoint movPos;          //����

protected:
	void contextMenuEvent(QContextMenuEvent *);
	void mousePressEvent(QMouseEvent *);
	void mouseMoveEvent(QMouseEvent *);
	void mouseReleaseEvent(QMouseEvent *);
	void paintEvent(QPaintEvent *);
	void showEvent(QShowEvent *);

	private slots:
	void saveScreen();
	void saveFullScreen();
	void saveScreenOther();
	void saveFullOther();
};
#endif // SCREENWIDGET_H