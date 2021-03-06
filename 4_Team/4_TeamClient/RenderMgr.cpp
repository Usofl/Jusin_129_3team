#include "stdafx.h"
#include "RenderMgr.h"
#include "ScrollMgr.h"

CRenderMgr*		CRenderMgr::m_pInstance = nullptr;

CRenderMgr::CRenderMgr()
{
}

CRenderMgr::~CRenderMgr()
{
}

void CRenderMgr::Add_Render_Obj(CObj* _obj)
{
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	RENDERID render_Id = _obj->Get_RenderID();
	INFO render_Info = _obj->Get_Info();
	
	if (render_Id == RENDER_TARGETLINE)
	{
		m_RenderSort[render_Id].push_back(_obj);
		return;
	}

	if (!(render_Info.vPos.x + iScrollX > (WINCX + 200) || render_Info.vPos.x + iScrollX <  - 200
		|| render_Info.vPos.y + iScrollY >(WINCY + 200) || render_Info.vPos.y + iScrollY <  - 200))
	{
		m_RenderSort[render_Id].push_back(_obj);
	}
}

template<typename T>
const bool	CompareY(const T Dest, const T Sour)
{
	return Dest->Get_Info().vPos.y < Sour->Get_Info().vPos.y;

	return true;
}

void CRenderMgr::Render(HDC _hDC)
{
	for (int i = RENDER_BACKGROUND; i < RENDER_END; ++i)
	{
		m_RenderSort[i].sort(CompareY<CObj*>);

		for (auto& iter : m_RenderSort[i])
		{
			iter->Render(_hDC);
		}

		m_RenderSort[i].clear();
	}
}
