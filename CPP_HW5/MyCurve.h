#pragma once
#include "MyShape.h"
class MyCurve : public MyShape
{
    CList<CPoint> points;
public:
    MyCurve(CPoint point);
    void draw(CDC& dc);
    void update(CPoint point);
    CRect getBorder();
    bool isIn(CPoint point);
    void move(CPoint point);
};

