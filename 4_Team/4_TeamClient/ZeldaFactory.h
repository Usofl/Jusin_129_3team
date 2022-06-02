#pragma once
#include "Zelda_Button.h"
#include "Zelda_Stone.h"
#include "Zelda_Wall.h"

class CZeldaFactory
{
public:

	CZeldaFactory()
	{
	}

	~CZeldaFactory()
	{
	}

public:
	static	CZelda_Wall*	Create_Zelda_Wall(const float& _fX, const float& _fY, const float& _fCX, const float& _fCY)
	{
		CZelda_Wall* pZelda_Wall = new CZelda_Wall(_fX, _fY, _fCX, _fCY);

		return pZelda_Wall;
	}

	static	CZelda_Button*	Create_Zelda_Button(const float& _fX, const float& _fY, const float& _fCX, const float& _fCY)
	{
		CZelda_Button* pZelda_Button = new CZelda_Button(_fX, _fY, _fCX, _fCY);

		return pZelda_Button;
	}

	static	CZelda_Stone*	Create_Zelda_Stone(const float& _fX, const float& _fY, const float& _fCX, const float& _fCY)
	{
		CZelda_Stone* pZelda_Stone = new CZelda_Stone(_fX, _fY, _fCX, _fCY);

		return pZelda_Stone;
	}
};

