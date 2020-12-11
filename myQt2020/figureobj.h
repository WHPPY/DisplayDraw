#ifndef _FIGUREOBJ_H_
#define _FIGUREOBJ_H_


class CFigureObj
{
public:
	void setWidth(int w)
	{
		width = w;
	}
	void setHeight(int h)
	{
		height = h;
	}
protected:
	int width;
	int height;
};


#endif