#include "stdafx.h"
#include "MomoDoraMgr.h"
#include "MomoAbstractFactory.h"
#include "MomoGun.h"
#include "MomoSword.h"
#include "Obj.h"

CMomoDoraMgr* CMomoDoraMgr::m_pInstance = nullptr;

CMomoDoraMgr::CMomoDoraMgr()
{
}


CMomoDoraMgr::~CMomoDoraMgr()
{
}

void CMomoDoraMgr::Add_Object(MOMOID eID, CMomo_Obj * pObj)
{
	if ((eID >= MOMO_END) || (nullptr == pObj))
		return;

	m_MomodoraList[eID].push_back(pObj);
}

int CMomoDoraMgr::Update(void)
{
	for (int i = 0; i < MOMO_END; ++i)
	{
		for (auto& iter = m_MomodoraList[i].begin();
			iter != m_MomodoraList[i].end(); )
		{
			int iResult = (*iter)->Update();

			if (OBJ_DEAD == iResult)
			{
				Safe_Delete<CMomo_Obj*>(*iter);
				iter = m_MomodoraList[i].erase(iter);
			}
			else
				++iter;
		}
	}

	return 0;
}

void CMomoDoraMgr::Late_Update(void)
{
	for (int i = 0; i < MOMO_END; ++i)
	{
		for (auto& iter : m_MomodoraList[i])
		{

			iter->Late_Update();
			
			RENDERID eRender = iter->Get_RenderID();
			m_RenderSort[eRender].push_back(iter);
		}
	}
}

void CMomoDoraMgr::Render(HDC hDC)
{
	for (int i = 0; i < RENDER_END; ++i)
	{
		//m_RenderSort[i].sort(CompareY<CObj*>);

		for (auto& iter : m_RenderSort[i])
			iter->Render(hDC);

		m_RenderSort[i].clear();
	}
}

void CMomoDoraMgr::Release(void)
{
	for (int i = 0; i < MOMO_END; ++i)
	{
		for (auto& iter : m_MomodoraList[i])
			Safe_Delete<CMomo_Obj*>(iter);

		m_MomodoraList[i].clear();
	}
}

void CMomoDoraMgr::Delete_ID(MOMOID eID)
{
	for (auto& iter : m_MomodoraList[eID])
		Safe_Delete(iter);

	m_MomodoraList[eID].clear();
}

void CMomoDoraMgr::Weapon_Change(MOMO_WEAPONID _eID)
{
	m_eCurWeapon = _eID;

	if (m_ePreWeapon != m_eCurWeapon)
	{

		for (auto& iter : m_MomodoraList[MOMO_WEAPON])
			Safe_Delete<CMomo_Obj*>(iter);

		m_MomodoraList[MOMO_WEAPON].clear();

		switch (m_eCurWeapon)
		{
		case MOMOWEAPON_GUN:
			Add_Object(MOMO_WEAPON, CMomoAbstractFactory<CMomoGun>::Create());
			break;

		case MOMOWEAPON_SWORD:
			Add_Object(MOMO_WEAPON, CMomoAbstractFactory<CMomoSword>::Create());
			break;
		}
	}

	m_ePreWeapon = m_eCurWeapon;
}
