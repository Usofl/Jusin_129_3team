#include "stdafx.h"
#include "FlashmanBlue.h"
#include "KeyMgr.h"


CFlashmanBlue::CFlashmanBlue()
{
	Initialize();
}

CFlashmanBlue::~CFlashmanBlue()
{
	Release();
}

void CFlashmanBlue::Initialize(void)
{
	m_fSize = 30.f;

	m_tInfo.vPos = { -50.f, 300.f, 0.f };
	m_tInfo.vLook = { 0.f, -1.f, 0.f };

	m_vPoint[POINT_HEAD] = { 0.f, -m_fSize * 1.5f, 0.f };
	m_vPoint[POINT_NECK] = { 0.f, -m_fSize, 0.f };
	m_vPoint[POINT_GROIN] = { 0.f, 0.f, 0.f };

	m_vPoint[POINT_LEFT_KNEE] = { -m_fSize * 0.2f, m_fSize * 0.5f, 0.f };
	m_vPoint[POINT_LEFT_FOOT] = { -m_fSize * 0.2f, m_fSize, 0.f };

	m_vPoint[POINT_RIGHT_KNEE] = { m_fSize * 0.2f, m_fSize * 0.5f, 0.f };
	m_vPoint[POINT_RIGHT_FOOT] = { m_fSize * 0.2f, m_fSize, 0.f };

	m_vPoint[POINT_LEFT_ELBOW] = { -m_fSize * 0.2f, -m_fSize * 0.5f, 0.f };
	m_vPoint[POINT_LEFT_HAND] = { -m_fSize * 0.2f, 0.f, 0.f };

	m_vPoint[POINT_RIGHT_ELBOW] = { m_fSize * 0.2f, -m_fSize * 0.5f, 0.f };
	m_vPoint[POINT_RIGHT_HAND] = { m_fSize * 0.2f, 0.f, 0.f };

	m_fAngle = 0.f;
}

const int CFlashmanBlue::Update(void)
{
	// 연산을 진행

	//m_tInfo.vPos += m_tInfo.vDir;

	Key_Input();

	switch (m_eCurState)
	{
	case CFlashmanPlayer::CHANGE:
		Change();
		ChangeJumping();
		break;
	case CFlashmanPlayer::IDLE:
		break;
	case CFlashmanPlayer::WALK:
		break;
	case CFlashmanPlayer::JUMPING:
		Jumping();
		break;
	case CFlashmanPlayer::ATTACK1:
		break;
	case CFlashmanPlayer::ATTACK2:
		break;
	}

	m_tInfo.vLook = { m_fScale, 0.f, 0.f };
	D3DXMatrixScaling(&m_tMatInfo.matScale, m_fScale, 1.f, 1.f);

	// z축 회전 행렬 생성 함수
	D3DXMatrixRotationZ(&m_tMatInfo.matRotZ, m_fAngle);

	// 이동 행렬 생성 함수
	D3DXMatrixTranslation(&m_tMatInfo.matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);

	Update_Matrix();

	for (int i = POINT_HEAD; i < POINT_END; ++i)
	{
		D3DXVec3TransformCoord(&m_vDrawPoint[i], &m_vPoint[i], &m_tInfo.matWorld);
	}

	D3DXVec3TransformNormal(&m_tInfo.vDir, &m_tInfo.vLook, &m_tInfo.matWorld);

	return OBJ_NOEVENT;
}

void CFlashmanBlue::Late_Update(void)
{
	Fallen();
}

void CFlashmanBlue::Render(HDC _hDC)
{
	HBRUSH MyBrush, OldBrush;
	MyBrush = (HBRUSH)CreateSolidBrush(RGB(0, 0, 255));
	OldBrush = (HBRUSH)SelectObject(_hDC, MyBrush);

	Ellipse(_hDC, (int)(m_vDrawPoint[POINT_HEAD].x - (m_fSize * 0.5f)), (int)(m_vDrawPoint[POINT_HEAD].y - (m_fSize * 0.5f)),
		(int)(m_vDrawPoint[POINT_HEAD].x + (m_fSize * 0.5f)), (int)(m_vDrawPoint[POINT_HEAD].y + (m_fSize * 0.5f)));

	SelectObject(_hDC, OldBrush);
	DeleteObject(MyBrush);

	MoveToEx(_hDC, (int)m_vDrawPoint[POINT_NECK].x, (int)m_vDrawPoint[POINT_NECK].y, nullptr);

	LineTo(_hDC, (int)m_vDrawPoint[POINT_GROIN].x, (int)m_vDrawPoint[POINT_GROIN].y);

	LineTo(_hDC, (int)m_vDrawPoint[POINT_LEFT_KNEE].x, (int)m_vDrawPoint[POINT_LEFT_KNEE].y);
	LineTo(_hDC, (int)m_vDrawPoint[POINT_LEFT_FOOT].x, (int)m_vDrawPoint[POINT_LEFT_FOOT].y);

	MoveToEx(_hDC, (int)m_vDrawPoint[POINT_GROIN].x, (int)m_vDrawPoint[POINT_GROIN].y, nullptr);
	LineTo(_hDC, (int)m_vDrawPoint[POINT_RIGHT_KNEE].x, (int)m_vDrawPoint[POINT_RIGHT_KNEE].y);
	LineTo(_hDC, (int)m_vDrawPoint[POINT_RIGHT_FOOT].x, (int)m_vDrawPoint[POINT_RIGHT_FOOT].y);

	MoveToEx(_hDC, (int)m_vDrawPoint[POINT_NECK].x, (int)m_vDrawPoint[POINT_NECK].y, nullptr);
	LineTo(_hDC, (int)m_vDrawPoint[POINT_LEFT_ELBOW].x, (int)m_vDrawPoint[POINT_LEFT_ELBOW].y);
	LineTo(_hDC, (int)m_vDrawPoint[POINT_LEFT_HAND].x, (int)m_vDrawPoint[POINT_LEFT_HAND].y);

	MoveToEx(_hDC, (int)m_vDrawPoint[POINT_NECK].x, (int)m_vDrawPoint[POINT_NECK].y, nullptr);
	LineTo(_hDC, (int)m_vDrawPoint[POINT_RIGHT_ELBOW].x, (int)m_vDrawPoint[POINT_RIGHT_ELBOW].y);
	LineTo(_hDC, (int)m_vDrawPoint[POINT_RIGHT_HAND].x, (int)m_vDrawPoint[POINT_RIGHT_HAND].y);
}

void CFlashmanBlue::Release(void)
{
}

void CFlashmanBlue::Key_Input(void)
{
	if (KEYMGR->Key_Pressing(VK_LEFT))
	{
		m_fScale = -1.f;
		m_tInfo.vPos -= m_tInfo.vDir * m_fSpeed;
	}

	else if (KEYMGR->Key_Pressing(VK_RIGHT))
	{
		m_fScale = 1.f;
		m_tInfo.vPos += m_tInfo.vDir * m_fSpeed;
	}

	if (KEYMGR->Key_Pressing(VK_SPACE))
	{
		m_eCurState = JUMPING;
	}
}
