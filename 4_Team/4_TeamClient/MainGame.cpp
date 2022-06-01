#include "stdafx.h"
#include "MainGame.h"
#include "SceneMgr.h"

CMainGame::CMainGame()
	: m_dwFPSTime(GetTickCount())
	, m_iFPS(0)
{
	ZeroMemory(m_szFPS, sizeof(TCHAR) * 64);
}

CMainGame::~CMainGame()
{
	Release();
}

void CMainGame::Initialize(void)
{
	m_hDC = GetDC(g_hWnd);
	//m_hBackDC = CBmpMgr::Get_Instance()->Find_Image(L"Back");

#ifdef _DEBUG

	if (::AllocConsole() == TRUE)
	{
		FILE* nfp[3];
		freopen_s(nfp + 0, "CONOUT$", "rb", stdin);
		freopen_s(nfp + 1, "CONOUT$", "wb", stdout);
		freopen_s(nfp + 2, "CONOUT$", "wb", stderr);
		std::ios::sync_with_stdio();
	}

#endif _DEBUG

	SCENEMGR->Scene_Change(SC_BRAWL_STARS);
}

void CMainGame::Update(void)
{
	SCENEMGR->Update();
}

void CMainGame::Late_Update(void)
{
	SCENEMGR->Late_Update();
}

void CMainGame::Render(void)
{
	BitBlt(m_hDC, 0, 0, WINCX, WINCY, m_hBackDC, 0, 0, SRCCOPY);

	SCENEMGR->Render(m_hDC);

#ifdef _DEBUG
	++m_iFPS;

	if (m_dwFPSTime + 1000 < GetTickCount())
	{
		swprintf_s(m_szFPS, L"FPS : %d", m_iFPS);
		SetWindowText(g_hWnd, m_szFPS);

		m_iFPS = 0;
		m_dwFPSTime = GetTickCount();
	}
#endif _DEBUG
}

void CMainGame::Release(void)
{
#ifdef _DEBUG

	FreeConsole();

#endif _DEBUG

	SCENEMGR->Destroy_Instance();

	ReleaseDC(g_hWnd, m_hDC);
	ReleaseDC(g_hWnd, m_hBackDC);
}
