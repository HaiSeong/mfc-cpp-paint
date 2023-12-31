#include "pch.h"
#include "MyGroup.h"

MyGroup::MyGroup(const CList<MyShape*>& selected) : MyShape(CPoint(0, 0)) {
	POSITION pos = selected.GetHeadPosition();
	while (pos) {
		children.AddTail(selected.GetNext(pos));
	}
}


void MyGroup::draw(CDC& dc) {
	POSITION pos = children.GetHeadPosition();
	while (pos) {
		children.GetNext(pos)->draw(dc);
	}
}


void MyGroup::update(CPoint point) {
}


CRect MyGroup::getBorder() {
	POSITION pos = children.GetHeadPosition();
	CRect rect = children.GetNext(pos)->getBorder();
	while (pos) {
		CRect r = children.GetNext(pos)->getBorder();
		rect.left = min(rect.left, r.left);
		rect.top = min(rect.top, r.top);
		rect.right = max(rect.right, r.right);
		rect.bottom = max(rect.bottom, r.bottom);
	}
	return rect;
}


bool MyGroup::isIn(CPoint point) {
	POSITION pos = children.GetHeadPosition();
	while (pos)
	{
		if (children.GetNext(pos)->isIn(point)) 
			return true;
	}
	return false;
}


void MyGroup::move(CPoint point) {
	POSITION pos = children.GetHeadPosition();
	while (pos) 
		children.GetNext(pos)->move(point);
}


void MyGroup::ungroup(CList<MyShape*>& selected) {
	POSITION pos = children.GetHeadPosition();
	while (pos) 
		selected.AddTail(children.GetNext(pos));
}