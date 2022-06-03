#pragma once
#include "Obj.h"
#include "Fortress_Monster_Bullet.h"

class CFortress_Monster :
	public CObj
{
public:
	CFortress_Monster();
	virtual ~CFortress_Monster();

public:
	virtual void Initialize(void) override;
	virtual const int  Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

public:
	void			Shoot_Bullet();


	list<CFortress_Monster_Bullet*>* Get_BulletList(void) { return &m_pMonster_Bullet; };

private:
	INFO			m_tInfo_Body_Local[4];
	INFO			m_tInfo_Body_World[4];

	INFO			m_tInfo_Head_Local[4];
	INFO			m_tInfo_Head_World[4];
		
	INFO			m_tInfo_Posin_Local[2];
	INFO			m_tInfo_Posin_World[2];

private:
	float			m_fSpeed;
	float			m_fRandom;
		
	float			m_fAngle_Body;
	float			m_fAngle_Posin;

	DWORD			m_dwShootCount;
	DWORD			m_dwShootDelay;
	D3DXMATRIX		m_PosinWorld;



	CFortress_Monster_Bullet*	Fortress_Monster_Bullet;
	list<CFortress_Monster_Bullet*>	m_pMonster_Bullet;
};

