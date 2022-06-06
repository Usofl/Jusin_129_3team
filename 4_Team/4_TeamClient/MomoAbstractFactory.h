#pragma once
#include "Momo_Obj.h"
#include "MomoSword.h"
#include "MomoBullet.h"

class CMomodoraPlayer;

class CMomoAbstractFactory
{
public:
	CMomoAbstractFactory(){}
	~CMomoAbstractFactory(){}

public:
	static CMomoSword*	Create_Momo_Sword(void)
	{
		CMomoSword*	pObj = new CMomoSword;

		return pObj;
	}

	static CMomoBullet*	Create_Momo_Bullet(void)
	{
		CMomoBullet*	pObj = new CMomoBullet;

		return pObj;
	}
};

