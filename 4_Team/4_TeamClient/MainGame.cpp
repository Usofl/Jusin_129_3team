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
		AfxMessageBox(L"m_pDevice ���� ����");
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

	SelectObject(m_hBackDC, m_hOldBackBit); //DC�� ���� ������ �����ݴϴ�.
	DeleteDC(m_hBackDC);  // �޸𸮸� ��ȯ�մϴ�.
	DeleteObject(m_hBackBit); // �޸𸮸� ��ȯ�մϴ�.
	ReleaseDC(g_hWnd, m_hDC);

	//DEVICE->Render_Begin();

	//DEVICE->Get_Sprite()->Draw(pTexInfo->pTexture,	// �׸����� �ϴ� �ؽ�ó
	//	nullptr, // ����� �̹��� ������ ���� rect ������, null�� ��� �̹����� 0, 0 �������� ���
	//	&D3DXVECTOR3(fX, fY, 0.f), // ����� �̹��� �߽� �࿡ ���� vec3 ����ü ������, null�� ��� 0, 0�� �߽� ��ǥ
	//	nullptr, // ��ġ ��ǥ�� ���� vec3 ����ü ������, null�� ��� ��ũ�� �� 0,0 ��ǥ�� ���
	//	D3DCOLOR_ARGB(255, 255, 255, 255)); //����� ���� �̹����� ���� ���� ��, ��� �� ���� ������ �ݿ�, 0xffffffff�� �Ѱ��ָ� ���� ���� ������ ���·� ���

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
