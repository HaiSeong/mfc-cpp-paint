#pragma once
class MyShape
{
protected:
	MyShape(CPoint point);
	CPoint point1;
	CPoint point2;
	CPen pen;
	CBrush brush;
public:
	virtual void draw(CDC& dc);
	virtual void update(CPoint point);
	virtual CRect getBorder() = 0;
	bool isIn(CRect rect);
	virtual bool isIn(CPoint point) = 0;
	virtual void move(CPoint point);
	virtual void ungroup(CList<MyShape *> & children);
};