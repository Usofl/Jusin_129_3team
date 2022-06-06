#pragma once
#include "Momo_Obj.h"
#include "MomoSword.h"
#include "Follower_Monster.h"

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

	static CMonster*	Create_Follower(void)
	{
		CMonster*	pObj = new CFollower_Monster;

		return pObj;
	}
};

