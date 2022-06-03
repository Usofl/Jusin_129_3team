#pragma once
#include "Device.h"
#include "SingleTexture.h"
#include "MultiTexture.h"
class CMainGame
{
public:
	CMainGame();
	~CMainGame();

public:
	void	Initialize(void);
	void	Update(void);
	void	Late_Update(void);
	void	Render(void);
	void	Release(void);

private:
	HDC		m_hDC;
	HDC		m_hBackDC;
	HDC		m_hGroundDC;

	TCHAR		m_szFPS[64];
	int			m_iFPS;
	DWORD		m_dwFPSTime;
};
