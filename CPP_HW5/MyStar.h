#pragma once
#include "MyShape.h"
class MyStar : public MyShape
{
    CPoint arr[10];
    void calArr();
public:
    MyStar(CPoint point);
    void draw(CDC& dc);
    CRect getBorder();
    bool isIn(CPoint point);
};

