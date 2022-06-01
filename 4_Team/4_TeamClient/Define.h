#pragma once

#define		WINCX		800
#define		WINCY		600

#define		PI			3.141592f

#define		PURE		= 0

#define		VK_MAX		0xff

#define		OBJ_NOEVENT  0
#define		OBJ_DEAD	 1

#define KEYMGR (CKeyMgr::Get_Instance())
#define SCROLLMGR (CScrollMgr::Get_Instance())
#define SCENEMGR (CSceneMgr::Get_Instance())
#define RENDERMGR (CRenderMgr::Get_Instance())
#define MOMODORAMGR (CMomodoraMgr::Get_Instance())

extern HWND			g_hWnd;