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

	if (!m_pBrawl_Stars_Monster)
	{
		m_pBrawl_Stars_Monster = new CBrawl_Stars_Monster;
		m_pBrawl_Stars_Monster->Initialize();
	}
}

void CBrawl_Stars_Scene::Update(void)
{
	m_pBrawl_Stars_Player->Update();
	m_pBrawl_Stars_Monster->Update();

	for (int i = 0; i < BRAWL_END; ++i)
	{
		for (auto& iter = m_Brawl_List[i].begin();
			iter != m_Brawl_List[i].end(); )
		{
			int iResult = (*iter)->Update();

			if(OBJ_DEAD == iResult)
			{
				Safe_Delete<CObj*>(*iter);
				iter = m_Brawl_List[i].erase(iter);
			}
			else
			{
				++iter;
			}
		}
	}
}

void CBrawl_Stars_Scene::Late_Update(void)
{
	m_pBrawl_Stars_Player->Late_Update();
	m_pBrawl_Stars_Monster->Late_Update();
	for (int i = 0; i < BRAWL_END; ++i)
	{
		for (auto& iter : m_Brawl_List[i])
			iter->Late_Update();
	}
}

void CBrawl_Stars_Scene::Render(HDC _hDC)
{
	Rectangle(_hDC, 0, 0, WINCX, WINCY);

	m_pBrawl_Stars_Monster->Render(_hDC);
	m_pBrawl_Stars_Player->Render(_hDC);

	for (int i = 0; i < BRAWL_END; ++i)
	{
		for (auto& iter : m_Brawl_List[i])
			iter->Render(_hDC);
	}
}

void CBrawl_Stars_Scene::Release(void)
{
	Safe_Delete<CBrawl_Stars_Monster*>(m_pBrawl_Stars_Monster);
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
