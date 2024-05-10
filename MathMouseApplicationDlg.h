
// MathMouseApplicationDlg.h: 헤더 파일
//

#pragma once
#include <vector>

// CMathMouseApplicationDlg 대화 상자

struct DoublePoint
{
	DoublePoint() {}
	DoublePoint(double x, double y) : x(x), y(y) {}
	double x;
	double y;
};

class CMathMouseApplicationDlg : public CDialogEx
{
// 생성입니다.
public:
	CMathMouseApplicationDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MATHMOUSEAPPLICATION_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP();
private:
	CImage m_image;
	CPoint m_foot;
	CPoint startPoint, endPoint;
	int count;
	int m_ptStart;
	int m_ptPrev;
	bool isMouseDown;

	
public:
	// radioBox
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnBnClickedRadio3();
	afx_msg void OnBnClickedRadio4();
	afx_msg void OnBnClickedRadio5();
	
	// 마우스 이벤트
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);

	// color
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

	// 화면 초기화
	void NumberInit();
	void ClearClientArea();

	// 수선의 발 계산
	void CalculatePerpendicularFoot();

	// 도형 그리기
	void DrawTriangle(const CPoint& p1, const CPoint& p2, const CPoint& p3, CDC* pDC);
	void DrawCrossLine(CDC* pDC);
	void DrawParabola(CDC* pDC, const std::vector<CPoint>& points);
	void DrawRotatedTriangle(CDC* pDC, INT degree);
	void DrawCircle(CDC* pDC, const std::vector<CPoint>& points);

	// edit 박스에 좌표 출력
	void WriteEdit(CPoint clientPnt, int count);
	
	// 화면에 선 긋기
	void DrawLinearRegression(CDC* pDC, const std::vector<CPoint>& points);
	
	
	CEdit xEdit;
	CEdit yEdit;
	CEdit xEdit1;
	CEdit yEdit1;
	CEdit xEdit2;
	CEdit yEdit2;
	CEdit xEdit3;
	CEdit yEdit3;
	CListBox listBox;
	std::vector<CPoint> m_points;
	CArray<DoublePoint> m_arrDPoints;

	CPoint m_pntOld, m_pntCur;
	CPoint Previous_;
	CPoint m_Pos;
	COLORREF m_colLine, m_colFill;
	COLORREF m_colLineXor;

	CBrush brush;
	
	CButton radioCheck1;
	CButton radioCheck2;
	CButton RotateButton;
	afx_msg void OnBnClickedButton1();
	
	CEdit angleEdit;
	CStatic m_picBoard;
	
	CButton radioCheck3;
	CButton radioCheck4;
	CButton radioCheck5;
	afx_msg void OnStnClickedPicconBoard();
};