#include "stdafx.h"
#include "LineMgr.h"

CLineMgr*		CLineMgr::m_pInstance = nullptr;

CLineMgr::CLineMgr()
{
}


CLineMgr::~CLineMgr()
{
	Release();
}

void CLineMgr::Initialize(void)
{
	Load_Line();
}

void CLineMgr::Render(HDC hDC)
{
	for (auto& iter : m_LineList)
		iter->Render(hDC);
}

void CLineMgr::Release(void)
{
	for_each(m_LineList.begin(), m_LineList.end(), CDeleteObj());
	m_LineList.clear();
}

bool CLineMgr::Collision_Line(float& _fX, float* pY)
{
	// 직선의 방정식

	// Y - y1 = ((y2 - y1) / (x2 - x1)) * X - x1
	// Y  = (((y2 - y1) / (x2 - x1)) * (X - x1)) + y1

	if (m_LineList.empty())
		return false;

	float	x1(0.f), x2(0.f), y1(0.f), y2(0.f);

	CLine*		pTarget = nullptr;

	for (auto& iter : m_LineList)
	{
		if (_fX >= iter->Get_Info().tLPoint.fX &&
			_fX <= iter->Get_Info().tRPoint.fX)
		{
			x1 = iter->Get_Info().tLPoint.fX;
			x2 = iter->Get_Info().tRPoint.fX;

			y1 = iter->Get_Info().tLPoint.fY;
			y2 = iter->Get_Info().tRPoint.fY;

			pTarget = iter;

			break;
		}
	}

	if (!pTarget)
		return false;

	*pY = (((y2 - y1) / (x2 - x1)) * (_fX - x1)) + y1;
	return true;
}

bool CLineMgr::Collision_DeLine(const float& _fX, const float& _fY)
{
	// 직선의 방정식

	// Y - y1 = ((y2 - y1) / (x2 - x1)) * X - x1
	// Y  = (((y2 - y1) / (x2 - x1)) * (X - x1)) + y1

	if (m_LineList.empty())
		return false;

	CLine*		pTarget = nullptr;

	//pTarget = *m_LineList.begin();

	for (auto iter = m_LineList.begin(); iter != m_LineList.end(); )
	{
		bool bX = false, bY = false;

		float	LX = (*iter)->Get_Info().tLPoint.fX;
		float	RX = (*iter)->Get_Info().tRPoint.fX;

		float	LY = (*iter)->Get_Info().tLPoint.fY;
		float	RY = (*iter)->Get_Info().tRPoint.fY;

		float	pY(0.f);

		if ((_fX >= LX - 20.f && _fX <= RX + 20.f) || (_fX >= RX + 20.f && _fX <= LX - 20.f))
		{
			bX	= true;
		}

		if ((_fY <= LY + 20.f && _fY >= RY - 20.f) || (_fY <= RY - 20.f && _fY >= LY + 20.f))
		{
			bY = true;
		}

		// 이전 인포랑 현재 인포 저장해서 그 사이에 있으면 충돌되게끔
		////L포가  R포보다 작다 생각한 기준이라 반대 경우가 거의 안먹는 듯 
		//if ((_fX >= (*iter)->Get_Info().tLPoint.fX && 
		//	_fX <= (*iter)->Get_Info().tRPoint.fX) && (_fY  <= (*iter)->Get_Info().tLPoint.fY &&
		//		_fY  >= (*iter)->Get_Info().tRPoint.fY))

		if (bX&&bY)
		{
			if (_fX - LX > 20.f && RX - _fX > 20.f)
			{
				pY = (((RY - LY) / (RX - LX)) * (_fX - 20.f - LX)) + LY;
				Create_Line(LX, LY, _fX - 20.f, pY);

				pY = (((RY - LY) / (RX - LX)) * (_fX + 20.f - LX)) + LY;
				Create_Line(_fX + 20.f, pY, RX, RY);
			}
			else if (_fX - LX > 30.f)
			{
				pY = (((RY - LY) / (RX - LX)) * (_fX - 30.f - LX)) + LY;
				Create_Line(LX, LY, _fX - 30.f, pY);
			}
			else if (RX - _fX > 30.f)
			{
				pY = (((RY - LY) / (RX - LX)) * (_fX + 30.f - LX)) + LY;
				Create_Line(_fX + 30.f, pY, RX, RY);
			}
			
			Safe_Delete(*iter);
			(iter) = m_LineList.erase((iter));

			return true;
		}

	/*	else if ((_fX >= (*iter)->Get_Info().tLPoint.fX &&
			_fX <= (*iter)->Get_Info().tRPoint.fX) && (_fY <= (*iter)->Get_Info().tRPoint.fY &&
				_fY >= (*iter)->Get_Info().tLPoint.fY))
		{
			Safe_Delete(*iter);
			(iter) = m_LineList.erase((iter));
			return true;
		}*/

		/*else if ()
		{

		}*/
		else
		{
			++iter;
		}

		//	int i = 5;

	}
	//for (auto& iter : m_LineList)
	//{
	//	if ((_fX >= iter->Get_Info().tLPoint.fX &&
	//		_fX <= iter->Get_Info().tRPoint.fX) && (_fY <= iter->Get_Info().tLPoint.fY &&
	//		_fY >= iter->Get_Info().tRPoint.fY))
	//	{
	//		pTarget = iter;
	//		/*&iter = m_LineList.erase(&iter);*/
	//		
	//	}
	//}

	if (!pTarget)
		return false;
	
	return true;
}

const bool CLineMgr::Collision_JunLine(float & _fX, float & _fY, float& _fAngle)
{
	if (m_LineList.empty())
		return false;

	CLine*		pTarget = nullptr;

	for (auto& iter : m_LineList)
	{
		if (_fX >= iter->Get_Info().tLPoint.fX &&
			_fX <= iter->Get_Info().tRPoint.fX)
		{
			pTarget = iter;
			break;
		}
	}

	if (!pTarget)
	{
		for (auto& iter : m_LineList)
		{
			if ((_fX - 50.f >= iter->Get_Info().tLPoint.fX && _fX - 50.f <= iter->Get_Info().tRPoint.fX)
				|| (_fX + 50.f >= iter->Get_Info().tLPoint.fX && _fX + 50.f <= iter->Get_Info().tRPoint.fX))
			{
				pTarget = iter;
				break;
			}
		}
	}

	if (!pTarget)
		return false;

	float	x1 = pTarget->Get_Info().tLPoint.fX;
	float	x2 = pTarget->Get_Info().tRPoint.fX;

	float	y1 = pTarget->Get_Info().tLPoint.fY;
	float	y2 = pTarget->Get_Info().tRPoint.fY;

	D3DXVECTOR3 vTemp = { 1.f,0.f,0.f };
	D3DXVECTOR3 vTemp2 = { x2 - x1 ,y2 - y1,0.f };
	
	_fY = (((y2 - y1) / (x2 - x1)) * (_fX - x1)) + y1;
	//D3DXVec3Normalize(&vTemp, &vTemp);
	D3DXVec3Normalize(&vTemp2, &vTemp2);
	_fAngle = acosf(D3DXVec3Dot(&vTemp, &vTemp2));

	if (y1 > y2)
	{
		_fAngle *= -1.f;
	}

	return true;
}

const float CLineMgr::Collision_Monster_Line(float & _fX, float * pY)
{
	if (m_LineList.empty())
		return false;

	CLine*		pTarget = nullptr;

	for (auto& iter : m_LineList)
	{
		if (_fX >= iter->Get_Info().tLPoint.fX &&
			_fX <= iter->Get_Info().tRPoint.fX)
		{
			pTarget = iter;
		}
	}

	if (!pTarget)
		return false;

	float	x1 = pTarget->Get_Info().tLPoint.fX;
	float	x2 = pTarget->Get_Info().tRPoint.fX;

	float	y1 = pTarget->Get_Info().tLPoint.fY;
	float	y2 = pTarget->Get_Info().tRPoint.fY;

	D3DXVECTOR3 vTemp = { 1.f,0.f,0.f };
	D3DXVECTOR3 vTemp2 = { x2 - x1 ,y2 - y1,0.f };
	
	*pY = (((y2 - y1) / (x2 - x1)) * (_fX - x1)) + y1;
	//D3DXVec3Normalize(&vTemp, &vTemp);
	D3DXVec3Normalize(&vTemp2, &vTemp2);
	float Temp = acosf(D3DXVec3Dot(&vTemp, &vTemp2));

	if (y1 > y2)
	{
		Temp *= -1.f;
	}

	return Temp;
}

void CLineMgr::Load_Line()
{
	HANDLE		hFile = CreateFile(L"../Data/Line.dat",			// 파일 경로와 이름 명시
		GENERIC_READ,				// 파일 접근 모드 (GENERIC_WRITE 쓰기 전용, GENERIC_READ 읽기 전용)
		NULL,						// 공유방식, 파일이 열려있는 상태에서 다른 프로세스가 오픈할 때 허용할 것인가, NULL인 경우 공유하지 않는다
		NULL,						// 보안 속성, 기본값	
		OPEN_EXISTING,				// 생성 방식, CREATE_ALWAYS는 파일이 없다면 생성, 있다면 덮어 쓰기, OPEN_EXISTING 파일이 있을 경우에면 열기
		FILE_ATTRIBUTE_NORMAL,		// 파일 속성(읽기 전용, 숨기 등), FILE_ATTRIBUTE_NORMAL 아무런 속성이 없는 일반 파일 생성
		NULL);						// 생성도리 파일의 속성을 제공할 템플릿 파일, 우리는 사용하지 않아서 NULL

	if (INVALID_HANDLE_VALUE == hFile)
	{
		// 팝업 창을 출력해주는 기능의 함수
		// 1. 핸들 2. 팝업 창에 띄우고자하는 메시지 3. 팝업 창 이름 4. 버튼 속성
		MessageBox(g_hWnd, _T("Load File"), _T("Fail"), MB_OK);
		return;
	}

	// 2. 파일 쓰기

	DWORD		dwByte = 0;
	LINE		tInfo{};

	while (true)
	{
		ReadFile(hFile, &tInfo, sizeof(LINE), &dwByte, nullptr);

		if (0 == dwByte)	// 더이상 읽을 데이터가 없을 경우
			break;

		m_LineList.push_back(new CLine(tInfo));
	}


	// 3. 파일 소멸
	CloseHandle(hFile);

	MessageBox(g_hWnd, _T("Load 완료"), _T("성공"), MB_OK);
}

void CLineMgr::Create_Line(const float& _fLX, const float& _fLY, const float& _fRX, const float& _fRY)
{
	m_LineList.push_back(new CLine(LINEPOINT(_fLX, _fLY), LINEPOINT(_fRX, _fRY)));
}
