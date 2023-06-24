
// ChildView.cpp: CChildView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
#include "CPP_HW5.h"
#include "ChildView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView() :
action(RECTANGLE), selectFlag(false)
{
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_KEYDOWN()
	ON_COMMAND(ID_DRAW_RECTANGLE, &CChildView::OnDrawRectangle)
	ON_COMMAND(ID_DRAW_CIRCLE, &CChildView::OnDrawCircle)
	ON_COMMAND(ID_DRAW_CURVE, &CChildView::OnDrawCurve)
	ON_COMMAND(ID_DRAW_STAR, &CChildView::OnDrawStar)
	ON_COMMAND(ID_ACTION_SELECT, &CChildView::OnActionSelect)
	ON_UPDATE_COMMAND_UI(ID_DRAW_RECTANGLE, &CChildView::OnUpdateDrawRectangle)
	ON_UPDATE_COMMAND_UI(ID_DRAW_CIRCLE, &CChildView::OnUpdateDrawCircle)
	ON_UPDATE_COMMAND_UI(ID_DRAW_CURVE, &CChildView::OnUpdateDrawCurve)
	ON_UPDATE_COMMAND_UI(ID_DRAW_STAR, &CChildView::OnUpdateDrawStar)
	ON_UPDATE_COMMAND_UI(ID_ACTION_SELECT, &CChildView::OnUpdateActionSelect)
	ON_COMMAND(ID_ACTION_GROUP, & CChildView::OnActionGroup)
	ON_UPDATE_COMMAND_UI(ID_ACTION_GROUP, &CChildView::OnUpdateActionGroup)
	ON_COMMAND(ID_ACTION_UNGROUP, &CChildView::OnActionUngroup)
	ON_UPDATE_COMMAND_UI(ID_ACTION_UNGROUP, &CChildView::OnUpdateActionUngroup)
	ON_COMMAND(ID_ALIGN_BRINGFRONT, &CChildView::OnAlignBringfront)
	ON_UPDATE_COMMAND_UI(ID_ALIGN_BRINGFRONT, &CChildView::OnUpdateAlignBringfront)
	ON_COMMAND(ID_ALIGN_BRINGBACK, &CChildView::OnAlignBringback)
	ON_UPDATE_COMMAND_UI(ID_ALIGN_BRINGBACK, &CChildView::OnUpdateAlignBringback)
	ON_WM_ERASEBKGND()
	ON_WM_CONTEXTMENU()
END_MESSAGE_MAP()



// CChildView 메시지 처리기

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(nullptr, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), nullptr);

	return TRUE;
}

void CChildView::OnPaint() 
{
	CPaintDC dc(this); 

	CRect rect;
	GetClientRect(rect);
	int w = rect.Width();
	int h = rect.Height();

	CDC memDc;
	memDc.CreateCompatibleDC(&dc);
	CBitmap bmp;
	bmp.CreateCompatibleBitmap(&dc, w, h);
	memDc.SelectObject(bmp);
	memDc.SelectStockObject(NULL_PEN);
	memDc.Rectangle(rect);
	memDc.SetBkMode(TRANSPARENT);

	POSITION pos = shapes.GetHeadPosition();
	while (pos != nullptr) 
	{
		MyShape* shape = shapes.GetNext(pos);
		shape->draw(memDc);

		if(selected.Find(shape) != nullptr)
		{
			CPen pen(PS_DOT, 1, RGB(200, 0, 0));
			memDc.SelectObject(pen);
			memDc.SelectStockObject(NULL_BRUSH);
			CRect rect = shape->getBorder();
			rect.left -= 5;
			rect.top -= 5;
			rect.right += 5;
			rect.bottom += 5;
			memDc.Rectangle(rect);
		}
	}

	if (action == SELECT && selectFlag)
	{
		CPen pen(PS_DOT, 1, RGB(0, 0, 0));
		memDc.SelectObject(pen);
		memDc.SelectStockObject(NULL_BRUSH);
		memDc.Rectangle(CRect(selectStart, selectEnd));
	}

	CString str;
	str.Format(_T("Number of Shapes: %ld\n"), shapes.GetSize());
	str.AppendFormat(_T("Number of Selected: %ld\n"), selected.GetSize());
	memDc.DrawText(str, rect, DT_LEFT | DT_TOP);

	dc.BitBlt(0, 0, w, h, &memDc, 0, 0, SRCCOPY);
}


void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
	SetCapture();
	switch (action) {
	case RECTANGLE: 
		shapes.AddTail(new MyRect(point));
		break;
	case CIRCLE: 
		shapes.AddTail(new MyCircle(point));
		break;
	case CURVE: 
		shapes.AddTail(new MyCurve(point));
		break;
	case STAR: 
		shapes.AddTail(new MyStar(point));
		break;
	case SELECT:
		selectStart = selectEnd = point;
		if (!(nFlags & MK_SHIFT)) {
			selected.RemoveAll();
		}
		POSITION pos = shapes.GetTailPosition();
		POSITION posSelected = selected.GetTailPosition();
		selectFlag = true;
		while (pos != nullptr)
		{
			MyShape* shape = shapes.GetPrev(pos);
			if (shape->isIn(point)) {
				selectFlag = false;
				if (selected.Find(shape) == nullptr)
					selected.InsertAfter(posSelected, shape);
				break;
			}
		}
		break;
	}
	Invalidate();
	CWnd::OnLButtonDown(nFlags, point);
}


void CChildView::OnMouseMove(UINT nFlags, CPoint point)
{
	if (nFlags & MK_LBUTTON) {
		if (action == SELECT && selectFlag) {
			selectEnd = point;
		}
		else if (action == SELECT && !selectFlag) {
			POSITION pos = selected.GetHeadPosition();
			CPoint dist = point - selectEnd;
			while (pos != nullptr) 
			{
				MyShape* shape = shapes.GetNext(pos);
				shape->move(dist);
			}
			selectEnd = point;
		}
		else {
			shapes.GetTail()->update(point);
		}
		Invalidate();
	}
	CWnd::OnMouseMove(nFlags, point);
}


void CChildView::OnLButtonUp(UINT nFlags, CPoint point)
{
	ReleaseCapture();
	if (action == SELECT && selectFlag)
	{
		POSITION pos = shapes.GetTailPosition();
		POSITION posSelected = selected.GetTailPosition();
		while (pos != nullptr) 
		{
			MyShape* shape = shapes.GetPrev(pos);
			if (shape->isIn(CRect(selectStart, selectEnd)) && selected.Find(shape) == nullptr)
				selected.InsertAfter(posSelected, shape);
		}
		selectStart = selectEnd = 0;
		Invalidate();
	}
	CWnd::OnLButtonUp(nFlags, point);
}


void CChildView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == VK_DELETE) {
		POSITION pos = shapes.GetHeadPosition();
		while (pos != nullptr) {
			MyShape* shape = shapes.GetAt(pos);
			if (selected.Find(shape) != nullptr) 
			{
				POSITION removePos = pos;
				shapes.GetNext(pos);
				shapes.RemoveAt(removePos);
				delete shape;
			}
			else
			{
				shapes.GetNext(pos);
			}
		}
		selected.RemoveAll();
		Invalidate();
	}
	CWnd::OnKeyDown(nChar, nRepCnt, nFlags);
}


void CChildView::OnDrawRectangle()
{
	selected.RemoveAll();
	action = RECTANGLE;
	Invalidate();
}

void CChildView::OnDrawCircle()
{
	selected.RemoveAll();
	action = CIRCLE;
	Invalidate();
}

void CChildView::OnDrawCurve()
{
	selected.RemoveAll();
	action = CURVE;
	Invalidate();
}

void CChildView::OnDrawStar()
{
	selected.RemoveAll();
	action = STAR;
	Invalidate();
}

void CChildView::OnActionSelect()
{
	action = SELECT;
}


void CChildView::OnUpdateDrawRectangle(CCmdUI* pCmdUI)
{
	if (action == RECTANGLE)
		pCmdUI->SetCheck(true);
	else
		pCmdUI->SetCheck(false);
}


void CChildView::OnUpdateDrawCircle(CCmdUI* pCmdUI)
{
	if (action == CIRCLE)
		pCmdUI->SetCheck(true);
	else
		pCmdUI->SetCheck(false);
}


void CChildView::OnUpdateDrawCurve(CCmdUI* pCmdUI)
{
	if (action == CURVE)
		pCmdUI->SetCheck(true);
	else
		pCmdUI->SetCheck(false);
}


void CChildView::OnUpdateDrawStar(CCmdUI* pCmdUI)
{
	if (action == STAR)
		pCmdUI->SetCheck(true);
	else
		pCmdUI->SetCheck(false);
}

void CChildView::OnUpdateActionSelect(CCmdUI* pCmdUI)
{
	if (action == SELECT)
		pCmdUI->SetCheck(true);
	else
		pCmdUI->SetCheck(false);
}


void CChildView::OnAlignBringfront()
{
	CList<MyShape*> tmp;
	POSITION pos = shapes.GetHeadPosition();
	while (pos != nullptr)
	{
		MyShape* shape = shapes.GetAt(pos);
		if (selected.Find(shape) != nullptr) 
		{
			POSITION removePos = pos;
			tmp.AddTail(shape);
			shapes.GetNext(pos);
			shapes.RemoveAt(removePos);
		}
		else
			shapes.GetNext(pos);
	}
	shapes.AddTail(&tmp);
	Invalidate();
}


void CChildView::OnUpdateAlignBringfront(CCmdUI* pCmdUI)
{
	if (selected.IsEmpty())
		pCmdUI->Enable(false);
	else
		pCmdUI->Enable(true);
}


void CChildView::OnAlignBringback()
{
	CList<MyShape *> tmp;
	POSITION pos = shapes.GetTailPosition();
	while (pos != nullptr)
	{
		MyShape* shape = shapes.GetAt(pos);
		if (selected.Find(shape) != nullptr) 
		{
			POSITION removePos = pos;
			tmp.AddHead(shape);
			shapes.GetPrev(pos);
			shapes.RemoveAt(removePos);
		}
		else
			shapes.GetPrev(pos);
	}
	shapes.AddHead(&tmp);
	Invalidate();
}


void CChildView::OnUpdateAlignBringback(CCmdUI* pCmdUI)
{
	if (selected.IsEmpty())
		pCmdUI->Enable(false);
	else
		pCmdUI->Enable(true);
}


void CChildView::OnActionGroup()
{
	shapes.AddTail(new MyGroup(selected));
	POSITION pos = shapes.GetHeadPosition();
	while (pos != nullptr) 
	{
		MyShape* shape = shapes.GetAt(pos);
		if (selected.Find(shape) != nullptr) 
		{
			POSITION removePos = pos;
			shapes.GetNext(pos);
			shapes.RemoveAt(removePos);
		}
		else
			shapes.GetNext(pos);
	}
	selected.RemoveAll();
	selected.AddTail(shapes.GetTail());
	Invalidate();
}


void CChildView::OnUpdateActionGroup(CCmdUI* pCmdUI)
{
	if (selected.GetSize() > 1)
		pCmdUI->Enable(true);
	else
		pCmdUI->Enable(false);
}


void CChildView::OnActionUngroup()
{
	CList<MyShape *> tmp;
	POSITION pos = shapes.GetHeadPosition();
	while (pos != nullptr)
	{
		MyShape* shape = shapes.GetAt(pos);
		if (selected.Find(shape) != nullptr)
		{
			POSITION removePos = pos;
			CList<MyShape*> children;
			shape->ungroup(children);
			tmp.AddTail(&children);
			shapes.GetNext(pos);
			if (children.IsEmpty())
				continue;
			shapes.RemoveAt(removePos);
			delete shape;
		}
		else
			shapes.GetNext(pos);
	}
	shapes.AddTail(&tmp);
	selected.AddTail(&tmp);
	Invalidate();
}


void CChildView::OnUpdateActionUngroup(CCmdUI* pCmdUI)
{
	if (selected.IsEmpty())
		pCmdUI->Enable(false);
	else
		pCmdUI->Enable(true);
}


BOOL CChildView::OnEraseBkgnd(CDC* pDC)
{
	return true;
}

void CChildView::OnContextMenu(CWnd* /*pWnd*/, CPoint point)
{
	CMenu menu;
	menu.LoadMenu(IDR_MAINFRAME);

	CMenu* pMenu = menu.GetSubMenu(4);

	pMenu->TrackPopupMenu(
		TPM_LEFTALIGN | TPM_RIGHTBUTTON,
		point.x, point.y, AfxGetMainWnd());
}