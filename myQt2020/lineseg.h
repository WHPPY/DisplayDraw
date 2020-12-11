#ifndef _LINESEG_H_
#define _LINESEG_H_
#include "figureobj.h"
#include "GraphBase.h"
#include "typeshape.h"

class LINESEG : public CFigureObj
{
public:
	bool bDraw; //�Ƿ����
	ShapeType curShape;
	bool bSelLine; //�Ƿ�ѡ����
	bool bSelStartPt; //�Ƿ�ѡ���߶����
	bool bSelEndPt; //�Ƿ�ѡ�߶��յ�
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