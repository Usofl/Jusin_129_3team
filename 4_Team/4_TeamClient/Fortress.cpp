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
	
	LINEMGR->Create_Line(0, 600, 150, 580);
	LINEMGR->Create_Line(150, 580, 300, 550);
	LINEMGR->Create_Line(300, 550, 330, 530);
	LINEMGR->Create_Line(330, 530, 350, 510);
	LINEMGR->Create_Line(350, 510, 370, 500);
	LINEMGR->Create_Line(370, 500, 500, 490);
	LINEMGR->Create_Line(500, 490,800,450);
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

	//UI ����
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

