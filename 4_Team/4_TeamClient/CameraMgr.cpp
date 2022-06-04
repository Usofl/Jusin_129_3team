#include "stdafx.h"
#include "CameraMgr.h"

IMPLEMENT_SINGLETON(CCameraMgr)

CCameraMgr::CCameraMgr()
{
}


CCameraMgr::~CCameraMgr()
{
}

void CCameraMgr::CloseUP_DC(HDC _hDC)
{
	int isizeX = int(WINCX * m_fMagnify);
	int isizeY = int(WINCY * m_fMagnify);

	m_hCameraDC = CreateCompatibleDC(_hDC);
	HBITMAP m_hBackBit = CreateCompatibleBitmap(_hDC, WINCX, WINCY);
	HBITMAP m_hOldBackBit = (HBITMAP)SelectObject(m_hCameraDC, m_hBackBit);

	StretchBlt(m_hCameraDC,
		0,
		0,
		WINCX,
		WINCY,
		_hDC,
		0 + (int)(isizeX * 0.5),
		0 + (int)(isizeY * 0.5),
		WINCX - (isizeX),
		WINCY - (isizeY),
		SRCCOPY);

	BitBlt(_hDC, 0, 0, WINCX, WINCY, m_hCameraDC, 0, 0, SRCCOPY);

	SelectObject(m_hCameraDC, m_hOldBackBit); //DC에 원래 설정을 돌려줍니다.
	DeleteDC(m_hCameraDC);  // 메모리를 반환합니다.
	DeleteObject(m_hBackBit); // 메모리를 반환합니다.
}
