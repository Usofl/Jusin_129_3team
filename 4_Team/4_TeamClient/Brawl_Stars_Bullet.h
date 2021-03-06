#pragma once
#include "Player.h"
class CBrawl_Stars_Bullet :
	public CPlayer
{
public:
	CBrawl_Stars_Bullet();
	virtual ~CBrawl_Stars_Bullet();

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

	void		Key_Input(void);

private:
	INFO		m_tInfo_Bullet_Local[4];
	INFO		m_tInfo_Bullet_World[4];

};

