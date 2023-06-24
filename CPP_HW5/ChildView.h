﻿
// ChildView.h: CChildView 클래스의 인터페이스
//


#pragma once

#include "MyShape.h"
#include "MyCircle.h"
#include "MyCurve.h"
#include "MyRect.h"
#include "MyStar.h"
#include "MyGroup.h"

#define RECTANGLE 0
#define CIRCLE 1
#define CURVE 2
#define STAR 3
#define SELECT 4

// CChildView 창

class CChildView : public CWnd
{
// 생성입니다.
public:
	CChildView();

// 특성입니다.
public:
	int action;
	CList<MyShape *> shapes;
	CList<MyShape *> selected;
	CPoint selectStart;
	CPoint selectEnd;
	bool selectFlag;

// 작업입니다.
public:

// 재정의입니다.
protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// 구현입니다.
public:
	virtual ~CChildView();

	// 생성된 메시지 맵 함수
protected:
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnDrawRectangle();
	afx_msg void OnDrawCircle();
	afx_msg void OnDrawCurve();
	afx_msg void OnDrawStar();
	afx_msg void OnActionSelect();
	afx_msg void OnUpdateDrawRectangle(CCmdUI* pCmdUI);
	afx_msg void OnUpdateDrawCircle(CCmdUI* pCmdUI);
	afx_msg void OnUpdateDrawCurve(CCmdUI* pCmdUI);
	afx_msg void OnUpdateDrawStar(CCmdUI* pCmdUI);
	afx_msg void OnUpdateActionSelect(CCmdUI* pCmdUI);
	afx_msg void OnAlignBringfront();
	afx_msg void OnUpdateAlignBringfront(CCmdUI* pCmdUI);
	afx_msg void OnAlignBringback();
	afx_msg void OnUpdateAlignBringback(CCmdUI* pCmdUI);
	afx_msg void OnActionGroup();
	afx_msg void OnUpdateActionGroup(CCmdUI* pCmdUI);
	afx_msg void OnActionUngroup();
	afx_msg void OnUpdateActionUngroup(CCmdUI* pCmdUI);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint point);
};

