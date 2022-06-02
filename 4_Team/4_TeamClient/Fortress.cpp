#include "stdafx.h"
#include "Fortress.h"


CFortress::CFortress()
	: JunPlayer(nullptr)
{
}

CFortress::~CFortress()
{
	Release();
}

void CFortress::Initialize(void)
{
	if (nullptr == JunPlayer)
	{
		JunPlayer = new CJunPlayer;
		
	}
	BulletList = *(JunPlayer->Get_BulletList());
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
	for (auto& iter : BulletList)
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
	Safe_Delete<CJunPlayer*>(JunPlayer);
}

void CFortress::Key_Input(void)
{
}
