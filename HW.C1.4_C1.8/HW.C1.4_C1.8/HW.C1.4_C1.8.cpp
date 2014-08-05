// HW.C1.4_C1.8.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"

#ifdef _DEBUG
#include <crtdbg.h>
#endif // _DEBUG


int CuttingRodWithCombination( int* valueTable, int totalLen );

void CuttingRodCombinationRecursive( int totalLen, int curPos, int* isCutTable, int* valueTable, int* maxValue );
int CalcValue( int totalLen, int* isCutTable, int* valueTable );

int CuttingRodRecursive( int* valueTable, int totalLen );

int CuttingRodTopDown( int* valueTable, int totalLen );
int CuttingRodTopDownRecursive( int* valueTable, int totalLen, int* memoryTable );

int _tmain(int argc, _TCHAR* argv[])
{
	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );

	// 배열 계산을 편하게 하기 위해 valueTable[0] = 0 으로 해 둠
	int valueTable[] = { 0, 1, 5, 8, 9, 10, 17, 17, 20, 24, 30 };

	// 길이는 배열 크기 - 1
	int totalLen = sizeof( valueTable ) / sizeof( int ) - 1;
	
	printf_s( "Press Any Key... \n" );
	getchar();

	printf_s( "Combination - Max Value = %d \n", CuttingRodWithCombination( valueTable, totalLen) );
	printf_s( "Press Any Key... \n" );
	getchar();

	printf_s( "Recursive - Max Value = %d \n", CuttingRodRecursive( valueTable, totalLen ) );
	printf_s( "Press Any Key... \n" );
	getchar();

	printf_s( "Top Down - Max Value = %d \n", CuttingRodTopDown( valueTable, totalLen ) );
	printf_s( "Press Any Key... \n" );
	getchar();
	
	return 0;
}

int CuttingRodWithCombination( int* valueTable, int totalLen )
{
	int maxValue = 0;

	// isCutTable은 어디를 자를지 위치를 정하는 배열이다.
	int* isCutTable = new int[totalLen];
	ZeroMemory( isCutTable, sizeof( int ) * totalLen );

	CuttingRodCombinationRecursive( totalLen, 1, isCutTable, valueTable, &maxValue );

	if ( isCutTable )
	{
		delete[] isCutTable;
		isCutTable = nullptr;
	}

	return maxValue;
}

void CuttingRodCombinationRecursive( int totalLen, int curPos, int* isCutTable, int* valueTable, int* maxValue )
{
	// 현재 위치 = 총 길이
	// 즉 끝까지 확인 다 했으면 isCutTable의 플래그들이 적절하게 설정 되어 있는 상태일 것이므로 값을 계산하자.
	if ( curPos == totalLen )
	{
		*maxValue = __max( *maxValue, CalcValue( totalLen, isCutTable, valueTable ) );
	}
	else
	{
		// 각각 현재 위치를 자르거나, 안 자른 상태로 다음 위치로 재귀
		//
		// isCutTable의 각 칸들을 각각 0 또는 1 로 채우는 조합이 만들어진다.
		// 2(자르거나 안 자르거나) * 2 * 2 * ..... * 2

		isCutTable[curPos] = TRUE;
		CuttingRodCombinationRecursive( totalLen, curPos + 1, isCutTable, valueTable, maxValue );

		isCutTable[curPos] = FALSE;
		CuttingRodCombinationRecursive( totalLen, curPos + 1, isCutTable, valueTable, maxValue );
	}
}

int CalcValue( int totalLen, int* isCutTable, int* valueTable )
{
	int prevCutPos = 0;
	int totalValue = 0;

	for ( int nowPos = 1; nowPos < totalLen; ++nowPos )
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

	// 마지막 토막을 빼먹지 말고 더해주자 (바운더리 컨디션 중요!)
	//
	// valueTable은 [0]을 포함한 [1]~[10] 까지의 11개	->	실제 길이는 1~10까지
	// isCutTable은 어디를 자를래?						->	[1]~[9]까지 9군데
	totalValue += valueTable[totalLen - prevCutPos];

	return totalValue;
}

int CuttingRodRecursive( int* valueTable, int totalLen )
{
	int maxValue = -1;
	
	// 종료 조건
	if ( totalLen == 0 )
	{
		return 0;
	}

	// 왼쪽을 1부터 잘라본다.
	for ( int leftPieceLen = 1; leftPieceLen <= totalLen; ++leftPieceLen )
	{
		// 왼쪽을 자르고 남은 나머지 부분(오른쪽 부분)은 계속 잘라나가면서 최대값을 반환할 것이다.
		//
		// 막대를 맨 왼쪽부터 차례대로 잘라보고, 오른쪽 결과값이 나온 부분과 그 수를 더하는 방식으로
		// 최종적으로 for 루프를 다 돌고 나면 그 최대값이 반환 될 것이다.
		//
		// valueTable[leftPieceLen]이 최대값이 아닌 경우는 어떻게 되나?
		//
		// 결국 valueTable[leftPieceLen]이 최대값이 아니란 이야기는 이 녀석(왼쪽 부분)을 더 자를 수 있다는 소리고,
		// 그렇게 더 자른 부분은 leftPiceLen이 더 작았던 for문의 이전 타이밍에서 체크 하고 왔을 것이다.
		//
		// 그렇게 되면 현재 __max() 비교식에서 패스 될 것임
		maxValue = __max( maxValue, valueTable[leftPieceLen] + CuttingRodRecursive( valueTable, totalLen - leftPieceLen ) );
	}

	return maxValue;
}


int CuttingRodTopDown( int* valueTable, int totalLen )
{
	// 이 부분을 놓치면 아래 new int[0]을 시도함! <- 위험!
	if ( totalLen == 0 )
	{
		return 0;
	}

	int* memoryTable = new int[totalLen + 1];
	memset( memoryTable, -1, sizeof(int) * (totalLen + 1) );

	int maxValue = CuttingRodTopDownRecursive( valueTable, totalLen, memoryTable );

	if ( memoryTable )
	{
		delete[] memoryTable;
		memoryTable = nullptr;
	}

	return maxValue;
}

int CuttingRodTopDownRecursive( int* valueTable, int totalLen, int* memoryTable )
{
	// 만약 이미 계산이 되어 있으면 재활용
	if ( memoryTable[totalLen] != -1 )
	{
		return memoryTable[totalLen];
	}

	// 종료 조건
	if ( totalLen == 0 )
	{
		return 0;
	}

	int maxValue = -1;

	// 왼쪽을 1부터 잘라본다.
	for ( int leftPieceLen = 1; leftPieceLen <= totalLen; ++leftPieceLen )
	{
		maxValue = __max( maxValue, valueTable[leftPieceLen] + CuttingRodTopDownRecursive( valueTable, totalLen - leftPieceLen, memoryTable ) );
	}

	memoryTable[totalLen] = maxValue;

	return maxValue;
}

