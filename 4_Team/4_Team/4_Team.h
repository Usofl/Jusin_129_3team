
// 4_Team.h : 4_Team ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.


// CMy4_TeamApp:
// �� Ŭ������ ������ ���ؼ��� 4_Team.cpp�� �����Ͻʽÿ�.
//

class CMy4_TeamApp : public CWinApp
{
public:
	CMy4_TeamApp();


// �������Դϴ�.
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// �����Դϴ�.
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
	virtual BOOL OnIdle(LONG lCount);
};

extern CMy4_TeamApp theApp;
