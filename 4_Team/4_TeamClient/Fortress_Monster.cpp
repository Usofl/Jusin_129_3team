#include "stdafx.h"
#include "Fortress_Monster.h"
#include "FortressFactory.h"
#include "ScrollMgr.h"
#include "SceneMgr.h"


CFortress_Monster::CFortress_Monster()
	:m_bRandom(true),
	m_bShoot(true),
	m_bMonster_Turn(true), 
	m_fSpeed(5.f), m_fRandom(0),
	m_dwShootCount(GetTickCount()),
	m_dwShootDelay(GetTickCount())
	, Fortress_Monster_Bullet(nullptr)
{
}


CFortress_Monster::~CFortress_Monster()
{
	Release();
}

void CFortress_Monster::Initialize(void)
{
	m_eRender = RENDER_GAMEOBJECT;

	srand(unsigned(time(NULL)));

	m_tInfo.vPos = { 600.f , 400.f , 0.f };
	m_tInfo.vDir = { 1.f, 0.f, 0.f };

	m_tInfo_Body_Local[0].vPos = { -50.f , -30.f , 0.f };
	m_tInfo_Body_Local[1].vPos = { +50.f , -30.f , 0.f };
	m_tInfo_Body_Local[2].vPos = { +50.f , +30.f , 0.f };
	m_tInfo_Body_Local[3].vPos = { -50.f , +30.f , 0.f };


	m_tInfo_Posin_Local[0].vPos = { 0.f , 0.f, 0.f };
	m_tInfo_Posin_Local[1].vPos = { -50.f , 0.f, 0.f };

	m_fAngle = 0.f;
	m_fAngle_Body = 0.f;
	m_fAngle_Posin = 0.f;


}

const int CFortress_Monster::Update(void)
{
	D3DXMatrixRotationZ(&m_tMatInfo.matRotZ, D3DXToRadian(m_fAngle));

	m_tInfo.matWorld = m_tMatInfo.matRotZ;

	D3DXVec3TransformNormal(&m_tInfo.vDir, &m_tInfo.vDir, &m_tInfo.matWorld);


	// �̵���� ���� ������ ����x , y == 400 , 300 , �׸��� matTrans�� ���� == ��ġ��
	D3DXMatrixTranslation(&m_tMatInfo.matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);

	// Z �߽������� ���Ե� �ޱ۹ٵ��� RotZ �� ���� == ����, �ޱ� ��
	D3DXMatrixRotationZ(&m_tMatInfo.matRotZ, D3DXToRadian(m_fAngle_Body));

	// ���� ��ȯ�� ���� ��Ŀ� matRotZ �� matTrans �����Ŀ� ���Ѵ�.
	m_tInfo.matWorld = m_tMatInfo.matRotZ * m_tMatInfo.matTrans;

	for (int i = 0; i < 4; ++i)
	{
		// �������� ��ġ���͸� ��ȯ ���ش� (���� ��ȯ�� ���� ��Ŀ� ����Ÿ�� �ٵ� ������ ������ ���ϱ⸦ ���Ŀ� �ٵ� ������ ������ ���� )
		D3DXVec3TransformCoord(&m_tInfo_Body_World[i].vPos, &m_tInfo_Body_Local[i].vPos, &m_tInfo.matWorld);
	}

	// ������ �ޱ۰� , ��ü�� �ޱ۰��� ���� ���� matRotZ �� ����
	D3DXMatrixRotationZ(&m_tMatInfo.matRotZ, D3DXToRadian(m_fAngle_Body + m_fAngle_Posin));

	// ���� ��ȯ�� ���� ��Ŀ� matRoz(�ޱ� ��) * matTrans(�̵����== ��ġ)
	m_PosinWorld = m_tMatInfo.matRotZ * m_tMatInfo.matTrans;

	for (int i = 0; i < 2; ++i)
	{
		// �������� ��ġ ���͸� ��ȯ ���ش� ( ���� ��ȯ�� ���� ��Ŀ� �������� ������ �����Ŀ� ���ſ��忡 ����
		D3DXVec3TransformCoord(&m_tInfo_Posin_World[i].vPos, &m_tInfo_Posin_Local[i].vPos, &m_PosinWorld);
	}

	Shoot_Bullet();

	// �ޱ۰��� 0���� �ʱ�ȭ�� �� ��Ű�� ��� ȸ����
	m_fAngle = 0.f;

	return 0;
}

void CFortress_Monster::Late_Update(void)
{
	
}

void CFortress_Monster::Render(HDC hDC)
{
	int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int	iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	MoveToEx(hDC, (int)m_tInfo_Body_World[0].vPos.x + iScrollX, (int)m_tInfo_Body_World[0].vPos.y + iScrollY, nullptr);
	for (int i = 0; i < 4; ++i)
	{
		LineTo(hDC, (int)m_tInfo_Body_World[i].vPos.x + iScrollX, (int)m_tInfo_Body_World[i].vPos.y + iScrollY);
	}
	LineTo(hDC, (int)m_tInfo_Body_World[0].vPos.x + iScrollX, (int)m_tInfo_Body_World[0].vPos.y + iScrollY);

	// �������� ��
	//Ellipse(hDC, (int)m_tInfo.vPos.x - 55, (int)m_tInfo.vPos.y - 15, (int)m_tInfo.vPos.x + 5, (int)m_tInfo.vPos.y + 45);
	//Ellipse(hDC, (int)m_tInfo.vPos.x + 25, (int)m_tInfo.vPos.y + 25, (int)m_tInfo.vPos.x + 45, (int)m_tInfo.vPos.y + 45);

	// ����θ� ��Ÿ���� ���׸��� �� 2��
	Ellipse(hDC, (int)m_tInfo_Body_World[0].vPos.x - 5 + iScrollX, (int)m_tInfo_Body_World[0].vPos.y - 5 + iScrollY, (int)m_tInfo_Body_World[0].vPos.x + 5 + iScrollX, (int)m_tInfo_Body_World[0].vPos.y + 5 + iScrollY);
	

	// ����
	MoveToEx(hDC, (int)m_tInfo_Posin_World[0].vPos.x + iScrollX, (int)m_tInfo_Posin_World[0].vPos.y + iScrollY, nullptr);
	LineTo(hDC, (int)m_tInfo_Posin_World[1].vPos.x + iScrollX, (int)m_tInfo_Posin_World[1].vPos.y + iScrollY);
}

void CFortress_Monster::Release(void)
{
}

void CFortress_Monster::Shoot_Bullet()
{
	/*if (m_dwCount + 500 < GetTickCount())
	{
		m_iRandom = rand() % 360;
		m_fAngle_Posin = m_iRandom;
		m_pMonster_Bullet->push_back(CFortressFactory::Create_Fortress_Bullet(m_tInfo_Posin_World[1].vPos.x, m_tInfo_Posin_World[1].vPos.y, m_fAngle_Posin));

		m_dwCount = GetTickCount();
	}*/

	/*if (m_dwShootCount + 1000 < GetTickCount())
	{
		m_fRandom = (float)(rand() % 90);
		Fortress_Monster_Bullet = new CFortress_Monster_Bullet;
		Fortress_Monster_Bullet->Initialize();
		if (m_fAngle_Posin < m_fRandom)
		{
			++m_fAngle_Posin;
		}
		else if (m_fAngle > m_fRandom)
		{
			--m_fAngle_Posin;
		}
	
		if (m_dwShootDelay + 5000 < GetTickCount())
		{
			Fortress_Monster_Bullet->Set_Angle(m_fAngle_Posin + m_fAngle_Body);
			Fortress_Monster_Bullet->Set_Pos(m_tInfo_Posin_World[1].vPos.x, m_tInfo_Posin_World[1].vPos.y);
			static_cast<CFortress*>(SCENEMGR->Get_Scene(SC_FORTRESS))->Get_Monster_Bullet_List()->push_back(Fortress_Monster_Bullet);

			m_dwShootDelay = GetTickCount();
		}
		else
		{
			Safe_Delete<CFortress_Monster_Bullet*>(Fortress_Monster_Bullet);
		}


		m_dwShootCount = GetTickCount();
	}*/
	if (m_bMonster_Turn == true)
	{
		if (m_bRandom == true)
		{
			m_fRandom = (float)(rand() % 91) + 1;
			m_bRandom = false;

		}
		if (m_fAngle_Posin <= m_fRandom)
		{
			++m_fAngle_Posin;
			if (m_fAngle_Posin >= m_fRandom)
			{
				m_fAngle_Posin = m_fRandom;
				if (m_fAngle_Posin == m_fRandom)
				{
					Fortress_Monster_Bullet = new CFortress_Monster_Bullet;
					Fortress_Monster_Bullet->Initialize();
					Fortress_Monster_Bullet->Set_Angle(m_fAngle_Posin);
					Fortress_Monster_Bullet->Set_Pos(m_tInfo_Posin_World[1].vPos.x, m_tInfo_Posin_World[1].vPos.y);
					static_cast<CFortress*>(SCENEMGR->Get_Scene(SC_FORTRESS))->Get_Monster_Bullet_List()->push_back(Fortress_Monster_Bullet);
					m_bRandom = true;
				}
			}
		}
		else if (m_fAngle_Posin >= m_fRandom)
		{
			--m_fAngle_Posin;
			if (m_fAngle_Posin <= m_fRandom)
			{
				m_fAngle_Posin = m_fRandom;
				if (m_fAngle_Posin == m_fRandom)
				{
					Fortress_Monster_Bullet = new CFortress_Monster_Bullet;
					Fortress_Monster_Bullet->Initialize();
					Fortress_Monster_Bullet->Set_Angle(m_fAngle_Posin);
					Fortress_Monster_Bullet->Set_Pos(m_tInfo_Posin_World[1].vPos.x, m_tInfo_Posin_World[1].vPos.y);
					static_cast<CFortress*>(SCENEMGR->Get_Scene(SC_FORTRESS))->Get_Monster_Bullet_List()->push_back(Fortress_Monster_Bullet);
					m_bRandom = true;
				}
			}
		}
		//m_bMonster_Turn = false;

	}
}
// �������� �ް� rnad ���� ���Ű����� ������ ++���Ű��� �������� ���߰�, �Ѿ� ���-> �ٸ� �������� ������ ���Ű����� ������ �������� �������� �Ѿ� ���
