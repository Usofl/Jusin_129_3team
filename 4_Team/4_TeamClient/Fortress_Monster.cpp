#include "stdafx.h"
#include "Fortress_Monster.h"
#include "FortressFactory.h"
#include <time.h>


CFortress_Monster::CFortress_Monster()
	:m_fSpeed(5.f), m_fRandom(0), m_dwShootCount(GetTickCount()), m_dwShootDelay(GetTickCount())
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

	m_fAngle_Body += m_fAngle;

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
	MoveToEx(hDC, (int)m_tInfo_Body_World[0].vPos.x, (int)m_tInfo_Body_World[0].vPos.y, nullptr);
	for (int i = 0; i < 4; ++i)
	{
		LineTo(hDC, (int)m_tInfo_Body_World[i].vPos.x, (int)m_tInfo_Body_World[i].vPos.y);
	}
	LineTo(hDC, (int)m_tInfo_Body_World[0].vPos.x, (int)m_tInfo_Body_World[0].vPos.y);

	// �������� ��
	Ellipse(hDC, (int)m_tInfo.vPos.x - 55, (int)m_tInfo.vPos.y - 15, (int)m_tInfo.vPos.x + 5, (int)m_tInfo.vPos.y + 45);
	Ellipse(hDC, (int)m_tInfo.vPos.x + 25, (int)m_tInfo.vPos.y + 25, (int)m_tInfo.vPos.x + 45, (int)m_tInfo.vPos.y + 45);

	// ����θ� ��Ÿ���� ���׸��� �� 2��
	Ellipse(hDC, (int)m_tInfo_Body_World[0].vPos.x - 5, (int)m_tInfo_Body_World[0].vPos.y - 5, (int)m_tInfo_Body_World[0].vPos.x + 5, (int)m_tInfo_Body_World[0].vPos.y + 5);
	

	// ����
	MoveToEx(hDC, (int)m_tInfo_Posin_World[0].vPos.x, (int)m_tInfo_Posin_World[0].vPos.y, nullptr);
	LineTo(hDC, (int)m_tInfo_Posin_World[1].vPos.x, (int)m_tInfo_Posin_World[1].vPos.y);
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

	if (m_dwShootCount + 1000 < GetTickCount())
	{
		m_fRandom = (float)(rand() % 90);
		Fortress_Monster_Bullet = new CFortress_Monster_Bullet;
		Fortress_Monster_Bullet->Initialize();
		m_fAngle_Posin = m_fRandom;

		if (m_dwShootDelay + 1100 < GetTickCount())
		{
			Fortress_Monster_Bullet->Set_Angle(m_fAngle_Posin + m_fAngle_Body);
			Fortress_Monster_Bullet->Set_Pos(m_tInfo_Posin_World[1].vPos.x, m_tInfo_Posin_World[1].vPos.y);
			m_pMonster_Bullet.push_back(Fortress_Monster_Bullet);

			m_dwShootDelay = 0;
		}
		else
		{
			Safe_Delete<CFortress_Monster_Bullet*>(Fortress_Monster_Bullet);
		}


		m_dwShootCount = GetTickCount();
	}

	if (GetAsyncKeyState('Z'))
	{
		m_fAngle_Posin += 1.f;
	}
}
