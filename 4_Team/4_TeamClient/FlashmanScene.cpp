#include "stdafx.h"
#include "FlashmanScene.h"
#include "FlashmanRed.h"
#include "FlashmanBlue.h"
#include "FlashmanYellow.h"
#include "KeyMgr.h"
#include "RenderMgr.h"

CFlashmanScene::CFlashmanScene()
	: m_eCurFlashMan_id(FLASHMAN_RED)
	, m_ePreFlashMan_id(FLASHMAN_YELLOW)
{
	for (int i = FLASHMAN_RED; i < FLASHMAN_END; ++i)
	{
		m_pPlayer[i] = nullptr;
	}
	Initialize();
}

CFlashmanScene::~CFlashmanScene()
{
	Release();
}

void CFlashmanScene::Initialize(void)
{
	m_vFeildLine[0] = { 0.f, (float)WINCY - 100.f, 0.f };
	m_vFeildLine[1] = { (float)WINCX , (float)WINCY - 100.f, 0.f };

	if (nullptr == m_pPlayer[FLASHMAN_RED])
	{
		m_pPlayer[FLASHMAN_RED] = new CFlashmanRed;
	}

	if (nullptr == m_pPlayer[FLASHMAN_BLUE])
	{
		m_pPlayer[FLASHMAN_BLUE] = new CFlashmanBlue;
	}

	if (nullptr == m_pPlayer[FLASHMAN_YELLOW])
	{
		m_pPlayer[FLASHMAN_YELLOW] = new CFlashmanYellow;
	}
}

void CFlashmanScene::Update(void)
{
	Key_Input();

	m_pPlayer[m_eCurFlashMan_id]->Update();

	//if (!(m_pPlayer[m_ePreFlashMan_id]->Get_Info().vPos.x <= 0) || !(m_pPlayer[m_ePreFlashMan_id]->Get_Info().vPos.x >= WINCX))
	if(m_pPlayer[m_ePreFlashMan_id]->Get_State() == CFlashmanPlayer::CHANGE)
	{
		m_pPlayer[m_ePreFlashMan_id]->Update();
	}

}

void CFlashmanScene::Late_Update(void)
{
	m_pPlayer[m_eCurFlashMan_id]->Late_Update();
	RENDERMGR->Add_Render_Obj(m_pPlayer[m_eCurFlashMan_id]);

	//if (!(m_pPlayer[m_ePreFlashMan_id]->Get_Info().vPos.x <= 0) || !(m_pPlayer[m_ePreFlashMan_id]->Get_Info().vPos.x >= WINCX))
	if (m_pPlayer[m_ePreFlashMan_id]->Get_State() == CFlashmanPlayer::CHANGE)
	{
		m_pPlayer[m_ePreFlashMan_id]->Late_Update();
		RENDERMGR->Add_Render_Obj(m_pPlayer[m_ePreFlashMan_id]);
	}
}

void CFlashmanScene::Render(HDC _hDC)
{
	MoveToEx(_hDC, (int)m_vFeildLine[0].x, (int)m_vFeildLine[0].y, nullptr);
	LineTo(_hDC, (int)m_vFeildLine[1].x, (int)m_vFeildLine[1].y);

	RENDERMGR->Render(_hDC);
}

void CFlashmanScene::Release(void)
{
	for (int i = FLASHMAN_RED; i < FLASHMAN_END; ++i)
	{ 
		Safe_Delete<CFlashmanPlayer*>(m_pPlayer[i]);
	}
}

void CFlashmanScene::Key_Input(void)
{
	if (KEYMGR->Key_Up('C'))
	{
		m_ePreFlashMan_id = m_eCurFlashMan_id;
		m_pPlayer[m_eCurFlashMan_id]->Set_State(CFlashmanPlayer::CHANGE);
		switch (m_eCurFlashMan_id)
		{
		case FLASHMAN_RED:
			m_eCurFlashMan_id = FLASHMAN_BLUE;
			m_pPlayer[m_eCurFlashMan_id]->Set_State(CFlashmanPlayer::IDLE);
			break;
		case FLASHMAN_BLUE:
			m_eCurFlashMan_id = FLASHMAN_YELLOW;
			m_pPlayer[m_eCurFlashMan_id]->Set_State(CFlashmanPlayer::IDLE);
			break;
		case FLASHMAN_YELLOW:
			m_eCurFlashMan_id = FLASHMAN_RED;
			m_pPlayer[m_eCurFlashMan_id]->Set_State(CFlashmanPlayer::IDLE);
			break;
		}
	}
}
