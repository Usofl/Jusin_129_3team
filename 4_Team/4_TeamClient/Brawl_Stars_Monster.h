#pragma once
#include "Obj.h"
class CBrawl_Stars_Monster :
	public CObj
{
public:
	CBrawl_Stars_Monster();
	virtual ~CBrawl_Stars_Monster();

public:
	virtual void Initialize(void) override;
	virtual const int  Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;


private:
	INFO		m_tInfo_Body_Local[4];
	INFO		m_tInfo_Body_World[4];

	float		m_fAngle_Body;

	std::list<CObj*>*	m_pBullet;

};

