// HW.C2.1_C2.4.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"

#define ROW(x) matrixChain[x - 1]
#define COL(x) matrixChain[x]

int CalcMinCostMatrixChain( int* matrixChain, int firstMatrix, int lastMatrix );

int CalcMatrixChainTopDown( int* matrixChain, int firstMatrix, int lastMatrix );
int CalcMatrixChainMemorization( int* matrixChain, int firstMatrix, int lastMatrix, int** resultMatrix );

int CalcMatrixChainBottomUp( int* matrixChain, int totalLength );
void PrintOptimalParenthesis( int** cutPosition, int startIndex, int endIndex );

int _tmain(int argc, _TCHAR* argv[])
{
	// 3x7 7x4 4x2 .... 4x3 3x4 매트릭스 체인에서
	// 중첩 되는 부분을 줄여서 하나의 배열로 만든다.
	int matrixChain[] = { 3, 7, 4, 2, 4, 6, 4, 3, 4 };

	printf_s( "Press Any Key... \n" );
	getchar();

	printf_s( "Recursion -> Minimum Coast : %d \n", CalcMinCostMatrixChain( matrixChain, 1, 8 ) );
	printf_s( "Press Any Key... \n" );
	getchar();

	printf_s( "Top Down -> Minimum Coast : %d \n", CalcMatrixChainTopDown( matrixChain, 1, 8 ) );
	printf_s( "Press Any Key... \n" );
	getchar();

	printf_s( "Bottom Up -> Minimum Coast : %d \n", CalcMatrixChainBottomUp( matrixChain, 8 ) );
	printf_s( "Press Any Key... \n" );
	getchar();

	return 0;
}

int CalcMinCostMatrixChain( int* matrixChain, int firstMatrix, int lastMatrix )
{
	// 단일 배열은 곱셈 Cost가 없음
	if ( firstMatrix == lastMatrix )
	{
		return 0;
	}

	// 초기값 - 적어도 맨 앞의 한 배열과 나머지 전체 토막 배열을 곱하는 비용 만큼은 지불해야 되겠지?
	int minCost = CalcMinCostMatrixChain( matrixChain, firstMatrix + 1, lastMatrix )
		+ ROW( firstMatrix ) * COL( firstMatrix ) * COL( lastMatrix );

	// 쭉 돌아가면서 더 작은 매트릭스 체인으로 나눠 곱할 비용을 계산해 봅시다.
	for ( int firstBoundary = firstMatrix + 1; firstBoundary < lastMatrix; ++firstBoundary )
	{
		// 대략 이러하다. 위의 테스트 케이스에서 보면
		//
		// 3 7 4 2 .... 4 3 4
		// 이런 배열에서 결과적으로
		//
		// 3x7 4x4 매트릭스의 형태로 곱해지게 된다면
		// 3x7 | 4x2 2x4 의 형태로...
		// 3x7 | 4x2 | 2x4 4x4 의 형태로...
		//
		// 이런 식으로 계속 쪼개나가게 될 것이다.

		// 이번에 쪼갠 왼쪽 부분하고 오른쪽 부분의 계산 비용을 더하고, 두 녀석을 곱하는데 드는 비용을 더하자.
		int cost = CalcMinCostMatrixChain( matrixChain, firstMatrix, firstBoundary )
			+ CalcMinCostMatrixChain( matrixChain, firstBoundary + 1, lastMatrix )
			+ ROW( firstMatrix ) * COL( firstBoundary ) * COL( lastMatrix );

		// 작다면 최소값을 갱신
		minCost = __min( minCost, cost );
	}

	return minCost;
}

int CalcMatrixChainTopDown( int* matrixChain, int firstMatrix, int lastMatrix )
{
	if ( firstMatrix == lastMatrix || lastMatrix <= 0 || firstMatrix < 0)
	{
		return 0;
	}

	int** resultMatrix = new int*[lastMatrix + 1];

	for ( int i = 0; i <= lastMatrix; ++i )
	{
		resultMatrix[i] = new int[lastMatrix + 1];

		for ( int j = 0; j <= lastMatrix; ++j )
		{
			resultMatrix[i][j] = -1;
		}
	}

	int minCost = CalcMatrixChainMemorization( matrixChain, firstMatrix, lastMatrix, resultMatrix );

	if ( resultMatrix )
	{
		for ( int i = 0; i <= lastMatrix; ++i )
		{
			delete[] resultMatrix[i];
			resultMatrix[i] = nullptr;
		}

		delete[] resultMatrix;
		resultMatrix = nullptr;
	}

	return minCost;
}

int CalcMatrixChainMemorization( int* matrixChain, int firstMatrix, int lastMatrix, int** resultMatrix )
{
	// 계산 결과가 이미 있다면 재활용
	if ( resultMatrix[firstMatrix][lastMatrix] != -1 )
	{
		return resultMatrix[firstMatrix][lastMatrix];
	}

	if ( firstMatrix == lastMatrix )
	{
		resultMatrix[firstMatrix][lastMatrix] = 0;
		return 0;
	}
	
	resultMatrix[firstMatrix][lastMatrix] = CalcMinCostMatrixChain( matrixChain, firstMatrix + 1, lastMatrix )
		+ ROW( firstMatrix ) * COL( firstMatrix ) * COL( lastMatrix );

	for ( int firstBoundary = firstMatrix + 1; firstBoundary < lastMatrix; ++firstBoundary )
	{
		int cost = CalcMinCostMatrixChain( matrixChain, firstMatrix, firstBoundary )
			+ CalcMinCostMatrixChain( matrixChain, firstBoundary + 1, lastMatrix )
			+ ROW( firstMatrix ) * COL( firstBoundary ) * COL( lastMatrix );

		// minCost를 이제는 배열로 대체하고, 배열의 결과는 있다면 재활용한다!
		resultMatrix[firstMatrix][lastMatrix] = __min( resultMatrix[firstMatrix][lastMatrix], cost );
	}

	return resultMatrix[firstMatrix][lastMatrix];
}

int CalcMatrixChainBottomUp( int* matrixChain, int totalLength )
{
	if ( totalLength == 0 )
	{
		return 0;
	}

	int** cutPosition = new int*[totalLength];

	for ( int i = 0; i < totalLength; ++i )
	{
		cutPosition[i] = new int[totalLength];

		for ( int j = 0; j < totalLength; ++j )
		{
			cutPosition[i][j] = 0;
		}
	}

	int** resultMatrix = new int*[totalLength];

	for ( int i = 0; i < totalLength; ++i )
	{
		resultMatrix[i] = new int[totalLength];

		for ( int j = 0; j < totalLength; ++j )
		{
			resultMatrix[i][j] = 0;
		}
	}
		
	// BottomUp - 2차원 배열을 채워나가는 문제
	//      0   1   2   3   4   5   6   7   <- endIndex
	//   0 [1] [2] [3] [4] [5] [6] [7] [8]
	//   1 [ ] [1] [2] [ ] [ ] [ ] [ ] [7]
	//   2 [ ] [ ] [1] [2] [ ] [ ] [ ] [6]
	//   3 [ ] [ ] [ ] [1] [2] [ ] [ ] [5]
	//   4 [ ] [ ] [ ] [ ] [1] [2] [ ] [4]  매트릭스 원소 채우는 순서(랄까 루프 반복 수랄까)
	//   5 [ ] [ ] [ ] [ ] [ ] [1] [2] [3]
	//   6 [ ] [ ] [ ] [ ] [ ] [ ] [1] [2]
	//   7 [ ] [ ] [ ] [ ] [ ] [ ] [ ] [1]
	// startIndex
	//


	// distance가 증가할수록 startIndex는 작은 범위를 돌 것이다.
	// 위의 도표에서 1번째는 맨 위에서 사실상 초기화 한 0 값이다.
	//
	// 2(distance = 1)번째는 0부터 7 - 1 (totalLength - 1 - distance) 까지 돈다
	// 3(distance = 1)번째는 0부터 7 - 2 (totalLength - 1 - distance) 까지 돈다
	// ...
	// 8(distance = 7)번째는 0부터 7 - 7 (totalLength - 1 - distance) 까지 돈다.
	//
	// distance 는 1부터 7까지 증가 (0은 대각선을 채우는 부분으로 위에서 패스
	for ( int distance = 1; distance < totalLength; ++distance )
	{
		// startIndex는 0부터 (totalLength - 1 - distance) 까지 순회
		for ( int startIndex = 0; startIndex < totalLength - distance; ++startIndex )
		{
			// endIndex는 startIndex부터 0, 1, 2, .... 7 (totalLength - 1) 까지 돈다.
			int endIndex = startIndex + distance;

			// 이 부분은 최소한의 계산을 해야 하는 값을 미리 설정
			resultMatrix[startIndex][endIndex] = resultMatrix[startIndex + 1][endIndex]
				+ ROW( startIndex + 1 ) * COL( startIndex + 1 ) * COL( endIndex + 1 );

			// 밑에서 갱신 되지 않는다면 일단 초기는 startIndex에서 자름
			cutPosition[startIndex][endIndex] = startIndex;

			// Recursion으로 구현했던 부분과 동일
			for ( int firstBoundary = startIndex + 1; firstBoundary < endIndex; ++firstBoundary )
			{
				int cost = resultMatrix[startIndex][firstBoundary] + resultMatrix[firstBoundary + 1][endIndex]
					+ ROW( startIndex + 1 ) * COL( firstBoundary + 1 ) * COL( endIndex + 1 );

				// 배열을 채워나가자
				if ( cost < resultMatrix[startIndex][endIndex] )
				{
					resultMatrix[startIndex][endIndex] = __min( resultMatrix[startIndex][endIndex], cost );

					// 자른 부분 기억하자!
					cutPosition[startIndex][endIndex] = firstBoundary;
				}
			}
		}
	}

	for ( int i = 0; i < totalLength; ++i )
	{
		for ( int j = 0; j < totalLength; ++j )
		{
			printf_s( "%4d ", resultMatrix[i][j] );
		}

		printf_s( "\n" );
	}

	// 출력 해 볼까?
	printf_s( "\n" );
	PrintOptimalParenthesis( cutPosition, 0, totalLength -1 );
	printf_s( "\n" );
	printf_s( "\n" );

	// 가장 마지막 채워진 [0][7] 원소가 최종 값이다.
	int minCost = resultMatrix[0][totalLength - 1];

	if ( resultMatrix )
	{
		for ( int i = 0; i < totalLength; ++i )
		{
			delete[] resultMatrix[i];
			resultMatrix[i] = nullptr;
		}

		delete[] resultMatrix;
		resultMatrix = nullptr;
	}

	if ( cutPosition )
	{
		for ( int i = 0; i < totalLength; ++i )
		{
			delete[] cutPosition[i];
			cutPosition[i] = nullptr;
		}

		delete[] resultMatrix;
		cutPosition = nullptr;
	}

	return minCost;
}

void PrintOptimalParenthesis( int** cutPosition, int startIndex, int endIndex )
{
	// 종료 조건 체크
	if ( startIndex == endIndex )
	{
		// 행렬이 하나일 땐 바로 출력
		printf_s( " A%d ", startIndex );
	}
	else
	{
		printf_s( " (" );

		// cutPosition[startIndex][endIndex]가 바로 startIndex~endIndex에서 잘라야 할 지점이다!
		//
		// startIndex ~ 자를 부분까지 출력하자
		PrintOptimalParenthesis( cutPosition, startIndex, cutPosition[startIndex][endIndex] );

		// (자른 부분 + 1) ~ endIndex, 즉 남은 부분을 출력하자
		PrintOptimalParenthesis( cutPosition, cutPosition[startIndex][endIndex] + 1, endIndex );

		printf_s( ") " );
	}
}