// wuziqiView.cpp : implementation of the CWuziqiView class
//

#include "stdafx.h"
#include "wuziqi.h"

#include "wuziqiDoc.h"
#include "wuziqiView.h"

/////////////////////////////////////////////////////////////////////////////
// CWuziqiView

IMPLEMENT_DYNCREATE(CWuziqiView, CView)

BEGIN_MESSAGE_MAP(CWuziqiView, CView)
	//{{AFX_MSG_MAP(CWuziqiView)
	ON_WM_LBUTTONUP()
	ON_WM_SETCURSOR()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWuziqiView construction/destruction

CWuziqiView::CWuziqiView()
{
	// TODO: add construction code here
	hcuesorblack = AfxGetApp()->LoadCursor(IDC_CURSOR2);
	hcursorwhite = AfxGetApp()->LoadCursor(IDC_CURSOR1);
	m_bmwhite.LoadBitmap(IDB_WHITE);
	m_bmblack.LoadBitmap(IDB_BLACK);
	
	for(int n=0;n<15;n++){
		for(int m=0;m<15;m++){
			WZQ_BOARD[n][m]=0;     //初始化所有的位置为空
		}
	}
	colorwhite = false;
}

CWuziqiView::~CWuziqiView()
{
}

BOOL CWuziqiView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CWuziqiView drawing

void CWuziqiView::OnDraw(CDC* pDC)
{
	CWuziqiDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
	CBrush mybrush;
	mybrush.CreateSolidBrush(RGB(0,0,0));
	CRect myrect(0,0,1200,800);
	pDC->FillRect(myrect,&mybrush);

	CPen mypen;
	mypen.CreatePen(PS_SOLID,1,RGB(255,255,255));
	pDC->SelectObject(&mypen);
	int WZQ_LENGTH = 20;
	for(int i = 0;i<=15;i++)
	{
		pDC->MoveTo(40,40+i*WZQ_LENGTH);
		pDC->LineTo(20*17,40+i*WZQ_LENGTH);
		pDC->MoveTo(40+i*WZQ_LENGTH,40);
		pDC->LineTo(40+i*WZQ_LENGTH,20*17);
	}
	CDC Dc;
// 	for (int n = 0;n<=15;n++)
// 	{
// 		for (int m= 0;m<=15;m++)
// 		{
// 			//默认黑棋先走即colorwhite=false
// 			Dc.SelectObject(m_bmblack);
// 			pDC->BitBlt(n*20+32,m*20+32,160,160,&Dc,0,0,SRCCOPY);
// 		}
// 	}
	CString str_Msg,str_col,str_name;
	
	CFont *pOldFont,font;
	CPoint point;
	font.CreateFont(40,0,0,0,300,FALSE,FALSE,0,OEM_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH,"楷体");
	pOldFont=pDC->SelectObject(&font);
	pDC->SetTextColor(RGB(0,0,0));
	if(colorwhite)
	{
		//pDC->TextOut(700,20,"白方：123下棋");
	}
	else
	{
		int px = (point.x-30)/20;
		int py = (point.y-30)/20;
		pDC->SetTextColor(RGB(55,23,55));
		pDC->TextOut(500,20,"黑方：AI下棋");
		pDC->BitBlt(px*20+30,py*20+30,160,160,&Dc,0,0,SRCCOPY);
		pDC->SetTextColor(RGB(25,23,25));
		pDC->TextOut(500,100,"白方：人工在线下棋");
		pDC->BitBlt(px*20,py*20,160,160,&Dc,0,0,SRCCOPY);
	}
	/*pDC->TextOut(700,20,"白方：123下棋");*/
	
			
}

/////////////////////////////////////////////////////////////////////////////
// CWuziqiView printing

BOOL CWuziqiView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CWuziqiView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CWuziqiView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CWuziqiView diagnostics

#ifdef _DEBUG
void CWuziqiView::AssertValid() const
{
	CView::AssertValid();
}

void CWuziqiView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CWuziqiDoc* CWuziqiView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CWuziqiDoc)));
	return (CWuziqiDoc*)m_pDocument;
}
#endif //_DEBUG

////////////////////////////////////////
bool CWuziqiView::isFinish(CPoint point,int flag)
{
	int count = 1;
	//int x1,y1;
	//x1 = (point.x-30)/20;
	int i;
	bool up, down, right, left, rup, lup, rdown, ldown;
	up = down = right = left = rup = lup = rdown = ldown = true;
	/* 上下5 */
	for (i = 1; i < 5; ++i) {
		
		if ((point.y + i) < 15) {
			if (WZQ_BOARD[point.x][point.y + i] == flag && down)
				count++;
			else
				down = false;
		}
		if (count >= 5)
			return true;
		if ((point.y - i) >= 0) {
			if (WZQ_BOARD[point.x][point.y - i] == flag && up)
				count++;
			else
				up = false;
		}
		if (count >= 5)
			return true;
	}
	count = 1;
	//left&right
	for (i = 1; i < 5; ++i) {
		if ((point.x + i) < 15) {
			if (WZQ_BOARD[point.x + i][point.y] == flag && right)
				count++;
			else
				right = false;
		}
		if (count >= 5)
			return true;
		if ((point.x - i) >= 0) {
			if (WZQ_BOARD[point.x - i][point.y] == flag && left)
				count++;
			else
				left = false;
		}
		if (count >= 5) {
			return true;
		}
	}
	count = 1;
	//lup-rdown
	for (i = 1; i < 5; ++i) {
		if ((point.x + i) < 15 && (point.y + i) < 15) {
			if (WZQ_BOARD[point.x + i][point.y + i] == flag && rdown)
				count++;
			else
				rdown = false;
		}
		else if ((point.x - i) >= 0 && (point.y - i) >= 0)
		{
			if (WZQ_BOARD[point.x - i][point.y - i] == flag && lup)
				count++;
			else
				lup = false;
		}
	}
	if (count >= 5)
	{
		return true;
	}
	count = 1;
	//rup-ldown
	for (i = 0; i <= 5; i++)
	{
		if ((point.x + i) < 15 && (point.y - i) >= 0) {
			if (WZQ_BOARD[point.x + i][point.y - i] == flag && rup)
				count++;
			else
				rup = false;
		}
		else if ((point.x - i) >= 0 && (point.y + i) < 15) {
			if (WZQ_BOARD[point.x - i][point.y + i] == flag && ldown)
				count++;
			else
				ldown = false;
		}
	}
	if (count >= 5) {
		//OnStart();
		return true;
	}
	
	return false;
}

/////////////////////////////////////////////////////////////////////////////
// CWuziqiView message handlers

void CWuziqiView::putdown(CPoint point)
{
    CDC *pDC=GetDC();
    CDC Dc;
    if(Dc.CreateCompatibleDC(pDC)==FALSE)
        AfxMessageBox("Can't create DC");
    Dc.SelectObject(m_bmblack);
// 	if(WZQ_BOARD[point.x][point.y]==0)
// 	{
    pDC->BitBlt(point.x*20+32,point.y*20+32,160,160,&Dc,0,0,SRCCOPY);   
    WZQ_BOARD[point.x][point.y]=-1;
    colorwhite=true;
//	}
}

void CWuziqiView::OnStart()
{
	for(int i = 0;i<15;i++)
		for(int j = 0;j<15;j++)
			WZQ_BOARD[i][j]=0;
}
int cou = 0;
int max_computer;
int computerScore[15][15]={0};
int HUO = 1;
int CHONG = 2;
int computerX;
int computerY;
void CWuziqiView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	int opt=2;//1==>person2person//2==>person2ai
	CView::OnLButtonUp(nFlags, point);
	CDC *pDC = GetDC();
	CDC Dc;
	if(Dc.CreateCompatibleDC(pDC)==FALSE)AfxMessageBox("Can't create DC");
	
	//OnStart();
	//////////////////////////////双人对战opt=1/////////////////////////////////////////
	if(opt ==1)
	{
		int px = (point.x-30)/20;
		int py = (point.y-30)/20;
		
		if(px>=0 && px<=15 && py>=0 && py<=15)
		{
			if(colorwhite)
			{
				if(WZQ_BOARD[px][py]==0)
				{
					CPoint tempP;
					tempP.x = px;
					tempP.y = py;
					Dc.SelectObject(m_bmwhite);
					pDC->BitBlt(px*20+32,py*20+32,160,160,&Dc,0,0,SRCCOPY);
					WZQ_BOARD[px][py] = 1;
					if(isFinish(tempP,1))
					{
						AfxMessageBox("白棋胜");
						OnStart();
					}
					colorwhite = false;
				}
			}
			else if (WZQ_BOARD[px][py]==0)
			{
				CPoint tempP;
				tempP.x = px;
				tempP.y = py;
				WZQ_BOARD[px][py] = -1;
				Dc.SelectObject(m_bmblack);
				pDC->BitBlt(px*20+32,py*20+32,160,160,&Dc,0,0,SRCCOPY);
				if(isFinish(tempP,-1))
				{
					AfxMessageBox("黑棋胜");;
					OnStart();
				}colorwhite = true;
			}
		}
	}
	
	/////////////////////////////人机对战opt=2/////////////////////////////////
	if(opt == 2)
	{
		int px = (point.x-30)/20;
		int py = (point.y-30)/20;
		
		if(px>=0 && px<=15 && py>=0 && py<=15)
		{
			if(colorwhite)
			{
				if(WZQ_BOARD[px][py]==0)
				{
					CPoint tempP;
					tempP.x = px;
					tempP.y = py;
					Dc.SelectObject(m_bmwhite);
					pDC->BitBlt(px*20+32,py*20+32,160,160,&Dc,0,0,SRCCOPY);
					WZQ_BOARD[px][py] = 1;
					if(isFinish(tempP,1))
					{
						AfxMessageBox("白棋胜");
						OnStart();
					}
					colorwhite = false;
				}
			}
			else if (WZQ_BOARD[px][py]==0)
			{
				cou++;
				if (cou==1)
				{
					OnStart();
				}
				CPoint tempP;
				computerX = 0;
				computerY = 0;
				max_computer = 0;
				bestputdown();
				if(max_computer==13)
				{
					AfxMessageBox("黑棋胜");;
					//OnStart();
				}
				else
				{
					tempP.x = computerX;
					tempP.y = computerY;
					putdown(tempP);
					WZQ_BOARD[computerX][computerY] = -1;
					colorwhite = true;
					
				}
				//colorwhite = true;
			}
		}
	}
///************////////////////

}

POINT CWuziqiView::bestputdown()
{
	//CPoint point1;
	max_computer = 0;
	computerX = 0;
	computerY = 0;
	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			if (WZQ_BOARD[i][j] == 0)
			{
				CPoint point;
				//point = (i,j);
				point.x = i;
				point.y = j;
				WZQ_BOARD[i][j]=0;
				if (isFinish(point,-1)) // 电脑能赢，故给分最高，因为可以结束，所以不再检测
				{ 
					max_computer = 13;//1e4
					computerScore[i][j] = max_computer;
					point.x = i;
					point.y = j;
					putdown(point);
					return point;
				}
 				WZQ_BOARD[i][j]=0;
// 				point.x=i;point.y=j;
				if(isFinish(point,1)) // 电脑不能赢，玩家能赢，要阻止，所以给12分
				{	
					max_computer = 12;//1e3
					computerScore[i][j] = max_computer;
					WZQ_BOARD[i][j] = 0;
					computerX = i;
					computerY = j;
					//putdown((i,j));
					//WZQ_BOARD[i][j]=-1;//return point;
				}
				
				else if (liveOR(-1, i, j, 4, HUO)) // 电脑玩家都不能赢，电脑能形成活四，给11分
				{
					max_computer = (max_computer > 11 ? max_computer : 11);
					computerScore[i][j] = 11;
					WZQ_BOARD[i][j]=0;
					if(max_computer==11)
					{
						computerX = i;
						computerY = j;
					}
				}
			
				else if (liveOR(-1, i, j, 4, CHONG)) // 电脑玩家都不能赢，电脑能形成冲四，给10分
				{
					max_computer = (max_computer > 10 ? max_computer : 10);
					computerScore[i][j] = 10;
					WZQ_BOARD[i][j] = 0;
					if(max_computer==10)
					{
						computerX = i;
						computerY = j;
					}
				}
				
				else if (liveOR(1, i, j, 4, HUO)) // 电脑玩家都不能赢，玩家能形成活四，给9分
				{
					max_computer = (max_computer > 9 ? max_computer : 9);
					computerScore[i][j] = 9;
					WZQ_BOARD[i][j] = 0;
					if(max_computer==9)
					{
						computerX = i;
						computerY = j;
					}
				}
				
				else if (liveOR(-1, i, j, 3, HUO)) // 电脑玩家都不能赢，电脑能形成活三，给8分
				{
					max_computer = (max_computer > 8 ? max_computer : 8);
					computerScore[i][j] = 8;
					WZQ_BOARD[i][j] = 0;
					if(max_computer==8)
					{
						computerX = i;
						computerY = j;
					}
				}
				
				else if (liveOR(1, i, j, 4, CHONG)) // 电脑玩家都不能赢，玩家能形成冲四，给7分
				{
					max_computer = (max_computer > 7 ? max_computer : 7);
					computerScore[i][j] = 7;
					WZQ_BOARD[i][j] = 0;
					if(max_computer==7)
					{
						computerX = i;
						computerY = j;
					}
				}
				
				else if (liveOR(-1, i, j, 3, CHONG)) // 电脑玩家都不能赢，电脑能形成冲三，给6分
				{
					max_computer = (max_computer > 6 ? max_computer : 6);
					computerScore[i][j] = 6;
					WZQ_BOARD[i][j] = 0;
					if(max_computer==6)
					{
						computerX = i;
						computerY = j;
					}
				}
				
				else if (liveOR(-1, i, j, 2, HUO)) // 电脑玩家都不能赢，电脑能形成活二，给5分
				{
					max_computer = (max_computer > 5 ? max_computer : 5);
					computerScore[i][j] = 5;
					WZQ_BOARD[i][j] = 0;
					if(max_computer==5)
					{
						computerX = i;
						computerY = j;
// 						computerX = 3;
// 						computerY = 7;
					}
					
				}
				
				else if (liveOR(1, i, j, 3, CHONG)) // 电脑玩家都不能赢，玩家能形成冲三，给4分
				{
					max_computer = (max_computer > 4 ? max_computer : 4);
					computerScore[i][j] = 4;
					WZQ_BOARD[i][j] = 0;
					if(max_computer==4)
					{
						computerX = i;
						computerY = j;
					}
				}
				
				else if (liveOR(1, i, j, 2, HUO)) // 电脑玩家都不能赢，玩家能形成活二，给3分
				{
					max_computer = (max_computer > 3 ? max_computer : 3);
					computerScore[i][j] = 3;
					WZQ_BOARD[i][j] = 0;
					if(max_computer==3)
					{
						computerX = i;
						computerY = j;
					}
// 					computerX = 3;
// 					computerY = 7;
				}
				
				else if (liveOR(-1, i, j, 2, CHONG)) // 电脑玩家都不能赢，电脑能形成冲二，给2分
				{
					max_computer = (max_computer > 2 ? max_computer : 2);
					computerScore[i][j] = 2;
					WZQ_BOARD[i][j] = 0;
					if(max_computer==2)
					{
						computerX = i;
						computerY = j;
					}
// 					computerX = 3;
// 					computerY = 7;
				}
				
				else if (liveOR(1, i, j, 2, CHONG)) // 电脑玩家都不能赢，玩家能形成冲二，给1分
				{
					max_computer = (max_computer > 1 ? max_computer : 1);
					computerScore[i][j] = 1;
					WZQ_BOARD[i][j] = 0;
					if(max_computer==1)
					{
						computerX = i;
						computerY = j;
					}
				}
				
				else {
					computerScore[i][j] = 0;
					WZQ_BOARD[i][j] = 0;
					if (cou==1)
					{
						computerX = i;
						computerY = j;
					}
					

					
				}
			//point = (i,j);
			}
		}
	}
}


bool CWuziqiView::liveOR(int f, int x, int y, int num, int sym)
{
	num = num+1;
	int i, count = 1;
	bool terminal1 = false;
	bool terminal2 = false;
	bool up, down, right, left, rup, lup, rdown, ldown;
	up = down = right = left = rup = lup = rdown = ldown = true;
	//down = true;
	/* 上下 */
	for (i = 1; i < num; ++i) {
		if ((y + i) < 15) {
			if (WZQ_BOARD[x][y + i] == f && down)
				count++;
			else 
			{
				if (WZQ_BOARD[x][y + i] == 0 && down) 
				{
					terminal1 = true;
				}
				down = false;
			}
		}
		if ((y - i) >= 0) {
			if (WZQ_BOARD[x][y - i] == f && up)
				count++;
			else {
				if (WZQ_BOARD[x][y - i] == 0 && up) {
					terminal2 = true;
				}
				up = false;
			}
		}
	}
	if (count == num-1 && sym == HUO && terminal1 && terminal2) {
		return true;
	}
	if (count == num-1 && sym == CHONG && ((terminal1 && !terminal2) || (!terminal1 && terminal2))) {
		return true;
	}
	count = 1;
	terminal1 = false;
	terminal2 = false;
	/* 左右 */
	for (i = 1; i < num; ++i) {
		if ((x + i) < 15) {
			if (WZQ_BOARD[x + i][y] == f && right)
				count++;
			else {
				if (WZQ_BOARD[x + i][y] == 0 && right) {
					terminal1 = true;
				}
				right = false;
			}
		}
		if ((x - i) >= 0) {
			if (WZQ_BOARD[x - i][y] == f && left)
				count++;
			else {
				if (WZQ_BOARD[x - i][y] == 0 && left) {
					terminal2 = true;
				}
				left = false;
			}
		}
	}
	if (count ==num-1 && sym == HUO && terminal1 && terminal2) {
		return true;
	}
	if (count ==num-1 && sym == CHONG && ((terminal1 && !terminal2) || (!terminal1 && terminal2))) {
		return true;
	}
	count = 1;
	terminal1 = false;
	terminal2 = false;
	/* 左上右下 */
	for (i = 1; i < num; ++i) {
		if ((x + i) < 15 && (y + i) < 15) {
			if (WZQ_BOARD[x + i][y + i] == f && rdown)
				count++;
			else {
				if (WZQ_BOARD[x + i][y + i] == 0 && rdown) {
					terminal1 = true;
				}
				rdown = false;
			}
		}
		if ((x - i) >= 0 && (y - i) >= 0) {
			if (WZQ_BOARD[x - i][y - i] == f && lup)
				count++;
			else {
				if (WZQ_BOARD[x - i][y - i] == 0 && lup) {
					terminal2 = true;
				}
				lup = false;
			}
		}
	}
	if (count ==num-1 && sym == HUO && terminal1 && terminal2) {
		return true;
	}
	if (count ==num-1 && sym == CHONG && ((terminal1 && !terminal2) || (!terminal1 && terminal2))) {
		return true;
	}
	count = 1;
	terminal1 = false;
	terminal2 = false;
	/* 右上左下 */
	for (i = 1; i < num; ++i) {
		if ((x + i) < 15 && (y - i) >= 0) {
			if (WZQ_BOARD[x + i][y - i] == f && rup)
				count++;
			else {
				if (WZQ_BOARD[x + i][y - i] == 0 && rup) {
					terminal1 = true;
				}
				rup = false;
			}
		}
		if ((x - i) >= 0 && (y + i) < 15) {
			if (WZQ_BOARD[x - i][y + i] == f && ldown)
				count++;
			else {
				if (WZQ_BOARD[x - i][y + i] == 0 && ldown) {
					terminal2 = true;
				}
				ldown = false;
			}
		}
	}
	if (count ==num-1 && sym == HUO && terminal1 && terminal2) {
		return true;
	}
	if (count ==num-1 && sym == CHONG && ((terminal1 && !terminal2) || (!terminal1 && terminal2))) {
		return true;
	}
	return false;
}

BOOL CWuziqiView::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	// TODO: Add your message handler code here and/or call default
	if (nHitTest==HTCLIENT)
	{
		//white-ing
		if (colorwhite) 
		{
			SetCursor(hcursorwhite);
// 			CDC *pDC;
// 			CFont *pOldFont,font;
// 			CPoint point;
// 			font.CreateFont(40,0,0,0,300,FALSE,FALSE,0,OEM_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH,"楷体");
// 			pOldFont=pDC->SelectObject(&font);
// 			pDC->SetTextColor(RGB(25,25,55));
// 			pDC->TextOut(700,20,"黑方：234下棋");
// 			CPoint point;
// 			int px = (point.x-30)/15;
// 			int py = (point.y-30)/15;
// 			pDC->BitBlt(px*15+30,py*15+30,160,160,&Dc,0,0,SRCCOPY);
		}
		else SetCursor(hcuesorblack);
		return 1;
	}

	return CView::OnSetCursor(pWnd, nHitTest, message);
}
