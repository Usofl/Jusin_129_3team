#include "stdafx.h"
#include "MainGame.h"
#include "SceneMgr.h"
#include "KeyMgr.h"
#include "RenderMgr.h"
#include "ScrollMgr.h"
#include "Device.h"
#include "TextureMgr.h"

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
	m_hBackDC = GetDC(g_hWnd);

	//SCENEMGR->Scene_Change(SC_ZELDA);
	//SCENEMGR->Scene_Change(SC_ZELDA_EDIT);
	SCENEMGR->Scene_Change(SC_FORTRESS);
	//SCENEMGR->Scene_Change(SC_FLASHMAN);
	//SCENEMGR->Scene_Change(SC_MOMO);
	//SCENEMGR->Scene_Change(SC_BRAWL_STARS);
	 
	if (FAILED(DEVICE->Initialize()))
	{
		AfxMessageBox(L"m_pDevice 생성 실패");
		return;
	}

	if (FAILED(TEXTUREMGR->InsertTexture(L"../Texture/Back.png", TEX_SINGLE, L"Back")))
	{
		AfxMessageBox(L"Back Image Insert failed");
		return;
	}

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
	D3DXMATRIX		matWorld, matScale, matRotZ, matTrans;

	D3DXMatrixIdentity(&matWorld);
	D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);
	D3DXMatrixRotationZ(&matRotZ, 0.f);
	D3DXMatrixTranslation(&matTrans, 400.f, 300.f, 0.f);

	matWorld = matScale * matRotZ * matTrans;

	DEVICE->Get_Sprite()->SetTransform(&matWorld);

	const TEXINFO*		pTexInfo = TEXTUREMGR->Get_Texture(L"Back");

	float		fX = pTexInfo->tImgInfo.Width / 2.f;
	float		fY = pTexInfo->tImgInfo.Height / 2.f;

	m_hDC = GetDC(g_hWnd);
	m_hBackDC = CreateCompatibleDC(m_hDC);
	HBITMAP m_hBackBit = CreateCompatibleBitmap(m_hDC, WINCX, WINCY);
	HBITMAP m_hOldBackBit = (HBITMAP)SelectObject(m_hBackDC, m_hBackBit);

	Rectangle(m_hBackDC, 0, 0, WINCX, WINCY);
	SCENEMGR->Render(m_hBackDC);

	BitBlt(m_hDC, 0, 0, WINCX, WINCY, m_hBackDC, 0, 0, SRCCOPY);

	SelectObject(m_hBackDC, m_hOldBackBit); //DC에 원래 설정을 돌려줍니다.
	DeleteDC(m_hBackDC);  // 메모리를 반환합니다.
	DeleteObject(m_hBackBit); // 메모리를 반환합니다.
	ReleaseDC(g_hWnd, m_hDC);

	//DEVICE->Render_Begin();

	//DEVICE->Get_Sprite()->Draw(pTexInfo->pTexture,	// 그리고자 하는 텍스처
	//	nullptr, // 출력할 이미지 영역에 대한 rect 포인터, null인 경우 이미지의 0, 0 기준으로 출력
	//	&D3DXVECTOR3(fX, fY, 0.f), // 출력할 이미지 중심 축에 대한 vec3 구조체 포인터, null인 경우 0, 0이 중심 좌표
	//	nullptr, // 위치 좌표에 대한 vec3 구조체 포인터, null인 경우 스크린 상 0,0 좌표에 출력
	//	D3DCOLOR_ARGB(255, 255, 255, 255)); //출력할 원본 이미지와 섞을 색상 값, 출력 시 섞은 색상이 반영, 0xffffffff를 넘겨주면 원본 색상 유지된 상태로 출력

	//DEVICE->Render_End();

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
	KEYMGR->Destroy_Instance();
	SCROLLMGR->Destroy_Instance();
	RENDERMGR->Destroy_Instance();
	TEXTUREMGR->Destroy_Instance();
	DEVICE->Destroy_Instance();

	ReleaseDC(g_hWnd, m_hDC);
	ReleaseDC(g_hWnd, m_hBackDC); 
}
