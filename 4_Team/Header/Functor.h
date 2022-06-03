#pragma once

// ÇÔ¼ö ÅÛÇÃ¸´

template<typename T>
void		Safe_Delete(T& Temp)
{
	if (Temp)
	{
		delete Temp;
		Temp = nullptr;
	}
}

template<typename T>
void		Safe_Delete_Array(T& Temp)
{
	if (Temp)
	{
		delete[] Temp;
		Temp = nullptr;
	}
}


// ÇÔ¼ö °´Ã¼

class CDeleteObj
{
public:
	template<typename T>
	void		operator()(T& Temp)
	{
		if (Temp)
		{
			delete Temp;
			Temp = nullptr;
		}
	}
};

class CDeleteMap
{
public:
	template<typename T>
	void		operator()(T& Pair)
	{
		if (Pair.second)
		{
			delete Pair.second;
			Pair.second = nullptr;
		}
	}
};

class CTag_Finder
{
private:
	const TCHAR*	m_pStr;

public:
	CTag_Finder(const TCHAR* pStr)
		: m_pStr(pStr)
	{

	}

public:
	template<typename T>
	bool	operator()(T& Pair)
	{
		return !lstrcmp(m_pStr, Pair.first.c_str());
	}
};

static D3DXVECTOR3		Get_Mouse(void)
{
	POINT	Pt{};

	GetCursorPos(&Pt);
	ScreenToClient(g_hWnd, &Pt);

	return D3DXVECTOR3((float)Pt.x, (float)Pt.y, 0.f);
}