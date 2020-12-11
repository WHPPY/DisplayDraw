#ifndef _LINESEG_H_
#define _LINESEG_H_
#include "figureobj.h"
#include "GraphBase.h"
#include "typeshape.h"

class LINESEG : public CFigureObj
{
public:
	bool bDraw; //是否绘制
	ShapeType curShape;
	bool bSelLine; //是否选中线
	bool bSelStartPt; //是否选中线段起点
	bool bSelEndPt; //是否选线段终点
	LineSegment* seg;
	ItemType itemType;
	LINESEG(){
		bDraw = false;
		curShape = ShapeType_None;
		bSelLine = false;
		bSelStartPt = false;
		bSelEndPt = false;
		seg = new LineSegment;
		itemType = ItemType_None;
	}
};


#endif