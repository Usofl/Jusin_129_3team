#include "stdafx.h"
#include "FlashmanPlayer.h"


CFlashmanPlayer::CFlashmanPlayer()
	: m_bAir(false)
	, m_fSize(0.f)
	, m_fScale(1.f)
	, m_fJumpPower(0.f)
	, m_fJumpTime(0.f)
	, m_ePreState(END)
	, m_eCurState(IDLE)
{
	m_eRender = RENDER_GAMEOBJECT;
}


CFlashmanPlayer::~CFlashmanPlayer()
{
}

void CFlashmanPlayer::Fallen(void)
{
	if (m_vDrawPoint[POINT_LEFT_FOOT].y >= (WINCY - 100))
	{
		m_fJumpTime = 0.f;
		if (m_eCurState != CHANGE || m_tInfo.vPos.x <= 0 || m_tInfo.vPos.x >= WINCX)
		{
			m_eCurState = IDLE;
		}
		m_tInfo.vPos.y = (WINCY - 100) - m_vPoint[POINT_LEFT_FOOT].y;
		m_bAir = false;

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

		return;
	}
	else
	{
		m_fJumpTime += 0.1f;
		m_tInfo.vPos.y += (0.5f * 3.8f * (m_fJumpTime * m_fJumpTime));
		m_bAir = true;
		
		return;
	}
}

void CFlashmanPlayer::Jumping(void)
{
	m_fJumpTime += 0.1f;
	m_tInfo.vPos.y -= m_fJumpPower * m_fJumpTime * sinf(m_fJumpAngle);
}

void CFlashmanPlayer::Change(void)
{
	if (m_tInfo.vPos.x >= WINCX * 0.5)
	{
		m_fScale = 1.f;
		m_tInfo.vPos += m_tInfo.vDir * m_fSpeed;
	}
	else
	{
		m_fScale = -1.f;
		m_tInfo.vPos -= m_tInfo.vDir * m_fSpeed;
	}
}

void CFlashmanPlayer::ChangeJumping(void)
{
	if (m_tInfo.vPos.x >= WINCX - 100)
	{
		Jumping();
	}

	if (m_tInfo.vPos.x <= 100)
	{
		Jumping();
	}
}
