// HW.C3.1_C3.4.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "Exception.h"

#pragma comment(lib, "DbgHelp.lib")

int LongestCommonSubseq( const std::string& str1, int str1subLen, const std::string& str2, int str2subLen );

int LongestCommonSubseqTopDown( const std::string& str1, int str1subLen, const std::string& str2, int str2subLen );
int LongestCommonSubseqMemorization( const std::string& str1, int str1subLen, const std::string& str2, int str2subLen, int** solveMatrix );

int LongestCommonSubseqBottomUp( const std::string& str1, const std::string& str2 );
void PrintLongestCommonSubseq( const std::string& str1, int str1subLen, const std::string& str2, int str2subLen, int** sequenceMatrix );

int _tmain(int argc, _TCHAR* argv[])
{
	std::string str1 = "ABCADEFAB";
	std::string str2 = "BCAEGHABB";

	printf_s( "Recursive -> LCS : %d \n", LongestCommonSubseq( str1, str1.length(), str2, str2.length() ) );

	printf_s( "Press Any Key... \n" );
	getchar();

	printf_s( "Top Down -> LCS : %d \n", LongestCommonSubseqTopDown( str1, str1.length(), str2, str2.length() ) );

	printf_s( "Press Any Key... \n" );
	getchar();

	printf_s( "Bottom Up -> LCS : %d \n", LongestCommonSubseqBottomUp( str1, str2 ) );

	printf_s( "Press Any Key... \n" );
	getchar();

	return 0;
}

//////////////////////////////////////////////////////////////////////////
// 기본 아이디어
//
// 뒤에서부터 한 글자씩 비교하면서 같으면 카운트 1 증가
//
// 다르면 한쪽 기준으로 잡고 다른 쪽을 앞으로 당겨가면서 비교 해본다 ( x2 회 )
// (A set과 B set이 있다고 치면 A set을 앞으로 했을 때, B 셋을 앞으로 했을 때를 또 비교함
//////////////////////////////////////////////////////////////////////////
int LongestCommonSubseq( const std::string& str1, int str1subLen, const std::string& str2, int str2subLen )
{
	if ( str1subLen == 0 || str2subLen == 0 )
	{
		return 0;
	}

	int lcsLen = 0;

	// 두 set의 현재 번째가 같을 경우
	if ( str1.at( str1subLen - 1 ) == str2.at( str2subLen - 1 ) )
	{
		// 카운터를 1 증가 시키고 두 set 모두 앞으로 한 칸 이동해서 다시 확인 ㄱㄱ
		lcsLen = LongestCommonSubseq( str1, str1subLen - 1, str2, str2subLen - 1 ) + 1;
	}
	// 다를 경우
	else
	{
		// A set을 당겨 보았을 때와 B set을 당겨 보았을 때를 상호 비교해서 더 긴쪽을 채택
		lcsLen = __max( LongestCommonSubseq( str1, str1subLen, str2, str2subLen - 1 ),
						LongestCommonSubseq( str1, str1subLen - 1, str2, str2subLen ) );
	}

	return lcsLen;
}

int LongestCommonSubseqTopDown( const std::string& str1, int str1subLen, const std::string& str2, int str2subLen )
{
	// 방어 코드
	if ( str1subLen < 0 || str2subLen < 0 )
	{
		return 0;
	}

	// 계산을 편하게 하기 위해서 배열에 +1씩 해둠
	int** solMatrix = new int*[str1subLen + 1];

	for ( int i = 0; i <= str1subLen; ++i )
	{
		solMatrix[i] = new int[str2subLen + 1];
		
		for ( int j = 0; j <= str2subLen; ++j )
		{
			solMatrix[i][j] = -1;
		}
	}

	int lcsLen = LongestCommonSubseqMemorization( str1, str1subLen, str2, str2subLen, solMatrix );

	if ( solMatrix )
	{
		for ( int i = 0; i <= str1subLen; ++i )
		{
			if ( solMatrix[i] )
			{
				delete[] solMatrix[i];
				solMatrix[i] = nullptr;
			}
		}

		delete[] solMatrix;
		solMatrix = nullptr;
	}

	return lcsLen;
}

int LongestCommonSubseqMemorization( const std::string& str1, int str1subLen, const std::string& str2, int str2subLen, int** solveMatrix )
{
	if ( solveMatrix[str1subLen][str2subLen] != -1 )
	{
		return solveMatrix[str1subLen][str2subLen];
	}

	if ( str1subLen == 0 || str2subLen == 0 )
	{
		solveMatrix[str1subLen][str2subLen] = 0;
		return 0;
	}

	int lcsLen = 0;

	if ( str1.at( str1subLen - 1 ) == str2.at( str2subLen - 1 ) )
	{
		lcsLen = LongestCommonSubseqMemorization( str1, str1subLen - 1, str2, str2subLen - 1, solveMatrix ) + 1;
	}
	else
	{
		lcsLen = __max( LongestCommonSubseqMemorization( str1, str1subLen, str2, str2subLen - 1, solveMatrix ),
						LongestCommonSubseqMemorization( str1, str1subLen - 1, str2, str2subLen, solveMatrix ) );
	}

	solveMatrix[str1subLen][str2subLen] = lcsLen;

	return lcsLen;
}

enum SequenceType : int
{
	ST_NONE = 0,
	ST_BOTH,
	ST_STR1,
	ST_STR2
};

int LongestCommonSubseqBottomUp( const std::string& str1, const std::string& str2 )
{
	// 계산을 편하게 하기 위해서 배열에 +1씩 해둠
	int** solMatrix = new int*[str1.length() + 1];

	for ( size_t i = 0; i <= str1.length(); ++i )
	{
		solMatrix[i] = new int[str2.length() + 1];

		for ( size_t j = 0; j <= str2.length(); ++j )
		{
			solMatrix[i][j] = 0;
		}
	}

	int** sequenceMatrix = new int*[str1.length() + 1];

	for ( size_t i = 0; i <= str1.length(); ++i )
	{
		sequenceMatrix[i] = new int[str2.length() + 1];

		for ( size_t j = 0; j <= str2.length(); ++j )
		{
			sequenceMatrix[i][j] = ST_NONE;
		}
	}

	// std::string str1 = "ABCADEFAB";
	// std::string str2 = "BCAEGHABB";

	//////////////////////////////////////////////////////////////////////////
	// 배열 채워나가기
	//   j  0  1  2  3  4  5  6  7  8  9
	// i   yj  B  C  A  E  G  H  A  B  B
	//
	// 0 xi 0  0  0  0  0  0  0  0  0  0  <- 초기화 0으로
	//
	// 1 A  0  0  0  1  1  1  1  1  1  1  <- (xi == yi이면 대각 왼쪽에서 +1을 하고, 아니면 위와 좌측 중 큰 값을 취한다)
	//       \\
	// 2 B  0  1  1  1  1  1  1  1  2  2  <- 같을 경우 대각으로 타고 내려가고 있음
	//          \\
	// 3 C  0  1  2  2  2  2  2  2  2  2
	//             \\
	// 4 A  0  1  2  3  3  3  3  3  3  3
	//               |
	// 5 D  0  1  2  3  3  3  3  3  3  3  <- 다를 경우 큰 쪽을 취함
	//                \\
	// 6 E  0  1  2  3  4--4--4  4  4  4
	//                        |
	// 7 F  0  1  2  3  4  4  4  4  4  4
	//                         \\
	// 8 A  0  1  2  3  4  4  4  5--5  5
	//                               \\
	// 9 B  0  1  2  3  4  4  4  5  6  6  <- 최종 값은 6이다!
	//
	// Top Down으로 문제 크기가 작아지는 과정과 Bottom Up으로 배열을 채우는 과정은 같은 모양, 반대 방향이다.

	for ( size_t str1SubLen = 1; str1SubLen <= str1.length(); ++str1SubLen )
	{
		for ( size_t str2SubLen = 1; str2SubLen <= str2.length(); ++str2SubLen )
		{
			if ( str1.at( str1SubLen - 1 ) == str2.at( str2SubLen - 1 ) )
			{
				// 문자가 같으면 대각 방향으로 +1 진행
				solMatrix[str1SubLen][str2SubLen] = solMatrix[str1SubLen - 1][str2SubLen - 1] + 1;

				// 대각 방향 진행이다
				sequenceMatrix[str1SubLen][str2SubLen] = ST_BOTH;
			}
			else
			{
				// 문자가 다르면 큰 값을 취해서 진행
				if ( solMatrix[str1SubLen - 1][str2SubLen] > solMatrix[str1SubLen][str2SubLen - 1] )
				{
					solMatrix[str1SubLen][str2SubLen] = solMatrix[str1SubLen - 1][str2SubLen];

					// str1 방향 진행이다
					sequenceMatrix[str1SubLen][str2SubLen] = ST_STR1;
				}
				else
				{
					solMatrix[str1SubLen][str2SubLen] = solMatrix[str1SubLen][str2SubLen - 1];

					// str2 방향 진행이다.
					sequenceMatrix[str1SubLen][str2SubLen] = ST_STR2;
				}
			}
		}
	}

	int lcsLen = solMatrix[str1.length()][str2.length()];

	PrintLongestCommonSubseq( str1, str1.length(), str2, str2.length(),sequenceMatrix );
	printf_s( "\n" );
	printf_s( "\n" );

	if ( solMatrix )
	{
		for ( size_t i = 0; i <= str1.length(); ++i )
		{
			if ( solMatrix[i] )
			{
				delete[] solMatrix[i];
				solMatrix[i] = nullptr;
			}
		}

		delete[] solMatrix;
		solMatrix = nullptr;
	}

	if ( sequenceMatrix )
	{
		for ( size_t i = 0; i <= str1.length(); ++i )
		{
			if ( sequenceMatrix[i] )
			{
				delete[] sequenceMatrix[i];
				sequenceMatrix[i] = nullptr;
			}
		}

		delete[] sequenceMatrix;
		sequenceMatrix = nullptr;
	}

	return lcsLen;
}

void PrintLongestCommonSubseq( const std::string& str1, int str1subLen, const std::string& str2, int str2subLen, int** sequenceMatrix )
{
	// 방어 코드!
	if ( str1subLen == 0 || str2subLen == 0 )
	{
		return;
	}

	// 진행 방향 저장 해 둔 것대로 리커시브하게 순회
	switch ( sequenceMatrix[str1subLen][str2subLen] )
	{
		// 같을 경우만 출력 해 주자
		case ST_BOTH:
			PrintLongestCommonSubseq( str1, str1subLen - 1, str2, str2subLen - 1, sequenceMatrix );
			printf_s( "%c", str1.at( str1subLen - 1 ) );
			break;

		case ST_STR1:
			PrintLongestCommonSubseq( str1, str1subLen - 1, str2, str2subLen, sequenceMatrix );
			break;

		case ST_STR2:
			PrintLongestCommonSubseq( str1, str1subLen, str2, str2subLen - 1, sequenceMatrix );
			break;

		default:
			CRASH_ASSERT( false );
			break;
	}
}
