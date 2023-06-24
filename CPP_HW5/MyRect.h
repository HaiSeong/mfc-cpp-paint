#pragma once
#include "MyShape.h"
class MyRect : public MyShape
{
public:
    MyRect(CPoint point);
    void draw(CDC& dc);
    void update(CPoint point);
    CRect getBorder();
    bool isIn(CPoint point);
};

