#include "stdafx.h"
#include "Brawl_Stars_Player.h"


CBrawl_Stars_Player::CBrawl_Stars_Player()
	:m_fSpeed(3.f)
{
}


CBrawl_Stars_Player::~CBrawl_Stars_Player()
{
	Release();
}

void CBrawl_Stars_Player::Initialize(void)
{
	m_tInfo.vPos = { 400.f, 300.f, 0.f };
	m_tInfo.vDir = { 1.f, 0.f, 0.f };

	// ���� �ٵ� 
	m_tInfo_Body_Local[0].vPos = { -50.f , -30.f , 0.f };
	m_tInfo_Body_Local[1].vPos = { +50.f , -30.f , 0.f };
	m_tInfo_Body_Local[2].vPos = { +50.f , +30.f , 0.f };
	m_tInfo_Body_Local[3].vPos = { -50.f , +30.f , 0.f };

	// ���� ����
	m_tInfo_Posin_Local[0].vPos = { 0.f , 0.f, 0.f };
	// ���� ����
	m_tInfo_Posin_Local[1].vPos = { 100.f , 0.f, 0.f };

	m_fAngle = 0.f;
	m_fAngle_Body = 0.f;
	m_fAngle_Posin = 0.f;

}

const int CBrawl_Stars_Player::Update(void)
{
	//Key_Input();

	/*D3DXMatrixRotationZ(&m_tMatInfo.matRotZ, D3DXToRadian(m_fAngle));

	m_tInfo.matWorld = m_tMatInfo.matRotZ;

	D3DXVec3TransformNormal(&m_tInfo.vDir, &m_tInfo.vDir, &m_tInfo.matWorld);

	m_fAngle_Body += m_fAngle;

	for (int i = 0; i < 4; ++i)
	{
		// �̵���� ���� ������ ����x , y == 400 , 300 , �׸��� matTrans�� ���� == ��ġ��
		D3DXMatrixTranslation(&m_tMatInfo.matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);

		// Z �߽������� ���Ե� �ޱ۹ٵ��� RotZ �� ���� == ����, �ޱ� ��
		D3DXMatrixRotationZ(&m_tMatInfo.matRotZ, D3DXToRadian(m_fAngle_Body));

		// ���� ��ȯ�� ���� ��Ŀ� matRotZ �� matTrans �����Ŀ� ���Ѵ�.
		m_tInfo.matWorld = m_tMatInfo.matRotZ * m_tMatInfo.matTrans;

		// �������� ��ġ���͸� ��ȯ ���ش� (���� ��ȯ�� ���� ��Ŀ� ����Ÿ�� �ٵ� ������ ������ ���ϱ⸦ ���Ŀ� �ٵ� ������ ������ ���� )
		D3DXVec3TransformCoord(&m_tInfo_Body_World[i].vPos, &m_tInfo_Body_Local[i].vPos, &m_tInfo.matWorld);
	}

	for (int i = 0; i < 2; ++i)
	{
		// ������ ���� x , y ���� �̵���Ŀ� ����
		D3DXMatrixTranslation(&m_tMatInfo.matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);

		// ������ �ޱ۰� , ��ü�� �ޱ۰��� ���� ���� matRotZ �� ����
		D3DXMatrixRotationZ(&m_tMatInfo.matRotZ, D3DXToRadian(m_fAngle_Body + m_fAngle_Posin));

		// ���� ��ȯ�� ���� ��Ŀ� matRoz(�ޱ� ��) * matTrans(�̵����== ��ġ)
		m_tInfo.matWorld = m_tMatInfo.matRotZ * m_tMatInfo.matTrans;

		// �������� ��ġ ���͸� ��ȯ ���ش� ( ���� ��ȯ�� ���� ��Ŀ� �������� ������ �����Ŀ� ���ſ��忡 ����
		D3DXVec3TransformCoord(&m_tInfo_Posin_World[i].vPos, &m_tInfo_Posin_Local[i].vPos, &m_tInfo.matWorld);
	}



	// �ޱ۰��� 0���� �ʱ�ȭ�� �� ��Ű�� ��� ȸ����
	m_fAngle = 0.f;*/
	return 0;
}

void CBrawl_Stars_Player::Late_Update(void)
{
}

void CBrawl_Stars_Player::Render(HDC hDC)
{
	MoveToEx(hDC, m_tInfo_Body_World[0].vPos.x, m_tInfo_Body_World[0].vPos.y, nullptr);
	for (int i = 0; i < 4; ++i)
	{
		LineTo(hDC, m_tInfo_Body_World[i].vPos.x, m_tInfo_Body_World[i].vPos.y);
	}
	LineTo(hDC, m_tInfo_Body_World[0].vPos.x, m_tInfo_Body_World[0].vPos.y);

	// �������� ��
	Ellipse(hDC, m_tInfo.vPos.x - 25, m_tInfo.vPos.y - 25, m_tInfo.vPos.x + 25, m_tInfo.vPos.y + 25);

	// ����θ� ��Ÿ���� ���׸��� �� 2��
	Ellipse(hDC, m_tInfo_Body_World[1].vPos.x - 5, m_tInfo_Body_World[1].vPos.y - 5, m_tInfo_Body_World[1].vPos.x + 5, m_tInfo_Body_World[1].vPos.y + 5);
	Ellipse(hDC, m_tInfo_Body_World[2].vPos.x - 5, m_tInfo_Body_World[2].vPos.y - 5, m_tInfo_Body_World[2].vPos.x + 5, m_tInfo_Body_World[2].vPos.y + 5);

	// ����
	MoveToEx(hDC, m_tInfo_Posin_World[0].vPos.x, m_tInfo_Posin_World[0].vPos.y, nullptr);
	LineTo(hDC, m_tInfo_Posin_World[1].vPos.x, m_tInfo_Posin_World[1].vPos.y);
}

void CBrawl_Stars_Player::Release(void)
{
}

void CBrawl_Stars_Player::Shoot_Bullet(void)
{
}

void CBrawl_Stars_Player::Key_Input(void)
{
	if (GetAsyncKeyState(VK_LEFT))
	{
		m_fAngle -= 5.f;
	}

	if (GetAsyncKeyState(VK_RIGHT))
	{
		m_fAngle += 5.f;
	}

	if (GetAsyncKeyState(VK_UP))
	{
		m_tInfo.vPos += m_tInfo.vDir;
	}

	if (GetAsyncKeyState(VK_DOWN))
	{
		m_tInfo.vPos -= m_tInfo.vDir;
	}
	if (GetAsyncKeyState(VK_SHIFT))
	{
		m_tInfo.vPos += m_tInfo.vDir * m_fSpeed;
	}
	if (GetAsyncKeyState('Z'))
	{
		m_fAngle_Posin += 5.f;
	}
	if (GetAsyncKeyState('C'))
	{
		m_fAngle_Posin -= 5.f;
	}

}
