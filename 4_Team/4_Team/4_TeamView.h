
// 4_TeamView.h : CMy4_TeamView Ŭ������ �������̽�
//

#pragma once


class CMy4_TeamView : public CView
{
protected: // serialization������ ��������ϴ�.
	CMy4_TeamView();
	DECLARE_DYNCREATE(CMy4_TeamView)

// Ư���Դϴ�.
public:
	CMy4_TeamDoc* GetDocument() const;

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
	virtual ~CMy4_TeamView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // 4_TeamView.cpp�� ����� ����
inline CMy4_TeamDoc* CMy4_TeamView::GetDocument() const
   { return reinterpret_cast<CMy4_TeamDoc*>(m_pDocument); }
#endif

