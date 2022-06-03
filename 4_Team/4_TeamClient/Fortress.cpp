#include "stdafx.h"
#include "Fortress.h"
#include "RenderMgr.h"
#include "FortressFactory.h"

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
	for (auto& iter : Monster_Bullet_List)
	{
		iter->Update();
	}

	for (auto iter = m_list_Bullet_Effect.begin(); iter != m_list_Bullet_Effect.end();)
	{
		if(OBJ_DEAD == (*iter)->Update())
		{
			Safe_Delete(*iter);
			(iter) = m_list_Bullet_Effect.erase((iter));
		}
		else
		{
			iter++;
		}
	}
}

void CFortress::Late_Update(void)
{
	JunPlayer->Late_Update();
	FortressMonster->Late_Update();

	RENDERMGR->Add_Render_Obj(JunPlayer);
	
	RENDERMGR->Add_Render_Obj(FortressMonster);

	for (auto iter = JunBulletList.begin(); iter != JunBulletList.end();)
	{
		(*iter)->Late_Update();
		//if (FortressMonster->Get_Info().vPos.x < iter->Get_Info().vPos.x)
		float fX = (*iter)->Get_Info().vPos.x;
		float fY = (*iter)->Get_Info().vPos.y;
		if (LINEMGR->Collision_DeLine(fX, fY))
		{
			int num = Random_Num(5, 10);
			for (int i = 0; i < num; ++i)
			{
				m_list_Bullet_Effect.push_back(CFortressFactory::Create_Fortress_Bullet_Effect((*iter)->Get_Info().vPos.x, (*iter)->Get_Info().vPos.y));
			}

			Safe_Delete(*iter);
			(iter) = JunBulletList.erase((iter));
		}
		else
		{
			RENDERMGR->Add_Render_Obj(*iter);
			iter++;
		}
			//iter->Set_Pos(1000.f, 1000.f);
	}

	for (auto& iter : Monster_Bullet_List)
	{
		iter->Late_Update();

		RENDERMGR->Add_Render_Obj(iter);
	}

	for (auto& iter : m_list_Bullet_Effect)
	{
		iter->Late_Update();

		RENDERMGR->Add_Render_Obj(iter);
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
	RENDERMGR->Render(_hDC);

	LINEMGR->Render(_hDC);

	//UI ¿¹Á¤
	RECT rc1 = { -100, 0, WINCX, 110 };
	RECT rc2 = { -100, WINCY - 110, WINCX, WINCY };

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
	
	Safe_Delete<CFortress_Monster*>(FortressMonster);

	for (auto iter = JunBulletList.begin(); iter != JunBulletList.end();)
	{
		(*iter)->Release();
		Safe_Delete<CJunBullet*>(*iter);

		iter = JunBulletList.erase(iter);
	}

	for (auto iter = Monster_Bullet_List.begin(); iter != Monster_Bullet_List.end();)
	{
		(*iter)->Release();
		Safe_Delete<CFortress_Monster_Bullet*>(*iter);

		iter = Monster_Bullet_List.erase(iter);
	}

	for (auto iter = m_list_Bullet_Effect.begin(); iter != m_list_Bullet_Effect.end();)
	{
		(*iter)->Release();
		Safe_Delete<CFortress_Bullet_Effect*>(*iter);

		iter = m_list_Bullet_Effect.erase(iter);
	}

	LINEMGR->Destroy_Instance();
}

void CFortress::Key_Input(void)
{

}

