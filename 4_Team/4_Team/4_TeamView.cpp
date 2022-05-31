
// 4_TeamView.cpp : CMy4_TeamView Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
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
	// ǥ�� �μ� ����Դϴ�.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CMy4_TeamView ����/�Ҹ�

CMy4_TeamView::CMy4_TeamView()
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.

}

CMy4_TeamView::~CMy4_TeamView()
{
}

BOOL CMy4_TeamView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CView::PreCreateWindow(cs);
}

// CMy4_TeamView �׸���

void CMy4_TeamView::OnDraw(CDC* /*pDC*/)
{
	CMy4_TeamDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.
}


// CMy4_TeamView �μ�

BOOL CMy4_TeamView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �⺻���� �غ�
	return DoPreparePrinting(pInfo);
}

void CMy4_TeamView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ��ϱ� ���� �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
}

void CMy4_TeamView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ� �� ���� �۾��� �߰��մϴ�.
}


// CMy4_TeamView ����

#ifdef _DEBUG
void CMy4_TeamView::AssertValid() const
{
	CView::AssertValid();
}

void CMy4_TeamView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMy4_TeamDoc* CMy4_TeamView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy4_TeamDoc)));
	return (CMy4_TeamDoc*)m_pDocument;
}
#endif //_DEBUG


// CMy4_TeamView �޽��� ó����
