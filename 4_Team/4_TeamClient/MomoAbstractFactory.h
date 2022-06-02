#pragma once
#include "Momo_Obj.h"

template<typename T>
class CMomoAbstractFactory
{
public:
	CMomoAbstractFactory(){}
	~CMomoAbstractFactory(){}

public:
	static CMomo_Obj*	Create(void)
	{
		CMomo_Obj*	pObj = new T;
		pObj->Initialize();

		return pObj;
	}

	static CMomo_Obj*	Create(float _fX, float _fY)
	{
		CMomo_Obj*	pObj = new T;

		pObj->Initialize();
		pObj->Set_Pos(_fX, _fY);

		return pObj;
	}

	static CMomo_Obj*	Create(float _fX, float _fY, float _fAngle)
	{
		CMomo_Obj*	pObj = new T;

		pObj->Initialize();
		pObj->Set_Pos(_fX, _fY);
		pObj->Set_Angle(_fAngle);

		return pObj;
	}
};

