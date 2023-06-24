#pragma once
#include "MyShape.h"
class MyGroup : public MyShape
{
	CList<MyShape*> children;
public:
	MyGroup(const CList<MyShape*>& children);
	void draw(CDC& dc);
	void update(CPoint point);
	CRect getBorder();
	bool isIn(CPoint point);
	void move(CPoint point);
	void ungroup(CList<MyShape*>& children);
};

