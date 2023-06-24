#include "pch.h"
#include "MyCurve.h"


MyCurve::MyCurve(CPoint point) : MyShape(point) {
}


void MyCurve::draw(CDC& dc) {
	MyShape::draw(dc);
	dc.MoveTo(point1);
	POSITION pos = points.GetHeadPosition();
	while (pos)
		dc.LineTo(points.GetNext(pos));
	dc.LineTo(point2);
}


void MyCurve::update(CPoint point) {
	MyShape::update(point);
	points.AddTail(point);
}


CRect MyCurve::getBorder() {
	CRect rect(point1, point1);
	rect.InflateRect(1, 1);
	POSITION pos = points.GetHeadPosition();
	while (pos) {
		CPoint p = points.GetNext(pos);
		rect.left = min(rect.left, p.x - 1);
		rect.top = min(rect.top, p.y - 1);
		rect.right = max(rect.right, p.x + 1);
		rect.bottom = max(rect.bottom, p.y + 1);
	}
	return rect;
}


bool MyCurve::isIn(CPoint point) {
	POSITION pos = points.GetHeadPosition();
	while (pos)
	{
		CPoint p = points.GetNext(pos);
		float dist = sqrt((p.x - point.x) * (p.x - point.x) + (p.y - point.y) * (p.y - point.y));
		if (dist < 10)
			return true;
	}
	return false;
}


void MyCurve::move(CPoint point) {
	MyShape::move(point);
	POSITION pos = points.GetHeadPosition();
	while (pos) {
		points.GetNext(pos).Offset(point);
	}
}