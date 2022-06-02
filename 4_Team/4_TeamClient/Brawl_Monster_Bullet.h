#pragma once
#include "Obj.h"
class CBrawl_Monster_Bullet :
	public CObj
{
public:
	CBrawl_Monster_Bullet();
	virtual ~CBrawl_Monster_Bullet();

public:
	virtual void Initialize(void) override;
	virtual const int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

private:
	INFO		m_tInfo_Bullet_Local[4];
	INFO		m_tInfo_Bullet_World[4];

};

