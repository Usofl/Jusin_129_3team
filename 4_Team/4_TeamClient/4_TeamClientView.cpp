
// 4_TeamClientView.cpp : CMy4_TeamClientView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "4_TeamClient.h"
#endif

#include "4_TeamClientDoc.h"
#include "4_TeamClientView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMy4_TeamClientView

IMPLEMENT_DYNCREATE(CMy4_TeamClientView, CView)

BEGIN_MESSAGE_MAP(CMy4_TeamClientView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CMy4_TeamClientView 생성/소멸

CMy4_TeamClientView::CMy4_TeamClientView()
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CMy4_TeamClientView::~CMy4_TeamClientView()
{
}

BOOL CMy4_TeamClientView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CMy4_TeamClientView 그리기

void CMy4_TeamClientView::OnDraw(CDC* /*pDC*/)
{
	CMy4_TeamClientDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
}


// CMy4_TeamClientView 인쇄

BOOL CMy4_TeamClientView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CMy4_TeamClientView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CMy4_TeamClientView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CMy4_TeamClientView 진단

#ifdef _DEBUG
void CMy4_TeamClientView::AssertValid() const
{
	CView::AssertValid();
}

void CMy4_TeamClientView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMy4_TeamClientDoc* CMy4_TeamClientView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy4_TeamClientDoc)));
	return (CMy4_TeamClientDoc*)m_pDocument;
}
#endif //_DEBUG


// CMy4_TeamClientView 메시지 처리기
