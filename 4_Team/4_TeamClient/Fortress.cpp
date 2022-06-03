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

	if (nullptr == FortressMonster)
	{
		FortressMonster = new CFortress_Monster;
		FortressMonster->Initialize();

	}
	Monster_Bullet_List = (FortressMonster->Get_BulletList());
	m_Line.tLPoint = { 0.f,0.f };
	m_Line.tRPoint = { 300.f,0.f };
	
	LINEMGR->Create_Line(0, 300, 100, 310);
	LINEMGR->Create_Line(100, 310, 120, 320);
	LINEMGR->Create_Line(120, 320, 140, 350);
	LINEMGR->Create_Line(140, 350, 200, 500);
	LINEMGR->Create_Line(200, 500, 210, 510);
	LINEMGR->Create_Line(210, 510, 230, 530);
	LINEMGR->Create_Line(230, 530, 250, 540);
	LINEMGR->Create_Line(250, 540, 320, 550);
	LINEMGR->Create_Line(320, 550, 410, 545);
	LINEMGR->Create_Line(410, 545, 460, 540);
	LINEMGR->Create_Line(460, 540, 520, 540);
	LINEMGR->Create_Line(520, 540, 560, 545);
	LINEMGR->Create_Line(560, 545, 650, 540);
	LINEMGR->Create_Line(650, 540, 770, 515);
	LINEMGR->Create_Line(770, 515, 810, 500);
	LINEMGR->Create_Line(810, 500, 900, 480);
	LINEMGR->Create_Line(900, 480, 920, 460);
	LINEMGR->Create_Line(920, 460, 1000, 410);
	LINEMGR->Create_Line(1000, 410, 1100, 405);
}

void CFortress::Update(void)
{
	JunPlayer->Update();
	FortressMonster->Update();
	for (auto& iter : JunBulletList)
	{
		iter->Update();
	}
	for (auto& iter : *Monster_Bullet_List)
	{
		iter->Update();
	}
}

void CFortress::Late_Update(void)
{
	JunPlayer->Late_Update();
	FortressMonster->Late_Update();
	for (auto& iter : JunBulletList)
	{
		iter->Late_Update();
	}
	for (auto& iter : *Monster_Bullet_List)
	{
		iter->Late_Update();
	}
	float fX = JunPlayer->Get_Info().vPos.x;
	float fY = JunPlayer->Get_Info().vPos.y;
	if (LINEMGR->Collision_Line(fX, &fY))
	{
		float fTemp = LINEMGR->Collision_JunLine(fX, &fY);
		JunPlayer->Set_Angle(fTemp);
		JunPlayer->Set_Pos(fX, fY);
		
	}
}

void CFortress::Render(HDC _hDC)
{
	
	FortressMonster->Render(_hDC);
	JunPlayer->Render(_hDC);
	for (auto& iter : JunBulletList)
	{
		iter->Render(_hDC);
	}
	for (auto& iter : *Monster_Bullet_List)
	{
		iter->Render(_hDC);
	}
	LINEMGR->Render(_hDC);

	//UI ¿¹Á¤
	RECT rc1 = { 0, 0, 1024, 110 };
	RECT rc2 = { 0, 658, 1024, 768 };

	InvertRect(_hDC, &rc1);
	InvertRect(_hDC, &rc2);

	//Rectangle(_hDC, 0, 0, 1024, 110);
	//Rectangle(_hDC, 0, 658, 1024, 768);

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
	for (auto iter = JunBulletList.begin(); iter != JunBulletList.end();)
	{
		(*iter)->Release();
		Safe_Delete<CJunBullet*>(*iter);

		iter = JunBulletList.erase(iter);
	}
	for (auto& iter : *Monster_Bullet_List)
	{
		iter->Release();
	}

}

void CFortress::Key_Input(void)
{

}

