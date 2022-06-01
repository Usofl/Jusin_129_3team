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

	// 로컬 바디 
	m_tInfo_Body_Local[0].vPos = { -50.f , -30.f , 0.f };
	m_tInfo_Body_Local[1].vPos = { +50.f , -30.f , 0.f };
	m_tInfo_Body_Local[2].vPos = { +50.f , +30.f , 0.f };
	m_tInfo_Body_Local[3].vPos = { -50.f , +30.f , 0.f };

	// 로컬 포신
	m_tInfo_Posin_Local[0].vPos = { 0.f , 0.f, 0.f };
	// 월드 포신
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
		// 이동행렬 생성 인포의 포스x , y == 400 , 300 , 그리고 matTrans에 대입 == 위치값
		D3DXMatrixTranslation(&m_tMatInfo.matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);

		// Z 중심축으로 대입된 앵글바디값을 RotZ 에 대입 == 방향, 앵글 값
		D3DXMatrixRotationZ(&m_tMatInfo.matRotZ, D3DXToRadian(m_fAngle_Body));

		// 월드 변환을 위한 행렬에 matRotZ 와 matTrans 곱한후에 더한다.
		m_tInfo.matWorld = m_tMatInfo.matRotZ * m_tMatInfo.matTrans;

		// 최종적인 위치벡터를 반환 해준다 (월드 변환을 위한 행렬에 인포타입 바디 로컬의 포스를 곱하기를 한후에 바디 월드의 포스에 대입 )
		D3DXVec3TransformCoord(&m_tInfo_Body_World[i].vPos, &m_tInfo_Body_Local[i].vPos, &m_tInfo.matWorld);
	}

	for (int i = 0; i < 2; ++i)
	{
		// 인포의 포스 x , y 값을 이동행렬에 대입
		D3DXMatrixTranslation(&m_tMatInfo.matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);

		// 포신의 앵글값 , 몸체의 앵글값을 더한 값을 matRotZ 에 대입
		D3DXMatrixRotationZ(&m_tMatInfo.matRotZ, D3DXToRadian(m_fAngle_Body + m_fAngle_Posin));

		// 월드 변환을 위한 행렬에 matRoz(앵글 값) * matTrans(이동행렬== 위치)
		m_tInfo.matWorld = m_tMatInfo.matRotZ * m_tMatInfo.matTrans;

		// 최종적인 위치 벡터를 반환 해준다 ( 월드 변환을 위한 행렬에 인포포신 로컬을 곱한후에 포신월드에 대입
		D3DXVec3TransformCoord(&m_tInfo_Posin_World[i].vPos, &m_tInfo_Posin_Local[i].vPos, &m_tInfo.matWorld);
	}



	// 앵글값을 0으로 초기화를 안 시키면 계속 회전함
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

	// 인포값의 원
	Ellipse(hDC, m_tInfo.vPos.x - 25, m_tInfo.vPos.y - 25, m_tInfo.vPos.x + 25, m_tInfo.vPos.y + 25);

	// 전면부를 나타내는 조그마한 점 2개
	Ellipse(hDC, m_tInfo_Body_World[1].vPos.x - 5, m_tInfo_Body_World[1].vPos.y - 5, m_tInfo_Body_World[1].vPos.x + 5, m_tInfo_Body_World[1].vPos.y + 5);
	Ellipse(hDC, m_tInfo_Body_World[2].vPos.x - 5, m_tInfo_Body_World[2].vPos.y - 5, m_tInfo_Body_World[2].vPos.x + 5, m_tInfo_Body_World[2].vPos.y + 5);

	// 포신
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
