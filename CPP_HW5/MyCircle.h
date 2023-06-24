#pragma once
#include "MyShape.h"
class MyCircle :
    public MyShape
{
public:
    MyCircle(CPoint point);
    void draw(CDC& dc);
    CRect getBorder();
    bool isIn(CPoint point);
};
