#pragma once

#include "Fortress_Monster.h"
#include "Fortress_Monster_Bullet.h"

class CFortressFactory
{
public:

	CFortressFactory()
	{
	}

	~CFortressFactory()
	{
	}

public:
	static	CObj*	Create_Fortress_Monster()
	{
		CObj*	pFortress_Monster = new CFortress_Monster;
		pFortress_Monster->Initialize();

		return pFortress_Monster;
	}

	static	CObj*	Create_Fortress_Bullet(float _fX, float _fY, float _fAngle)
	{
		CFortress_Monster_Bullet*	pFortress_Bullet = new CFortress_Monster_Bullet;
		pFortress_Bullet->Initialize();
		pFortress_Bullet->Set_Pos(_fX, _fY);
		pFortress_Bullet->Set_Angle(_fAngle);

		return pFortress_Bullet;
	}
};

