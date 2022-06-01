#include "stdafx.h"
#include "ZeldaEditScene.h"
#include "ScrollMgr.h"
#include "KeyMgr.h"


CZeldaEditScene::CZeldaEditScene()
	: m_fSpeed(3.f)
{
}


CZeldaEditScene::~CZeldaEditScene()
{
	Release();
}

void CZeldaEditScene::Initialize(void)
{
}

void CZeldaEditScene::Update(void)
{
	Key_Input();
}

void CZeldaEditScene::Late_Update(void)
{
}

void CZeldaEditScene::Render(HDC _hDC)
{
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

}

void CZeldaEditScene::Release(void)
{
}

void CZeldaEditScene::Key_Input(void)
{
	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LEFT))
	{
		CScrollMgr::Get_Instance()->Plus_ScrollX(m_fSpeed);
	}

	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_RIGHT))
	{
		CScrollMgr::Get_Instance()->Plus_ScrollX(-m_fSpeed);
	}

	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_UP))
	{
		CScrollMgr::Get_Instance()->Plus_ScrollY(m_fSpeed);
	}

	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_DOWN))
	{
		CScrollMgr::Get_Instance()->Plus_ScrollY(-m_fSpeed);
	}

}
