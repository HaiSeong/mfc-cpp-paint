#include "pch.h"
#include "MyShape.h"

MyShape::MyShape(CPoint point) : point1(point), point2(point) {
	COLORREF pen_color = RGB(rand() % 128, rand() % 128, rand() % 128);
	COLORREF brush_color = pen_color + RGB(128, 128, 128);
	pen.CreatePen(PS_SOLID, 5, pen_color);
	brush.CreateSolidBrush(brush_color);
}


void MyShape::draw(CDC& dc) {
	dc.SelectObject(pen);
	dc.SelectObject(brush);
}


void MyShape::update(CPoint point) {
	point2 = point;
}


bool MyShape::isIn(CRect rect) {
	CRect border = getBorder();
	border.NormalizeRect();
	rect.NormalizeRect();
	CRect intersection;
	intersection.IntersectRect(border, rect);
	return intersection.EqualRect(border);
}


void MyShape::move(CPoint point) {
	point1 += point;
	point2 += point;
}


void MyShape::ungroup(CList<MyShape*>& children) {
}