#pragma once
#include "Obj.h"
#include "JunPlayer.h"
#include "Fortress_Monster_Bullet.h"

class CFortress_Monster : public CObj
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
	void		Shoot_Bullet();
	void		Move();

	void		Set_Angle(float _f) {	m_fAngle = (_f);}
	
	const int&		Get_Hp() { return m_iHp; }
	void			Set_Hp(const int& _Hp) { m_iHp -= _Hp; }

private:
	INFO			m_tInfo_Body_Local[4];
	INFO			m_tInfo_Body_World[4];

	INFO			m_tInfo_Head_Local[4];
	INFO			m_tInfo_Head_World[4];
		
	INFO			m_tInfo_Posin_Local[2];
	INFO			m_tInfo_Posin_World[2];

private:
	int				m_iHp;
	int				m_iRandom_Move;

	float			m_fRandom;
		
	float			m_fAngle_Body;
	float			m_fAngle_Posin;

	bool			m_bRandom;
	bool			m_bRandom_Move;
	bool			m_bShoot;
	bool			m_bMonster_Turn;

	DWORD			m_dwShootCount;
	DWORD			m_dwShootDelay;
	D3DXMATRIX		m_PosinWorld;

	CFortress_Monster_Bullet*	Fortress_Monster_Bullet;
	CJunPlayer*		pJunPlayer;

};

