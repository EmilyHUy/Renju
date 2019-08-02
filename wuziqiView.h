// wuziqiView.h : interface of the CWuziqiView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_WUZIQIVIEW_H__884F5201_D9F0_4DE7_AE26_AFFA369A43C3__INCLUDED_)
#define AFX_WUZIQIVIEW_H__884F5201_D9F0_4DE7_AE26_AFFA369A43C3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CWuziqiView : public CView
{
protected: // create from serialization only
	CWuziqiView();
	DECLARE_DYNCREATE(CWuziqiView)

public:
	//两个鼠标
	HCURSOR hcursorwhite;
	HCURSOR hcuesorblack;
	//棋盘
	int	WZQ_BOARD[15][15];
	//黑先走
	bool colorwhite;
	//棋子的位置
	CBitmap m_bmblack;
	CBitmap m_bmwhite;
	void sava();
	bool isFinish(CPoint point,int kind);
	afx_msg CPoint AutoPlay();
	afx_msg int Values(int x,int y,int flag);
	void putdown(CPoint point);
	void compute();//find the best place
	CPoint b4,//这个位置空，它旁边有四个黑棋
		w4,//这个位置空，它旁边有四个白棋
		b3,//这个位置空，它的旁边有三个黑棋
		w3,//这个位置空，它的旁边有三个白棋
		b2,//这个位置空，它的旁边有两个黑棋
		w2,//这个位置空，它的旁边有两个白棋
		b1;//不是以上情况，这个位置空
	bool liveOR(int f, int x, int y, int num, int sym);
    //在得到最大值和方向上寻找落棋点
    //其中i、j表示搜索起点，n表示方向
    void searchcandown1(int i,int j,int n);
    void searchcandown2(int i,int j,int n);
    void searchcandown3(int i,int j,int n);
    void searchcandown4(int i,int j,int n);

	
    //计算最大值及方向
    CPoint maxnum(int a,int b,int c,int d);
	
    //最好落棋点
    POINT bestputdown();

protected:
	afx_msg void OnStart(); //菜单的开始
// Attributes
public:
	CWuziqiDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWuziqiView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CWuziqiView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CWuziqiView)
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in wuziqiView.cpp
inline CWuziqiDoc* CWuziqiView::GetDocument()
   { return (CWuziqiDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WUZIQIVIEW_H__884F5201_D9F0_4DE7_AE26_AFFA369A43C3__INCLUDED_)
