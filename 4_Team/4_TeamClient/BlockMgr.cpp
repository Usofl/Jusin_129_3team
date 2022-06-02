#include "stdafx.h"
#include "BlockMgr.h"

CBlockMgr*		CBlockMgr::m_pInstance = nullptr;

CBlockMgr::CBlockMgr()
{

}


CBlockMgr::~CBlockMgr()
{
}

void CBlockMgr::Initialize(void)
{
}

const int CBlockMgr::Update(void)
{
	return 0;
}

void CBlockMgr::Late_Update(void)
{
}

void CBlockMgr::Render(HDC hDC)
{
}

void CBlockMgr::Release(void)
{
}

void CBlockMgr::Key_Input(void)
{
}
