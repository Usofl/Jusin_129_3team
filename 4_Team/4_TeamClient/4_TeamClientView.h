
// 4_TeamClientView.h : CMy4_TeamClientView Ŭ������ �������̽�
//

#pragma once


class CMy4_TeamClientView : public CView
{
protected: // serialization������ ��������ϴ�.
	CMy4_TeamClientView();
	DECLARE_DYNCREATE(CMy4_TeamClientView)

// Ư���Դϴ�.
public:
	CMy4_TeamClientDoc* GetDocument() const;

// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual void OnDraw(CDC* pDC);  // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// �����Դϴ�.
public:
	virtual ~CMy4_TeamClientView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // 4_TeamClientView.cpp�� ����� ����
inline CMy4_TeamClientDoc* CMy4_TeamClientView::GetDocument() const
   { return reinterpret_cast<CMy4_TeamClientDoc*>(m_pDocument); }
#endif

