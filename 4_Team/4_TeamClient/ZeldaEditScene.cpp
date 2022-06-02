#include "stdafx.h"
#include "ZeldaEditScene.h"
#include "ScrollMgr.h"
#include "KeyMgr.h"
#include "ZeldaFactory.h"

CZeldaEditScene::CZeldaEditScene()
	: m_fSpeed(3.f)
	, m_pZelda_Obj(nullptr)
	, m_Zelda_Obj_Id(ZELDAOBJ_END)
{
	Initialize();
}


CZeldaEditScene::~CZeldaEditScene()
{
	Release();
}

void CZeldaEditScene::Initialize(void)
{
	GetCursorPos(&m_pt);
	ScreenToClient(g_hWnd, &m_pt);

	m_pt.x -= (LONG)CScrollMgr::Get_Instance()->Get_ScrollX();
	m_pt.y -= (LONG)CScrollMgr::Get_Instance()->Get_ScrollY();

	if (nullptr == m_pZelda_Obj)
	{
		m_pZelda_Obj = CZeldaFactory::Create_Zelda_Wall((const float)m_pt.x, (const float)m_pt.y, 50.f, 50.f);
		m_Zelda_Obj_Id = ZELDAOBJ_WALL;
	}
}

void CZeldaEditScene::Update(void)
{
	GetCursorPos(&m_pt);
	ScreenToClient(g_hWnd, &m_pt);

	m_pt.x -= (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	m_pt.y -= (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	m_pZelda_Obj->Set_Pos((const float)m_pt.x, (const float)m_pt.y);
	m_pZelda_Obj->Update();

	Key_Input();
}

void CZeldaEditScene::Late_Update(void)
{
}

void CZeldaEditScene::Render(HDC _hDC)
{
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	m_pZelda_Obj->Render(_hDC);
}

void CZeldaEditScene::Release(void)
{
	Safe_Delete<CZelda_Obj*>(m_pZelda_Obj);
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

	if (CKeyMgr::Get_Instance()->Key_Up(VK_LBUTTON))
	{
		switch (m_Zelda_Obj_Id)
		{
		case ZELDAOBJ_WALL:
			m_vecZelda_Obj[m_Zelda_Obj_Id].push_back(CZeldaFactory::Create_Zelda_Wall(m_pZelda_Obj->Get_Info().vPos.x, m_pZelda_Obj->Get_Info().vPos.y,
														m_pZelda_Obj->Get_X_Size(), m_pZelda_Obj->Get_Y_Size() ));
			break;
		case ZELDAOBJ_STONE:
			m_vecZelda_Obj[m_Zelda_Obj_Id].push_back(CZeldaFactory::Create_Zelda_Stone(m_pZelda_Obj->Get_Info().vPos.x, m_pZelda_Obj->Get_Info().vPos.y,
				m_pZelda_Obj->Get_X_Size(), m_pZelda_Obj->Get_Y_Size()));
			break;
		case ZELDAOBJ_BUTTON:
			m_vecZelda_Obj[m_Zelda_Obj_Id].push_back(CZeldaFactory::Create_Zelda_Button(m_pZelda_Obj->Get_Info().vPos.x, m_pZelda_Obj->Get_Info().vPos.y,
				m_pZelda_Obj->Get_X_Size(), m_pZelda_Obj->Get_Y_Size()));
			break;
		}
	}

	if (CKeyMgr::Get_Instance()->Key_Up(VK_RBUTTON))
	{
		Safe_Delete<CZelda_Obj*>(m_pZelda_Obj);
		switch (m_Zelda_Obj_Id)
		{
		case ZELDAOBJ_WALL:
			m_pZelda_Obj = CZeldaFactory::Create_Zelda_Stone((const float)m_pt.x, (const float)m_pt.y, 50.f, 50.f);
			m_Zelda_Obj_Id = ZELDAOBJ_STONE;
			break;
		case ZELDAOBJ_STONE:
			m_pZelda_Obj = CZeldaFactory::Create_Zelda_Button((const float)m_pt.x, (const float)m_pt.y, 50.f, 50.f);
			m_Zelda_Obj_Id = ZELDAOBJ_BUTTON;
			break;
		case ZELDAOBJ_BUTTON:
			m_pZelda_Obj = CZeldaFactory::Create_Zelda_Wall((const float)m_pt.x, (const float)m_pt.y, 50.f, 50.f);
			m_Zelda_Obj_Id = ZELDAOBJ_WALL;
			break;
		}
	}
}
