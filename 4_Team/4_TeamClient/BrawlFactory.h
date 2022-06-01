#pragma once
#include "Brawl_Stars_Player.h"
#include "Brawl_Stars_Bullet.h"

class CBrawlFactory
{
public:

	CBrawlFactory()
	{
	}

	~CBrawlFactory()
	{
	}

public:
	static	CObj*	Create_Brawl_Player()
	{
		CObj* pBrawl_Player = new CBrawl_Stars_Player;
		pBrawl_Player->Initialize();

		return pBrawl_Player;
	}
	static	CObj*	Create_Brawl_Bullet(float _fX, float _fY, float _fAngle)
	{
		CBrawl_Stars_Bullet* pBrawl_Bullet = new CBrawl_Stars_Bullet;
		pBrawl_Bullet->Initialize();
		pBrawl_Bullet->Set_Pos(_fX, _fY);
		pBrawl_Bullet->Set_Angle(_fAngle);

		return pBrawl_Bullet;
	}
};

