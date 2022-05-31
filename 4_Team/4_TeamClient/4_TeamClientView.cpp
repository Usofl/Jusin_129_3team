
// 4_TeamClientView.cpp : CMy4_TeamClientView Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
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
	// ǥ�� �μ� ����Դϴ�.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CMy4_TeamClientView ����/�Ҹ�

CMy4_TeamClientView::CMy4_TeamClientView()
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.

}

CMy4_TeamClientView::~CMy4_TeamClientView()
{
}

BOOL CMy4_TeamClientView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CView::PreCreateWindow(cs);
}

// CMy4_TeamClientView �׸���

void CMy4_TeamClientView::OnDraw(CDC* /*pDC*/)
{
	CMy4_TeamClientDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.
}


// CMy4_TeamClientView �μ�

BOOL CMy4_TeamClientView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �⺻���� �غ�
	return DoPreparePrinting(pInfo);
}

void CMy4_TeamClientView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ��ϱ� ���� �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
}

void CMy4_TeamClientView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ� �� ���� �۾��� �߰��մϴ�.
}


// CMy4_TeamClientView ����

#ifdef _DEBUG
void CMy4_TeamClientView::AssertValid() const
{
	CView::AssertValid();
}

void CMy4_TeamClientView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMy4_TeamClientDoc* CMy4_TeamClientView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy4_TeamClientDoc)));
	return (CMy4_TeamClientDoc*)m_pDocument;
}
#endif //_DEBUG


// CMy4_TeamClientView �޽��� ó����
