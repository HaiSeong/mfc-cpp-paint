#include "pch.h"
#include "MyStar.h"


MyStar::MyStar(CPoint point) : MyShape(point) {
}

void MyStar::calArr() {
	float d = -3.14 / 2;
	const float delta = 2 * 3.14 / 10;
	float r1 = sqrt((point1.x - point2.x) * (point1.x - point2.x) + (point1.y - point2.y) * (point1.y - point2.y));
	float r2 = r1 * 0.45;
	for (int i = 0; i < 5; i++)
	{
		arr[2 * i] = point1 + CPoint(r1 * cos(d), r1 * sin(d));
		d += delta;
		arr[2 * i + 1] = point1 + CPoint(r2 * cos(d), r2 * sin(d));
		d += delta;
	}
}


void MyStar::draw(CDC& dc) {
	MyShape::draw(dc);
	calArr();
	dc.Polygon(arr, 10);
}


CRect MyStar::getBorder() {
	calArr();
	CRect rect(point1, point1);
	for (int i = 0; i < 10; ++i) {
		rect.left = min(rect.left, arr[i].x);
		rect.top = min(rect.top, arr[i].y);
		rect.right = max(rect.right, arr[i].x);
		rect.bottom = max(rect.bottom, arr[i].y);
	}
	return rect;
}


bool MyStar::isIn(CPoint point) {
	CRgn rgn;
	rgn.CreatePolygonRgn(arr, 10, ALTERNATE);
	return rgn.PtInRegion(point);
}