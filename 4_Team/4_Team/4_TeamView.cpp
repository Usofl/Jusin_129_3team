
// 4_TeamView.cpp : CMy4_TeamView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "4_Team.h"
#endif

#include "4_TeamDoc.h"
#include "4_TeamView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMy4_TeamView

IMPLEMENT_DYNCREATE(CMy4_TeamView, CView)

BEGIN_MESSAGE_MAP(CMy4_TeamView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CMy4_TeamView 생성/소멸

CMy4_TeamView::CMy4_TeamView()
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CMy4_TeamView::~CMy4_TeamView()
{
}

BOOL CMy4_TeamView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CMy4_TeamView 그리기

void CMy4_TeamView::OnDraw(CDC* /*pDC*/)
{
	CMy4_TeamDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
}


// CMy4_TeamView 인쇄

BOOL CMy4_TeamView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CMy4_TeamView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CMy4_TeamView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CMy4_TeamView 진단

#ifdef _DEBUG
void CMy4_TeamView::AssertValid() const
{
	CView::AssertValid();
}

void CMy4_TeamView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMy4_TeamDoc* CMy4_TeamView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy4_TeamDoc)));
	return (CMy4_TeamDoc*)m_pDocument;
}
#endif //_DEBUG


// CMy4_TeamView 메시지 처리기
