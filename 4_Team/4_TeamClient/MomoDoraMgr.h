#pragma once
#include "Momo_Obj.h"
class CMomoDoraMgr
{
private:
	CMomoDoraMgr();
	~CMomoDoraMgr();

public:
	void		Add_Object(MOMOID eID, CMomo_Obj* pObj);
	int			Update(void);
	void		Late_Update(void);
	void		Render(HDC hDC);
	void		Release(void);

	void		Delete_ID(MOMOID eID);
	void		Weapon_Change(MOMO_WEAPONID _eID);


	const INFO&		Get_Info(void) const { return m_tInfo; }

private:
	list<CMomo_Obj*>	m_MomodoraList[MOMO_END];

public:
	static		CMomoDoraMgr*		Get_Instance(void)
	{
		if (!m_pInstance)
		{
			m_pInstance = new CMomoDoraMgr;
		}

		return m_pInstance;
	}

	static	void	Destroy_Instance(void)
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

protected:
	INFO		m_tInfo;

private:
	static CMomoDoraMgr*			m_pInstance;
	list<CMomo_Obj*>				m_RenderSort[RENDER_END];
	MOMO_WEAPONID		m_eCurWeapon;  
	MOMO_WEAPONID		m_ePreWeapon;
};

