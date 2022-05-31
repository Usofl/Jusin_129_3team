
// 4_TeamToolView.cpp : CMy4_TeamToolView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "4_TeamTool.h"
#endif

#include "4_TeamToolDoc.h"
#include "4_TeamToolView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMy4_TeamToolView

IMPLEMENT_DYNCREATE(CMy4_TeamToolView, CView)

BEGIN_MESSAGE_MAP(CMy4_TeamToolView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CMy4_TeamToolView 생성/소멸

CMy4_TeamToolView::CMy4_TeamToolView()
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CMy4_TeamToolView::~CMy4_TeamToolView()
{
}

void CMy4_TeamToolView::Render()
{
}

BOOL CMy4_TeamToolView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CMy4_TeamToolView 그리기

void CMy4_TeamToolView::OnDraw(CDC* /*pDC*/)
{
	CMy4_TeamToolDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
}


// CMy4_TeamToolView 인쇄

BOOL CMy4_TeamToolView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CMy4_TeamToolView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CMy4_TeamToolView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CMy4_TeamToolView 진단

#ifdef _DEBUG
void CMy4_TeamToolView::AssertValid() const
{
	CView::AssertValid();
}

void CMy4_TeamToolView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMy4_TeamToolDoc* CMy4_TeamToolView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy4_TeamToolDoc)));
	return (CMy4_TeamToolDoc*)m_pDocument;
}
#endif //_DEBUG


// CMy4_TeamToolView 메시지 처리기


void CMy4_TeamToolView::OnInitialUpdate()
{
	m_bReady = TRUE;
	CView::OnInitialUpdate();

	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
}
