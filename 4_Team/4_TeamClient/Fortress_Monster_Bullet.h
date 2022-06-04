#pragma once
#include "Obj.h"
#include "JunPlayer.h"
class CFortress_Monster_Bullet :
	public CObj
{
public:
	CFortress_Monster_Bullet();
	virtual ~CFortress_Monster_Bullet();

public:
	virtual void Initialize(void) override;
	virtual const int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;	
	virtual void Release(void) override;

public:
	void		Set_Pos(const float& _fX, const float& _fY)
	{
		m_tInfo.vPos.x = _fX;
		m_tInfo.vPos.y = _fY;
	}
	void		Set_Angle(const float& _fAngle) { m_fAngle = _fAngle; }

private:
	INFO		m_tInfo_Bullet_Local[4];
	INFO		m_tInfo_Bullet_World[4];


	float		m_fSpeed;

	float		m_fAir_Shoot;
	float		m_fShoot_Power;

};

