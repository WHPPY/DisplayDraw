#ifndef _BEZIERCURVE_H_
#define _BEZIERCURVE_H_
#include "figureobj.h"
#include "GraphBase.h"
#include "typeshape.h"

class CBEZIERCURVE : public CFigureObj
{
public:
	bool bDraw;//是否绘制
	ShapeType curShape;
	ItemType itemType;
	bool bSelLine;//是否选中线
	bool bSelPtCtr1;//是否选中第一个控制点
	bool bSelPtCtr2;//是否选中第二个控制点
	bool bSelPtCtr3;//是否选中第三个控制点
	bool bSelPtCtr4;//是否选中第四个控制点


	CurveLineSegment* curvelineseg;

	CBEZIERCURVE()
	{
		bDraw = false;
		curShape = ShapeType_None;
		itemType = ItemType_None;
		bSelLine = false;
		bSelPtCtr1 = false;
		bSelPtCtr2 = false;
		bSelPtCtr3 = false;
		bSelPtCtr4 = false;
		curvelineseg = new CurveLineSegment;
	}

};





#endif