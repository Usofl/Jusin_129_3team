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

	BulletList = (JunPlayer->Get_BulletList());
	m_Line.tLPoint = { 0.f,0.f };
	m_Line.tRPoint = { 300.f,0.f };
	
	LINEMGR->Create_Line(0, 500, 200, 500);
	LINEMGR->Create_Line(200, 500, 300, 200);
	LINEMGR->Create_Line(300, 200, 500, 400);
	LINEMGR->Create_Line(500,400,800,200);

}

void CFortress::Update(void)
{
	JunPlayer->Update();
	for (auto& iter : *BulletList)
	{
		iter->Update();
	}
}

void CFortress::Late_Update(void)
{
	JunPlayer->Late_Update();
	for (auto& iter : *BulletList)
	{
		iter->Late_Update();
	}
	float fX = JunPlayer->Get_Info().vPos.x;
	float* fY = JunPlayer->Get_InfoY();
	if (LINEMGR->Collision_Line(fX, fY))
		JunPlayer->Set_Angle(LINEMGR->Collision_JunLine(fX, fY));
}

void CFortress::Render(HDC _hDC)
{
	

	JunPlayer->Render(_hDC);
	for (auto& iter : *BulletList)
	{
		iter->Render(_hDC);
	}
	LINEMGR->Render(_hDC);

	/*for (int i = 0; 6 > i; ++i)
	{
		MoveToEx(_hDC, LineArray[i].tLPoint.fX, LineArray[i].tLPoint.fY, nullptr);
		LineTo(_hDC, LineArray[i+1].tLPoint.fX, LineArray[i + 1].tLPoint.fY);
	}
	*/
	//LineArray[0].Render(_hDC);
	/*MoveToEx(_hDC,., 320, nullptr);
	LineTo(_hDC, 500, 320);*/
	
	
}

void CFortress::Release(void)
{

	Safe_Delete<CJunPlayer*>(JunPlayer);
	for (auto& iter : *BulletList)
	{
		iter->Release();
	}

}

void CFortress::Key_Input(void)
{

}
