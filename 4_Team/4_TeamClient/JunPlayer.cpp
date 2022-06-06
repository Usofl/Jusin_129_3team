#include "stdafx.h"
#include "JunPlayer.h"
#include "KeyMgr.h"
#include "SceneMgr.h"
#include "Fortress.h"
#include "MainScene.h"
#include "ScrollMgr.h"
#include "CameraMgr.h"
#include "LineMgr.h"
#include "Fortress_TargetLine.h"

CJunPlayer::CJunPlayer()
	: m_iAngleCount(0)
	, m_fPoAngle(0.f)
	, BeforePoAngle(0.f)
	, BeforeAngle(m_fAngle)
	, m_fShootPower(0.f)
	, m_fFallenTime(0.f)
	, m_bNextLine(false)
	, m_pBullet(nullptr)
	, m_bPlayer_Turn(true)
	, m_iHp(100)
	, m_bTargetLine(false)
	, m_iMaxHp(100)
	, m_fRenderPower(0.f)
	, m_bMyTurn(true)

{
	ZeroMemory(m_vAfter_RenderLine, sizeof(m_vAfter_RenderLine));
	ZeroMemory(m_vLineArray, sizeof(m_vLineArray));
	Initialize();
}


CJunPlayer::~CJunPlayer()
{
	Release();
}

void CJunPlayer::Initialize(void)
{
	m_eRender = RENDER_GAMEOBJECT;
	//m_tInfo.
	//int iArray[4] = { 0,0,50,50 };
	//SCENEMGR->Get_Instance()->

	m_vLocalTank[0] = { -50.f,-30.f - 29.f,0.f };
	m_vLocalTank[1] = { 50.f, -30.f - 29.f,0.f };
	m_vLocalTank[2] = { 50.f,30.f - 29.f,0.f };
	m_vLocalTank[3] = { -50.f,30.f - 29.f,0.f };

	m_vLocalTankHead[0] = { -20.f, -50.f - 20.f - 29.f ,0.f };
	m_vLocalTankHead[1] = { 20.f, -50.f - 20.f - 29.f ,0.f };
	m_vLocalTankHead[2] = { 20.f,-50.f + 20.f - 29.f ,0.f };
	m_vLocalTankHead[3] = { -20.f, -50.f + 20.f - 29.f ,0.f };
	
	m_vLocal_Po_One = { 0, -79.f,0.f };
	m_vLocal_Po = { 80.f, 0.f ,0.f };

	m_HeadInfo.vPos = { 50.f,-50.f,0.f };

	m_tInfo.vPos = { 300.f,300.f,0.f };

	m_HeadInfo.vPos = { 300.f,250.f,0.f };
	//vHeadPos = { m_tInfo.vPo,300.f,0.f };
	//m_tInfo.vDir = { 0.f,1.f,0.f };

	m_tInfo.vLook = { 1.f,0.f,0.f };
	m_fSpeed = 5.f;
	OriPo_Dir = { 1.f,0.f,0.f };
	m_fShootPower = 0.f;
	m_fTempPower = 0.f;
	m_bMaxPower = true;
	m_bGageRender = false;
	m_iHp = m_iMaxHp;
}

const int CJunPlayer::Update(void)
{
	if (m_iHp <= 0)
	{
		return OBJ_DEAD;
	}

	Key_Input();
	if (nullptr == m_pBullet)
	{
		m_fRenderPower = 0.f;

	}
	
	if (BeforeAngle != m_fAngle)
	{
		if (m_fAngle < BeforeAngle)
		{
			m_fPoAngle -= (BeforeAngle - m_fAngle);
		}
		else
		{
			m_fPoAngle += (m_fAngle - BeforeAngle);
		}
		/*else
			m_fPoAngle += (BeforeAngle - m_fAngle);*/
		BeforeAngle = m_fAngle;
	}

	D3DXMatrixScaling(&m_matScale, 1.f, 1.f, 0);

	D3DXMatrixRotationZ(&m_matRotZ, m_fAngle);

	D3DXMatrixTranslation(&m_matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);

	//m_tInfo.matWorld = m_matScale * m_matRotZ;
	//D3DXVec3TransformCoord(&Po_One, &Po_One, &m_tInfo.matWorld);

	m_tInfo.matWorld = m_matScale * m_matRotZ * m_matTrans;

	for (int i = 0; i < 4; ++i)
	{
		D3DXVec3TransformCoord(&m_vTank[i], &m_vLocalTank[i], &m_tInfo.matWorld);
		D3DXVec3TransformCoord(&m_vTankHead[i], &m_vLocalTankHead[i], &m_tInfo.matWorld);
	}

	D3DXVec3TransformCoord(&m_vPo_One, &m_vLocal_Po_One, &m_tInfo.matWorld);

	D3DXMatrixRotationZ(&m_HmatRotZ, m_fPoAngle);
	D3DXMatrixTranslation(&m_HmatTrans, m_vPo_One.x, m_vPo_One.y, 0.f);

	m_HeadInfo.matWorld = m_matScale * m_HmatRotZ * m_HmatTrans;

	D3DXVec3TransformCoord(&m_vPo, &m_vLocal_Po, &m_HeadInfo.matWorld);

	//D3DXVec3TransformNormal(&Po_Dir, &OriPo_Dir, &m_HeadInfo.matWorld);

	//float fTe = D3DXVec3Dot(&TempVec1, &TempVec2);
	//D3DXVec3Normalize

	switch (m_eCurState)
	{
	case CJunPlayer::IDLE:
		m_fFallenTime = 0.f;
		Shoot();
		break;
	case CJunPlayer::FALLEN:
		Fallen();
		break;
	}

	return 0;
}

void CJunPlayer::Late_Update(void)
{
	Line_Calculation();
}

void CJunPlayer::Render(HDC hDC)
{
	//Ellipse(hDC, iArray[0], iArray[1], iArray[2], iArray[3]);
	/*MoveToEx(hDC, 0, 0, nullptr);
	LineTo(hDC,300, 500);*/
	int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int	iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	MoveToEx(hDC, (int)m_vTank[0].x + iScrollX, (int)m_vTank[0].y + iScrollY, nullptr);
	LineTo(hDC, (int)m_vTank[1].x + iScrollX, (int)m_vTank[1].y + iScrollY);
	LineTo(hDC, (int)m_vTank[2].x + iScrollX, (int)m_vTank[2].y + iScrollY);
	LineTo(hDC, (int)m_vTank[3].x + iScrollX, (int)m_vTank[3].y + iScrollY);
	LineTo(hDC, (int)m_vTank[0].x + iScrollX, (int)m_vTank[0].y + iScrollY);


	MoveToEx(hDC, (int)m_vTankHead[0].x + iScrollX, (int)m_vTankHead[0].y + iScrollY, nullptr);
	LineTo(hDC, (int)m_vTankHead[1].x + iScrollX, (int)m_vTankHead[1].y + iScrollY);
	LineTo(hDC, (int)m_vTankHead[2].x + iScrollX, (int)m_vTankHead[2].y + iScrollY);
	LineTo(hDC, (int)m_vTankHead[3].x + iScrollX, (int)m_vTankHead[3].y + iScrollY);
	LineTo(hDC, (int)m_vTankHead[0].x + iScrollX, (int)m_vTankHead[0].y + iScrollY);
	Ellipse(hDC, (int)m_vTankHead[1].x - 5 + iScrollX, (int)m_vTankHead[1].y - 5 + iScrollY, (int)m_vTankHead[1].x + 5 + iScrollX, (int)m_vTankHead[1].y + 5 + iScrollY);

	Ellipse(hDC, (int)m_vPo_One.x - 5 + iScrollX, (int)m_vPo_One.y - 5 + iScrollY, (int)m_vPo_One.x + 5 + iScrollX, (int)m_vPo_One.y + 5 + iScrollY);
	MoveToEx(hDC, (int)m_vPo_One.x + iScrollX, (int)m_vPo_One.y + iScrollY, nullptr);
	LineTo(hDC, (int)m_vPo.x + iScrollX, (int)m_vPo.y + iScrollY);


	//임시 게이지 보게 끔 만든 렉트
	//색상 변경점
	HPEN MyPen, OldPen;
	MyPen = (HPEN)CreatePen(PS_SOLID, 3, RGB(255, 0, 0));
	OldPen = (HPEN)::SelectObject(hDC, (HGDIOBJ)MyPen);

	Rectangle(hDC, (int)700/* + iScrollX*/, WINCY - (int)80 /*+ iScrollY*/, (int)960/* + iScrollX*/, WINCY - (int)30/*+ iScrollY*/);
	Rectangle(hDC, (int)955/* + iScrollX*/, WINCY - (int)80 /*+ iScrollY*/, (int)960/* + iScrollX*/, WINCY - (int)30/*+ iScrollY*/);
	Rectangle(hDC, (int)700/* + iScrollX*/, WINCY - (int)80 /*+ iScrollY*/, (int)705/* + iScrollX*/, WINCY - (int)30/*+ iScrollY*/);



	if (m_bGageRender && !m_pBullet)
	{
		//Ellipse(hDC, (int)800/* + iScrollX*/, (int)(400 - (m_fTempPower * 10)) /*+ iScrollY*/, (int)850/* + iScrollX*/, (int)(450 - (m_fTempPower * 10))/*+ iScrollY*/);
		Ellipse(hDC, (int)(705 + (m_fTempPower * 10))/* + iScrollX*/, WINCY - (int)80 /*+ iScrollY*/, (int)(755 + (m_fTempPower * 10))/* + iScrollX*/, WINCY - (int)30/*+ iScrollY*/);
	}
	
	float fTempX = m_vPo.x;
	float fTempY = m_vPo.y;
	D3DXVECTOR3 TempVec1 = { m_vPo.x - m_vPo_One.x, m_vPo.y - m_vPo_One.y,0.f };
	D3DXVECTOR3 TempVec2 = { 1.f,0.f,0.f };

	D3DXVec3Normalize(&TempVec1, &TempVec1);
	//펜 삭제인데 잘 몰라서 그냥 삭제했다가 재생성 함
	SelectObject(hDC, OldPen);
	DeleteObject(MyPen);

	//HPEN MyPen2, OldPen2;
	//MyPen2 = (HPEN)CreatePen(PS_SOLID, 3, RGB(125, 0, 0));
	//OldPen2 = (HPEN)::SelectObject(hDC, (HGDIOBJ)MyPen2);
	//if(m_bTargetLine)
	//{
	//	//(int)m_vPo.x + iScrollX, (int)m_vPo.y + iScrollY
	//	float fTempTime = 0.f;

	//	if (m_bGageRender)
	//	{
	//		for (int i = 0; i < 30; ++i)
	//		{
	//			fTempX += 5 * (m_fShootPower * TempVec1.x);
	//			fTempY += 5 * (m_fShootPower * TempVec1.y);
	//			fTempY += 5 * (0.5f * (9.8f) * fTempTime * fTempTime);
	//			fTempTime += 5 * 0.016f;
	//			D3DXVECTOR3 vTemp = { fTempX + iScrollX ,fTempY + iScrollY, 0.f };
	//			float fTemp = 0.f;
	//			/*if (vTemp.y <   100)*/
	//			Ellipse(hDC, (int)(fTempX + iScrollX - 5), (int)(fTempY + iScrollY - 5), (int)(fTempX + iScrollX + 5), (int)(fTempY + iScrollY + 5));
	//		}
	//	}
	//	else
	//	{
	//		for (int i = 0; i < 30; ++i)
	//		{
	//			fTempX += 5 * (m_fRenderPower * TempVec1.x);
	//			fTempY += 5 * (m_fRenderPower * TempVec1.y);
	//			fTempY += 5 * (0.5f * (9.8f) * fTempTime * fTempTime);
	//			fTempTime += 5 * 0.016f;
	//			D3DXVECTOR3 vTemp = { fTempX + iScrollX ,fTempY + iScrollY, 0.f };
	//			float fTemp = 0.f;
	//			Ellipse(hDC, (int)(fTempX + iScrollX - 5), (int)(fTempY + iScrollY - 5), (int)(fTempX + iScrollX + 5), (int)(fTempY + iScrollY + 5));

	//		}
	//	}
	//	
	//}

	//SelectObject(hDC, OldPen2);
	//DeleteObject(MyPen2);
	
//	Rectangle(hDC, )
	 
	/*MoveToEx(hDC, (int)m_tInfo.vPos.x, (int)m_tInfo.vPos.y, nullptr);
	LineTo(hDC, (int)Po.x, (int)Po.y);*/
}

void CJunPlayer::Release(void)
{

}

void CJunPlayer::Key_Input(void)
{
	if (!m_bMyTurn)
		return;
	if (KEYMGR->Key_Pressing(VK_LEFT))
	{
		//m_fAngle -= D3DXToRadian(3.f);
		//m_fPoAngle += D3DXToRadian(3.f);
		D3DXVec3TransformNormal(&m_tInfo.vDir, &m_tInfo.vLook, &m_tInfo.matWorld);
		m_tInfo.vPos -= m_tInfo.vDir * m_fSpeed;
	}

	if (KEYMGR->Key_Pressing(VK_RIGHT))
	{
		//m_fAngle += D3DXToRadian(3.f);
		//m_fPoAngle -= D3DXToRadian(3.f);
		D3DXVec3TransformNormal(&m_tInfo.vDir, &m_tInfo.vLook, &m_tInfo.matWorld);
		m_tInfo.vPos += m_tInfo.vDir * m_fSpeed;
	}

	if (KEYMGR->Key_Pressing(VK_UP))
	{
		m_fPoAngle -= D3DXToRadian(3.f);
	}

	if (KEYMGR->Key_Pressing(VK_DOWN))
	{
		m_fPoAngle += D3DXToRadian(3.f);
	}


	if (KEYMGR->Key_Up('T'))
	{
		
		m_bTargetLine = !m_bTargetLine;
	}

	if (KEYMGR->Key_Pressing('A'))
	{
		//m_fPoAngle -= D3DXToRadian(3.f);
	}

	if (KEYMGR->Key_Pressing('D'))
	{
		//m_fPoAngle += D3DXToRadian(3.f);
	}

	/*if (KEYMGR->Key_Pressing(VK_DOWN))
	{
		m_fAngle += D3DXToRadian(3.f);
	}*/
}

void CJunPlayer::Shoot(void)
{
	if (!m_bMyTurn)
		return;

	D3DXVECTOR3 TempVec1 = { m_vPo.x - m_vPo_One.x, m_vPo.y - m_vPo_One.y,0.f };
	D3DXVECTOR3 TempVec2 = { 1.f,0.f,0.f };

	D3DXVec3Normalize(&TempVec1, &TempVec1);

	if (KEYMGR->Key_Pressing(VK_SPACE))
	{
		

		if (m_pBullet != nullptr)
		{
			return;
		}
		m_bGageRender = true;

		if (m_bMaxPower)
		{
			m_fShootPower += 0.4f;
		}
		else
		{
			m_fShootPower -= 0.4f;
		}
		if (m_fShootPower >= 20.f)
		{
			m_bMaxPower = false;
		}
		else if (m_fShootPower <= 0.f)
		{
			m_bMaxPower = true;
		}
		m_fTempPower = m_fShootPower;
	}

	if (KEYMGR->Key_Up(VK_SPACE))
	{
		//fShootPower;
		m_bGageRender = false;
		m_fRenderPower = m_fShootPower;
		if (m_pBullet == nullptr)
		{
			m_pBullet = new CJunBullet;
			m_pBullet->Initialize();
			if (m_vPo_One.x > m_vPo.x)
			{
				m_pBullet->Set_Pos_Dir(m_vPo.x, m_vPo.y, TempVec1, -1, m_fShootPower, m_vPo - m_vPo_One);
			}
			//	Bullet->Set_Pos_Dir(Po.x, Po.y, Po_Dir ,-1);
			else
			{
				m_pBullet->Set_Pos_Dir(m_vPo.x, m_vPo.y, TempVec1, 1, m_fShootPower, m_vPo - m_vPo_One);
			}

			if (SC_FORTRESS == SCENEMGR->Get_Scene_ID())
			{
				CFortress* FortressScene = static_cast<CFortress*>(SCENEMGR->Get_Scene(SC_FORTRESS));
				m_pBullet->Set_BulletID(BULLET_BASIC);
				FortressScene->Get_JunBulletList()->push_back(m_pBullet);
				FortressScene->Set_Target(FortressScene->Get_JunBulletList()->back());
				m_fShootPower = 0.f;
				//m_fTempPower = 0.f;

				FortressScene->Set_Monster_Turn(true);
				FortressScene->Set_Player_Turn(false);
			}


			if (SC_MAIN == SCENEMGR->Get_Scene_ID())
			{
				CMainScene* MainScene = static_cast<CMainScene*>(SCENEMGR->Get_Scene(SC_MAIN));
				m_pBullet->Set_BulletID(BULLET_BASIC);

				MainScene->Set_Bullet(m_pBullet);

				m_fShootPower = 0.f;
				m_fTempPower = 0.f;
			}
		}

		//int i = 5;
	}
}

void CJunPlayer::Fallen(void)
{
	m_fFallenTime += 0.1f;
	m_tInfo.vPos.y += (0.5f * 3.8f * (m_fFallenTime * m_fFallenTime));

	m_fAngle -= D3DXToRadian(1.f);
}

void CJunPlayer::Line_Calculation(void)
{

	float fTempX = m_vPo.x;
	float fTempY = m_vPo.y;
	D3DXVECTOR3 TempVec1 = { m_vPo.x - m_vPo_One.x, m_vPo.y - m_vPo_One.y,0.f };
	D3DXVECTOR3 TempVec2 = { 1.f,0.f,0.f };

	D3DXVec3Normalize(&TempVec1, &TempVec1);
	//펜 삭제인데 잘 몰라서 그냥 삭제했다가 재생성 함
	
	
		//(int)m_vPo.x + iScrollX, (int)m_vPo.y + iScrollY
		float fTempTime = 0.f;

		if (m_bGageRender)
		{
			for (int i = 0; i < 200; ++i) // 30이랑 * 5
			{/*
				fTempX += 5 * (m_fShootPower * TempVec1.x);
				fTempY += 5 * (m_fShootPower * TempVec1.y);
				fTempY += 5 * (0.5f * (9.8f) * fTempTime * fTempTime);
				fTempTime += 5 * 0.016f;
				m_vLineArray[i] = { fTempX,fTempY,0.f };*/


				fTempX += (m_fShootPower * TempVec1.x);
				fTempY += (m_fShootPower * TempVec1.y);
				fTempY += (0.5f * (9.8f) * fTempTime * fTempTime);
				fTempTime +=  0.016f;
				m_vLineArray[i] = { fTempX,fTempY,0.f };
			}
		}

		else
		{
			for (int i = 0; i < 200; ++i)
			{
				fTempX +=  (m_fTempPower * TempVec1.x);
				fTempY +=  (m_fTempPower * TempVec1.y);
				fTempY +=  (0.5f * (9.8f) * fTempTime * fTempTime);
				fTempTime +=  0.016f;
				m_vLineArray[i] = { fTempX,fTempY,0.f };
			}
		}


		if (SC_FORTRESS == SCENEMGR->Get_Scene_ID())
		{
			m_pTargetLine->Set_RenderArray(m_vLineArray, m_bTargetLine);
		}
		
}
