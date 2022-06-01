#include "stdafx.h"
#include "Fortress.h"


CFortress::CFortress()
{
}


CFortress::~CFortress()
{
}

void CFortress::Initialize(void)
{
	JunPlayer = new CJunPlayer;
	JunPlayer->Initialize();
	//RenderList.
}

void CFortress::Update(void)
{
	JunPlayer->Update();
}

void CFortress::Late_Update(void)
{
	JunPlayer->Late_Update();

}

void CFortress::Render(HDC _hDC)
{
	for (auto& iter : RenderList)
	{
		iter->Render(_hDC);
	}
	JunPlayer->Render(_hDC);
	//RenderList
	/*Ellipse(_hDC, 50, 50, 200, 200);
	Ellipse(_hDC, 200, 200, 500, 500);*/
}

void CFortress::Release(void)
{
	JunPlayer->Release();
}

void CFortress::Key_Input(void)
{
}
