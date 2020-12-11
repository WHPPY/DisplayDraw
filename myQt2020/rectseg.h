#ifndef _RECTSEG_H_
#define _RECTSEG_H_
#include "GraphBase.h"
#include "typeshape.h"
#include "figureobj.h"

class RECTSEG : public CFigureObj
{
public:
	bool bDraw;//是否绘制
	bool bSelFrame;//是否选矩形边框
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