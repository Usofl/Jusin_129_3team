
// 4_TeamToolView.h : CMy4_TeamToolView Ŭ������ �������̽�
//

#pragma once


class CMy4_TeamToolView : public CView
{
protected: // serialization������ ��������ϴ�.
	CMy4_TeamToolView();
	DECLARE_DYNCREATE(CMy4_TeamToolView)

// Ư���Դϴ�.
public:
	CMy4_TeamToolDoc* GetDocument() const;

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
	virtual ~CMy4_TeamToolView();
	void	Render();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();

private:
	bool m_bReady;
};

#ifndef _DEBUG  // 4_TeamToolView.cpp�� ����� ����
inline CMy4_TeamToolDoc* CMy4_TeamToolView::GetDocument() const
   { return reinterpret_cast<CMy4_TeamToolDoc*>(m_pDocument); }
#endif

