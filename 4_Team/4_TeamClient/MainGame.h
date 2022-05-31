#pragma once
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

	TCHAR		m_szFPS[64];
	int			m_iFPS;
	DWORD		m_dwFPSTime;
};
