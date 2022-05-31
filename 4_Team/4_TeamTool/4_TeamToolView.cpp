
// 4_TeamToolView.cpp : CMy4_TeamToolView Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
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
	// ǥ�� �μ� ����Դϴ�.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CMy4_TeamToolView ����/�Ҹ�

CMy4_TeamToolView::CMy4_TeamToolView()
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.

}

CMy4_TeamToolView::~CMy4_TeamToolView()
{
}

void CMy4_TeamToolView::Render()
{
}

BOOL CMy4_TeamToolView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CView::PreCreateWindow(cs);
}

// CMy4_TeamToolView �׸���

void CMy4_TeamToolView::OnDraw(CDC* /*pDC*/)
{
	CMy4_TeamToolDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.
}


// CMy4_TeamToolView �μ�

BOOL CMy4_TeamToolView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �⺻���� �غ�
	return DoPreparePrinting(pInfo);
}

void CMy4_TeamToolView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ��ϱ� ���� �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
}

void CMy4_TeamToolView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ� �� ���� �۾��� �߰��մϴ�.
}


// CMy4_TeamToolView ����

#ifdef _DEBUG
void CMy4_TeamToolView::AssertValid() const
{
	CView::AssertValid();
}

void CMy4_TeamToolView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMy4_TeamToolDoc* CMy4_TeamToolView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy4_TeamToolDoc)));
	return (CMy4_TeamToolDoc*)m_pDocument;
}
#endif //_DEBUG


// CMy4_TeamToolView �޽��� ó����


void CMy4_TeamToolView::OnInitialUpdate()
{
	m_bReady = TRUE;
	CView::OnInitialUpdate();

	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
}
