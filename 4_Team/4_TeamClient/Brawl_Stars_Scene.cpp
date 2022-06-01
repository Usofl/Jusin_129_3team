#include "stdafx.h"
#include "Brawl_Stars_Scene.h"
#include "BrawlFactory.h"

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
		m_pBrawl_Stars_Player->Set_BulletList(&m_Brawl_List[BRAWL_BULLET]);
	}

	//m_Brawl_List[BRAWL_INFO].push_back(CBrawlFactory::Create_Brawl_Player());
	//dynamic_cast<CBrawl_Stars_Player*>(m_Brawl_List[BRAWL_INFO].front())->Set_BulletList(&m_Brawl_List[BRAWL_BULLET]);
}

void CBrawl_Stars_Scene::Update(void)
{
	m_pBrawl_Stars_Player->Update();

	for (int i = 0; i < BRAWL_END; ++i)
	{
		for (auto& iter = m_Brawl_List[i].begin();
			iter != m_Brawl_List[i].end(); )
		{
			(*iter)->Update();

			++iter;
		}
	}
}

void CBrawl_Stars_Scene::Late_Update(void)
{
}

void CBrawl_Stars_Scene::Render(HDC _hDC)
{
	Rectangle(_hDC, 0, 0, WINCX, WINCY);

	m_pBrawl_Stars_Player->Render(_hDC);

	for (int i = 0; i < BRAWL_END; ++i)
	{
		for (auto& iter : m_Brawl_List[i])
			iter->Render(_hDC);
	}
}

void CBrawl_Stars_Scene::Release(void)
{
	Safe_Delete<CBrawl_Stars_Player*>(m_pBrawl_Stars_Player);
	for (int i = 0; i < BRAWL_END; ++i)
	{
		for (auto& iter : m_Brawl_List[i])
			Safe_Delete<CObj*>(iter);

		m_Brawl_List[i].clear();
	}

}

void CBrawl_Stars_Scene::Key_Input(void)
{
}
