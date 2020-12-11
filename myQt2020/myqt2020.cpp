#include "myqt2020.h"
#include <QMouseEvent>
#include <QPaintEvent>
#include <QPainter>
#include <QDebug>
#include <math.h>
#include <cmath>
#include <QAction>
#include <qtoolbar.h>
#include <string>
#include <sstream>
#include <QApplication>
#include <QTextCodec>

#include "ScreenWidget.h"

myQt2020::myQt2020(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	ui.centralWidget->setMouseTracking(true);
	setMouseTracking(true);

	image = QImage(800, 800, QImage::Format_RGB32);
	backColor = qRgb(255, 255, 255);
	image.fill(backColor);

	QToolBar *pToolBar = ui.mainToolBar;

	beginPoint = QPointF(400, 100);

	

	//string vexs[] = { "V1", "V2", "V3", "V4", "V5" , "V6", "V7", "V8", "V9", "V10", "V11", "V12", "V13", "V14", "V15",
	//	"V16", "V17", "V18", "V19", "V20", "V21", "V22", "V23", "V24", "V25"};
	//string edges[][2] = {
	//		{ "V1", "V2" },
	//		{ "V1", "V3" },
	//		{ "V1", "V4" },
	//		{ "V1", "V5" },
	//		{ "V2", "V5" },
	//		{ "V2", "V14" },
	//		{ "V3", "V4" },
	//		{ "V3", "V10" },
	//		{ "V3", "V12" },
	//		{ "V4", "V11" },
	//		{ "V4", "V13" },
	//		{ "V5", "V6" },
	//		{ "V5", "V7" },
	//		{ "V5", "V8" },
	//		{ "V5", "V14" },
	//		{ "V7", "V19" },
	//		{ "V8", "V9" },
	//		{ "V10", "V22" },
	//		{ "V11", "V23" },
	//		{ "V12", "V24" },
	//		{ "V13", "V25" },
	//		{ "V14", "V16" },
	//		{ "V14", "V15" },
	//		{ "V14", "V21" },
	//		{ "V15", "V20" },
	//		{ "V16", "V17" },
	//		{ "V17", "V18" },
	//		{ "V18", "V20" },
	//		{ "V19", "V20" } };
	//int vlen = sizeof(vexs) / sizeof(vexs[0]);
	//int elen = sizeof(edges) / sizeof(edges[0]);

	//pG = new ListDG(vexs, vlen, edges, elen);
	//pG->print();
	
	
	/*int idx = 0;
	pG->DFS(idx);*/

	//std::cout << "ItemType:" << ItemType_Aux_line << std::endl;
	connect(ui.actionOpen_O, SIGNAL(triggered()), &m_form, SLOT(show()));
	connect(&m_form, SIGNAL(sendInfo(QString, QString, QString, QString, QString)), this, SLOT(recvInfo(QString, QString, QString, QString, QString)));


	connect(ui.actionLine_Edit, SIGNAL(triggered(bool)), this, SLOT(changeSL(bool)));
	connect(ui.actionCurve_Edit, SIGNAL(triggered(bool)), this, SLOT(changeCL(bool)));

	
	QAction *pOpenAction = new QAction(QIcon(":/myQt2020/images/popen.png"), "Open", this);
	pToolBar->addAction(pOpenAction);
	connect(pOpenAction, SIGNAL(triggered()), &m_form, SLOT(show()));

	QAction *pSLAction = new QAction(QIcon(":/myQt2020/images/line.png"), "LineEdit", this);
	QAction *pCLAction = new QAction(QIcon(":/myQt2020/images/curve.png"), "CurveEdit", this);

	pSLAction->setCheckable(true);
	connect(pSLAction, SIGNAL(triggered(bool)), this, SLOT(changeSL(bool)));

	pCLAction->setCheckable(false);
	connect(pCLAction, SIGNAL(triggered(bool)), this, SLOT(changeCL(bool)));
	
	pToolBar->addAction(pCLAction);
	pToolBar->addAction(pSLAction);

	QAction *pSaveAction = new QAction(QIcon(":/myQt2020/images/save.png"), "ScreenShot", this);
	connect(pSaveAction, SIGNAL(triggered()), this, SLOT(savePicture()));
	connect(ui.actionSave_S, SIGNAL(triggered()), this, SLOT(savePicture()));
	pToolBar->addAction(pSaveAction);

	QAction *pShowBackPatternAction = new QAction(QIcon(":/myQt2020/images/back.png"), "Back Pattern", this);
	pShowBackPatternAction->setCheckable(false);
	connect(pShowBackPatternAction, SIGNAL(triggered(bool)), this, SLOT(showBP(bool)));
	pToolBar->addAction(pShowBackPatternAction);

	QAction *pShowFrontPatternAction = new QAction(QIcon(":/myQt2020/images/front.png"), "Front Pattern", this);
	pShowFrontPatternAction->setCheckable(false);
	connect(pShowFrontPatternAction, SIGNAL(triggered(bool)), this, SLOT(showFP(bool)));
	pToolBar->addAction(pShowFrontPatternAction);


	ui.statusBar->showMessage(QStringLiteral("@zjut 2019-09"));
	this->setWindowTitle(tr("DisplayDraw"));
	setWindowIcon(QIcon(":/myQt2020/images/pshowaxis.png"));
}

myQt2020::~myQt2020()
{

}

void myQt2020::initEntity(const float &input_f_waistline, const float &input_f_hipline, const float &input_f_crotchDepth, const float &input_f_trousersLength, const float &input_f_sweepBottom)
{
	int scale = 5;

	x_0 = beginPoint.x();
	y_0 = beginPoint.y();

	x_1 = x_0;
	y_1 = (y_0 + input_f_crotchDepth * scale);

	x_2 = x_0;
	y_2 = y_1 - (y_1 - y_0) / 3;

	x_3 = x_0;
	y_3 = y_0 + input_f_trousersLength*scale;

	x_4 = x_0;
	y_4 = y_1 + (y_3 - y_1) / 2 - 5 * scale;

	x_5 = x_1 - (input_f_hipline / 12 + 1) * scale;
	y_5 = y_1;

	x_6 = x_5;
	y_6 = y_2;

	x_7 = x_6;
	y_7 = y_0;

	x_8 = x_6 + (input_f_hipline / 4 - 0.5) * scale;
	y_8 = y_2;

	x_9 = x_5 - (input_f_hipline / 16) * scale;
	y_9 = y_1;

	x_10 = x_7 + scale;
	y_10 = y_0;

	x_11 = x_10 + (input_f_waistline / 4 - 0.5 + 2) * scale;
	y_11 = y_0;

	x_12 = x_3 + (input_f_sweepBottom / 2 - 0.5) * scale;
	y_12 = y_3;

	x_13 = x_4 + (input_f_sweepBottom / 2 - 0.5 + 1.5) * scale;
	y_13 = y_4;

	x_14 = x_3 - (input_f_sweepBottom / 2 - 0.5) * scale;
	y_14 = y_3;

	x_15 = x_4 - (input_f_sweepBottom / 2 - 0.5 + 1.5) * scale;
	y_15 = y_4;

	x_16 = x_5 + (x_1 - x_5) / 4;
	y_16 = y_1;

	x_17 = x_16;
	y_17 = y_2;

	x_18 = x_16;
	y_18 = y_0;

	x_19 = x_16;
	y_19 = y_18 + (y_16 - y_18) / 2;

	x_20 = x_18 + 2*scale;
	y_20 = y_0;

	float mlen_p19p18 = sqrt(pow((x_19 - x_18), 2) + pow((y_19 - y_18), 2));
	float mlen_p18p20 = sqrt(pow((x_18 - x_20), 2) + pow((y_18 - y_20), 2));
	float theata0 = atan(10 / mlen_p19p18) * 180 / PI;
	x_21 = x_20 + 10 * sin(90 - theata0);
	y_21 = y_20 - 10 * cos(90 - theata0);

	float mlen_p20p21 = sqrt(pow((x_20 - x_21), 2) + pow((y_20 - y_21), 2));
	float mlen_p21p22 = (input_f_waistline / 4 + 0.5 + 4);
	float theata1 = atan(mlen_p20p21 / mlen_p21p22) * 180 / PI;
	float rlen = mlen_p21p22 / cos(theata1);
	rlen = round(rlen * 100) / 100.0;
	x_22 = x_20 + rlen*5;
	y_22 = y_0;

	x_23 = x_9 - (x_5 - x_9) / 2;
	y_23 = y_1;

	x_24 = x_23;
	y_24 = y_23 + 5;

	x_25 = x_17 + (input_f_hipline / 4 + 0.5) * 5;
	y_25 = y_2;

	x_26 = x_12 + 10;
	y_26 = y_3;

	x_27 = x_13 + 10;
	y_27 = y_4;

	x_28 = x_14 - 10;
	y_28 = y_3;

	x_29 = x_15 - 10;
	y_29 = y_4;


	//lineSegs_0_V1
	tempLine01 = new LINESEG;
	tempLine01->seg->startPoint.x = x_0;
	tempLine01->seg->startPoint.y = y_0;
	tempLine01->seg->endPoint.x = x_1;
	tempLine01->seg->endPoint.y = y_1;
	tempLine01->bDraw = true;
	tempLine01->curShape = ShapeType_LineSegment;
	tempLine01->itemType = ItemType_Aux_line;
	lineSegs.push_back(tempLine01);

	//lineSegs_1_V2
	tempLine12 = new LINESEG;
	tempLine12->seg->startPoint.x = x_1;
	tempLine12->seg->startPoint.y = y_1;
	tempLine12->seg->endPoint.x = x_2;
	tempLine12->seg->endPoint.y = y_2;
	tempLine12->bDraw = true;
	tempLine12->curShape = ShapeType_LineSegment;
	tempLine12->itemType = ItemType_Aux_line;
	lineSegs.push_back(tempLine12);

	//lineSegs_2_V3
	tempLine03 = new LINESEG;
	tempLine03->seg->startPoint.x = x_0;
	tempLine03->seg->startPoint.y = y_0;
	tempLine03->seg->endPoint.x = x_3;
	tempLine03->seg->endPoint.y = y_3;
	tempLine03->bDraw = true;
	tempLine03->curShape = ShapeType_LineSegment;
	tempLine03->itemType = ItemType_Aux_line;
	lineSegs.push_back(tempLine03);

	//lineSegs_3_V4
	tempLine14 = new LINESEG;
	tempLine14->seg->startPoint.x = x_1;
	tempLine14->seg->startPoint.y = y_1;
	tempLine14->seg->endPoint.x = x_4;
	tempLine14->seg->endPoint.y = y_4;
	tempLine14->bDraw = true;
	tempLine14->curShape = ShapeType_LineSegment;
	tempLine14->itemType = ItemType_Aux_line;
	lineSegs.push_back(tempLine14);

	//lineSegs_4_V5
	tempLine15 = new LINESEG;
	tempLine15->seg->startPoint.x = x_1;
	tempLine15->seg->startPoint.y = y_1;
	tempLine15->seg->endPoint.x = x_5;
	tempLine15->seg->endPoint.y = y_5;
	tempLine15->bDraw = true;
	tempLine15->curShape = ShapeType_LineSegment;
	tempLine15->itemType = ItemType_Aux_line;
	lineSegs.push_back(tempLine15);

	//lineSegs_5_V5
	tempLine56 = new LINESEG;
	tempLine56->seg->startPoint.x = x_5;
	tempLine56->seg->startPoint.y = y_5;
	tempLine56->seg->endPoint.x = x_6;
	tempLine56->seg->endPoint.y = y_6;
	tempLine56->bDraw = true;
	tempLine56->curShape = ShapeType_LineSegment;
	tempLine56->itemType = ItemType_Aux_line;
	lineSegs.push_back(tempLine56);

	//lineSegs_6_V5
	tempLine67 = new LINESEG;
	tempLine67->seg->startPoint.x = x_6;
	tempLine67->seg->startPoint.y = y_6;
	tempLine67->seg->endPoint.x = x_7;
	tempLine67->seg->endPoint.y = y_7;
	tempLine67->bDraw = true;
	tempLine67->curShape = ShapeType_LineSegment;
	tempLine67->itemType = ItemType_Aux_line;
	lineSegs.push_back(tempLine67);

	//lineSegs_7_V6
	tempLine68 = new LINESEG;
	tempLine68->seg->startPoint.x = x_6;
	tempLine68->seg->startPoint.y = y_6;
	tempLine68->seg->endPoint.x = x_8;
	tempLine68->seg->endPoint.y = y_8;
	tempLine68->bDraw = true;
	tempLine68->curShape = ShapeType_LineSegment;
	tempLine68->itemType = ItemType_Aux_line;
	lineSegs.push_back(tempLine68);

	//lineSegs_8_V7
	tempLine59 = new LINESEG;
	tempLine59->seg->startPoint.x = x_5;
	tempLine59->seg->startPoint.y = y_5;
	tempLine59->seg->endPoint.x = x_9;
	tempLine59->seg->endPoint.y = y_9;
	tempLine59->bDraw = true;
	tempLine59->curShape = ShapeType_LineSegment;
	tempLine59->itemType = ItemType_Aux_line;
	lineSegs.push_back(tempLine59);

	//lineSegs_9_V8
	tempLine710 = new LINESEG;
	tempLine710->seg->startPoint.x = x_7;
	tempLine710->seg->startPoint.y = y_7;
	tempLine710->seg->endPoint.x = x_10;
	tempLine710->seg->endPoint.y = y_10;
	tempLine710->bDraw = true;
	tempLine710->curShape = ShapeType_LineSegment;
	tempLine710->itemType = ItemType_Aux_line;
	lineSegs.push_back(tempLine710);

	//lineSegs_10_V8
	tempLine610 = new LINESEG;
	tempLine610->seg->startPoint.x = x_6;
	tempLine610->seg->startPoint.y = y_6;
	tempLine610->seg->endPoint.x = x_10;
	tempLine610->seg->endPoint.y = y_10;
	tempLine610->bDraw = true;
	tempLine610->curShape = ShapeType_LineSegment;
	tempLine610->itemType = ItemType_Solid_Front_line;
	lineSegs.push_back(tempLine610);

	//lineSegs_11_V9
	tempLine1011 = new LINESEG;
	tempLine1011->seg->startPoint.x = x_10;
	tempLine1011->seg->startPoint.y = y_10;
	tempLine1011->seg->endPoint.x = x_11;
	tempLine1011->seg->endPoint.y = y_11;
	tempLine1011->bDraw = true;
	tempLine1011->curShape = ShapeType_LineSegment;
	tempLine1011->itemType = ItemType_Solid_Front_line;
	lineSegs.push_back(tempLine1011);

	//lineSegs_12_V10
	tempLine312 = new LINESEG;
	tempLine312->seg->startPoint.x = x_3;
	tempLine312->seg->startPoint.y = y_3;
	tempLine312->seg->endPoint.x = x_12;
	tempLine312->seg->endPoint.y = y_12;
	tempLine312->bDraw = true;
	tempLine312->curShape = ShapeType_LineSegment;
	tempLine312->itemType = ItemType_Aux_line;
	lineSegs.push_back(tempLine312);

	//lineSegs_13_V11
	tempLine413 = new LINESEG;
	tempLine413->seg->startPoint.x = x_4;
	tempLine413->seg->startPoint.y = y_4;
	tempLine413->seg->endPoint.x = x_13;
	tempLine413->seg->endPoint.y = y_13;
	tempLine413->bDraw = true;
	tempLine413->curShape = ShapeType_LineSegment;
	tempLine413->itemType = ItemType_Aux_line;
	lineSegs.push_back(tempLine413);

	//lineSegs_14_V12
	tempLine314 = new LINESEG;
	tempLine314->seg->startPoint.x = x_3;
	tempLine314->seg->startPoint.y = y_3;
	tempLine314->seg->endPoint.x = x_14;
	tempLine314->seg->endPoint.y = y_14;
	tempLine314->bDraw = true;
	tempLine314->curShape = ShapeType_LineSegment;
	tempLine314->itemType = ItemType_Aux_line;
	lineSegs.push_back(tempLine314);

	//lineSegs_15_V13
	tempLine415 = new LINESEG;
	tempLine415->seg->startPoint.x = x_4;
	tempLine415->seg->startPoint.y = y_4;
	tempLine415->seg->endPoint.x = x_15;
	tempLine415->seg->endPoint.y = y_15;
	tempLine415->bDraw = true;
	tempLine415->curShape = ShapeType_LineSegment;
	tempLine415->itemType = ItemType_Aux_line;
	lineSegs.push_back(tempLine415);

	//lineSegs_16_V13
	tempLineinseamline2 = new LINESEG;
	tempLineinseamline2->seg->startPoint.x = x_15;
	tempLineinseamline2->seg->startPoint.y = y_15;
	tempLineinseamline2->seg->endPoint.x = x_14;
	tempLineinseamline2->seg->endPoint.y = y_14;
	tempLineinseamline2->bDraw = true;
	tempLineinseamline2->curShape = ShapeType_LineSegment;
	tempLineinseamline2->itemType = ItemType_Solid_Front_line;
	lineSegs.push_back(tempLineinseamline2);

	//lineSegs_17_V11
	tempLineseamline3 = new LINESEG;
	tempLineseamline3->seg->startPoint.x = x_13;
	tempLineseamline3->seg->startPoint.y = y_13;
	tempLineseamline3->seg->endPoint.x = x_12;
	tempLineseamline3->seg->endPoint.y = y_12;
	tempLineseamline3->bDraw = true;
	tempLineseamline3->curShape = ShapeType_LineSegment;
	tempLineseamline3->itemType = ItemType_Solid_Front_line;
	lineSegs.push_back(tempLineseamline3);


	//lineSegs_18_V14
	tempLine516 = new LINESEG;
	tempLine516->seg->startPoint.x = x_5;
	tempLine516->seg->startPoint.y = y_5;
	tempLine516->seg->endPoint.x = x_16;
	tempLine516->seg->endPoint.y = y_16;
	tempLine516->bDraw = true;
	tempLine516->curShape = ShapeType_LineSegment;
	tempLine516->itemType = ItemType_Aux_line;
	lineSegs.push_back(tempLine516);

	//lineSegs_19_V14
	tempLine1617 = new LINESEG;
	tempLine1617->seg->startPoint.x = x_16;
	tempLine1617->seg->startPoint.y = y_16;
	tempLine1617->seg->endPoint.x = x_17;
	tempLine1617->seg->endPoint.y = y_17;
	tempLine1617->bDraw = true;
	tempLine1617->curShape = ShapeType_LineSegment;
	tempLine1617->itemType = ItemType_Aux_line;
	lineSegs.push_back(tempLine1617);

	//lineSegs_20_V14
	tempLine1618 = new LINESEG;
	tempLine1618->seg->startPoint.x = x_16;
	tempLine1618->seg->startPoint.y = y_16;
	tempLine1618->seg->endPoint.x = x_18;
	tempLine1618->seg->endPoint.y = y_18;
	tempLine1618->bDraw = true;
	tempLine1618->curShape = ShapeType_LineSegment;
	tempLine1618->itemType = ItemType_Aux_line;
	lineSegs.push_back(tempLine1618);

	//lineSegs_21_V15
	tempLine1619 = new LINESEG;
	tempLine1619->seg->startPoint.x = x_16;
	tempLine1619->seg->startPoint.y = y_16;
	tempLine1619->seg->endPoint.x = x_19;
	tempLine1619->seg->endPoint.y = y_19;
	tempLine1619->bDraw = false;
	tempLine1619->curShape = ShapeType_LineSegment;
	tempLine1619->itemType = ItemType_Aux_line;
	lineSegs.push_back(tempLine1619);

	//lineSegs_22_V16
	tempLine1820 = new LINESEG;
	tempLine1820->seg->startPoint.x = x_18;
	tempLine1820->seg->startPoint.y = y_18;
	tempLine1820->seg->endPoint.x = x_20;
	tempLine1820->seg->endPoint.y = y_20;
	tempLine1820->bDraw = false;
	tempLine1820->curShape = ShapeType_LineSegment;
	tempLine1820->itemType = ItemType_Aux_line;
	lineSegs.push_back(tempLine1820);

	//lineSegs_23_V17
	tempLine2021 = new LINESEG;
	tempLine2021->seg->startPoint.x = x_20;
	tempLine2021->seg->startPoint.y = y_20;
	tempLine2021->seg->endPoint.x = x_21;
	tempLine2021->seg->endPoint.y = y_21;
	tempLine2021->bDraw = true;
	tempLine2021->curShape = ShapeType_LineSegment;
	tempLine2021->itemType = ItemType_Solid_Back_line;
	lineSegs.push_back(tempLine2021);

	//lineSegs_24_V18
	tempLine2122 = new LINESEG;
	tempLine2122->seg->startPoint.x = x_21;
	tempLine2122->seg->startPoint.y = y_21;
	tempLine2122->seg->endPoint.x = x_22;
	tempLine2122->seg->endPoint.y = y_22;
	tempLine2122->bDraw = true;
	tempLine2122->curShape = ShapeType_LineSegment;
	tempLine2122->itemType = ItemType_Solid_Back_line;
	lineSegs.push_back(tempLine2122);

	//lineSegs_25_V19
	tempLine923 = new LINESEG;
	tempLine923->seg->startPoint.x = x_9;
	tempLine923->seg->startPoint.y = y_9;
	tempLine923->seg->endPoint.x = x_23;
	tempLine923->seg->endPoint.y = y_23;
	tempLine923->bDraw = true;
	tempLine923->curShape = ShapeType_LineSegment;
	tempLine923->itemType = ItemType_Aux_line;
	lineSegs.push_back(tempLine923);

	//lineSegs_26_V20
	tempLine2324 = new LINESEG;
	tempLine2324->seg->startPoint.x = x_23;
	tempLine2324->seg->startPoint.y = y_23;
	tempLine2324->seg->endPoint.x = x_24;
	tempLine2324->seg->endPoint.y = y_24;
	tempLine2324->bDraw = false;
	tempLine2324->curShape = ShapeType_LineSegment;
	tempLine2324->itemType = ItemType_Aux_line;
	lineSegs.push_back(tempLine2324);

	//lineSegs_27_V20
	tempLine1921 = new LINESEG;
	tempLine1921->seg->startPoint.x = x_19;
	tempLine1921->seg->startPoint.y = y_19;
	tempLine1921->seg->endPoint.x = x_21;
	tempLine1921->seg->endPoint.y = y_21;
	tempLine1921->bDraw = true;
	tempLine1921->curShape = ShapeType_LineSegment;
	tempLine1921->itemType = ItemType_Solid_Back_line;
	lineSegs.push_back(tempLine1921);

	//lineSegs_28_V21
	tempLine1725 = new LINESEG;
	tempLine1725->seg->startPoint.x = x_17;
	tempLine1725->seg->startPoint.y = y_17;
	tempLine1725->seg->endPoint.x = x_25;
	tempLine1725->seg->endPoint.y = y_25;
	tempLine1725->bDraw = true;
	tempLine1725->curShape = ShapeType_LineSegment;
	tempLine1725->itemType = ItemType_Aux_line;
	lineSegs.push_back(tempLine1725);

	//lineSegs_29_V22
	tempLine1226 = new LINESEG;
	tempLine1226->seg->startPoint.x = x_12;
	tempLine1226->seg->startPoint.y = y_12;
	tempLine1226->seg->endPoint.x = x_26;
	tempLine1226->seg->endPoint.y = y_26;
	tempLine1226->bDraw = true;
	tempLine1226->curShape = ShapeType_LineSegment;
	tempLine1226->itemType = ItemType_Aux_line;
	lineSegs.push_back(tempLine1226);

	//lineSegs_30_V23
	tempLine1327 = new LINESEG;
	tempLine1327->seg->startPoint.x = x_13;
	tempLine1327->seg->startPoint.y = y_13;
	tempLine1327->seg->endPoint.x = x_27;
	tempLine1327->seg->endPoint.y = y_27;
	tempLine1327->bDraw = true;
	tempLine1327->curShape = ShapeType_LineSegment;
	tempLine1327->itemType = ItemType_Aux_line;
	lineSegs.push_back(tempLine1327);

	//lineSegs_31_V24
	tempLine1428 = new LINESEG;
	tempLine1428->seg->startPoint.x = x_14;
	tempLine1428->seg->startPoint.y = y_14;
	tempLine1428->seg->endPoint.x = x_28;
	tempLine1428->seg->endPoint.y = y_28;
	tempLine1428->bDraw = true;
	tempLine1428->curShape = ShapeType_LineSegment;
	tempLine1428->itemType = ItemType_Aux_line;
	lineSegs.push_back(tempLine1428);

	//lineSegs_32_V25
	tempLine1529 = new LINESEG;
	tempLine1529->seg->startPoint.x = x_15;
	tempLine1529->seg->startPoint.y = y_15;
	tempLine1529->seg->endPoint.x = x_29;
	tempLine1529->seg->endPoint.y = y_29;
	tempLine1529->bDraw = true;
	tempLine1529->curShape = ShapeType_LineSegment;
	tempLine1529->itemType = ItemType_Aux_line;
	lineSegs.push_back(tempLine1529);

	//lineSegs_33_V23
	tempLine2627 = new LINESEG;
	tempLine2627->seg->startPoint.x = x_26;
	tempLine2627->seg->startPoint.y = y_26;
	tempLine2627->seg->endPoint.x = x_27;
	tempLine2627->seg->endPoint.y = y_27;
	tempLine2627->bDraw = true;
	tempLine2627->curShape = ShapeType_LineSegment;
	tempLine2627->itemType = ItemType_Solid_Back_line;
	lineSegs.push_back(tempLine2627);

	//lineSegs_34_V25
	tempLine2829 = new LINESEG;
	tempLine2829->seg->startPoint.x = x_28;
	tempLine2829->seg->startPoint.y = y_28;
	tempLine2829->seg->endPoint.x = x_29;
	tempLine2829->seg->endPoint.y = y_29;
	tempLine2829->bDraw = true;
	tempLine2829->curShape = ShapeType_LineSegment;
	tempLine2829->itemType = ItemType_Solid_Back_line;
	lineSegs.push_back(tempLine2829);


	//curveSegs_0
	tempcrothbendline = new CBEZIERCURVE;
	PointEx p0_ctrl(x_6, y_6);
	PointEx p1_ctrl(x_5, y_6 + (y_5 - y_6) / 2);
	PointEx p2_ctrl(x_5 - (x_5 - x_9) / 2, y_5);
	PointEx p3_ctrl(x_9, y_9);
	std::vector<PointEx> pts_Ctrls;
	pts_Ctrls.push_back(p0_ctrl);
	pts_Ctrls.push_back(p1_ctrl);
	pts_Ctrls.push_back(p2_ctrl);
	pts_Ctrls.push_back(p3_ctrl);
	tempcrothbendline->curvelineseg->pts = pts_Ctrls;
	tempcrothbendline->bDraw = true;
	tempcrothbendline->curShape = ShapeType_CurveLine;
    tempcrothbendline->itemType = ItemType_Solid_Front_line;
	bezierCurvelineSegs.push_back(tempcrothbendline);

	//curveSegs_1
	tempseamsideline = new CBEZIERCURVE;
	PointEx p0_ctrl1(x_11, y_11);
	PointEx p1_ctrl1(x_11 + 15, y_11);
	PointEx p2_ctrl1(x_8, y_8 - 10);
	PointEx p3_ctrl1(x_8, y_8);
	std::vector<PointEx> pts_Ctrls1;
	pts_Ctrls1.push_back(p0_ctrl1);
	pts_Ctrls1.push_back(p1_ctrl1);
	pts_Ctrls1.push_back(p2_ctrl1);
	pts_Ctrls1.push_back(p3_ctrl1);
	tempseamsideline->curvelineseg->pts = pts_Ctrls1;
	tempseamsideline->bDraw = true;
	tempseamsideline->curShape = ShapeType_CurveLine;
	tempseamsideline->itemType = ItemType_Solid_Front_line;
	bezierCurvelineSegs.push_back(tempseamsideline);

	//curveSegs_2
	tempseamsideline2 = new CBEZIERCURVE;
	PointEx p0_ctrl2(x_8, y_8);
	PointEx p1_ctrl2(2 * x_8 - (x_8), 2 * y_8 - (y_8 - 10));
	PointEx p2_ctrl2(x_13 + 5, y_13 - 20);
	PointEx p3_ctrl2(x_13, y_13);
	std::vector<PointEx> pts_Ctrls2;
	pts_Ctrls2.push_back(p0_ctrl2);
	pts_Ctrls2.push_back(p1_ctrl2);
	pts_Ctrls2.push_back(p2_ctrl2);
	pts_Ctrls2.push_back(p3_ctrl2);
	tempseamsideline2->curvelineseg->pts = pts_Ctrls2;
	tempseamsideline2->bDraw = true;
	tempseamsideline2->curShape = ShapeType_CurveLine;
	tempseamsideline2->itemType = ItemType_Solid_Front_line;
	bezierCurvelineSegs.push_back(tempseamsideline2);

	//curveSegs_3
	tempinseamline1 = new CBEZIERCURVE;
	PointEx p0_ctrl3(x_9, y_9);
	PointEx p1_ctrl3(x_9 + 10, y_1 + 10);
	PointEx p2_ctrl3(x_15 - 2, y_15 - 10);
	PointEx p3_ctrl3(x_15, y_15);
	std::vector<PointEx> pts_Ctrls3;
	pts_Ctrls3.push_back(p0_ctrl3);
	pts_Ctrls3.push_back(p1_ctrl3);
	pts_Ctrls3.push_back(p2_ctrl3);
	pts_Ctrls3.push_back(p3_ctrl3);
	tempinseamline1->curvelineseg->pts = pts_Ctrls3;
	tempinseamline1->bDraw = true;
	tempinseamline1->curShape = ShapeType_CurveLine;
	tempinseamline1->itemType = ItemType_Solid_Front_line;
	bezierCurvelineSegs.push_back(tempinseamline1);

	//curveSegs_4
	temprearcrotcharc = new CBEZIERCURVE;
	PointEx p0_ctrl6(x_19, y_19);
	PointEx p1_ctrl6(x_17, y_17);
	PointEx p2_ctrl6(x_5, y_5 + 15);
	PointEx p3_ctrl6(x_24, y_24);
	std::vector<PointEx> pts_Ctrls6;
	pts_Ctrls6.push_back(p0_ctrl6);
	pts_Ctrls6.push_back(p1_ctrl6);
	pts_Ctrls6.push_back(p2_ctrl6);
	pts_Ctrls6.push_back(p3_ctrl6);
	temprearcrotcharc->curvelineseg->pts = pts_Ctrls6;
	temprearcrotcharc->bDraw = true;
	temprearcrotcharc->curShape = ShapeType_CurveLine;
	temprearcrotcharc->itemType = ItemType_Solid_Back_line;
	bezierCurvelineSegs.push_back(temprearcrotcharc);

	//curveSegs_5
	tempseamsideline3 = new CBEZIERCURVE;
	PointEx p0_ctrl4(x_22, y_22);
	PointEx p1_ctrl4(x_22 + 15, y_22 + 20);
	PointEx p2_ctrl4(x_25 + 5, y_25 - 20);
	PointEx p3_ctrl4(x_25, y_25);
	std::vector<PointEx> pts_Ctrls4;
	pts_Ctrls4.push_back(p0_ctrl4);
	pts_Ctrls4.push_back(p1_ctrl4);
	pts_Ctrls4.push_back(p2_ctrl4);
	pts_Ctrls4.push_back(p3_ctrl4);
	tempseamsideline3->curvelineseg->pts = pts_Ctrls4;
	tempseamsideline3->bDraw = true;
	tempseamsideline3->curShape = ShapeType_CurveLine;
	tempseamsideline3->itemType = ItemType_Solid_Back_line;
	bezierCurvelineSegs.push_back(tempseamsideline3);

	//curveSegs_6
	tempseamsideline4 = new CBEZIERCURVE;
	PointEx p0_ctrl8(x_25, y_25);
	PointEx p1_ctrl8(2 * x_25 - (x_25 + 10), 2 * y_25 - (y_25 - 20));
	PointEx p2_ctrl8(x_27, y_27 - 10);
	PointEx p3_ctrl8(x_27, y_27);
	std::vector<PointEx> pts_Ctrls8;
	pts_Ctrls8.push_back(p0_ctrl8);
	pts_Ctrls8.push_back(p1_ctrl8);
	pts_Ctrls8.push_back(p2_ctrl8);
	pts_Ctrls8.push_back(p3_ctrl8);
	tempseamsideline4->curvelineseg->pts = pts_Ctrls8;
	tempseamsideline4->bDraw = true;
	tempseamsideline4->curShape = ShapeType_CurveLine;
	tempseamsideline4->itemType = ItemType_Solid_Back_line;
	bezierCurvelineSegs.push_back(tempseamsideline4);

	//curveSegs_7
	tempinseamline2 = new CBEZIERCURVE;
	PointEx p0_ctrl7(x_24, y_24);
	PointEx p1_ctrl7(x_24 + 10, y_24 + 10);
	PointEx p2_ctrl7(x_29 + 5, y_29 - 5);
	PointEx p3_ctrl7(x_29, y_29);
	std::vector<PointEx> pts_Ctrls7;
	pts_Ctrls7.push_back(p0_ctrl7);
	pts_Ctrls7.push_back(p1_ctrl7);
	pts_Ctrls7.push_back(p2_ctrl7);
	pts_Ctrls7.push_back(p3_ctrl7);
	tempinseamline2->curvelineseg->pts = pts_Ctrls7;
	tempinseamline2->bDraw = true;
	tempinseamline2->curShape = ShapeType_CurveLine;
	tempinseamline2->itemType = ItemType_Solid_Back_line;
	bezierCurvelineSegs.push_back(tempinseamline2);

}

void myQt2020::paintEvent(QPaintEvent *event)
{
	QPainter p(this);
	p.setRenderHint(QPainter::Antialiasing);

	drawLineSeg(&p); //draw line segment
	drawCurveLineSeg(&p); //draw curve-line


}

void myQt2020::mousePressEvent(QMouseEvent *event)
{
	
	if (ispainting == false)
	{
		QMessageBox::information(this, "Information", "Please open the size input dialog box!", QMessageBox::Ok);
	}
	else
	{
		std::vector<string>::iterator vit;

		dfsRelVids.clear();
		dfsRelationLines.clear();

		switch (event->button()){
		case Qt::LeftButton:
			bLBtnDown = true;
			selectLineSeg = nullptr;
			selectCurveLineSeg = nullptr;
			/*vec_DfsRet.clear();*/

			if (!islineEdit)
			{
				selectCurveLineSeg = getSeleledCurve();
			}
			else
			{
				//selectCurveLineSeg = getSeleledCurve();


				if (getSeleled() == -1){
					selectLineSeg = nullptr;
				}
				else{
				
					selectLineSeg = lineSegs.at(getSeleled());
				}

				qDebug() << "select LineSeg:" << getSeleled() << endl;

				string stEntity2Lineseg[] = { "V1", "V2", "V3", "V4", "V5", "V5", "V5", "V6", "V7", "V8", "V8",
					"V9", "V10", "V11", "V12", "V13", "V13", "V11", "V14", "V14", "V14", "V15", "V16", "V17", "V18",
					"V19", "V20", "V20", "V21", "V22", "V23", "V24", "V25", "V23", "V25" };
				selEntityVert = stEntity2Lineseg[getSeleled()];

				qDebug() << "selEntityVert:" << QString::fromStdString(selEntityVert) << endl;

				vit = vec_DfsRet.begin();
				while (vit != vec_DfsRet.end()){
					vit = vec_DfsRet.erase(vit);
				}
				std::vector<string>(vec_DfsRet).swap(vec_DfsRet);

				string vexs[] = { "V1", "V2", "V3", "V4", "V5", "V6", "V7", "V8", "V9", "V10", "V11", "V12", "V13", "V14", "V15",
					"V16", "V17", "V18", "V19", "V20", "V21", "V22", "V23", "V24", "V25" };
				string edges[][2] = {
						{ "V1", "V2" },
						{ "V1", "V3" },
						{ "V1", "V4" },
						{ "V1", "V5" },
						{ "V2", "V5" },
						{ "V2", "V14" },
						{ "V3", "V4" },
						{ "V3", "V10" },
						{ "V3", "V12" },
						{ "V4", "V11" },
						{ "V4", "V13" },
						{ "V5", "V6" },
						{ "V5", "V7" },
						{ "V5", "V8" },
						{ "V5", "V14" },
						{ "V7", "V19" },
						{ "V8", "V9" },
						{ "V10", "V22" },
						{ "V11", "V23" },
						{ "V12", "V24" },
						{ "V13", "V25" },
						{ "V14", "V16" },
						{ "V14", "V15" },
						{ "V14", "V21" },
						{ "V15", "V19" },
						{ "V16", "V17" },
						{ "V17", "V18" },
						{ "V18", "V20" },
						{ "V19", "V20" } };
				int vlen = sizeof(vexs) / sizeof(vexs[0]);
				int elen = sizeof(edges) / sizeof(edges[0]);

				ListDG *pG = new ListDG(vexs, vlen, edges, elen);
				//pG->print();
				pG->DFS(pG->getPosition(selEntityVert));
				vec_DfsRet = pG->getDfsRet();
				if (vec_DfsRet.size() > 0){
					for (vit = vec_DfsRet.begin() + 1; vit != vec_DfsRet.end(); vit++){
						cout << "Dfs_Ret:" << *vit << endl;
						findLineSegs(pG->getPosition(*vit));
						dfsRelVids.push_back(*vit);
					}

					for (int i = 0; i < dfsRelVids.size(); i++){
						std::cout << "dfsRelVids" << i << ":" << dfsRelVids[i] << endl;
					}
				}
			}


			if (selectLineSeg != nullptr){ //选中线段
				selectLineSeg->bDraw = false;

				if (selectLineSeg->bSelStartPt){ //选中起点
					startPoint.setX(selectLineSeg->seg->endPoint.x);
					startPoint.setY(selectLineSeg->seg->endPoint.y);

					endPoint.setX(selectLineSeg->seg->startPoint.x);
					endPoint.setY(selectLineSeg->seg->startPoint.y);
				}
				else if (selectLineSeg->bSelEndPt){//选中终点
					startPoint.setX(selectLineSeg->seg->startPoint.x);
					startPoint.setY(selectLineSeg->seg->startPoint.y);

					endPoint.setX(selectLineSeg->seg->endPoint.x);
					endPoint.setY(selectLineSeg->seg->endPoint.y);


				}
				else if (selectLineSeg->bSelLine){//选中线段
					movePoint = event->pos();

					startPoint.setX(selectLineSeg->seg->startPoint.x);
					startPoint.setY(selectLineSeg->seg->startPoint.y);

					endPoint.setX(selectLineSeg->seg->endPoint.x);
					endPoint.setY(selectLineSeg->seg->endPoint.y);

				}
				update();
			}

			else if (selectRectSeg != nullptr) //选中矩形
			{
			
				moveRectPoint = event->pos();
			
				beginPoint.setX(selectRectSeg->rectseg->beginPt.x);
				beginPoint.setY(selectRectSeg->rectseg->beginPt.y);
				qDebug() << "beginPoint.x:" << beginPoint.x() << "beginPoint.y:" << beginPoint.y() << endl;
				
				update();


			}

			else if (selectCurveLineSeg != nullptr) //选中曲线
			{
				selectCurveLineSeg->bDraw = false;
				qDebug() << "selCurveLineId:" << selCurveLineId << endl;

				if (selectCurveLineSeg->bSelPtCtr2)
				{
					moveCtrlPoint = event->pos();
					curveCtrlPt2.setX(selectCurveLineSeg->curvelineseg->pts[1].x);
					curveCtrlPt2.setY(selectCurveLineSeg->curvelineseg->pts[1].y);
				}

				else if (selectCurveLineSeg->bSelPtCtr3)
				{
					moveCtrlPoint = event->pos();
					curveCtrlPt3.setX(selectCurveLineSeg->curvelineseg->pts[2].x);
					curveCtrlPt3.setY(selectCurveLineSeg->curvelineseg->pts[2].x);
				}

				update();
			}

			else
			{
				selectLineSeg = nullptr;
				selectCurveLineSeg = nullptr;
			}
			break;
		default:
			break;

		}
	}
}

//移动鼠标
void myQt2020::mouseMoveEvent(QMouseEvent *event){
	QPointF movePt = event->pos();
	if (selectLineSeg != nullptr){ //选中线段
		if (bLBtnDown){//鼠标按下
			if (selectLineSeg->bSelStartPt || selectLineSeg->bSelEndPt){ //选中起点或者终点
				endPoint = movePt;
			}
			else if (selectLineSeg->bSelLine){//选中线段
				double disX = movePt.x() - movePoint.x();
				double disY = movePt.y() - movePoint.y();

				startPoint.setX(startPoint.x() + disX);
				startPoint.setY(startPoint.y() + disY);

				endPoint.setX(endPoint.x() + disX);
				endPoint.setY(endPoint.y() + disY);


				movePoint = movePt;

			}
		}
	}

	else if (selectRectSeg != nullptr)
	{
		if (bLBtnDown) {
			if (selectRectSeg->bSelFrame){
				double disX = movePt.x() - moveRectPoint.x();
				double disY = movePt.y() - moveRectPoint.y();

				beginPoint.setX(beginPoint.x() + disX);
				beginPoint.setY(beginPoint.y() + disY);

				moveRectPoint = movePt;
				qDebug() << "beginPoint.x:" << beginPoint.x() << ",beginPoint.y:" << beginPoint.y() << endl;
			}

		}
	}

	else if (selectCurveLineSeg != nullptr)
	{
		if (bLBtnDown){ //鼠标按下
			if (selectCurveLineSeg->bSelPtCtr2){
				double disX = movePt.x() - moveCtrlPoint.x();
				double disY = movePt.y() - moveCtrlPoint.y();

				qDebug() << "movePt.x" << movePt.x() << endl;

				qDebug() << "disX" << disX << endl;

				curveCtrlPt2.setX(movePt.x());
				curveCtrlPt2.setY(movePt.y());
			}

			else if (selectCurveLineSeg->bSelPtCtr3){

				double disX = movePt.x() - moveCtrlPoint.x();
				double disY = movePt.y() - moveCtrlPoint.y();

				qDebug() << "movePt.x" << movePt.x() << endl;

				qDebug() << "disX" << disX << endl;

				curveCtrlPt3.setX(movePt.x());
				curveCtrlPt3.setY(movePt.y());

			}
		}
	}

	else{ //Lineseg not selected
		if (bLBtnDown){
			endPoint = movePt;
		}
		else{
			selSeg(movePt);
			selCurveSeg(movePt);
		}

	}
	update();
}

//Release the mouse button
void myQt2020::mouseReleaseEvent(QMouseEvent *event){
	switch (event->button()){
	case Qt::LeftButton:
		bLBtnDown = false;
		
		if (selectLineSeg != nullptr){

			if (selectLineSeg->bSelStartPt){//select the starting point
				//selectLineSeg->seg->endPoint.x = event->pos().x();
				//selectLineSeg->seg->endPoint.y = event->pos().y();


			}
			else if (selectLineSeg->bSelEndPt){//select the endpoint
				/*selectLineSeg->seg->endPoint.x = event->pos().x();
				selectLineSeg->seg->endPoint.y = event->pos().y();*/
				 

				if (selEntityVert == "V10")
				{
					selectLineSeg->seg->endPoint.x = event->pos().x();
					
					dfsRelationLines.at(0)->seg->startPoint.x = selectLineSeg->seg->endPoint.x;
					dfsRelationLines.at(0)->seg->endPoint.x = dfsRelationLines.at(0)->seg->startPoint.x + 10;

					lineSegs.at(17)->seg->endPoint.x = dfsRelationLines.at(0)->seg->startPoint.x;
					lineSegs.at(33)->seg->startPoint.x = dfsRelationLines.at(0)->seg->endPoint.x;

				}
				else if (selEntityVert == "V12")
				{
					selectLineSeg->seg->endPoint.x = event->pos().x();
					
					dfsRelationLines.at(0)->seg->startPoint.x = selectLineSeg->seg->endPoint.x;
					dfsRelationLines.at(0)->seg->endPoint.x = dfsRelationLines.at(0)->seg->startPoint.x - 10;

					lineSegs.at(16)->seg->endPoint.x = dfsRelationLines.at(0)->seg->startPoint.x;
					lineSegs.at(34)->seg->startPoint.x = dfsRelationLines.at(0)->seg->endPoint.x;
				}

				else if (selEntityVert == "V3")
				{
					selectLineSeg->seg->endPoint.y = event->pos().y();

					//V4:
					dfsRelationLines.at(0)->seg->endPoint.y = y_1 + (event->pos().y() - y_1) / 2 - 5 * 5;

					//V11:
					dfsRelationLines.at(1)->seg->startPoint.y = y_1 + (event->pos().y() - y_1) / 2 - 5 * 5;
					dfsRelationLines.at(1)->seg->endPoint.y = y_1 + (event->pos().y() - y_1) / 2 - 5 * 5;
					bezierCurvelineSegs.at(2)->curvelineseg->pts[2].y = dfsRelationLines.at(1)->seg->endPoint.y - 10;
					bezierCurvelineSegs.at(2)->curvelineseg->pts[3].y = dfsRelationLines.at(1)->seg->endPoint.y;

					dfsRelationLines.at(2)->seg->startPoint.y = dfsRelationLines.at(0)->seg->endPoint.y;
					dfsRelationLines.at(2)->seg->endPoint.y = selectLineSeg->seg->endPoint.y;

					//V23:
					dfsRelationLines.at(3)->seg->startPoint.y = dfsRelationLines.at(0)->seg->endPoint.y;
					dfsRelationLines.at(3)->seg->endPoint.y = dfsRelationLines.at(0)->seg->endPoint.y;

					dfsRelationLines.at(4)->seg->startPoint.y = selectLineSeg->seg->endPoint.y;
					dfsRelationLines.at(4)->seg->endPoint.y = dfsRelationLines.at(0)->seg->endPoint.y;

					bezierCurvelineSegs.at(6)->curvelineseg->pts[2].y = dfsRelationLines.at(3)->seg->endPoint.y - 10;
					bezierCurvelineSegs.at(6)->curvelineseg->pts[3].y = dfsRelationLines.at(3)->seg->endPoint.y;

					//V13:
					dfsRelationLines.at(5)->seg->startPoint.y = dfsRelationLines.at(1)->seg->startPoint.y;
					dfsRelationLines.at(5)->seg->endPoint.y = dfsRelationLines.at(1)->seg->startPoint.y;

					dfsRelationLines.at(6)->seg->startPoint.y = dfsRelationLines.at(1)->seg->startPoint.y;
					dfsRelationLines.at(6)->seg->endPoint.y = selectLineSeg->seg->endPoint.y;

					bezierCurvelineSegs.at(3)->curvelineseg->pts[2].y = dfsRelationLines.at(5)->seg->endPoint.y - 10;
					bezierCurvelineSegs.at(3)->curvelineseg->pts[3].y = dfsRelationLines.at(5)->seg->endPoint.y;

					//V25:
					dfsRelationLines.at(7)->seg->startPoint.y = dfsRelationLines.at(1)->seg->startPoint.y;
					dfsRelationLines.at(7)->seg->endPoint.y = dfsRelationLines.at(1)->seg->startPoint.y;

					dfsRelationLines.at(8)->seg->startPoint.y = selectLineSeg->seg->endPoint.y;
					dfsRelationLines.at(8)->seg->endPoint.y = dfsRelationLines.at(1)->seg->startPoint.y;

					bezierCurvelineSegs.at(7)->curvelineseg->pts[2].y = dfsRelationLines.at(7)->seg->endPoint.y - 5;
					bezierCurvelineSegs.at(7)->curvelineseg->pts[3].y = dfsRelationLines.at(7)->seg->endPoint.y;

					//V10:
					dfsRelationLines.at(9)->seg->startPoint.y = selectLineSeg->seg->endPoint.y;
					dfsRelationLines.at(9)->seg->endPoint.y = selectLineSeg->seg->endPoint.y;

					//V22:
					dfsRelationLines.at(10)->seg->startPoint.y = selectLineSeg->seg->endPoint.y;
					dfsRelationLines.at(10)->seg->endPoint.y = selectLineSeg->seg->endPoint.y;

					//V12:
					dfsRelationLines.at(11)->seg->startPoint.y = selectLineSeg->seg->endPoint.y;
					dfsRelationLines.at(11)->seg->endPoint.y = selectLineSeg->seg->endPoint.y;

					//V24:
					dfsRelationLines.at(12)->seg->startPoint.y = selectLineSeg->seg->endPoint.y;
					dfsRelationLines.at(12)->seg->endPoint.y = selectLineSeg->seg->endPoint.y;

					
				}

				else if (selEntityVert == "V11"){
					selectLineSeg->seg->endPoint.x = event->pos().x();

					lineSegs.at(17)->seg->startPoint.x = selectLineSeg->seg->endPoint.x;
					bezierCurvelineSegs.at(2)->curvelineseg->pts[2].x = selectLineSeg->seg->endPoint.x + 5;
					bezierCurvelineSegs.at(2)->curvelineseg->pts[3].x = selectLineSeg->seg->endPoint.x;

					//V23:
					dfsRelationLines.at(0)->seg->startPoint.x = selectLineSeg->seg->endPoint.x;
					dfsRelationLines.at(0)->seg->endPoint.x = selectLineSeg->seg->endPoint.x + 10;

					dfsRelationLines.at(1)->seg->endPoint.x = dfsRelationLines.at(0)->seg->endPoint.x;
					bezierCurvelineSegs.at(6)->curvelineseg->pts[2].x = dfsRelationLines.at(0)->seg->endPoint.x;
					bezierCurvelineSegs.at(6)->curvelineseg->pts[3].x = dfsRelationLines.at(0)->seg->endPoint.x;
				}


				else if (selEntityVert == "V13")
				{
					selectLineSeg->seg->endPoint.x = event->pos().x();

					lineSegs.at(16)->seg->startPoint.x = selectLineSeg->seg->endPoint.x;
					bezierCurvelineSegs.at(3)->curvelineseg->pts[2].x = selectLineSeg->seg->endPoint.x - 2;
					bezierCurvelineSegs.at(3)->curvelineseg->pts[3].x = selectLineSeg->seg->endPoint.x;

					dfsRelationLines.at(0)->seg->startPoint.x = selectLineSeg->seg->endPoint.x;
					dfsRelationLines.at(0)->seg->endPoint.x = selectLineSeg->seg->endPoint.x - 10;

					dfsRelationLines.at(1)->seg->endPoint.x = dfsRelationLines.at(0)->seg->endPoint.x;

					bezierCurvelineSegs.at(7)->curvelineseg->pts[2].x = dfsRelationLines.at(0)->seg->endPoint.x + 5;
					bezierCurvelineSegs.at(7)->curvelineseg->pts[3].x = dfsRelationLines.at(0)->seg->endPoint.x;
				}

				else if (selEntityVert == "V1")
				{
					selectLineSeg->seg->endPoint.y = event->pos().y();

					//V2:
					dfsRelationLines.at(0)->seg->startPoint.y = selectLineSeg->seg->endPoint.y;  //lineseg_P1P2
					dfsRelationLines.at(0)->seg->endPoint.y = dfsRelationLines.at(0)->seg->startPoint.y - (dfsRelationLines.at(0)->seg->startPoint.y - y_0) / 3;
					//dfsRelationLines.at(0)->itemType = ItemType_Solid_Back_line;

					//V5:
					dfsRelationLines.at(1)->seg->startPoint.y = dfsRelationLines.at(0)->seg->startPoint.y;  //lineseg_P1P5
					dfsRelationLines.at(1)->seg->endPoint.y = dfsRelationLines.at(0)->seg->startPoint.y;

					dfsRelationLines.at(2)->seg->startPoint.y = dfsRelationLines.at(1)->seg->endPoint.y;  //lineseg_P5P6
					dfsRelationLines.at(2)->seg->endPoint.y = dfsRelationLines.at(0)->seg->endPoint.y;
					//dfsRelationLines.at(2)->itemType = ItemType_Solid_Back_line;

					dfsRelationLines.at(3)->seg->startPoint.y = dfsRelationLines.at(0)->seg->endPoint.y; //lineseg_P6P7
					dfsRelationLines.at(3)->seg->endPoint.y = y_0;
					//dfsRelationLines.at(3)->itemType = ItemType_Solid_Back_line;

					lineSegs.at(10)->seg->startPoint.y = dfsRelationLines.at(3)->seg->startPoint.y;

					//V6:
					dfsRelationLines.at(4)->seg->startPoint.y = dfsRelationLines.at(0)->seg->endPoint.y; //lineseg_P6P8
					dfsRelationLines.at(4)->seg->endPoint.y = dfsRelationLines.at(0)->seg->endPoint.y;
					dfsRelationLines.at(4)->itemType = ItemType_Solid_Front_line;

					//V7:
					dfsRelationLines.at(5)->seg->startPoint.y = dfsRelationLines.at(0)->seg->startPoint.y; //lineseg_P5P9
					dfsRelationLines.at(5)->seg->endPoint.y = dfsRelationLines.at(0)->seg->startPoint.y;

					//V19:
					dfsRelationLines.at(6)->seg->startPoint.y = dfsRelationLines.at(0)->seg->startPoint.y; //lineseg_P9P23
					dfsRelationLines.at(6)->seg->endPoint.y = dfsRelationLines.at(0)->seg->startPoint.y;

					bezierCurvelineSegs.at(0)->curvelineseg->pts[0].y = dfsRelationLines.at(3)->seg->startPoint.y;
					bezierCurvelineSegs.at(0)->curvelineseg->pts[1].y = dfsRelationLines.at(3)->seg->startPoint.y + (dfsRelationLines.at(2)->seg->startPoint.y - dfsRelationLines.at(3)->seg->startPoint.y) / 2;
					bezierCurvelineSegs.at(0)->curvelineseg->pts[2].y = dfsRelationLines.at(2)->seg->startPoint.y;
					bezierCurvelineSegs.at(0)->curvelineseg->pts[3].y = dfsRelationLines.at(6)->seg->startPoint.y;

					//bezierCurvelineSegs.at(3)->curvelineseg->pts[0].y = dfsRelationLines.at(6)->seg->startPoint.y;
					//bezierCurvelineSegs.at(3)->curvelineseg->pts[1].y = dfsRelationLines.at(6)->seg->startPoint.y + 10;

					//V20:
					dfsRelationLines.at(7)->seg->startPoint.y = dfsRelationLines.at(0)->seg->startPoint.y;   //lineseg_P23P24
					dfsRelationLines.at(7)->seg->endPoint.y = dfsRelationLines.at(0)->seg->startPoint.y + 5;

					dfsRelationLines.at(8)->seg->startPoint.y = y_18 + (dfsRelationLines.at(0)->seg->startPoint.y - y_18) / 2;

					//V8:
					dfsRelationLines.at(10)->seg->startPoint.y = dfsRelationLines.at(0)->seg->endPoint.y; //lineseg_P6P10

					//V9:
					

					//V14:
					dfsRelationLines.at(12)->seg->startPoint.y = dfsRelationLines.at(2)->seg->startPoint.y; //lineseg_P5P16
					dfsRelationLines.at(12)->seg->endPoint.y = dfsRelationLines.at(2)->seg->startPoint.y;

					dfsRelationLines.at(13)->seg->startPoint.y = dfsRelationLines.at(12)->seg->endPoint.y; //lineseg_P16P17
					dfsRelationLines.at(13)->seg->endPoint.y = dfsRelationLines.at(0)->seg->endPoint.y;

					dfsRelationLines.at(14)->seg->startPoint.y = dfsRelationLines.at(13)->seg->startPoint.y; //lineseg_P16P18


					//V16:

					//V17:

					//V18:

					//V15:
					dfsRelationLines.at(18)->seg->startPoint.y = dfsRelationLines.at(12)->seg->startPoint.y; //lineseg_P16P19
					dfsRelationLines.at(18)->seg->endPoint.y = y_18 + (dfsRelationLines.at(18)->seg->startPoint.y - y_18) / 2;

					lineSegs.at(27)->seg->startPoint.y = dfsRelationLines.at(18)->seg->endPoint.y;  //lineseg_P19P21

					bezierCurvelineSegs.at(4)->curvelineseg->pts[0].y = dfsRelationLines.at(18)->seg->endPoint.y;  //curveline _P19P17P5P24
					bezierCurvelineSegs.at(4)->curvelineseg->pts[1].y = dfsRelationLines.at(13)->seg->endPoint.y;
					bezierCurvelineSegs.at(4)->curvelineseg->pts[2].y = dfsRelationLines.at(2)->seg->startPoint.y + 15;
					bezierCurvelineSegs.at(4)->curvelineseg->pts[3].y = dfsRelationLines.at(7)->seg->endPoint.y;

					//bezierCurvelineSegs.at(7)->curvelineseg->pts[0].y = dfsRelationLines.at(7)->seg->endPoint.y;   //curveline_P24P29
					//bezierCurvelineSegs.at(7)->curvelineseg->pts[1].y = dfsRelationLines.at(7)->seg->endPoint.y + 10;

					//V21:
					dfsRelationLines.at(19)->seg->startPoint.y = dfsRelationLines.at(0)->seg->endPoint.y;
					dfsRelationLines.at(19)->seg->endPoint.y = dfsRelationLines.at(0)->seg->endPoint.y;

					//V3:

					
					//V4:
					dfsRelationLines.at(21)->seg->startPoint.y = dfsRelationLines.at(0)->seg->startPoint.y;  //lineseg_P1P4
					dfsRelationLines.at(21)->seg->endPoint.y = dfsRelationLines.at(0)->seg->startPoint.y + (y_3 - dfsRelationLines.at(0)->seg->startPoint.y) / 2 - 5 * 5;
					//dfsRelationLines.at(21)->itemType = ItemType_Solid_Front_line;

					//V11:
					dfsRelationLines.at(22)->seg->startPoint.y = dfsRelationLines.at(21)->seg->endPoint.y; //lineseg_P4P13
					dfsRelationLines.at(22)->seg->endPoint.y = dfsRelationLines.at(21)->seg->endPoint.y;

					dfsRelationLines.at(23)->seg->startPoint.y = dfsRelationLines.at(22)->seg->endPoint.y; //lineseg_P13P12

					//V23:
					dfsRelationLines.at(24)->seg->startPoint.y = dfsRelationLines.at(21)->seg->endPoint.y; //lineseg_P13P27
					dfsRelationLines.at(24)->seg->endPoint.y = dfsRelationLines.at(21)->seg->endPoint.y;
				
					dfsRelationLines.at(25)->seg->endPoint.y = dfsRelationLines.at(24)->seg->startPoint.y;


					//V13:
					dfsRelationLines.at(26)->seg->startPoint.y = dfsRelationLines.at(21)->seg->endPoint.y; //lineseg_P4P15
					dfsRelationLines.at(26)->seg->endPoint.y = dfsRelationLines.at(21)->seg->endPoint.y;

					dfsRelationLines.at(27)->seg->startPoint.y = dfsRelationLines.at(26)->seg->endPoint.y;

					//V25:
					dfsRelationLines.at(28)->seg->startPoint.y = dfsRelationLines.at(26)->seg->startPoint.y; //lineseg_P15P29
					dfsRelationLines.at(28)->seg->endPoint.y = dfsRelationLines.at(26)->seg->endPoint.y;

					dfsRelationLines.at(29)->seg->endPoint.y = dfsRelationLines.at(28)->seg->endPoint.y;


					bezierCurvelineSegs.at(1)->curvelineseg->pts[2].x = dfsRelationLines.at(4)->seg->endPoint.x;
					bezierCurvelineSegs.at(1)->curvelineseg->pts[2].y = dfsRelationLines.at(4)->seg->endPoint.y - 10;
					bezierCurvelineSegs.at(1)->curvelineseg->pts[3].x = dfsRelationLines.at(4)->seg->endPoint.x;
					bezierCurvelineSegs.at(1)->curvelineseg->pts[3].y = dfsRelationLines.at(4)->seg->endPoint.y;

					bezierCurvelineSegs.at(5)->curvelineseg->pts[2].x = dfsRelationLines.at(19)->seg->endPoint.x + 5;
					bezierCurvelineSegs.at(5)->curvelineseg->pts[2].y = dfsRelationLines.at(19)->seg->endPoint.y - 20;
					bezierCurvelineSegs.at(5)->curvelineseg->pts[3].x = dfsRelationLines.at(19)->seg->endPoint.x;
					bezierCurvelineSegs.at(5)->curvelineseg->pts[3].y = dfsRelationLines.at(19)->seg->endPoint.y;

					bezierCurvelineSegs.at(2)->curvelineseg->pts[0].x = dfsRelationLines.at(4)->seg->endPoint.x;
					bezierCurvelineSegs.at(2)->curvelineseg->pts[0].y = dfsRelationLines.at(4)->seg->endPoint.y;
					bezierCurvelineSegs.at(2)->curvelineseg->pts[1].x = 2 * dfsRelationLines.at(4)->seg->endPoint.x - (dfsRelationLines.at(4)->seg->endPoint.x);
					bezierCurvelineSegs.at(2)->curvelineseg->pts[1].y = 2 * dfsRelationLines.at(4)->seg->endPoint.y - (dfsRelationLines.at(4)->seg->endPoint.y - 10);
					bezierCurvelineSegs.at(2)->curvelineseg->pts[2].x = dfsRelationLines.at(24)->seg->startPoint.x + 5;
					bezierCurvelineSegs.at(2)->curvelineseg->pts[2].y = dfsRelationLines.at(24)->seg->startPoint.y - 20;
					bezierCurvelineSegs.at(2)->curvelineseg->pts[3].x = dfsRelationLines.at(24)->seg->startPoint.x;
					bezierCurvelineSegs.at(2)->curvelineseg->pts[3].y = dfsRelationLines.at(24)->seg->startPoint.y;

					bezierCurvelineSegs.at(6)->curvelineseg->pts[0].x = dfsRelationLines.at(19)->seg->endPoint.x;
					bezierCurvelineSegs.at(6)->curvelineseg->pts[0].y = dfsRelationLines.at(19)->seg->endPoint.y;
					bezierCurvelineSegs.at(6)->curvelineseg->pts[1].x = 2 * dfsRelationLines.at(19)->seg->endPoint.x - (dfsRelationLines.at(19)->seg->endPoint.x + 10);
					bezierCurvelineSegs.at(6)->curvelineseg->pts[1].y = 2 * dfsRelationLines.at(19)->seg->endPoint.y - (dfsRelationLines.at(19)->seg->endPoint.y - 20);
					bezierCurvelineSegs.at(6)->curvelineseg->pts[2].x = dfsRelationLines.at(24)->seg->endPoint.x;
					bezierCurvelineSegs.at(6)->curvelineseg->pts[2].y = dfsRelationLines.at(24)->seg->endPoint.y - 10;
					bezierCurvelineSegs.at(6)->curvelineseg->pts[3].x = dfsRelationLines.at(24)->seg->endPoint.x;
					bezierCurvelineSegs.at(6)->curvelineseg->pts[3].y = dfsRelationLines.at(24)->seg->endPoint.y;

					bezierCurvelineSegs.at(3)->curvelineseg->pts[0].x = dfsRelationLines.at(6)->seg->startPoint.x;
					bezierCurvelineSegs.at(3)->curvelineseg->pts[0].y = dfsRelationLines.at(6)->seg->startPoint.y;
					bezierCurvelineSegs.at(3)->curvelineseg->pts[1].x = dfsRelationLines.at(6)->seg->startPoint.x + 10;
					bezierCurvelineSegs.at(3)->curvelineseg->pts[1].y = dfsRelationLines.at(6)->seg->startPoint.y + 10;
					bezierCurvelineSegs.at(3)->curvelineseg->pts[2].x = dfsRelationLines.at(28)->seg->startPoint.x - 2;
					bezierCurvelineSegs.at(3)->curvelineseg->pts[2].y = dfsRelationLines.at(28)->seg->startPoint.y - 10;
					bezierCurvelineSegs.at(3)->curvelineseg->pts[3].x = dfsRelationLines.at(28)->seg->startPoint.x;
					bezierCurvelineSegs.at(3)->curvelineseg->pts[3].y = dfsRelationLines.at(28)->seg->startPoint.y;


					bezierCurvelineSegs.at(7)->curvelineseg->pts[0].y = dfsRelationLines.at(7)->seg->endPoint.y;   //curveline_P24P29
					bezierCurvelineSegs.at(7)->curvelineseg->pts[1].y = dfsRelationLines.at(7)->seg->endPoint.y + 10;
					bezierCurvelineSegs.at(7)->curvelineseg->pts[2].y = dfsRelationLines.at(28)->seg->endPoint.y - 5;
					bezierCurvelineSegs.at(7)->curvelineseg->pts[3].y = dfsRelationLines.at(28)->seg->endPoint.y;


				}
				
				
			}
			else if (selectLineSeg->bSelLine){//select the line segment
			/*	selectLineSeg->seg->endPoint.x = event->pos().x();
				selectLineSeg->seg->endPoint.y = event->pos().y();*/

				if (selEntityVert == "V10")
				{
					selectLineSeg->seg->endPoint.x = event->pos().x();

					dfsRelationLines.at(0)->seg->startPoint.x = selectLineSeg->seg->endPoint.x;
					dfsRelationLines.at(0)->seg->endPoint.x = dfsRelationLines.at(0)->seg->startPoint.x + 10;

					lineSegs.at(17)->seg->endPoint.x = dfsRelationLines.at(0)->seg->startPoint.x;
					lineSegs.at(33)->seg->startPoint.x = dfsRelationLines.at(0)->seg->endPoint.x;
				}

				else if (selEntityVert == "V12")
				{
					selectLineSeg->seg->endPoint.x = event->pos().x();

					dfsRelationLines.at(0)->seg->startPoint.x = selectLineSeg->seg->endPoint.x;
					dfsRelationLines.at(0)->seg->endPoint.x = dfsRelationLines.at(0)->seg->startPoint.x - 10;

					lineSegs.at(16)->seg->endPoint.x = dfsRelationLines.at(0)->seg->startPoint.x;
					lineSegs.at(34)->seg->startPoint.x = dfsRelationLines.at(0)->seg->endPoint.x;
				}

				else if (selEntityVert == "V3")
				{
					selectLineSeg->seg->endPoint.y = event->pos().y();

					//V4:
					dfsRelationLines.at(0)->seg->endPoint.y = y_1 + (event->pos().y() - y_1) / 2 - 5 * 5;

					//V11:
					dfsRelationLines.at(1)->seg->startPoint.y = y_1 + (event->pos().y() - y_1) / 2 - 5 * 5;
					dfsRelationLines.at(1)->seg->endPoint.y = y_1 + (event->pos().y() - y_1) / 2 - 5 * 5;
					bezierCurvelineSegs.at(2)->curvelineseg->pts[2].y = dfsRelationLines.at(1)->seg->endPoint.y - 10;
					bezierCurvelineSegs.at(2)->curvelineseg->pts[3].y = dfsRelationLines.at(1)->seg->endPoint.y;

					dfsRelationLines.at(2)->seg->startPoint.y = dfsRelationLines.at(0)->seg->endPoint.y;
					dfsRelationLines.at(2)->seg->endPoint.y = selectLineSeg->seg->endPoint.y;

					//V23:
					dfsRelationLines.at(3)->seg->startPoint.y = dfsRelationLines.at(0)->seg->endPoint.y;
					dfsRelationLines.at(3)->seg->endPoint.y = dfsRelationLines.at(0)->seg->endPoint.y;

					dfsRelationLines.at(4)->seg->startPoint.y = selectLineSeg->seg->endPoint.y;
					dfsRelationLines.at(4)->seg->endPoint.y = dfsRelationLines.at(0)->seg->endPoint.y;

					bezierCurvelineSegs.at(6)->curvelineseg->pts[2].y = dfsRelationLines.at(3)->seg->endPoint.y - 10;
					bezierCurvelineSegs.at(6)->curvelineseg->pts[3].y = dfsRelationLines.at(3)->seg->endPoint.y;

					//V13:
					dfsRelationLines.at(5)->seg->startPoint.y = dfsRelationLines.at(1)->seg->startPoint.y; 
					dfsRelationLines.at(5)->seg->endPoint.y = dfsRelationLines.at(1)->seg->startPoint.y;   

					dfsRelationLines.at(6)->seg->startPoint.y = dfsRelationLines.at(1)->seg->startPoint.y;
					dfsRelationLines.at(6)->seg->endPoint.y = selectLineSeg->seg->endPoint.y;

					bezierCurvelineSegs.at(3)->curvelineseg->pts[2].y = dfsRelationLines.at(5)->seg->endPoint.y - 10;
					bezierCurvelineSegs.at(3)->curvelineseg->pts[3].y = dfsRelationLines.at(5)->seg->endPoint.y;

					//V25:
					dfsRelationLines.at(7)->seg->startPoint.y = dfsRelationLines.at(1)->seg->startPoint.y;
					dfsRelationLines.at(7)->seg->endPoint.y = dfsRelationLines.at(1)->seg->startPoint.y;

					dfsRelationLines.at(8)->seg->startPoint.y = selectLineSeg->seg->endPoint.y;
					dfsRelationLines.at(8)->seg->endPoint.y = dfsRelationLines.at(1)->seg->startPoint.y;

					bezierCurvelineSegs.at(7)->curvelineseg->pts[2].y = dfsRelationLines.at(7)->seg->endPoint.y - 5;
					bezierCurvelineSegs.at(7)->curvelineseg->pts[3].y = dfsRelationLines.at(7)->seg->endPoint.y;

					//V10:
					dfsRelationLines.at(9)->seg->startPoint.y = selectLineSeg->seg->endPoint.y;
					dfsRelationLines.at(9)->seg->endPoint.y = selectLineSeg->seg->endPoint.y;

					//V22:
					dfsRelationLines.at(10)->seg->startPoint.y = selectLineSeg->seg->endPoint.y;
					dfsRelationLines.at(10)->seg->endPoint.y = selectLineSeg->seg->endPoint.y;

					//V12:
					dfsRelationLines.at(11)->seg->startPoint.y = selectLineSeg->seg->endPoint.y;
					dfsRelationLines.at(11)->seg->endPoint.y = selectLineSeg->seg->endPoint.y;

					//V24:
					dfsRelationLines.at(12)->seg->startPoint.y = selectLineSeg->seg->endPoint.y;
					dfsRelationLines.at(12)->seg->endPoint.y = selectLineSeg->seg->endPoint.y;


				}
			
				else if (selEntityVert == "V11"){
					selectLineSeg->seg->endPoint.x = event->pos().x();

					lineSegs.at(17)->seg->startPoint.x = selectLineSeg->seg->endPoint.x;
					bezierCurvelineSegs.at(2)->curvelineseg->pts[2].x = selectLineSeg->seg->endPoint.x + 5;
					bezierCurvelineSegs.at(2)->curvelineseg->pts[3].x = selectLineSeg->seg->endPoint.x;

					//V23:
					dfsRelationLines.at(0)->seg->startPoint.x = selectLineSeg->seg->endPoint.x;
					dfsRelationLines.at(0)->seg->endPoint.x = selectLineSeg->seg->endPoint.x + 10;

					dfsRelationLines.at(1)->seg->endPoint.x = dfsRelationLines.at(0)->seg->endPoint.x;
					bezierCurvelineSegs.at(6)->curvelineseg->pts[2].x = dfsRelationLines.at(0)->seg->endPoint.x;
					bezierCurvelineSegs.at(6)->curvelineseg->pts[3].x = dfsRelationLines.at(0)->seg->endPoint.x;
				}

				else if (selEntityVert == "V13")
				{
					selectLineSeg->seg->endPoint.x = event->pos().x();

					lineSegs.at(16)->seg->startPoint.x = selectLineSeg->seg->endPoint.x;
					bezierCurvelineSegs.at(3)->curvelineseg->pts[2].x = selectLineSeg->seg->endPoint.x - 2;
					bezierCurvelineSegs.at(3)->curvelineseg->pts[3].x = selectLineSeg->seg->endPoint.x;

					dfsRelationLines.at(0)->seg->startPoint.x = selectLineSeg->seg->endPoint.x;
					dfsRelationLines.at(0)->seg->endPoint.x = selectLineSeg->seg->endPoint.x - 10;

					dfsRelationLines.at(1)->seg->endPoint.x = dfsRelationLines.at(0)->seg->endPoint.x;

					bezierCurvelineSegs.at(7)->curvelineseg->pts[2].x = dfsRelationLines.at(0)->seg->endPoint.x + 5;
					bezierCurvelineSegs.at(7)->curvelineseg->pts[3].x = dfsRelationLines.at(0)->seg->endPoint.x;
				}


				else if (selEntityVert == "V1")
				{
					selectLineSeg->seg->endPoint.y = event->pos().y();

					//V2:
					dfsRelationLines.at(0)->seg->startPoint.y = selectLineSeg->seg->endPoint.y;  //lineseg_P1P2
					dfsRelationLines.at(0)->seg->endPoint.y = dfsRelationLines.at(0)->seg->startPoint.y - (dfsRelationLines.at(0)->seg->startPoint.y - y_0) / 3;


					//V5:
					dfsRelationLines.at(1)->seg->startPoint.y = dfsRelationLines.at(0)->seg->startPoint.y;  //lineseg_P1P5
					dfsRelationLines.at(1)->seg->endPoint.y = dfsRelationLines.at(0)->seg->startPoint.y;

					dfsRelationLines.at(2)->seg->startPoint.y = dfsRelationLines.at(1)->seg->endPoint.y;  //lineseg_P5P6
					dfsRelationLines.at(2)->seg->endPoint.y = dfsRelationLines.at(0)->seg->endPoint.y;


					dfsRelationLines.at(3)->seg->startPoint.y = dfsRelationLines.at(0)->seg->endPoint.y; //lineseg_P6P7
					dfsRelationLines.at(3)->seg->endPoint.y = y_0;


					lineSegs.at(10)->seg->startPoint.y = dfsRelationLines.at(3)->seg->startPoint.y;

					//V6:
					dfsRelationLines.at(4)->seg->startPoint.y = dfsRelationLines.at(0)->seg->endPoint.y; //lineseg_P6P8
					dfsRelationLines.at(4)->seg->endPoint.y = dfsRelationLines.at(0)->seg->endPoint.y;
					//dfsRelationLines.at(4)->itemType = ItemType_Solid_Front_line;

					//V7:
					dfsRelationLines.at(5)->seg->startPoint.y = dfsRelationLines.at(0)->seg->startPoint.y; //lineseg_P5P9
					dfsRelationLines.at(5)->seg->endPoint.y = dfsRelationLines.at(0)->seg->startPoint.y;

					//V19:
					dfsRelationLines.at(6)->seg->startPoint.y = dfsRelationLines.at(0)->seg->startPoint.y; //lineseg_P9P23
					dfsRelationLines.at(6)->seg->endPoint.y = dfsRelationLines.at(0)->seg->startPoint.y;

					bezierCurvelineSegs.at(0)->curvelineseg->pts[0].y = dfsRelationLines.at(3)->seg->startPoint.y;
					bezierCurvelineSegs.at(0)->curvelineseg->pts[1].y = dfsRelationLines.at(3)->seg->startPoint.y + (dfsRelationLines.at(2)->seg->startPoint.y - dfsRelationLines.at(3)->seg->startPoint.y) / 2;
					bezierCurvelineSegs.at(0)->curvelineseg->pts[2].y = dfsRelationLines.at(2)->seg->startPoint.y;
					bezierCurvelineSegs.at(0)->curvelineseg->pts[3].y = dfsRelationLines.at(6)->seg->startPoint.y;

					//bezierCurvelineSegs.at(3)->curvelineseg->pts[0].y = dfsRelationLines.at(6)->seg->startPoint.y;
					//bezierCurvelineSegs.at(3)->curvelineseg->pts[1].y = dfsRelationLines.at(6)->seg->startPoint.y + 10;

					//V20:
					dfsRelationLines.at(7)->seg->startPoint.y = dfsRelationLines.at(0)->seg->startPoint.y; //lineseg_P23P24
					dfsRelationLines.at(7)->seg->endPoint.y = dfsRelationLines.at(0)->seg->startPoint.y + 5;

					dfsRelationLines.at(8)->seg->startPoint.y = y_18 + (dfsRelationLines.at(0)->seg->startPoint.y - y_18) / 2;

					//V8:
					dfsRelationLines.at(10)->seg->startPoint.y = dfsRelationLines.at(0)->seg->endPoint.y; //lineseg_P6P10

					//V9:


					//V14:
					dfsRelationLines.at(12)->seg->startPoint.y = dfsRelationLines.at(2)->seg->startPoint.y; //lineseg_P5P16
					dfsRelationLines.at(12)->seg->endPoint.y = dfsRelationLines.at(2)->seg->startPoint.y;

					dfsRelationLines.at(13)->seg->startPoint.y = dfsRelationLines.at(12)->seg->endPoint.y; //lineseg_P16P17
					dfsRelationLines.at(13)->seg->endPoint.y = dfsRelationLines.at(0)->seg->endPoint.y;

					dfsRelationLines.at(14)->seg->startPoint.y = dfsRelationLines.at(13)->seg->startPoint.y; //lineseg_P16P18

					//V16:

					//V17:

					//V18:

					//V15:
					dfsRelationLines.at(18)->seg->startPoint.y = dfsRelationLines.at(12)->seg->startPoint.y; //lineseg_P16P19
					dfsRelationLines.at(18)->seg->endPoint.y = y_18 + (dfsRelationLines.at(18)->seg->startPoint.y - y_18) / 2;

					lineSegs.at(27)->seg->startPoint.y = dfsRelationLines.at(18)->seg->endPoint.y;  //lineseg_P19P21

					bezierCurvelineSegs.at(4)->curvelineseg->pts[0].y = dfsRelationLines.at(18)->seg->endPoint.y;  //curveline_P19P17P5P24
					bezierCurvelineSegs.at(4)->curvelineseg->pts[1].y = dfsRelationLines.at(13)->seg->endPoint.y;
					bezierCurvelineSegs.at(4)->curvelineseg->pts[2].y = dfsRelationLines.at(2)->seg->startPoint.y + 15;
					bezierCurvelineSegs.at(4)->curvelineseg->pts[3].y = dfsRelationLines.at(7)->seg->endPoint.y;

					bezierCurvelineSegs.at(7)->curvelineseg->pts[0].y = dfsRelationLines.at(7)->seg->endPoint.y;   //curveline_P24P29
					bezierCurvelineSegs.at(7)->curvelineseg->pts[1].y = dfsRelationLines.at(7)->seg->endPoint.y + 10;

					//V21:
					dfsRelationLines.at(19)->seg->startPoint.y = dfsRelationLines.at(0)->seg->endPoint.y; //lineseg_P17P25
					dfsRelationLines.at(19)->seg->endPoint.y = dfsRelationLines.at(0)->seg->endPoint.y;

					//V3:
					
					//V4:
					dfsRelationLines.at(21)->seg->startPoint.y = dfsRelationLines.at(0)->seg->startPoint.y;  //lineseg_P1P4
					dfsRelationLines.at(21)->seg->endPoint.y = dfsRelationLines.at(0)->seg->startPoint.y + (y_3 - dfsRelationLines.at(0)->seg->startPoint.y) / 2 - 5 * 5;
					//dfsRelationLines.at(21)->itemType = ItemType_Solid_Back_line;

					//V11:
					dfsRelationLines.at(22)->seg->startPoint.y = dfsRelationLines.at(21)->seg->endPoint.y; //lineseg_P4P13
					dfsRelationLines.at(22)->seg->endPoint.y = dfsRelationLines.at(21)->seg->endPoint.y;

					dfsRelationLines.at(23)->seg->startPoint.y = dfsRelationLines.at(22)->seg->endPoint.y; //lineseg_P13P12

					//V23:
					dfsRelationLines.at(24)->seg->startPoint.y = dfsRelationLines.at(21)->seg->endPoint.y; //lineseg_P13P27
					dfsRelationLines.at(24)->seg->endPoint.y = dfsRelationLines.at(21)->seg->endPoint.y;
				

					dfsRelationLines.at(25)->seg->endPoint.y = dfsRelationLines.at(24)->seg->startPoint.y;

					//V13:
					dfsRelationLines.at(26)->seg->startPoint.y = dfsRelationLines.at(21)->seg->endPoint.y; //lineseg_P4P15
					dfsRelationLines.at(26)->seg->endPoint.y = dfsRelationLines.at(21)->seg->endPoint.y;

					dfsRelationLines.at(27)->seg->startPoint.y = dfsRelationLines.at(26)->seg->endPoint.y;

					//V25:
					dfsRelationLines.at(28)->seg->startPoint.y = dfsRelationLines.at(26)->seg->startPoint.y; //lineseg_P15P29
					dfsRelationLines.at(28)->seg->endPoint.y = dfsRelationLines.at(26)->seg->endPoint.y;

					dfsRelationLines.at(29)->seg->endPoint.y = dfsRelationLines.at(28)->seg->endPoint.y;


					bezierCurvelineSegs.at(1)->curvelineseg->pts[2].x = dfsRelationLines.at(4)->seg->endPoint.x;
					bezierCurvelineSegs.at(1)->curvelineseg->pts[2].y = dfsRelationLines.at(4)->seg->endPoint.y -10;
					bezierCurvelineSegs.at(1)->curvelineseg->pts[3].x = dfsRelationLines.at(4)->seg->endPoint.x;
					bezierCurvelineSegs.at(1)->curvelineseg->pts[3].y = dfsRelationLines.at(4)->seg->endPoint.y;

					bezierCurvelineSegs.at(5)->curvelineseg->pts[2].x = dfsRelationLines.at(19)->seg->endPoint.x + 5;
					bezierCurvelineSegs.at(5)->curvelineseg->pts[2].y = dfsRelationLines.at(19)->seg->endPoint.y - 20;
					bezierCurvelineSegs.at(5)->curvelineseg->pts[3].x = dfsRelationLines.at(19)->seg->endPoint.x;
					bezierCurvelineSegs.at(5)->curvelineseg->pts[3].y = dfsRelationLines.at(19)->seg->endPoint.y;

					bezierCurvelineSegs.at(2)->curvelineseg->pts[0].x = dfsRelationLines.at(4)->seg->endPoint.x;
					bezierCurvelineSegs.at(2)->curvelineseg->pts[0].y = dfsRelationLines.at(4)->seg->endPoint.y;
					bezierCurvelineSegs.at(2)->curvelineseg->pts[1].x = 2 * dfsRelationLines.at(4)->seg->endPoint.x - (dfsRelationLines.at(4)->seg->endPoint.x);
					bezierCurvelineSegs.at(2)->curvelineseg->pts[1].y = 2 * dfsRelationLines.at(4)->seg->endPoint.y - (dfsRelationLines.at(4)->seg->endPoint.y - 10);
					bezierCurvelineSegs.at(2)->curvelineseg->pts[2].x = dfsRelationLines.at(24)->seg->startPoint.x + 5;
					bezierCurvelineSegs.at(2)->curvelineseg->pts[2].y = dfsRelationLines.at(24)->seg->startPoint.y - 20;
					bezierCurvelineSegs.at(2)->curvelineseg->pts[3].x = dfsRelationLines.at(24)->seg->startPoint.x;
					bezierCurvelineSegs.at(2)->curvelineseg->pts[3].y = dfsRelationLines.at(24)->seg->startPoint.y;

					bezierCurvelineSegs.at(6)->curvelineseg->pts[0].x = dfsRelationLines.at(19)->seg->endPoint.x;
					bezierCurvelineSegs.at(6)->curvelineseg->pts[0].y = dfsRelationLines.at(19)->seg->endPoint.y;
					bezierCurvelineSegs.at(6)->curvelineseg->pts[1].x = 2 * dfsRelationLines.at(19)->seg->endPoint.x - (dfsRelationLines.at(19)->seg->endPoint.x +10);
					bezierCurvelineSegs.at(6)->curvelineseg->pts[1].y = 2 * dfsRelationLines.at(19)->seg->endPoint.y - (dfsRelationLines.at(19)->seg->endPoint.y - 20);
					bezierCurvelineSegs.at(6)->curvelineseg->pts[2].x = dfsRelationLines.at(24)->seg->endPoint.x;
					bezierCurvelineSegs.at(6)->curvelineseg->pts[2].y = dfsRelationLines.at(24)->seg->endPoint.y - 10;
					bezierCurvelineSegs.at(6)->curvelineseg->pts[3].x = dfsRelationLines.at(24)->seg->endPoint.x;
					bezierCurvelineSegs.at(6)->curvelineseg->pts[3].y = dfsRelationLines.at(24)->seg->endPoint.y;

					bezierCurvelineSegs.at(3)->curvelineseg->pts[0].x = dfsRelationLines.at(6)->seg->startPoint.x;
					bezierCurvelineSegs.at(3)->curvelineseg->pts[0].y = dfsRelationLines.at(6)->seg->startPoint.y;
					bezierCurvelineSegs.at(3)->curvelineseg->pts[1].x = dfsRelationLines.at(6)->seg->startPoint.x + 10;
					bezierCurvelineSegs.at(3)->curvelineseg->pts[1].y = dfsRelationLines.at(6)->seg->startPoint.y + 10;
					bezierCurvelineSegs.at(3)->curvelineseg->pts[2].x = dfsRelationLines.at(28)->seg->startPoint.x - 2;
					bezierCurvelineSegs.at(3)->curvelineseg->pts[2].y = dfsRelationLines.at(28)->seg->startPoint.y - 10;
					bezierCurvelineSegs.at(3)->curvelineseg->pts[3].x = dfsRelationLines.at(28)->seg->startPoint.x;
					bezierCurvelineSegs.at(3)->curvelineseg->pts[3].y = dfsRelationLines.at(28)->seg->startPoint.y;

					bezierCurvelineSegs.at(7)->curvelineseg->pts[0].y = dfsRelationLines.at(7)->seg->endPoint.y;   //curveline_P24P29
					bezierCurvelineSegs.at(7)->curvelineseg->pts[1].y = dfsRelationLines.at(7)->seg->endPoint.y + 10;
					bezierCurvelineSegs.at(7)->curvelineseg->pts[2].y = dfsRelationLines.at(28)->seg->endPoint.y - 5;
					bezierCurvelineSegs.at(7)->curvelineseg->pts[3].y = dfsRelationLines.at(28)->seg->endPoint.y;
				
				}


			}
			selectLineSeg->bDraw = true;
	
			selectLineSeg->bSelStartPt = false;
			selectLineSeg->bSelEndPt = false;
			selectLineSeg->bSelLine = false;
			selectLineSeg = nullptr;
			if (!selEntityVert.empty()){
				selEntityVert.erase();
			}
			selectLineSeg = nullptr;
			//dfsRelationLines.clear();

		}

		else if (selectRectSeg != nullptr)
		{
			if (selectRectSeg->bSelFrame)
			{
				selectRectSeg->rectseg->beginPt.x = beginPoint.x();
				selectRectSeg->rectseg->beginPt.y = beginPoint.y();
			}
			selectRectSeg->bDraw = true;
			selectRectSeg = nullptr;
		}

		else if (selectCurveLineSeg != nullptr)
		{
			if (selectCurveLineSeg->bSelPtCtr2)
			{
				selectCurveLineSeg->curvelineseg->pts[1].x = curveCtrlPt2.x();
				selectCurveLineSeg->curvelineseg->pts[1].y = curveCtrlPt2.y();
			}

			else if (selectCurveLineSeg->bSelPtCtr3)
			{
				selectCurveLineSeg->curvelineseg->pts[2].x = curveCtrlPt3.x();
				selectCurveLineSeg->curvelineseg->pts[2].y = curveCtrlPt3.y();
			}

			selectCurveLineSeg->bDraw = true;
			selectCurveLineSeg = nullptr;
		}
		else
		{
			selectLineSeg = nullptr;
			selectCurveLineSeg = nullptr;
		}

		break;
	default:
		break;

	}
	update();
}

void myQt2020::selSeg(QPointF &pt){
	int num = lineSegs.size();
	
	//qDebug() << "num:" << num << endl;
	for (int i = 0; i < num; i++){
		LINESEG* oneLine = lineSegs.at(i);
		LineSegment* oneLineDeg = oneLine->seg;

		PointEx ptEx(pt.x(), pt.y());
		PointEx np; //线段上的点
		double dis = pToLinesegDist(ptEx, *oneLineDeg, np);
		if (dis < 5 && dis >= 0.0){
			double l = relation(np, *oneLineDeg);
			if (abs(l) < EP){//起点
				oneLine->bSelStartPt = true;
				oneLine->bSelLine = false;
				oneLine->bSelEndPt = false;
			}
			else if (abs(l - 1.0) < EP) {//终点
				oneLine->bSelEndPt = true;
				oneLine->bSelLine = false;
				oneLine->bSelStartPt = false;
			}
			else if (l < 1 && l > 0) {//整条线
				oneLine->bSelLine = true;
				oneLine->bSelEndPt = false;
				oneLine->bSelStartPt = false;

			}
		}

		else{
			oneLine->bSelLine = false;
			oneLine->bSelEndPt = false;
			oneLine->bSelStartPt = false;
		}

	}


}

void myQt2020::drawLineSeg(QPainter* p)
{
	QPen pen;
	//pen.setColor(QColor(62, 62, 62));

	int num = lineSegs.size();
	QPointF pt1, pt2;
	for (int i = 0; i < num; i++){
		LINESEG* oneLine = lineSegs.at(i);
		if (oneLine->bDraw){ //是否绘制

			switch (oneLine->curShape)
			{
			case ShapeType_LineSegment:
				pt1.setX(oneLine->seg->startPoint.x);
				pt1.setY(oneLine->seg->startPoint.y);

				pt2.setX(oneLine->seg->endPoint.x);
				pt2.setY(oneLine->seg->endPoint.y);

				if (oneLine->bSelLine || oneLine->bSelStartPt || oneLine->bSelEndPt){ //选中
					pen.setColor(QColor(255, 255, 0));
					pen.setWidth(4);
					p->setPen(pen);

					if (oneLine->bSelLine){
						p->drawLine(pt1, pt2);
					}
					else if (oneLine->bSelStartPt){
						p->drawEllipse(pt1, 5, 5);
						pen.setWidth(2);
						p->setPen(pen);
						p->drawLine(pt1, pt2);
					}
					else if (oneLine->bSelEndPt){
						p->drawEllipse(pt2, 5, 5);
						pen.setWidth(2);
						p->setPen(pen);
						p->drawLine(pt1, pt2);
					}	
				}
				else if (oneLine->bSelLine == false && oneLine->bSelStartPt == false && oneLine->bSelEndPt == false) {
					//pen.setColor(QColor(62, 62, 62));
					//pen.setWidth(2);
					if ((oneLine->itemType == ItemType_Aux_line) && (bPainting_FP == true) && (bPainting_BP == true)){
						p->setPen(QPen(QBrush(QColor(62, 62, 62)), 2, Qt::DashLine));
						p->drawLine(pt1, pt2);
					}
					else if ((oneLine->itemType == ItemType_Solid_Front_line) && (bPainting_FP==true))
					{
						p->setPen(QPen(QBrush(QColor(255, 84, 33)), 3, Qt::SolidLine));
						p->drawLine(pt1, pt2);
					}
					else if ((oneLine->itemType == ItemType_Solid_Back_line) && (bPainting_BP==true))
					{
						p->setPen(QPen(QBrush(QColor(5, 1, 130)), 3, Qt::SolidLine));
						p->drawLine(pt1, pt2);
					}
					

				}
				if (!bPainting_FP){
					lineSegs.at(14)->itemType = ItemType_Solid_Back_line;
					lineSegs.at(12)->itemType = ItemType_Solid_Back_line;
					lineSegs.at(29)->itemType = ItemType_Solid_Back_line;
					lineSegs.at(31)->itemType = ItemType_Solid_Back_line;
				}
				else if (!bPainting_BP){
					lineSegs.at(14)->itemType = ItemType_Solid_Front_line;
					lineSegs.at(12)->itemType = ItemType_Solid_Front_line;

				}
				break;
			default:
				break;

			}

		}

	}

}
void myQt2020::drawRectSeg(QPainter* p){
	QPen pen;
	pen.setColor(QColor(255, 0, 0));
	pen.setWidth(2);
	p->setPen(pen);
	int num = rectSegs.size();
	QPointF pt;
	float w;
	float h;
	for (int i = 0; i < num; i++)
	{
		RECTSEG* oneRect = rectSegs.at(i);
		if (oneRect->bDraw)
		{
			switch (oneRect->curShape)
			{
			case ShapeType_Rectangle:
				pt.setX(oneRect->rectseg->beginPt.x);
				pt.setY(oneRect->rectseg->beginPt.y);
				w = oneRect->rectseg->width;
				h = oneRect->rectseg->height;
				p->drawRect(pt.x(), pt.y(), w, h);
				break;
			default:
				break;

			}
		}
	}
}


void myQt2020::drawCurveLineSeg(QPainter* p)
{
	QPen pen;
	pen.setColor(QColor(62, 62, 62));

	int num = bezierCurvelineSegs.size();

	PointEx p0, p1, p2, p3;

	for (int idx = 0; idx < num;idx++){
		CBEZIERCURVE* oneCurveLine = bezierCurvelineSegs.at(idx);
		if (oneCurveLine->bDraw){ //是否绘制
			switch (oneCurveLine->curShape)
			{
			case ShapeType_CurveLine:
				
				m_vecBezierCurvePt.clear();
				m_vecBezierCurvePtCtrls.clear();
				ptCurCtrls.clear();

				p->setPen(QPen(Qt::blue, 0.5));
				p->setBrush(Qt::blue);

				ptCurCtrls = oneCurveLine->curvelineseg->pts;

				for (int i = 0; i < ptCurCtrls.size(); i++)
				{
					QPointF tempPtCtrl(ptCurCtrls[i].x, ptCurCtrls[i].y);

					if ((bPainting_BP == true) && (bPainting_FP == true)){
						p->drawEllipse(tempPtCtrl, 3, 3);
					}
					m_vecBezierCurvePtCtrls.push_back(ptCurCtrls[i]);
				}

				if ((bPainting_BP == true) && (bPainting_FP == true)){
					for (int i = 0; i<ptCurCtrls.size() - 1; ++i){
						p->drawLine(ptCurCtrls[i].x, ptCurCtrls[i].y, ptCurCtrls[i + 1].x, ptCurCtrls[i + 1].y);
					}
				}

				CreateBezierCurve();

				for (int i = 0; i < 100; i++)
				{
					
					if ((oneCurveLine->itemType == ItemType_Solid_Front_line) && (bPainting_FP == true)){
						p->setPen(QPen(QBrush(QColor(255, 84, 33)), 2.5, Qt::SolidLine));
						p->drawLine(m_vecBezierCurvePt[i].x, m_vecBezierCurvePt[i].y, m_vecBezierCurvePt[i + 1].x, m_vecBezierCurvePt[i + 1].y);

					}
					else if ((oneCurveLine->itemType == ItemType_Solid_Back_line) && (bPainting_BP == true)){
						p->setPen(QPen(QBrush(QColor(5, 1, 130)), 2.5, Qt::SolidLine));
						p->drawLine(m_vecBezierCurvePt[i].x, m_vecBezierCurvePt[i].y, m_vecBezierCurvePt[i + 1].x, m_vecBezierCurvePt[i + 1].y);
					}
					
					
				}

				if (oneCurveLine->bSelPtCtr2 == true)
				{
					p->setPen(QPen(Qt::blue, 0.5));
					p->setBrush(Qt::blue);
					QPointF tempPtCtrl(ptCurCtrls[1].x, ptCurCtrls[1].y);
					p->drawEllipse(tempPtCtrl, 5, 5);
				}
				else if (oneCurveLine->bSelPtCtr3 == true)
				{
					p->setPen(QPen(Qt::blue, 0.5));
					p->setBrush(Qt::blue);
					QPointF tempPtCtrl(ptCurCtrls[2].x, ptCurCtrls[2].y);
					p->drawEllipse(tempPtCtrl, 5, 5);
				}

				break;
			default:
				break;
			}
		}

	}
}

void myQt2020::CreateBezierCurve()
{
	float step = 0.01f;
	for (float t = 0; t <= 1.0f; t += step)
	{
		PointEx stPt;
		CalBezierCurvePoint(t, stPt);
		m_vecBezierCurvePt.push_back(stPt);
	}
}

void myQt2020::CalBezierCurvePoint(float t, PointEx &stPt)
{
	float x, y;
	//x = (pt0.x())*pow(1 - t, 2) + (pt1.x())*t*(1 - t) * 2 + (pt2.x())*pow(t, 2);
	//y = (pt0.y())*pow(1 - t, 2) + (pt1.y())*t*(1 - t) * 2 + (pt2.y())*pow(t, 2);
	x = (1 - t)*(1 - t)*(1 - t)*(m_vecBezierCurvePtCtrls[0].x) + 3 * t*(1 - t)*(1 - t)*(m_vecBezierCurvePtCtrls[1].x) + 3 * t*t*(1 - t)*(m_vecBezierCurvePtCtrls[2].x) + (m_vecBezierCurvePtCtrls[3].x)*t*t*t;
	y = (1 - t)*(1 - t)*(1 - t)*(m_vecBezierCurvePtCtrls[0].y) + 3 * t*(1 - t)*(1 - t)*(m_vecBezierCurvePtCtrls[1].y) + 3 * t*t*(1 - t)*(m_vecBezierCurvePtCtrls[2].y) + (m_vecBezierCurvePtCtrls[3].y)*t*t*t;

	stPt.x = x;
	stPt.y = y;
}

void myQt2020::selRectSeg(QPointF &pt) {
	int num = rectSegs.size();

	for (int i = 0; i < num; i++) {
		RECTSEG* oneRect = rectSegs.at(i);
		Rectangle* oneRectDeg = oneRect->rectseg;

		PointEx ptEx(pt.x(), pt.y());

		PointEx point1Ex(oneRectDeg->beginPt.x, oneRectDeg->beginPt.y);
		PointEx point2Ex(oneRectDeg->beginPt.x + oneRectDeg->width, oneRectDeg->beginPt.y);
		PointEx point3Ex(oneRectDeg->beginPt.x + oneRectDeg->width, oneRectDeg->beginPt.y + oneRectDeg->height);
		PointEx point4Ex(oneRectDeg->beginPt.x, oneRectDeg->beginPt.y + oneRectDeg->height);

		bool isPointIn = (GetCross(point1Ex, point2Ex, ptEx) * GetCross(point3Ex, point4Ex, ptEx) >= 0) && ((GetCross(point2Ex, point3Ex, ptEx)*GetCross(point4Ex, point1Ex, ptEx)) >= 0);

		//qDebug() << "isPointIn:" << isPointIn << endl;

		oneRect->bSelFrame = isPointIn;

	}

}

float myQt2020::GetCross(PointEx p1, PointEx p2, PointEx p)
{
	return (p2.x - p1.x)*(p.y - p1.y) - (p.x - p1.x)*(p2.y - p1.y);
}

int myQt2020::getSeleled(){
	int num = lineSegs.size();
	//qDebug() << "num:" << num << endl;
	for (int idx = 0; idx < num; idx++){
		LINESEG* oneLine = lineSegs.at(idx);
		//std::vector<LINESEG*> dfsRelationLines;
		//dfsRelationLines.push_back(lineSegs.at(idx));
		//dfsRelationLines.push_back(lineSegs.at(4));
		if (oneLine->bSelLine || oneLine->bSelStartPt || oneLine->bSelEndPt){ 
			//qDebug() << "selLineId:" << idx << endl;
			selLineId = idx;
			//pG->DFS(selLineId);
			return selLineId;
				
		}
	}

	return -1;
	
}

RECTSEG* myQt2020::getSeleledRectSeg()
{
	int num = rectSegs.size();
	for (int i = 0; i < num; i++)
	{
		RECTSEG* oneRect = rectSegs.at(i);
		if (oneRect->bSelFrame){ //selection
			qDebug() << "bSelFrame" << endl;
		}
		return oneRect;
	}
	return nullptr;
}

CBEZIERCURVE* myQt2020::getSeleledCurve()
{
	CBEZIERCURVE* oneCurveLine = nullptr;
	if (selCurveLineId != -1)
	{
		oneCurveLine = bezierCurvelineSegs.at(selCurveLineId);

		return  oneCurveLine;
	}


	return nullptr;

}

void myQt2020::selCurveSeg(QPointF &pt)
{
	int numCurve = bezierCurvelineSegs.size();

	for (int idx = 0; idx < numCurve; idx++) {
		CBEZIERCURVE* onebeziercurveLine = bezierCurvelineSegs.at(idx);
		onebeziercurveLine->bSelPtCtr1 = false;
		onebeziercurveLine->bSelPtCtr2 = false;
		onebeziercurveLine->bSelPtCtr3 = false;
		onebeziercurveLine->bSelPtCtr4 = false;

		onebezierLineSeg = onebeziercurveLine->curvelineseg;

		std::vector<PointEx> ptCurveCtrls = onebezierLineSeg->pts;

		int numCtrls = ptCurveCtrls.size();

		for (int i = 0; i < numCtrls; i++)
		{
			PointEx ptEx(pt.x(), pt.y());
			PointEx tempPt;
			tempPt.x = ptCurveCtrls[i].x;
			tempPt.y = ptCurveCtrls[i].y;
			double disCtrls = dist(tempPt, ptEx);
			if (disCtrls < 5.0)
			{
				qDebug() << "disCtrls:" << disCtrls << endl;

				selCurveLineId = idx;

				qDebug() << "selCurveLineId:" << selCurveLineId << endl;

				onebeziercurveLine->bSelLine = true;
				switch (i)
				{
				case 0:
					onebeziercurveLine->bSelPtCtr1 = true;
					qDebug() << "onebeziercurveLine->bSelPtCtr1" << endl;
					break;
				case 1:
					onebeziercurveLine->bSelPtCtr2 = true;
					qDebug() << "onebeziercurveLine->bSelPtCtr2" << endl;
					break;
				case 2:
					onebeziercurveLine->bSelPtCtr3 = true;
					qDebug() << "onebeziercurveLine->bSelPtCtr3" << endl;
					break;
				case 3:
					onebeziercurveLine->bSelPtCtr4 = true;
					qDebug() << "onebeziercurveLine->bSelPtCtr4" << endl;
					break;
				default:
					break;
				}

			}
		}
	}
}

void myQt2020::changeSL(bool boolValue)
{
	islineEdit = boolValue;
	
}

void myQt2020::changeCL(bool boolValue)
{
	islineEdit = boolValue;

	dfsRelationLines.swap(std::vector<LINESEG*>());
	dfsRelVids.swap(std::vector<string>());
}

void myQt2020::showBP(bool boolValue)
{
	bPainting_FP = boolValue;
}

void myQt2020::showFP(bool boolValue)
{
	bPainting_BP = boolValue;
}



void myQt2020::findLineSegs(int i)
{
	switch (i)
	{
	case EntityPt_V1:
		dfsRelationLines.push_back(lineSegs.at(0));
		break;
	case EntityPt_V2:
		dfsRelationLines.push_back(lineSegs.at(1));
		break;
	case EntityPt_V3:
		dfsRelationLines.push_back(lineSegs.at(2));
		break;
	case EntityPt_V4:
		dfsRelationLines.push_back(lineSegs.at(3));
		break;
	case EntityPt_V5:
		dfsRelationLines.push_back(lineSegs.at(4));
		dfsRelationLines.push_back(lineSegs.at(5));
		dfsRelationLines.push_back(lineSegs.at(6));
		break;
	case EntityPt_V6:
		dfsRelationLines.push_back(lineSegs.at(7));
		break;
	case EntityPt_V7:
		dfsRelationLines.push_back(lineSegs.at(8));
		break;
	case EntityPt_V8:
		dfsRelationLines.push_back(lineSegs.at(9));
		dfsRelationLines.push_back(lineSegs.at(10));
		break;
	case EntityPt_V9:
		dfsRelationLines.push_back(lineSegs.at(11));
		break;
	case EntityPt_V10:
		dfsRelationLines.push_back(lineSegs.at(12));
		break;
	case EntityPt_V11:
		dfsRelationLines.push_back(lineSegs.at(13));
		dfsRelationLines.push_back(lineSegs.at(17));
		break;
	case EntityPt_V12:
		dfsRelationLines.push_back(lineSegs.at(14));
		break;
	case EntityPt_V13:
		dfsRelationLines.push_back(lineSegs.at(15));
		dfsRelationLines.push_back(lineSegs.at(16));
		break;
	case EntityPt_V14:
		dfsRelationLines.push_back(lineSegs.at(18));
		dfsRelationLines.push_back(lineSegs.at(19));
		dfsRelationLines.push_back(lineSegs.at(20));
		break;
	case EntityPt_V15:
		dfsRelationLines.push_back(lineSegs.at(21));
		break;
	case EntityPt_V16:
		dfsRelationLines.push_back(lineSegs.at(22));
		break;
	case EntityPt_V17:
		dfsRelationLines.push_back(lineSegs.at(23));
		break;
	case EntityPt_V18:
		dfsRelationLines.push_back(lineSegs.at(24));
		break;
	case EntityPt_V19:
		dfsRelationLines.push_back(lineSegs.at(25));
		break;
	case EntityPt_V20:
		dfsRelationLines.push_back(lineSegs.at(26));
		dfsRelationLines.push_back(lineSegs.at(27));
		break;
	case EntityPt_V21:
		dfsRelationLines.push_back(lineSegs.at(28));
		break;
	case EntityPt_V22:
		dfsRelationLines.push_back(lineSegs.at(29));
		break;
	case EntityPt_V23:
		dfsRelationLines.push_back(lineSegs.at(30));
		dfsRelationLines.push_back(lineSegs.at(33));
		break;
	case EntityPt_V24:
		dfsRelationLines.push_back(lineSegs.at(31));
		break;
	case EntityPt_V25:
		dfsRelationLines.push_back(lineSegs.at(32));
		dfsRelationLines.push_back(lineSegs.at(34));
		break;
	default:
		break;

	}
		
}

void myQt2020::savePicture()
{
	#if (QT_VERSION <= QT_VERSION_CHECK(5,0,0))
	#if _MSC_VER
		QTextCodec *codec = QTextCodec::codecForName("gbk");
	#else
		QTextCodec *codec = QTextCodec::codecForName("utf-8");
	#endif
		QTextCodec::setCodecForLocale(codec);
		QTextCodec::setCodecForCStrings(codec);
		QTextCodec::setCodecForTr(codec);
	#else
		QTextCodec *codec = QTextCodec::codecForName("utf-8");
		QTextCodec::setCodecForLocale(codec);
	#endif

	ScreenWidget::Instance()->showFullScreen();   //直接调用实例

}

void myQt2020::recvInfo(const QString &t_waistGirth, const QString &t_hipGirth,
	const QString &t_crotchDepth, const QString &t_trousersLength, const QString &t_sweepBottom)
{
	m_waistline = t_waistGirth;
	m_hipline = t_hipGirth;
	m_crotchDepth = t_crotchDepth;
	m_trousersLength = t_trousersLength;
	m_sweepBottom = t_sweepBottom;


	qDebug() << QString::fromLocal8Bit("recvInfo:");
	qDebug() << QString::fromLocal8Bit("waist_girth:") << t_waistGirth << QString::fromLocal8Bit("hip_girth:") << t_hipGirth
		<< QString::fromLocal8Bit("crotchDepth:") << t_crotchDepth << QString::fromLocal8Bit("trousersLength:") << t_trousersLength << QString::fromLocal8Bit("sweepBottom:") << t_sweepBottom << endl;

	string s_waistline = m_waistline.toStdString();
	input_f_waistline = atof(s_waistline.c_str());
	string s_hipline = m_hipline.toStdString();
	input_f_hipline = atof(s_hipline.c_str());
	string s_crotchDepth = m_crotchDepth.toStdString();
	input_f_crotchDepth = atof(s_crotchDepth.c_str());
	string s_trousersLength = m_trousersLength.toStdString();
	input_f_trousersLength = atof(s_trousersLength.c_str());
	string s_sweepBottom = m_sweepBottom.toStdString();
	input_f_sweepBottom = atof(s_sweepBottom.c_str());

	qDebug() << QString::fromLocal8Bit("waist_girth:") << input_f_waistline << QString::fromLocal8Bit("hip_girth:") << input_f_hipline 
		<< QString::fromLocal8Bit("crotch_depth:") << input_f_crotchDepth << QString::fromLocal8Bit("trousersLength:") << input_f_trousersLength << QString::fromLocal8Bit("sweep_bottom:") << input_f_sweepBottom << endl;

	if (input_f_waistline != 0.0f || input_f_hipline != 0.0f || input_f_crotchDepth != 0.0f || input_f_trousersLength != 0.0f || input_f_sweepBottom!=0.0f){
		initEntity(input_f_waistline, input_f_hipline, input_f_crotchDepth, input_f_trousersLength, input_f_sweepBottom);
	}

	ispainting = true;
}