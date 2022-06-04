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
	if (nullptr != FortressMonster)
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
	RENDERMGR->Add_Render_Obj(JunPlayer);

	if (nullptr != FortressMonster)
	{
		FortressMonster->Late_Update();
	}

	float fMonsterX2 = 0, fMonsterY2 = 0;
	if (nullptr != FortressMonster)
	{
		D3DXVECTOR3 vMonster = FortressMonster->Get_Info().vPos;
		fMonsterX2 = vMonster.x;
		fMonsterY2 = vMonster.y;
	}
	
	//임시 총알 - 몬스터 충돌처리(몬스터 1마리 기준이라 추후 수정 필요)
	if (fMonsterX2 != 0 && fMonsterY2 != 0)
	{
		for (auto iter = JunBulletList.begin(); iter != JunBulletList.end();)
		{
			(*iter)->Late_Update();

			if (MonsterCollision_Check(fMonsterX2, fMonsterY2, (*iter)->Get_Info().vPos.x, (*iter)->Get_Info().vPos.y))
			{
				Safe_Delete(*iter);
				(iter) = JunBulletList.erase((iter));
				Safe_Delete<CFortress_Monster*>(FortressMonster);
			}
			else
			{
				iter++;
			}
		}
	}

	//총알 충돌 했으면 몬스터가 없을테니 렌더를 안하게 해서 오류 없애기
	if (nullptr != FortressMonster)
	{
		RENDERMGR->Add_Render_Obj(FortressMonster);
	}

	for (auto iter = JunBulletList.begin(); iter != JunBulletList.end();)
	{
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
	}

	

	for (auto iter = Monster_Bullet_List.begin(); iter != Monster_Bullet_List.end();)
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
			(iter) = Monster_Bullet_List.erase((iter));
		}
		else
		{
			RENDERMGR->Add_Render_Obj(*iter);
			iter++;
		}
		//iter->Set_Pos(1000.f, 1000.f);
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

	if (nullptr == FortressMonster)
	{
		return;
	}

	float fMonsterX = FortressMonster->Get_Info().vPos.x;
	float fMonsterY = FortressMonster->Get_Info().vPos.y;

	if (LINEMGR->Collision_Line(fMonsterX, &fMonsterY))
	{
		float fSour = LINEMGR->Collision_Monster_Line(fMonsterX, &fMonsterY);
		FortressMonster->Set_Angle(fSour);
		FortressMonster->Set_Pos(fMonsterX, fMonsterY - 20);
	}

	
}

void CFortress::Render(HDC _hDC)
{
	RENDERMGR->Render(_hDC);

	LINEMGR->Render(_hDC);

	//UI 예정
	RECT rc1 = { -100, 0, WINCX, 110 };
	RECT rc2 = { -100, WINCY - 110, WINCX, WINCY };

	InvertRect(_hDC, &rc1);
	InvertRect(_hDC, &rc2);
	/*const TCHAR *str2 = TEXT("45%d");
	int i = 45;*/
	//TextOut(_hDC, 100, 100, i"%d", _tcslen(str2));
	//CString::Format()
	
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

const bool CFortress::MonsterCollision_Check(float _fMonsterX, float _fMonsterY, float _fBulletX, float _fBulletY)
{
	if ((_fMonsterX - 50 <= _fBulletX &&
		_fMonsterX + 50 >= _fBulletX) &&
		(_fMonsterY - 30 <= _fBulletY &&
			_fMonsterY + 30 >= _fBulletY))
	{
		return true;
	}

	return false;
}

