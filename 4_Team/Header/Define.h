#pragma once

#define		WINCX		1024
#define		WINCY		768

#define		PI			3.141592f

#define		PURE		= 0

#define		VK_MAX		0xff

#define		OBJ_NOEVENT  0
#define		OBJ_DEAD	 1

#define		MIN_STR			64
#define		MAX_STR			256

#define		RUBY			0x01		// -> 0001
#define		DIAMOND			0x02		// -> 0010
#define		SAPPHIRE		0x04		// -> 0100

#define ERR_MSG(message)								\
::MessageBox(nullptr, message, L"error", MB_OK)

#define NO_COPY(ClassName)								\
ClassName(const ClassName&) = delete;					\
ClassName& operator=(const ClassName&) = delete;

#define DECLARE_SINGLETON(ClassName)					\
		NO_COPY(ClassName)								\
public :												\
	static ClassName* Get_Instance();					\
	static void		  Destroy_Instance();				\
private:												\
	static ClassName* m_pInstance;

#define IMPLEMENT_SINGLETON(ClassName)					\
ClassName* ClassName::m_pInstance = nullptr;			\
ClassName* ClassName::Get_Instance()					\
{														\
	if (nullptr == m_pInstance)							\
		m_pInstance = new ClassName;					\
	return m_pInstance;									\
}														\
void ClassName::Destroy_Instance()						\
{														\
	if(nullptr != m_pInstance)							\
	{													\
		delete m_pInstance;								\
		m_pInstance = nullptr;							\
	}													\
}


#define KEYMGR		(CKeyMgr::Get_Instance())
#define SCROLLMGR	(CScrollMgr::Get_Instance())
#define SCENEMGR	(CSceneMgr::Get_Instance())
#define RENDERMGR	(CRenderMgr::Get_Instance())
#define MOMODORAMGR (CMomodoraMgr::Get_Instance())
#define LINEMGR		(CLineMgr::Get_Instance())

#define TEXTUREMGR	(CTextureMgr::Get_Instance())
#define DEVICE		(CDevice::Get_Instance())

extern HWND			g_hWnd;