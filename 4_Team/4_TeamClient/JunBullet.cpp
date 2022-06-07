#include "stdafx.h"
#include "JunBullet.h"
#include "ScrollMgr.h"
#include "KeyMgr.h"
#include "SceneMgr.h"
#include <ctime>

CJunBullet::CJunBullet():
	m_BulletID(BULLET_END),
	vSu(NORMALVECTOR_X),
	m_vDpDir(NORMALVECTOR_X),
	m_vOne(NORMALVECTOR_X),
	m_bDp_Line(false),
	m_iDestroy_Count(0)
{
	ZeroMemory(m_vLocalPoint, sizeof(m_vLocalPoint));
	ZeroMemory(m_vLocalWind, sizeof(m_vLocalWind));
	ZeroMemory(m_DpINFO_Local, sizeof(m_DpINFO_Local));
	ZeroMemory(m_DpINFO_World, sizeof(m_DpINFO_World));
	
}


CJunBullet::~CJunBullet()
{
	Release();
}

void CJunBullet::Initialize(void)
{
	srand((unsigned)time(NULL));
	
	Local_Initialize(); // 로컬 포인트 초기화가 너무 길어서 밑에 따로 빼놓음
	m_eRender = RENDER_GAMEOBJECT;
	m_tInfo.vDir = NORMALVECTOR_X;

	m_fAngle = 0.f;
	m_fTempTime = 0.f;
	int i = 5;

	for (int i = 0; i < 10; ++i)
	{
		m_DpBullet[i] = nullptr;
	}
	
	m_iDestroy_Count = sizeof(m_vDpPoint) / sizeof(D3DXVECTOR3);
}

const int CJunBullet::Update(void)
{
	if (m_bDead)
	{
		return OBJ_DEAD;
	}
	

	if(m_BulletID == BULLET_DP)
	{
	
	}


	for (int i = 0; sizeof(m_vWorldPoint) / sizeof(D3DXVECTOR3)> i; ++i)
	{
		m_vWorldPoint[i] = m_vLocalPoint[i];
	}

	for (int i = 0; sizeof(m_vWorldWind) / sizeof(D3DXVECTOR3) > i; ++i)
	{
		m_vWorldWind[i] = m_vLocalWind[i];
	}

	D3DXVECTOR3  m_vTemp = m_tInfo.vPos;

	float fTempAngle = m_fAngle;
	m_fTempTime += 0.016f;

	m_fFallValue = m_tInfo.vPos.y;
	Move();

	D3DXVECTOR3  m_vTemp2 = m_tInfo.vPos;

	D3DXVECTOR3 m_vTemp3 = m_vTemp2 - m_vTemp;

	D3DXVec3Normalize(&m_vTemp3, &m_vTemp3);
	
	/*if(D3DXVec3Dot(&m_vTemp3, &vSu) > D3DX_PI)
		m_fAngle = */
	float fSour = 0.f;

	//노력의 결과니까 코드 더러워도 혼내지 않기로 약속~
	if (m_vTemp2.y > m_vTemp.y)
	{
		fSour = D3DXVec3Dot(&m_vTemp3, &vSu);
		D3DXMatrixScaling(&m_matScale, 1.f, 1.f, 0.f);
	}

	else
	{
		fSour = -D3DXVec3Dot(&m_vTemp3, &vSu);
		D3DXMatrixScaling(&m_matScale, -1.f, 1.f, 0.f);
	}

	/*if (-1 > fSour || 1 < fSour)
		fSour *= -1;*/
	m_fAngle = acosf(fSour);
	//m_fAngle = acosf(D3DXVec3Dot(&vSu, &_vOne));
	
	int i = 5;

	//D3DXMatrixScaling(&m_matScale, 1.f, 1.f, 0.f);
	D3DXMatrixRotationZ(&m_matRotZ, m_fAngle);
	D3DXMatrixTranslation(&m_matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);
	m_tInfo.matWorld = m_matScale * m_matRotZ * m_matTrans;

	//D3DXMatrixScaling();

	//D3DXVec3TransformNormal(&m_vDpDir, &m_vDpDir, &m_tInfo.matWorld);

	for (int i = 0; sizeof(m_vWorldPoint)/sizeof(D3DXVECTOR3)  > i; ++i)
	{
		D3DXVec3TransformCoord(&m_vWorldPoint[i], &m_vWorldPoint[i], &m_tInfo.matWorld);
	}

	

	//int iArray[8];
	for (int i = 0; 16 > i; i+= 2)
	{
		int iTemp = (rand() % 65) -62;
		m_vWorldWind[i].x += iTemp;
		m_vWorldWind[i+1].x += iTemp;
	}
	for (int i = 0; sizeof(m_vWorldWind) / sizeof(D3DXVECTOR3)> i; ++i)
	{
		D3DXVec3TransformCoord(&m_vWorldWind[i], &m_vWorldWind[i], &m_tInfo.matWorld);
	}

	//Dp_Test
	/*srand(unsigned(time(NULL)));*/
	
	if (m_BulletID == BULLET_DP)
	{
	//	int iRandom = rand() % 3 + 1;
		
		for (int i = 0; i < (sizeof(m_vDpPoint) / sizeof(D3DXVECTOR3)); ++i)
		{
			
			if (i > 4)
			{
				m_vDpPoint[i].x += (0.13f * m_fSpeed) * m_tInfo.vDir.x * i * 2 * 1.5f;
			}
			else
			{
				m_vDpPoint[i].x -= (0.13f * m_fSpeed)* m_tInfo.vDir.x * i * 1.5f;
			}
			m_vDpPoint[i].y += (0.5f * (9.8f) *((m_fTempTime) * (m_fTempTime)));
		}
	}
	

	return 0;
}

void CJunBullet::Late_Update(void)
{
	if (KEYMGR->Key_Up('F'))
	{

		m_BulletID = BULLET_DP;
		Dp_Local_Initialize();
		//m_tInfo.vPos = { 300.f,300.f,0.f };//D3DXVECTOR3 vTemp = { 0.3f,0.3f,0.f };
	}
}

void CJunBullet::Render(HDC hDC)
{
	//Ellipse(hDC, (int)m_tInfo.vPos.x - 10, (int)m_tInfo.vPos.y - 10, (int)m_tInfo.vPos.x + 10, (int)m_tInfo.vPos.y + 10);
	int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int	iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();
	D3DXVECTOR3 vTemp = m_tInfo.vPos;

	switch (m_BulletID)
	{
		
	case BULLET_BASIC:
		MoveToEx(hDC, (int)m_vWorldPoint[0].x + iScrollX, (int)m_vWorldPoint[0].y + iScrollY, nullptr);
		LineTo(hDC, (int)m_vWorldPoint[1].x + iScrollX, (int)m_vWorldPoint[1].y + iScrollY);
		LineTo(hDC, (int)m_vWorldPoint[2].x + iScrollX, (int)m_vWorldPoint[2].y + iScrollY);
		LineTo(hDC, (int)m_vWorldPoint[3].x + iScrollX, (int)m_vWorldPoint[3].y + iScrollY);
		LineTo(hDC, (int)m_vWorldPoint[4].x + iScrollX, (int)m_vWorldPoint[4].y + iScrollY);
		LineTo(hDC, (int)m_vWorldPoint[5].x + iScrollX, (int)m_vWorldPoint[5].y + iScrollY);
		LineTo(hDC, (int)m_vWorldPoint[6].x + iScrollX, (int)m_vWorldPoint[6].y + iScrollY);
		LineTo(hDC, (int)m_vWorldPoint[0].x + iScrollX, (int)m_vWorldPoint[0].y + iScrollY);
		//불꽃 테스트
		MoveToEx(hDC, (int)m_vWorldPoint[6].x + iScrollX, (int)m_vWorldPoint[6].y + iScrollY, nullptr);
		LineTo(hDC, (int)m_vWorldPoint[7].x + iScrollX, (int)m_vWorldPoint[7].y + iScrollY);
		LineTo(hDC, (int)m_vWorldPoint[8].x + iScrollX, (int)m_vWorldPoint[8].y + iScrollY);
		LineTo(hDC, (int)m_vWorldPoint[9].x + iScrollX, (int)m_vWorldPoint[9].y + iScrollY);
		LineTo(hDC, (int)m_vWorldPoint[10].x + iScrollX, (int)m_vWorldPoint[10].y + iScrollY);
		LineTo(hDC, (int)m_vWorldPoint[11].x + iScrollX, (int)m_vWorldPoint[11].y + iScrollY);
		LineTo(hDC, (int)m_vWorldPoint[0].x + iScrollX, (int)m_vWorldPoint[0].y + iScrollY);

		//바람 테스트
		MoveToEx(hDC, (int)m_vWorldWind[0].x + iScrollX, (int)m_vWorldWind[0].y + iScrollY, nullptr);
		LineTo(hDC, (int)m_vWorldWind[1].x + iScrollX, (int)m_vWorldWind[1].y + iScrollY);

		MoveToEx(hDC, (int)m_vWorldWind[2].x + iScrollX, (int)m_vWorldWind[2].y + iScrollY, nullptr);
		LineTo(hDC, (int)m_vWorldWind[3].x + iScrollX, (int)m_vWorldWind[3].y + iScrollY);

		MoveToEx(hDC, (int)m_vWorldWind[4].x + iScrollX, (int)m_vWorldWind[4].y + iScrollY, nullptr);
		LineTo(hDC, (int)m_vWorldWind[5].x + iScrollX, (int)m_vWorldWind[5].y + iScrollY);

		MoveToEx(hDC, (int)m_vWorldWind[6].x + iScrollX, (int)m_vWorldWind[6].y + iScrollY, nullptr);
		LineTo(hDC, (int)m_vWorldWind[7].x + iScrollX, (int)m_vWorldWind[7].y + iScrollY);

		MoveToEx(hDC, (int)m_vWorldWind[8].x + iScrollX, (int)m_vWorldWind[8].y + iScrollY, nullptr);
		LineTo(hDC, (int)m_vWorldWind[9].x + iScrollX, (int)m_vWorldWind[9].y + iScrollY);

		MoveToEx(hDC, (int)m_vWorldWind[10].x + iScrollX, (int)m_vWorldWind[10].y + iScrollY, nullptr);
		LineTo(hDC, (int)m_vWorldWind[11].x + iScrollX, (int)m_vWorldWind[11].y + iScrollY);

		MoveToEx(hDC, (int)m_vWorldWind[12].x + iScrollX, (int)m_vWorldWind[12].y + iScrollY, nullptr);
		LineTo(hDC, (int)m_vWorldWind[13].x + iScrollX, (int)m_vWorldWind[13].y + iScrollY);

		MoveToEx(hDC, (int)m_vWorldWind[14].x + iScrollX, (int)m_vWorldWind[14].y + iScrollY, nullptr);
		LineTo(hDC, (int)m_vWorldWind[15].x + iScrollX, (int)m_vWorldWind[15].y + iScrollY);

		MoveToEx(hDC, (int)m_vWorldWind[4].x + iScrollX, (int)m_vWorldWind[4].y + iScrollY, nullptr);
		LineTo(hDC, (int)m_vWorldWind[5].x + iScrollX, (int)m_vWorldWind[5].y + iScrollY);
		MoveToEx(hDC, (int)m_vWorldPoint[8].x + iScrollX, (int)m_vWorldPoint[8].y + iScrollY, nullptr);
		LineTo(hDC, (int)m_vWorldPoint[9].x + iScrollX, (int)m_vWorldPoint[9].y + iScrollY);

		MoveToEx(hDC, (int)m_vWorldPoint[10].x + iScrollX, (int)m_vWorldPoint[10].y + iScrollY, nullptr);
		LineTo(hDC, (int)m_vWorldPoint[11].x + iScrollX, (int)m_vWorldPoint[11].y + iScrollY);
		break;

	case BULLET_DP:
		for (int i = 0; i < (sizeof(m_vDpPoint) / sizeof(D3DXVECTOR3)); ++i)
		{
			Ellipse(hDC, (int)(m_vDpPoint[i].x - 8) + iScrollX, (int)(m_vDpPoint[i].y - 8) + iScrollY,
				(int)(m_vDpPoint[i].x + 8) + iScrollX, (int)(m_vDpPoint[i].y + 8) + iScrollY);
		}
		break;
	case BULLET_END:
		break;
	}





//	LineTo(hDC, (int)m_vWorldPoint[0].x+ iScrollX, (int)m_vWorldPoint[0].y+ iScrollY);
									  


	//Ellipse(hDC, (int)m_tInfo.vPos.x - 10 + iScrollX, (int)m_tInfo.vPos.y - 10 + iScrollY, (int)m_tInfo.vPos.x + 10 + iScrollX, (int)m_tInfo.vPos.y + 10 + iScrollY);

}

void CJunBullet::Release(void)
{

}

void CJunBullet::Move(void)
{
	/*	m_tInfo.vPos.x += iBulletDir * (m_fSpeed * cosf(m_fAngle) * m_fTempTime);
		m_tInfo.vPos.y -= (m_fSpeed * sinf(m_fAngle) * m_fTempTime) - (0.5f * (9.8f) * m_fTempTime * m_fTempTime);
	*/
	//int i;
	m_tInfo.vPos += m_fSpeed * m_tInfo.vDir;
	m_tInfo.vPos.y += (0.5f * (9.8f) * m_fTempTime * m_fTempTime);

	switch (m_BulletID)
	{
	case BULLET_BASIC:
		
		//i = 5;
		break;
	case BULLET_DP:
		/*m_tInfo.vPos += m_fSpeed* m_tInfo.vDir;
		m_tInfo.vPos.y += (0.5f * (9.8f) * m_fTempTime * m_fTempTime);*/
		
		break;
	case BULLET_END:
		break;
	}	
}

void CJunBullet::Local_Initialize(void)
{
	m_vLocalPoint[0] = { -20.f,-10.f,0.f };
	m_vLocalPoint[1] = { 20.f, -10.f,0.f };
	m_vLocalPoint[2] = { 25.f, -6.f,0.f };
	m_vLocalPoint[3] = { 27.5f, 0.f,0.f };
	m_vLocalPoint[4] = { 25.f,  6.f,0.f };
	m_vLocalPoint[5] = { 20.f, 10.f,0.f };

	m_vLocalPoint[6] = { -20.f, 10.f,0.f };

	m_vLocalPoint[7] = { -60.f, 15.f,0.f };
	m_vLocalPoint[8] = { -40.f, 5.f,0.f };
	m_vLocalPoint[9] = { -60.f, 0.f,0.f };
	m_vLocalPoint[10] = { -40.f, -5.f,0.f };
	m_vLocalPoint[11] = { -60.f,-10.f,0.f };

	
	m_vLocalWind[0] = { -15.f,-15.f,0.f };
	m_vLocalWind[1] = { -45.f,-15.f,0.f };
	m_vLocalWind[2] = {  5.f, 17.f,0.f };
	m_vLocalWind[3] = {  -21.f, 17.f,0.f };
	m_vLocalWind[4] = { -30.f, 22.f,0.f };
	m_vLocalWind[5] = { 18.f, 22.f,0.f };
	m_vLocalWind[6] = {  13.f, 26.f,0.f };
	m_vLocalWind[7] = { -10.f, 26.f,0.f };
	m_vLocalWind[8] = { -33.f, -21.f,0.f };
	m_vLocalWind[9] = {  12.f, -21.f,0.f };
	m_vLocalWind[10] = { -38.f, 26.f,0.f };
	m_vLocalWind[11] = { -10.f, 26.f,0.f };
	m_vLocalWind[12] = { 14.f, -18.f,0.f };
	m_vLocalWind[13] = { -26.f, -18.f,0.f };
	m_vLocalWind[14] = { 9.f, 11.f,0.f };
	m_vLocalWind[15] = { -39.f, 11.f,0.f };
	/*m_vLocalWind[15] = { 3.f, -19.f,0.f };
	m_vLocalWind[16] = {  24.f, -19.f,0.f };*/

}

void CJunBullet::Dp_Local_Initialize(void)
{
	srand((unsigned)time(NULL));
	for (int i = 0; sizeof(m_vDpPoint) / sizeof(D3DXVECTOR3) > i; ++i)
	{
		int iRandom = rand() % 6;
		/*m_DpINFO_Local[i].vPos = { m_vLocalPoint[i].x + iRandom , m_vLocalPoint[i].y + iRandom, 0.f };
		float fTemp = (float)iRandom * 0.1f;
		m_DpINFO_Local[i].vDir.x = m_tInfo.vDir.x += iRandom;
		m_DpINFO_Local[i].vDir.y = m_tInfo.vDir.y += iRandom;
*/
		//int iRandom = rand() % 60;
		/*m_DpINFO_World[i].vPos = { m_vWorldPoint[i].x + iRandom , m_vWorldPoint[i].y + iRandom, 0.f };*/
		float fTemp = (float)iRandom * 0.1f;
		m_vDpPoint[i].x = m_vWorldPoint[i].x;
		m_vDpPoint[i].y = m_vWorldPoint[i].y;
		/*m_DpINFO_World[i].vDir.x = m_tInfo.vDir.x += iRandom;
		m_DpINFO_World[i].vDir.y = m_tInfo.vDir.y += iRandom;*/
	}
	
	int i = 5;

}
