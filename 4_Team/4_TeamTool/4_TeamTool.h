
// 4_TeamTool.h : 4_TeamTool ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.


// CMy4_TeamToolApp:
// �� Ŭ������ ������ ���ؼ��� 4_TeamTool.cpp�� �����Ͻʽÿ�.
//

class CMy4_TeamToolApp : public CWinApp
{
public:
	CMy4_TeamToolApp();


// �������Դϴ�.
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// �����Դϴ�.
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
	virtual BOOL OnIdle(LONG lCount);
};

extern CMy4_TeamToolApp theApp;
