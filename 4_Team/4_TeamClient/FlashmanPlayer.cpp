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
	if (m_tInfo.vPos.y + m_vPoint[POINT_LEFT_FOOT].y >= (WINCY - 100))
	{
		m_fJumpTime = 0.f;
		if (m_eCurState != CHANGE || m_tInfo.vPos.x <= 0 || m_tInfo.vPos.x >= WINCX)
		{
			m_eCurState = IDLE;
		}
		m_tInfo.vPos.y = (WINCY - 100) - m_vPoint[POINT_LEFT_FOOT].y;
		m_bAir = false;
	}
	else
	{
		m_fJumpTime += 0.1f;
		m_tInfo.vPos.y += (0.5f * 3.8f * (m_fJumpTime * m_fJumpTime));
		m_bAir = true;
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
