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
	//�������
	HCURSOR hcursorwhite;
	HCURSOR hcuesorblack;
	//����
	int	WZQ_BOARD[15][15];
	//������
	bool colorwhite;
	//���ӵ�λ��
	CBitmap m_bmblack;
	CBitmap m_bmwhite;
	void sava();
	bool isFinish(CPoint point,int kind);
	afx_msg CPoint AutoPlay();
	afx_msg int Values(int x,int y,int flag);
	void putdown(CPoint point);
	void compute();//find the best place
	CPoint b4,//���λ�ÿգ����Ա����ĸ�����
		w4,//���λ�ÿգ����Ա����ĸ�����
		b3,//���λ�ÿգ������Ա�����������
		w3,//���λ�ÿգ������Ա�����������
		b2,//���λ�ÿգ������Ա�����������
		w2,//���λ�ÿգ������Ա�����������
		b1;//����������������λ�ÿ�
	bool liveOR(int f, int x, int y, int num, int sym);
    //�ڵõ����ֵ�ͷ�����Ѱ�������
    //����i��j��ʾ������㣬n��ʾ����
    void searchcandown1(int i,int j,int n);
    void searchcandown2(int i,int j,int n);
    void searchcandown3(int i,int j,int n);
    void searchcandown4(int i,int j,int n);

	
    //�������ֵ������
    CPoint maxnum(int a,int b,int c,int d);
	
    //��������
    POINT bestputdown();

protected:
	afx_msg void OnStart(); //�˵��Ŀ�ʼ
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
