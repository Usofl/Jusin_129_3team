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
	//int iArray[4] = { 0,0,50,50 };
	m_tInfo.vPos = { 0.f,0.f,0.f };
	m_tInfo.vDir = { 1.f,0.f,0.f };
}

const int CJunPlayer::Update(void)
{

	if (iArray[0] < 500)
	{
		for (int i = 0; i < 4; ++i)
			iArray[i] += 3;
	}

}

void CJunPlayer::Late_Update(void)
{

}

void CJunPlayer::Render(HDC hDC)
{
	Ellipse(hDC, iArray[0], iArray[1], iArray[2], iArray[3]);
}

void CJunPlayer::Release(void)
{

}

void CJunPlayer::Key_Input(void)
{

}

void CJunPlayer::Key_Input(void)
{
}
