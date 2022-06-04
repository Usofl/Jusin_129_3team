#pragma once
class CCameraMgr
{
	DECLARE_SINGLETON(CCameraMgr)
public:
	CCameraMgr();
	~CCameraMgr();

public:
	inline void Set_Magnify(const float& _Magnify) { m_fMagnify = _Magnify; }
	inline const float& Get_Magnify(void) { return m_fMagnify; }

	void CloseUP_DC(HDC _hDC);

private:
	HDC						m_hCameraDC;

	float					m_fMagnify;
};
