#include "stdafx.h"
#include "JunPlayer.h"


CJunPlayer::CJunPlayer()
{
}


CJunPlayer::~CJunPlayer()
{
}

void CJunPlayer::Initialize(void)
{
	m_tInfo.vPos = { 0.f,0.f,0.f };
	m_tInfo.vDir = { 1.f,0.f,0.f };

}

void CJunPlayer::Update(void)
{
}

void CJunPlayer::Late_Update(void)
{
}

void CJunPlayer::Render(HDC hDC)
{
	Rectangle(hDC, 50, 50, 200, 250);
}

void CJunPlayer::Release(void)
{
}

void CJunPlayer::Key_Input(void)
{
}
