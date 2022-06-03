
// stdafx.cpp : 표준 포함 파일만 들어 있는 소스 파일입니다.
// 4_TeamClient.pch는 미리 컴파일된 헤더가 됩니다.
// stdafx.obj에는 미리 컴파일된 형식 정보가 포함됩니다.

#include "stdafx.h"

const int Random_Num(const int & _min, const int & _max)
{// 시드값을 얻기 위한 random_device 생성.
	std::random_device rd;

	// random_device 를 통해 난수 생성 엔진을 초기화 한다.
	std::mt19937 gen(rd());

	// _min 부터 _max 까지 균등하게 나타나는 난수열을 생성하기 위해 균등 분포 정의.
	std::uniform_int_distribution<int> dis(_min, _max);

	return dis(gen);
}
