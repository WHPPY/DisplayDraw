#ifndef _RECTSEG_H_
#define _RECTSEG_H_
#include "GraphBase.h"
#include "typeshape.h"
#include "figureobj.h"

class RECTSEG : public CFigureObj
{
public:
	bool bDraw;//�Ƿ����
	bool bSelFrame;//�Ƿ�ѡ���α߿�
	ShapeType curShape;

	Rectangle* rectseg;
	RECTSEG() {
		bDraw = false;
		bSelFrame = false;
		curShape = ShapeType_None;
		rectseg = new Rectangle;
	}
};

#endif