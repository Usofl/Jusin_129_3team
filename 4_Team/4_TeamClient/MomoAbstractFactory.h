#pragma once
#include "Momo_Obj.h"
#include "MomoSword.h"

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
};

