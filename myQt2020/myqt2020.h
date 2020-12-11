#ifndef MYQT2020_H
#define MYQT2020_H

#include <QtWidgets/QMainWindow>
#include "ui_myqt2020.h"
#include "GraphBase.h"
#include "figureobj.h"
#include "lineseg.h"
#include <vector>
#include "typeshape.h"
#include <QScrollArea>
#include "form.h"
#include <QDebug>
#include <QAction>
#include <iostream>
#include <map>
#include <math.h>
#include <cmath>
#include "listdg.h"
#include "beziercurve.h"
#include "rectseg.h"

#define PI 3.1415

using namespace std;
class QMouseEvent;
class QPaintEvent;

class myQt2020 : public QMainWindow
{
	Q_OBJECT

public:
	myQt2020(QWidget *parent = 0);
	~myQt2020();

	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);

	void paintEvent(QPaintEvent *event);

private:
	void drawLineSeg(QPainter *p);
	void drawCurveLineSeg(QPainter *p);
	void drawRectSeg(QPainter *p);

	void selSeg(QPointF &pt);
	void selCurveSeg(QPointF &pt);
	void selRectSeg(QPointF &pt);
	void initEntity(const float &input_f_waistline, const float &input_f_hipline, const float &input_f_crotchDepth, const float &input_f_trousersLength, const float &input_f_sweepBottom);

	void CreateBezierCurve();
	void CalBezierCurvePoint(float t, PointEx &stPt);

	void findLineSegs(int i);


private slots:
	void recvInfo(const QString &t_waistGirth, const QString &t_hipGirth,\
		const QString &t_crotchDepth, const QString &t_trousersLength, const QString &t_sweepBottom);
	void changeSL(bool boolValue);
	void changeCL(bool boolValue);
	void showBP(bool boolValue);
	void showFP(bool boolValue);
	void savePicture();
//
//private:
//	QAction *openAction;


private:
	Ui::myQt2020Class ui;
	Form m_form;

	bool islineEdit = true;
	bool bLBtnDown = false;//左键按下
	bool ispainting = false;
	bool bPainting_BP = true;
	bool bPainting_FP = true;

	QPointF startPoint, endPoint;//绘制线的起点和终点

	QPointF beginPoint; //绘制矩形的起点
	QPointF curveCtrlPt2; //曲线的第二个控制点
	QPointF curveCtrlPt3; //曲线的第三个控制点

	std::vector<PointEx> m_vecBezierCurvePt;
	std::vector<PointEx> m_vecBezierCurvePtCtrls;

	std::vector<PointEx> ptCurCtrls;

	CBEZIERCURVE* onebezierCurveLine;

	//ListDG *pG;

	QList<QPoint> ptCtrls;

	QImage image; //QImage类对象，用于其上绘图
	QRgb backColor; //QRgb颜色对象，存储image的背景颜色


	std::vector<string> vec_DfsRet; //返回DFS遍历结果

	LINESEG* tempLine01 = nullptr;
	LINESEG* tempLine12 = nullptr;
	LINESEG* tempLine03 = nullptr;
	LINESEG* tempLine14 = nullptr;
	LINESEG* tempLine15 = nullptr;
	LINESEG* tempLine56 = nullptr;
	LINESEG* tempLine67 = nullptr;
	LINESEG* tempLine68 = nullptr;
	LINESEG* tempLine59 = nullptr;
	LINESEG* tempLine710 = nullptr;
	LINESEG* tempLine610 = nullptr;
	LINESEG* tempLine1011 = nullptr;
	LINESEG* tempLine312 = nullptr;
	LINESEG* tempLine413 = nullptr;
	LINESEG* tempLine314 = nullptr;
	LINESEG* tempLine415 = nullptr;
	LINESEG* tempLine516 = nullptr;
	LINESEG* tempLine1617 = nullptr;
	LINESEG* tempLine1618 = nullptr;
	LINESEG* tempLine1619 = nullptr;
	LINESEG* tempLine1820 = nullptr;
	LINESEG* tempLine2021 = nullptr;
	LINESEG* tempLine2122 = nullptr;
	LINESEG* tempLine923 = nullptr;
	LINESEG* tempLine920 = nullptr;
	LINESEG* tempLine2324 = nullptr;
	LINESEG* tempLine1921 = nullptr;
	LINESEG* tempLine1725 = nullptr;
	LINESEG* tempLine1226 = nullptr;
	LINESEG* tempLine1327 = nullptr;
	LINESEG* tempLine1428 = nullptr;
	LINESEG* tempLine1529 = nullptr;
	LINESEG* tempLine2627 = nullptr;
	LINESEG* tempLine2829 = nullptr;

	LINESEG* tempLineinseamline2 = nullptr;
	LINESEG* tempLineseamline3 = nullptr;

	CBEZIERCURVE* tempcrothbendline = nullptr;
	CBEZIERCURVE* tempseamsideline = nullptr;
	CBEZIERCURVE* tempseamsideline2 = nullptr;
	CBEZIERCURVE* tempseamsideline3 = nullptr;
	CBEZIERCURVE* tempseamsideline4 = nullptr;
	CBEZIERCURVE* tempinternalsideline = nullptr;
	CBEZIERCURVE* tempinseamline1 = nullptr;
	CBEZIERCURVE* tempinseamline2 = nullptr;
	CBEZIERCURVE* temprearcrotcharc = nullptr;
	

	CurveLineSegment*  onebezierLineSeg = nullptr;

	RECTSEG* tempRect = nullptr;
	std::vector<RECTSEG*> rectSegs;//rectangle list
	std::vector<LINESEG*> lineSegs; //line segments
	std::vector<LINESEG*> dfsRelationLines; //dfs traverse list
	std::vector<string> dfsRelVids; //dfs traverse node ID
	std::vector<CBEZIERCURVE*> bezierCurvelineSegs; //curve lines

	/*std::map<LINESEG, std::vector<LINESEG*>> getSeleledMapItem;*/

	RECTSEG* selectRectSeg = nullptr;//selected rectangle
	LINESEG* selectLineSeg = nullptr;//selected linesegment
	CBEZIERCURVE* selectCurveLineSeg = nullptr; //selected curveline


	//LINESEG* getSeleled();//Get the selected line segment
	int getSeleled();//Get the selected line segment
	CBEZIERCURVE* getSeleledCurve();//Get the selected curve
	RECTSEG* getSeleledRectSeg(); //Get the selected rectangle

	float GetCross(PointEx p1, PointEx p2, PointEx p);
	
	QPointF movePoint;
	QPointF moveRectPoint;
	QPointF moveCtrlPoint;

	float input_f_waistline = 0.0f;
	float input_f_hipline = 0.0f;
	float input_f_crotchDepth = 0.0f;
	float input_f_trousersLength = 0.0f;
	float input_f_sweepBottom = 0.0f;

	QString m_waistline;
	QString m_hipline;
	QString m_crotchDepth;
	QString m_trousersLength;
	QString m_sweepBottom;

	float x_0, y_0;
	float x_1, y_1;
	float x_2, y_2;
	float x_3, y_3;
	float x_4, y_4;
	float x_5, y_5;
	float x_6, y_6;
	float x_7, y_7;
	float x_8, y_8;
	float x_9, y_9;
	float x_10, y_10;
	float x_11, y_11;
	float x_12, y_12;
	float x_13, y_13;
	float x_14, y_14;
	float x_15, y_15;

	float x_16, y_16;
	float x_17, y_17;
	float x_18, y_18;
	float x_19, y_19;
	float x_20, y_20;
	float x_21, y_21;
	float x_22, y_22;
	float x_23, y_23;
	float x_24, y_24;
	float x_25, y_25;
	float x_26, y_26;
	float x_27, y_27;
	float x_28, y_28;
	float x_29, y_29;


	int selLineId; //选中的直线Id
	int selCurveLineId = -1; //选中的曲线Id
	string selEntityVert; //选中的实体Point
};

#endif // MYQT2020_H
