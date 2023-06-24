#include "pch.h"
#include "MyCircle.h"


MyCircle::MyCircle(CPoint point) : MyShape(point) {
}


void MyCircle::draw(CDC& dc) {
	MyShape::draw(dc);
	dc.Ellipse(getBorder());
}


CRect MyCircle::getBorder() {
	int radius = sqrt((point1.x - point2.x) * (point1.x - point2.x) + (point1.y - point2.y) * (point1.y - point2.y));
	CPoint p(radius, radius);
	return CRect(CRect(point1 + -p, point1 + p));
}


bool MyCircle::isIn(CPoint point) {
	int r = sqrt((point1.x - point2.x) * (point1.x - point2.x) + (point1.y - point2.y) * (point1.y - point2.y));
	int dist = sqrt((point1.x - point.x) * (point1.x - point.x) + (point1.y - point.y) * (point1.y - point.y));
	if (dist < r)
		return true;
	else
		return false;
}