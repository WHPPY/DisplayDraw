#ifndef _BEZIERCURVE_H_
#define _BEZIERCURVE_H_
#include "figureobj.h"
#include "GraphBase.h"
#include "typeshape.h"

class CBEZIERCURVE : public CFigureObj
{
public:
	bool bDraw;//�Ƿ����
	ShapeType curShape;
	ItemType itemType;
	bool bSelLine;//�Ƿ�ѡ����
	bool bSelPtCtr1;//�Ƿ�ѡ�е�һ�����Ƶ�
	bool bSelPtCtr2;//�Ƿ�ѡ�еڶ������Ƶ�
	bool bSelPtCtr3;//�Ƿ�ѡ�е��������Ƶ�
	bool bSelPtCtr4;//�Ƿ�ѡ�е��ĸ����Ƶ�


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