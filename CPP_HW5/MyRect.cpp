#include "pch.h"
#include "MyRect.h"


MyRect::MyRect(CPoint point) : MyShape(point) 
{
}


void MyRect::draw(CDC& dc) {
	MyShape::draw(dc);
	dc.Rectangle(getBorder());
}


void MyRect::update(CPoint point) {
	MyShape::update(point);
	point1.x = min(point1.x, point.x);
	point1.y = min(point1.y, point.y);
	
}


CRect MyRect::getBorder() {
	return CRect(point1, point2 + CPoint(1, 1));
}


bool MyRect::isIn(CPoint point) {
	return getBorder().PtInRect(point);
}