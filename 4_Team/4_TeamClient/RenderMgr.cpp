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

	//RENDERID render_Id = _obj->Get_RenderID();
	//INFO render_Info = _obj->Get_Info();

	//if (!(render_Rect.left + iScrollX > (WINCX + 200) || render_Rect.right + iScrollX <  - 200
	//	|| render_Rect.top + iScrollY >(WINCY + 200) || render_Rect.bottom + iScrollY <  - 200))
	//{
	//	m_RenderSort[render_Id].push_back(_obj);
	//}
}

template<typename T>
const bool	CompareY(const T Dest, const T Sour)
{
	//return Dest->Get_Rect().bottom < Sour->Get_Rect().bottom;

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
