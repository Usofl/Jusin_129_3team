
// 4_TeamClient.h : 4_TeamClient ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.


// CMy4_TeamClientApp:
// �� Ŭ������ ������ ���ؼ��� 4_TeamClient.cpp�� �����Ͻʽÿ�.
//

class CMy4_TeamClientApp : public CWinAppEx
{
public:
	CMy4_TeamClientApp();


// �������Դϴ�.
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// �����Դϴ�.
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
	virtual BOOL OnIdle(LONG lCount);
};

extern CMy4_TeamClientApp theApp;
