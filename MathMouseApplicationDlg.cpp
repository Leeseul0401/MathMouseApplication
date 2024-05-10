
// MathMouseApplicationDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "MathMouseApplication.h"
#include "MathMouseApplicationDlg.h"
#include "afxdialogex.h"
#include <iostream>
#include <afxwin.h>
#include <vector>
#include <cmath>
#include <numeric>

#ifdef _DEBUG
#define new DEBUG_NEW
#define M_PI 3.14159265358979323846
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMathMouseApplicationDlg 대화 상자



CMathMouseApplicationDlg::CMathMouseApplicationDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MATHMOUSEAPPLICATION_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMathMouseApplicationDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC1, xEdit);
	DDX_Control(pDX, IDC_STATIC2, yEdit);

	DDX_Control(pDX, IDC_EDIT1, angleEdit);
	DDX_Control(pDX, IDC_EDIT3, xEdit1);
	DDX_Control(pDX, IDC_EDIT6, yEdit1);
	DDX_Control(pDX, IDC_EDIT7, xEdit2);
	DDX_Control(pDX, IDC_EDIT8, yEdit2);
	DDX_Control(pDX, IDC_EDIT9, xEdit3);
	DDX_Control(pDX, IDC_EDIT10, yEdit3);

	DDX_Control(pDX, IDC_LIST1, listBox);

	DDX_Control(pDX, IDC_RADIO1, radioCheck1);
	DDX_Control(pDX, IDC_RADIO2, radioCheck2);

	DDX_Control(pDX, IDC_PICCON_BOARD, m_picBoard);
	DDX_Control(pDX, IDC_BUTTON1, RotateButton);
	DDX_Control(pDX, IDC_RADIO3, radioCheck3);
	DDX_Control(pDX, IDC_RADIO4, radioCheck4);
	DDX_Control(pDX, IDC_RADIO5, radioCheck5);
}

BEGIN_MESSAGE_MAP(CMathMouseApplicationDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()	
//	ON_WM_MOUSEHOVER()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_RADIO1, &CMathMouseApplicationDlg::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &CMathMouseApplicationDlg::OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_RADIO3, &CMathMouseApplicationDlg::OnBnClickedRadio3)
	ON_BN_CLICKED(IDC_RADIO4, &CMathMouseApplicationDlg::OnBnClickedRadio4)
	ON_BN_CLICKED(IDC_RADIO5, &CMathMouseApplicationDlg::OnBnClickedRadio5)
	ON_BN_CLICKED(IDC_BUTTON1, &CMathMouseApplicationDlg::OnBnClickedButton1)
	ON_STN_CLICKED(IDC_PICCON_BOARD, &CMathMouseApplicationDlg::OnStnClickedPicconBoard)
END_MESSAGE_MAP()


// CMathMouseApplicationDlg 메시지 처리기

BOOL CMathMouseApplicationDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다
	brush.CreateSolidBrush(RGB(255, 255, 255));
	isMouseDown = false;
	CButton* pCheck;
	pCheck = ((CButton*)GetDlgItem(IDC_RADIO1));
	pCheck->SetCheck(TRUE);

	// edotBpx에 노출되는 좌표값을 나타내기 위한 클릭 횟수
	count = 1;

	if (radioCheck2.GetCheck() == TRUE)
	{
		CClientDC dc(this);
		DrawCrossLine(&dc);
	} 
	else if (radioCheck3.GetCheck() == TRUE)
	{
		CClientDC dc(this);
	}
	else if (radioCheck5.GetCheck() == TRUE)
	{
		CClientDC dc(this);
	}
	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CMathMouseApplicationDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CMathMouseApplicationDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();

		
		// 점 찍기
		CClientDC dc(&m_picBoard);
		CBrush red(RGB(255, 0, 0));
		CBrush *old_blue = dc.SelectObject(&red);
		for (const auto& point : m_points)
		{
			dc.Ellipse(point.x - 5, point.y - 5, point.x + 5, point.y + 5);
		}
	}
	
	CDialogEx::OnPaint();

}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CMathMouseApplicationDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMathMouseApplicationDlg::OnBnClickedRadio4()
{
	NumberInit();
}

void CMathMouseApplicationDlg::WriteEdit(CPoint clientPnt, int count)
{
	CString xStr;
	CString yStr;
	xStr.Format(L"%d", clientPnt.x);
	yStr.Format(L"%d", clientPnt.y);

	xEdit.SetWindowTextW(xStr);
	yEdit.SetWindowTextW(yStr);
}
void CMathMouseApplicationDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CPoint screenPoint = point;
	ClientToScreen(&screenPoint);

	CRect wRect;
	m_picBoard.GetWindowRect(&wRect);
	if (radioCheck2.GetCheck() == TRUE)
	{
		CRect cRect;
		m_picBoard.GetClientRect(&cRect);

		auto clientPnt = CPoint(screenPoint.x - wRect.left, screenPoint.y - wRect.top);

		int horizontalLineY = cRect.top + cRect.Height() / 2;
		int verticalLineX = cRect.left + cRect.Width() / 2;

		clientPnt.x -= verticalLineX;
		clientPnt.y -= horizontalLineY;
		clientPnt.y *= -1;

		WriteEdit(clientPnt, count);
	}
	else
	{

		if (screenPoint.x >= wRect.left && screenPoint.y >= wRect.top && screenPoint.x <= wRect.right && screenPoint.y <= wRect.bottom)
		{
			auto clientPnt = CPoint(screenPoint.x - wRect.left, screenPoint.y - wRect.top);

			CString xStr;
			CString yStr;
			WriteEdit(clientPnt, count);
		}

	}
}

void CMathMouseApplicationDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	CDialogEx::OnLButtonDown(nFlags, point);
	//형주
	CPoint screenPoint = point;
	ClientToScreen(&screenPoint);

	CRect wRect;
	m_picBoard.GetWindowRect(&wRect);

	auto clientPnt = CPoint(screenPoint.x - wRect.left, screenPoint.y - wRect.top);
	if (true)
	{
		CClientDC dc(&m_picBoard);
		CRect cRect;
		m_picBoard.GetClientRect(&cRect);

		CBrush red(RGB(255, 0, 0));
		CBrush *old_blue = dc.SelectObject(&red);
		
			if (clientPnt.x >= cRect.left && clientPnt.y >= cRect.top && clientPnt.x <= cRect.right && clientPnt.y <= cRect.bottom)
			{
				if (nFlags)
				{
					dc.Ellipse(clientPnt.x - 5, clientPnt.y - 5, clientPnt.x + 5, clientPnt.y + 5);
				}
			}
	
		dc.SelectObject(old_blue);
	}

	CClientDC dc(&m_picBoard);
	CRect cRect;
	m_picBoard.GetClientRect(&cRect);
	dc.IntersectClipRect(&cRect);
	CString mouseX;
	CString mouseY;
	if (radioCheck1.GetCheck() == TRUE)
	{
		CString xStr;
		CString yStr;
		xStr.Format(L"%d", clientPnt.x);
		yStr.Format(L"%d", clientPnt.y);
		if (count == 1)
		{
			xEdit1.SetWindowTextW(xStr);
			yEdit1.SetWindowTextW(yStr);
			listBox.AddString(xStr);
			listBox.AddString(yStr);
			listBox.SetTopIndex(listBox.GetCount() - 1);
		}
		else if (count == 2)
		{
			xEdit2.SetWindowTextW(xStr);
			yEdit2.SetWindowTextW(yStr);
			listBox.AddString(xStr);
			listBox.AddString(yStr);
			listBox.SetTopIndex(listBox.GetCount() - 1);
		}
		else if (count == 3)
		{
			xEdit3.SetWindowTextW(xStr);
			yEdit3.SetWindowTextW(yStr);
			listBox.AddString(xStr);
			listBox.AddString(yStr);
			listBox.SetTopIndex(listBox.GetCount() - 1);
			CalculatePerpendicularFoot();
		}
	} 
	else if (radioCheck2.GetCheck() == TRUE)
	{
		CRect cRect;
		m_picBoard.GetClientRect(&cRect);

		auto clientPnt = CPoint(screenPoint.x - wRect.left, screenPoint.y - wRect.top);

		int horizontalLineY = cRect.top + cRect.Height() / 2;
		int verticalLineX = cRect.left + cRect.Width() / 2;

		clientPnt.x -= verticalLineX;
		clientPnt.y -= horizontalLineY;
		clientPnt.y *= -1;

		m_arrDPoints.Add(DoublePoint( clientPnt.x, clientPnt.y ));

		CString xStr;
		CString yStr;
		xStr.Format(L"%d", clientPnt.x);
		yStr.Format(L"%d", clientPnt.y);
		if (count == 1)
		{
			xEdit1.SetWindowTextW(xStr);
			yEdit1.SetWindowTextW(yStr);
			listBox.AddString(xStr);
			listBox.AddString(yStr);
			listBox.SetTopIndex(listBox.GetCount() - 1);
		}
		else if (count == 2)
		{
			xEdit2.SetWindowTextW(xStr);
			yEdit2.SetWindowTextW(yStr);
			listBox.AddString(xStr);
			listBox.AddString(yStr);
			listBox.SetTopIndex(listBox.GetCount() - 1);
		}
		else if (count == 3)
		{
			xEdit3.SetWindowTextW(xStr);
			yEdit3.SetWindowTextW(yStr);
			listBox.AddString(xStr);
			listBox.AddString(yStr);
			listBox.SetTopIndex(listBox.GetCount() - 1);
			CalculatePerpendicularFoot();
		}
		

	} 
	else if (radioCheck3.GetCheck() == TRUE)
	{
		CRect cRect;
		m_picBoard.GetClientRect(&cRect);

		
		CString xStr;
		CString yStr;
		xStr.Format(L"%d", clientPnt.x);
		yStr.Format(L"%d", clientPnt.y);
		if (count == 1)
		{
			xEdit1.SetWindowTextW(xStr);
			yEdit1.SetWindowTextW(yStr);
			listBox.AddString(xStr);
			listBox.AddString(yStr);
			listBox.SetTopIndex(listBox.GetCount() - 1);
		}
		else if (count == 2)
		{
			xEdit2.SetWindowTextW(xStr);
			yEdit2.SetWindowTextW(yStr);
			listBox.AddString(xStr);
			listBox.AddString(yStr);
			listBox.SetTopIndex(listBox.GetCount() - 1);
		}
		else if (count == 3)
		{
			xEdit3.SetWindowTextW(xStr);
			yEdit3.SetWindowTextW(yStr);
			listBox.AddString(xStr);
			listBox.AddString(yStr);
			listBox.SetTopIndex(listBox.GetCount() - 1);
			
		}
	}
	else if (radioCheck4.GetCheck() == TRUE)
	{
		
		CString xStr;
		CString yStr;
		xStr.Format(L"%d", clientPnt.x);
		yStr.Format(L"%d", clientPnt.y);
		if (count == 1)
		{
			xEdit1.SetWindowTextW(xStr);
			yEdit1.SetWindowTextW(yStr);
			listBox.AddString(xStr);
			listBox.AddString(yStr);
			listBox.SetTopIndex(listBox.GetCount() - 1);
		}
		else if (count == 2)
		{
			xEdit2.SetWindowTextW(xStr);
			yEdit2.SetWindowTextW(yStr);
			listBox.AddString(xStr);
			listBox.AddString(yStr);
			listBox.SetTopIndex(listBox.GetCount() - 1);
		}
		else if (count == 3)
		{
			xEdit3.SetWindowTextW(xStr);
			yEdit3.SetWindowTextW(yStr);
			listBox.AddString(xStr);
			listBox.AddString(yStr);
			listBox.SetTopIndex(listBox.GetCount() - 1);
			CalculatePerpendicularFoot();
		}
	}
	else if (radioCheck5.GetCheck() == TRUE)
	{
		
		CString xStr;
		CString yStr;
		xStr.Format(L"%d", clientPnt.x);
		yStr.Format(L"%d", clientPnt.y);
		if (count == 1)
		{
			xEdit1.SetWindowTextW(xStr);
			yEdit1.SetWindowTextW(yStr);
			listBox.AddString(xStr);
			listBox.AddString(yStr);
			listBox.SetTopIndex(listBox.GetCount() - 1);
		}
		else if (count == 2)
		{
			xEdit2.SetWindowTextW(xStr);
			yEdit2.SetWindowTextW(yStr);
			listBox.AddString(xStr);
			listBox.AddString(yStr);
			listBox.SetTopIndex(listBox.GetCount() - 1);
		}
		else if (count == 3)
		{
			xEdit3.SetWindowTextW(xStr);
			yEdit3.SetWindowTextW(yStr);
			listBox.AddString(xStr);
			listBox.AddString(yStr);
			listBox.SetTopIndex(listBox.GetCount() - 1);
			CalculatePerpendicularFoot();
		}
	}
	count++;
	
	
	RECT rect;
	GetDlgItem(IDC_PICCON_BOARD)->GetClientRect(&rect);
	m_points.push_back(clientPnt);

	if (radioCheck1.GetCheck() == TRUE)
	{
		if (m_points.size() == 2) 
		{
			CClientDC dc(&m_picBoard);
			dc.MoveTo(m_points[0]);
			dc.LineTo(m_points[1]);
		}
		else if (m_points.size() == 3)
		{
			CClientDC dc(&m_picBoard);
			dc.MoveTo(m_points[0]);
			dc.LineTo(m_points[1]); 

			// 두 점 사이의 x, y 좌표의 차이를 계산하여 두 점을 통과하는 직선의 기울기를 계산
			double slope = static_cast<double>(m_points[1].y - m_points[0].y) / (m_points[1].x - m_points[0].x);

			//(m_points[0].x, m_points[0].y)와 (m_points[1].x, m_points[1].y)를 통과하는 직선의 y절편을 계산  |  y = mx + b -> m 기울기, b y절편
			double y_intercept = m_points[1].y - slope * m_points[1].x;

			int x3 = m_points[2].x;
			int y3 = m_points[2].y; 


			double foot_x = (x3 + slope * (y3 - y_intercept)) / (slope * slope + 1);
			double foot_y = slope * foot_x + y_intercept;

			if (point.x >= rect.left && point.y >= rect.top && point.x <= rect.right && point.y <= rect.bottom)
			{
				dc.MoveTo(m_points[0]);
				dc.LineTo(m_points[1]);

				dc.MoveTo(m_points[2]);
				dc.LineTo((int)foot_x, (int)foot_y);
			}
		}


	}
	else if (radioCheck2.GetCheck() == TRUE)
	{
		CPoint p1, p2, p3;
		CClientDC dc(&m_picBoard);

		if (m_points.size() == 2)
		{

			dc.MoveTo(m_points[0]);
			dc.LineTo(m_points[1]);
		}
		else if (m_points.size() == 3)
		{
			p1 = m_points[0];
			p2 = m_points[1];
			p3 = m_points[2];
			DrawTriangle(p1, p2, p3, &dc);
		}
	} 
	else if (radioCheck3.GetCheck() == TRUE)
	{	
		DrawLinearRegression(&dc, m_points);	
	}
	else if (radioCheck4.GetCheck() == TRUE)
	{
		DrawCircle(&dc, m_points);
	}
	else if (radioCheck5.GetCheck() == TRUE)
	{
		DrawParabola(&dc, m_points);
	}
	
}

void CMathMouseApplicationDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CDialogEx::OnLButtonUp(nFlags, point);
	
}

HBRUSH CMathMouseApplicationDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  여기서 DC의 특성을 변경합니다.
	if (pWnd->GetDlgCtrlID() == IDC_PICCON_BOARD)
	{
		pDC->SetBkColor(RGB(255, 255, 255));
		return brush;
	}
	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}

void CMathMouseApplicationDlg::OnBnClickedRadio1()
{
	NumberInit();

	CString str;
	radioCheck1.GetWindowTextW(str);
	CString result;
	result.Format(_T("Radio Box ---- %s"), str);
	listBox.InsertString(-1, result);
	listBox.SetTopIndex(listBox.GetCount() - 1);
}

void CMathMouseApplicationDlg::OnBnClickedRadio2()
{
	NumberInit();

	CClientDC dc(this);
	DrawCrossLine(&dc);

	CString str;
	radioCheck2.GetWindowTextW(str);
	CString result;
	result.Format(_T("Radio Box ---- %s"), str);
	listBox.InsertString(-1, result);
	listBox.SetTopIndex(listBox.GetCount() - 1);
}

void CMathMouseApplicationDlg::OnBnClickedRadio3()
{
	NumberInit();

	CClientDC dc(this);
	//DrawCrossLine(&dc);

	CString str;
	radioCheck2.GetWindowTextW(str);
	CString result;
	result.Format(_T("Radio Box ---- %s"), str);
	listBox.InsertString(-1, result);
	listBox.SetTopIndex(listBox.GetCount() - 1);
}

void CMathMouseApplicationDlg::NumberInit()
{

	CRect rect;
	m_picBoard.GetWindowRect(&rect);
	ScreenToClient(&rect);

	InvalidateRect(&rect); // 화면 갱신
	UpdateWindow();

	xEdit1.SetSel(0, -1, TRUE);
	xEdit1.Clear();
	yEdit1.SetSel(0, -1, TRUE);
	yEdit1.Clear();

	xEdit2.SetSel(0, -1, TRUE);
	xEdit2.Clear();
	yEdit2.SetSel(0, -1, TRUE);
	yEdit2.Clear();
	   	 
	xEdit3.SetSel(0, -1, TRUE);
	xEdit3.Clear();
	yEdit3.SetSel(0, -1, TRUE);
	yEdit3.Clear();

	//listBox.ResetContent();

	count = 1;
	m_points.clear();
	m_arrDPoints.RemoveAll();
}

void CMathMouseApplicationDlg::OnBnClickedRadio5()
{

	NumberInit();
}

void CMathMouseApplicationDlg::CalculatePerpendicularFoot()
{
	if (radioCheck1.GetCheck() == TRUE)
	{
		CString strX1, strY1, strX2, strY2, strXp, strYp;

		// Edit Box에서 좌표값을 문자열로 가져옴
		GetDlgItemText(IDC_EDIT3, strX1);
		GetDlgItemText(IDC_EDIT6, strY1);
		GetDlgItemText(IDC_EDIT7, strX2);
		GetDlgItemText(IDC_EDIT8, strY2);
		GetDlgItemText(IDC_EDIT9, strXp);
		GetDlgItemText(IDC_EDIT10, strYp);

		// 문자열을 정수로 변환
		double x1 = _ttoi(strX1);
		double y1 = _ttoi(strY1);
		double x2 = _ttoi(strX2);
		double y2 = _ttoi(strY2);
		double xp = _ttoi(strXp);
		double yp = _ttoi(strYp);
		
		double slope = 0;
		double inter_slope = 0;
		double inter_y = 0;
		double y_intercept = 0;
		double foot_x = 0;
		double foot_y = 0;
		
		if (y1 == y2)
		{
			foot_x = xp;
			foot_y = y1;

		}
		else if (x1 == x2)
		{
			foot_x = x1;
			foot_y = yp;
		}
		else 
		{
			// 두 점을 지나는 직선의 기울기와 y절편 계산
			slope = (y2 - y1) / (x2 - x1);
			y_intercept = y1 - slope * x1;

			//수선의 방정식
			inter_slope = -1 / slope;
			inter_y = -inter_slope * xp + yp;
			 
			//교점 
			foot_x = (inter_y - y_intercept) / (slope - inter_slope);
			foot_y = slope * (inter_y - y_intercept) / (slope - inter_slope) + y_intercept;
		}

		// 수선의 발 좌표 설정
		m_foot = CPoint(foot_x, foot_y);
		
		CString slopeStr;
		slopeStr.Format(L"직선 방정식 [y = %.3fx + %.3f]", slope, y_intercept);
		CString y_interceptStr;
		y_interceptStr.Format(L"수선 방정식	[y = %.3fx + %.3f]", inter_slope, inter_y);
		CString crossPointStr;
		crossPointStr.Format(L"교점 (%.3f, %.3f)", foot_x, foot_y);
	
		
		listBox.AddString(slopeStr);
		listBox.AddString(y_interceptStr);
		listBox.AddString(crossPointStr);
		listBox.SetTopIndex(listBox.GetCount() - 1);

	}
}

void CMathMouseApplicationDlg::DrawTriangle(const CPoint& p1, const CPoint& p2, const CPoint& p3, CDC * pDC)
{
	CClientDC dc(&m_picBoard);
	CPen pen(PS_SOLID, 3, RGB(0, 0, 0));
	CPen* oldPen = dc.SelectObject(&pen);
	dc.MoveTo(p1);
	dc.LineTo(p2);
	dc.LineTo(p3);
	dc.LineTo(p1);
	
	dc.SelectObject(oldPen);
}

void CMathMouseApplicationDlg::DrawCrossLine(CDC * pDC)
{
	CRect staticBoxRect;
	GetDlgItem(IDC_PICCON_BOARD)->GetWindowRect(&staticBoxRect);
	ScreenToClient(&staticBoxRect);
	
	int horizontalLineY = staticBoxRect.top + staticBoxRect.Height() / 2;
	int verticalLineX = staticBoxRect.left + staticBoxRect.Width() / 2;

	pDC->MoveTo(staticBoxRect.left, horizontalLineY);
	pDC->LineTo(staticBoxRect.right, horizontalLineY);

	pDC->MoveTo(verticalLineX, staticBoxRect.top);
	pDC->LineTo(verticalLineX, staticBoxRect.bottom);

}

void  CMathMouseApplicationDlg::DrawRotatedTriangle(CDC* pDC, INT degree)
{

	double radians = degree * M_PI / 180.0;
	double cosA = cos(radians);
	double sinA = sin(radians);

	CRect cRect;
	m_picBoard.GetClientRect(&cRect);

	for (int i = 0; i < m_arrDPoints.GetSize(); i++)
	{
		// 회전 변환 적용
		double x = m_arrDPoints[i].x;
		double y = m_arrDPoints[i].y;

		m_arrDPoints[i].x = x * cosA - y * sinA;
		m_arrDPoints[i].y = x * sinA + y * cosA;

		m_points[i] = CPoint(m_arrDPoints[i].x, m_arrDPoints[i].y);
		m_points[i].y *= -1;
		m_points[i].x += cRect.right / 2;
		m_points[i].y += cRect.bottom / 2;

		CString str;
		str.Format(L"( %.3f,  %.3f )", m_arrDPoints[i].x, m_arrDPoints[i].y);
		listBox.AddString(str);
		listBox.SetTopIndex(listBox.GetCount() - 1);
	}
	
	DrawTriangle(m_points[0], m_points[1], m_points[2], pDC);
}

void CMathMouseApplicationDlg::OnBnClickedButton1()
{
	CString angleStr;
	angleEdit.GetWindowTextW(angleStr);
	double degree = _ttoi(angleStr);

	CClientDC dc(&m_picBoard);
	DrawRotatedTriangle(&dc, degree);
}

void CMathMouseApplicationDlg::DrawLinearRegression(CDC* pDC, const std::vector<CPoint>& points) {

	// 직선 지우기
	ClearClientArea();


	std::vector<double> x, y;
	for (const auto& point : points) {
		x.push_back(point.x);
		y.push_back(point.y);
	}

	double x_mean = 0.0;
	double y_mean = 0.0;
	double sigma_x = 0.0;
	double sigma_y = 0.0;
	
	for (int i = 0; i < x.size(); i++)
	{
		sigma_x += x[i];
		sigma_y += y[i];
	}
	// 평균
	x_mean = sigma_x / x.size();
	y_mean = sigma_y / y.size();

	double numerator = 0.0;
	double denominator = 0.0;

	for (int i = 0; i < x.size(); ++i) {
		numerator += (y[i] - y_mean) * (x[i] - x_mean);
		denominator += (x[i] - x_mean) * (x[i] - x_mean);
	}
	double slope = numerator / denominator;
	
	// b = y평균 - a * x평균
	double intercept = y_mean - slope * x_mean;
	
	
	CPen cPen(PS_SOLID, 1, RGB(255, 255, 255)); 
	CPen* oldPen = pDC->SelectObject(&cPen);

	CPen pen(PS_SOLID, 5, RGB(0, 0, 255));
	CPen* pOldPen = pDC->SelectObject(&pen);

	CRect staticBoxRect;
	GetDlgItem(IDC_PICCON_BOARD)->GetWindowRect(&staticBoxRect);
	ScreenToClient(&staticBoxRect);

	pDC->MoveTo(0, intercept);
	//int index = 0;
	for (int i = 1; i < x.size(); i++) {
		pDC->LineTo(staticBoxRect.right - staticBoxRect.left, slope * (staticBoxRect.right - staticBoxRect.left) + intercept);		
	}
	pDC->SelectObject(pOldPen);

	CString slopeStr;

	slopeStr.Format(L"최소자승법 [%.3f = Σ(%.3f-%.3f)(%.3f-%.3f) / Σ(%.3f-%.3f)(%.3f-%.3f)]", 
			slope, y[y.size()-1], y_mean, x[x.size()-1], x_mean, x[x.size()-1], x_mean, x[x.size()-1], x_mean);
	
	listBox.AddString(slopeStr);

	CString interceptStr;
	interceptStr.Format(L"직선의 방정식[%.3f = %.3f + (%.3f) * %.3f]", intercept, y_mean, slope, x_mean);

	listBox.AddString(interceptStr);
	listBox.SetTopIndex(listBox.GetCount() - 1);
}


void CMathMouseApplicationDlg::ClearClientArea() {
	
	CRect rect;
	GetClientRect(&rect);
	CClientDC cDc(this);

	m_picBoard.GetWindowRect(&rect);
	ScreenToClient(&rect);
	
	InvalidateRect(&rect); // 화면 갱신
	
	UpdateWindow();
}

void CMathMouseApplicationDlg::DrawParabola(CDC* pDC, const std::vector<CPoint>& points) {
	
	ClearClientArea();
	
	std::vector<double> x, y;
	for (const auto& point : points) {
		x.push_back(point.x);
		y.push_back(point.y);
	}

	double sigma_x = 0.0;
	double sigma_y = 0.0;

	double xSquare4 = 0.0;
	double xSquare3 = 0.0;
	double xSquare2 = 0.0;
	double x2ySquare = 0.0;
	double xySquare = 0.0;

	double ySquare4 = 0.0;
	double ySquare3 = 0.0;
	double ySquare2 = 0.0;
	double y2xSquare = 0.0;
	
	for (int i = 0; i < points.size(); i++)
	{
		sigma_x += x[i];
		sigma_y += y[i];
		xSquare4 += x[i] * x[i] * x[i] * x[i];
		xSquare3 += x[i] * x[i] * x[i];
		xSquare2 += x[i] * x[i];
		x2ySquare += (x[i] * x[i]) * y[i];
		xySquare += x[i] * y[i];

		ySquare4 += y[i] * y[i] * y[i] * y[i];
		ySquare3 += y[i] * y[i] * y[i];
		ySquare2 += y[i] * y[i];
		y2xSquare += (y[i] * y[i]) * x[i];

	}

	// 분모
	double denominator = (xSquare4 * (x.size() * xSquare2 - (sigma_x * sigma_x)))
						- (xSquare3 * (x.size() * xSquare3 - xSquare2 * sigma_x))
						+ (xSquare2 * (xSquare3 * sigma_x - (xSquare2 * xSquare2)));
	// 분자
	double numeratorA = (x2ySquare * ((x.size() * xSquare2) - (sigma_x * sigma_x))
						- xSquare3 * (x.size() * xySquare - (sigma_x * sigma_y))
						+ xSquare2 * ((sigma_x * xySquare) - (xSquare2 * sigma_y))) / denominator;

	double numeratorB = (xSquare4 * ((x.size() * xySquare) - (sigma_x * sigma_y))
						- x2ySquare * (x.size() * xSquare3 - (xSquare2 * sigma_x))
						+ xSquare2 * ((xSquare3 * sigma_y) - (xSquare2 * xySquare))) / denominator;

	double numeratorC = (xSquare4 * ((xSquare2 * sigma_y) - (xySquare * sigma_x))
						- xSquare3 * ((xSquare3 * sigma_y) - (xySquare * xSquare2))
						+ x2ySquare * ((xSquare3 * sigma_x) - (xSquare2 * xSquare2))) / denominator;
	
	//Y 분모
	double denominatorYstandard = (ySquare4 * (y.size() * ySquare2 - (sigma_y * sigma_y)))
						- (ySquare3 * (y.size() * ySquare3 - ySquare2 * sigma_y))
						+ (ySquare2 * (ySquare3 * sigma_y - (ySquare2 * ySquare2)));

	//Y 분자
	double numeratorAYstandard = (y2xSquare * ((y.size() * ySquare2) - (sigma_y * sigma_y))
						- ySquare3 * (y.size() * xySquare - (sigma_x * sigma_y))
						+ ySquare2 * ((sigma_y * xySquare) - (ySquare2 * sigma_x))) / denominatorYstandard;

	double numeratorBYstandard = (ySquare4 * ((y.size() * xySquare) - (sigma_x * sigma_y))
						- y2xSquare * (y.size() * ySquare3 - (ySquare2 * sigma_y))
						+ ySquare2 * ((ySquare3 * sigma_x) - (ySquare2 * xySquare))) / denominatorYstandard;

	double numeratorCYstandard = (ySquare4 * ((ySquare2 * sigma_x) - (xySquare * sigma_y))
						- ySquare3 * ((ySquare3 * sigma_x) - (xySquare * ySquare2))
						+ y2xSquare * ((ySquare3 * sigma_y) - (ySquare2 * ySquare2))) / denominatorYstandard;


	CBrush red(RGB(255, 0, 0));
	CBrush *old_blue = pDC->SelectObject(&red);

	CRect staticBoxRect;
	GetDlgItem(IDC_PICCON_BOARD)->GetClientRect(&staticBoxRect);
	
	//pDC->MoveTo(0, numeratorC);
	//double realY = numeratorA * ((staticBoxRect.right - staticBoxRect.left) * (staticBoxRect.right - staticBoxRect.left)) + numeratorB * (staticBoxRect.right - staticBoxRect.left) + numeratorC;
	double yPosStandard = 0;
	double xPosStandard = 0;
	for (int i = 0; i < points.size(); i++)
	{
		yPosStandard = abs(y[i] - (numeratorA * (x[i] * x[i]) + numeratorB * x[i] + numeratorC));
		xPosStandard = abs(x[i] - (numeratorAYstandard * (y[i] * y[i]) + numeratorBYstandard * y[i] + numeratorCYstandard));
	}

	double yPos = 0.0;
	double xPos = 0.0;
	for (int i = 0; i < points.size(); i++)
	{
		if (yPosStandard < xPosStandard)
		{
			for (int i = 0; i < staticBoxRect.Width(); i++) {
				xPos = i;
				yPos = numeratorA * (xPos * xPos) + numeratorB * xPos + numeratorC;

				//xPos = numeratorA * (yPos * yPos) + numeratorB * yPos + numeratorC;

				pDC->SetPixelV(static_cast<long>(xPos), static_cast<long>(yPos), RGB(0, 0, 0));
			}
		}
		else
		{
			for (int i = 0; i < staticBoxRect.Height(); i++) {
				yPos = i;
				//yPos = numeratorA * (xPos * xPos) + numeratorB * xPos + numeratorC;
				xPos = numeratorAYstandard * (yPos * yPos) + numeratorBYstandard * yPos + numeratorCYstandard;

				pDC->SetPixelV(static_cast<long>(xPos), static_cast<long>(yPos), RGB(0, 0, 0));

			}
		}
	}
	


	CString str;
	str.Format(L"이차 방정식 [%.3f = %.3f * (%.3f * %.3f) + %.3f * %.3f + %.3f]", yPos, numeratorA, xPos, xPos, numeratorB, xPos, numeratorC);
	listBox.AddString(str);
	listBox.SetTopIndex(listBox.GetCount() - 1);
	pDC->SelectObject(old_blue);
	
}

void CMathMouseApplicationDlg::DrawCircle(CDC* pDC, const std::vector<CPoint>& points)
{
	ClearClientArea();

	std::vector<double> x, y;
	for (const auto& point : points) {
		x.push_back(point.x);
		y.push_back(point.y);
	}

	double circleA = 0.0;
	double circleB = 0.0;
	double radius = 0.0;

	for (int i = 0; i < points.size(); i++)
	{
		circleA += x[i];
		circleB += y[i];
	}
	circleA = circleA / x.size();
	circleB = circleB / y.size();

	for (int i = 0; i < points.size(); i++)
	{
		radius += sqrt((x[i] - circleA) * (x[i] - circleA) + (y[i] - circleB) * (y[i] - circleB));
	}
	radius /= points.size();

	CBrush red(RGB(0, 255, 0));
	red.CreateStockObject(NULL_BRUSH);
	CBrush *old_blue = pDC->SelectObject(&red);
	
	pDC->Ellipse(circleA - radius, circleB - radius, circleA + radius, circleB + radius);
	
	CString str;
	str.Format(L"원의 방정식 %.3f * %.3f = (%.3f - %.3f) * (%.3f - %.3f) + (%.3f - %.3f) * (%.3f - %.3f)", radius, radius, x[x.size() - 1], circleA, x[x.size() - 1], circleA, y[y.size() - 1], circleB, y[y.size() - 1], circleB);
	
	listBox.AddString(str);
	listBox.SetTopIndex(listBox.GetCount() - 1);
	pDC->SelectObject(&old_blue);

}

void CMathMouseApplicationDlg::OnStnClickedPicconBoard()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
