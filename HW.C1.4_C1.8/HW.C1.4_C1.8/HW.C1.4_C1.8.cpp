// HW.C1.4_C1.8.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"

void RodCuttingCombination( int totalLen, int curPos, int* isCutTable, int* valueTable, int* maxValue );
int CalcValue( int totalLen, int* isCutTable, int* valueTable );

int _tmain(int argc, _TCHAR* argv[])
{
	printf_s( "Press Any Key... \n" );
	getchar();

	// 배열 계산을 편하게 하기 위해 valueTable[0] = 0 으로 해 둠
	int valueTable[] = { 0, 1, 5, 8, 9, 10, 17, 17, 20, 24, 30 };
	
	int maxValue = 0;

	// 길이는 배열 크기 - 1
	int totalLen = sizeof( valueTable ) / sizeof( int ) - 1;

	// isCutTable은 어디를 자를지 위치를 정하는 배열이다.
	int* isCutTable = new int[totalLen];
	ZeroMemory( isCutTable, sizeof( int ) * totalLen );

	RodCuttingCombination( totalLen, 1, isCutTable, valueTable, &maxValue );

	printf_s( "Max Value = %d \n", maxValue );
	
	if ( isCutTable )
	{
		delete[] isCutTable;
		isCutTable = nullptr;
	}

	printf_s( "Press Any Key... \n" );
	getchar();

	return 0;
}

void RodCuttingCombination( int totalLen, int curPos, int* isCutTable, int* valueTable, int* maxValue )
{
	// 현재 위치 = 총 길이
	// 즉 끝까지 확인 다 했으면 isCutTable의 플래그들이 적절하게 설정 되어 있는 상태일 것이므로 값을 계산하자.
	if ( curPos == totalLen )
	{
		int totalValue = CalcValue( totalLen, isCutTable, valueTable );
		
		// isCutTable 플래그들에 의해 계산 된 값이 최대치를 갱신하는가?
		if ( totalValue > *maxValue )
		{
			printf_s( "Cut Flag = " );
			for ( int i = 0; i < totalLen; ++i )
			{
				printf_s( " %d ", isCutTable[i] );
			}
			printf_s( "\n" );

			printf_s( "Max Value Change %d -> %d \n", *maxValue, totalValue );
			*maxValue = totalValue;
		}
	}
	else
	{
		// 각각 현재 위치를 자르거나, 안 자른 상태로 다음 위치로 재귀
		//
		// isCutTable의 각 칸들을 각각 0 또는 1 로 채우는 조합이 만들어진다.
		// 2(자르거나 안 자르거나) * 2 * 2 * ..... * 2

		isCutTable[curPos] = TRUE;
		RodCuttingCombination( totalLen, curPos + 1, isCutTable, valueTable, maxValue );

		isCutTable[curPos] = FALSE;
		RodCuttingCombination( totalLen, curPos + 1, isCutTable, valueTable, maxValue );
	}
}

int CalcValue( int totalLen, int* isCutTable, int* valueTable )
{
	int prevCutPos = 0;
	int totalValue = 0;

	for ( int nowPos = 0; nowPos < totalLen; ++nowPos )
	{
		// 현재 위치가 잘렸다면
		if ( isCutTable[nowPos] == TRUE )
		{
			// 이전 잘린 위치부터 현 위치까지의 한 토막의 가격을 더하고 잘린 위치 갱신
			totalValue += valueTable[nowPos - prevCutPos];
			prevCutPos = nowPos;

			// 마치 이런 상태
			// ---- | -- | - | -----
			// 4    + 2  + 1 +  5     이런 식으로 각 잘린 토막들 가격을 더함
		}
	}

	// 마지막 토막을 빼먹지 말고 더해주자
	totalValue += valueTable[totalLen - prevCutPos];

	return totalValue;
}
