#include "stdafx.h"
#include "Brawl_Stars_Scene.h"


CBrawl_Stars_Scene::CBrawl_Stars_Scene()
	:m_pBrawl_Stars_Player(nullptr)
{
}


CBrawl_Stars_Scene::~CBrawl_Stars_Scene()
{
	Release();
}

void CBrawl_Stars_Scene::Initialize(void)
{
	if (!m_pBrawl_Stars_Player)
	{
		m_pBrawl_Stars_Player = new	CBrawl_Stars_Player;
		m_pBrawl_Stars_Player->Initialize();
	}
}

void CBrawl_Stars_Scene::Update(void)
{
	m_pBrawl_Stars_Player->Update();
}

void CBrawl_Stars_Scene::Late_Update(void)
{
}

void CBrawl_Stars_Scene::Render(HDC _hDC)
{
	Rectangle(_hDC, 0, 0, WINCX, WINCY);

	m_pBrawl_Stars_Player->Render(_hDC);
}

void CBrawl_Stars_Scene::Release(void)
{
	Safe_Delete<CObj*>(m_pBrawl_Stars_Player);


}

void CBrawl_Stars_Scene::Key_Input(void)
{
}
