// HW.C4.1_C4.3.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"

struct Activity
{
	Activity(int startTime, int endTime): m_StartTime(startTime), m_EndTime(endTime) {}

	int m_StartTime = 0;
	int m_EndTime = 0;
};

int ActivitySelectionProblemRecursion( Activity* acts, int startId, int endId, int startTime, int endTime );

int ActivitySelectionProblemRecursiveGreedy( Activity* acts, int count, int firstId, int endTimeOfLastAdded );

int ActivitySelectionProblemIterativeGreedy( Activity* acts, int count );

int _tmain(int argc, _TCHAR* argv[])
{
	Activity acts[] =
	{
		Activity( 1, 4 ),
		Activity( 3, 5 ),
		Activity( 0, 6 ),
		Activity( 5, 7 ),
		Activity( 3, 9 ),
		Activity( 5, 9 ),
		Activity( 6, 10 ),
		Activity( 8, 11 ),
		Activity( 8, 12 ),
		Activity( 2, 14 ),
		Activity( 12, 16 )
	};

	int startId = 0;
	int count = sizeof( acts ) / sizeof( Activity );
	int endId = count - 1;

	int aspResult = ActivitySelectionProblemRecursion( acts, startId, endId, acts[startId].m_StartTime, acts[endId].m_EndTime );

	printf_s( "Recursion -> ASP : %d \n", aspResult );

	printf_s( "Press Any Key... \n" );
	getchar();

	aspResult = ActivitySelectionProblemRecursiveGreedy( acts, count, startId, 0 );

	printf_s( "Recursive Greedy -> ASP : %d \n", aspResult );

	printf_s( "Press Any Key... \n" );
	getchar();

	aspResult = ActivitySelectionProblemIterativeGreedy( acts, count );

	printf_s( "Iterative Greedy -> ASP : %d \n", aspResult );

	printf_s( "Press Any Key... \n" );
	getchar();

	return 0;
}

int ActivitySelectionProblemRecursion( Activity* acts, int startId, int endId, int startTime, int endTime )
{
	int maxCountOfAct = 0;

	// 시간 기준으로 for루프를 모두 돌면서 액티비티들을 상호 시간 비교 하면 비용이 너무 크다.
	// index를 함께 넘겨서 인덱스로 빠르게 잘라냄으로써 비용 절약
	if ( startId > endId )
	{
		return 0;
	}

	// 가장 작은 단위로 잘라진 종료 조건
	if ( startId == endId )
	{
		// 이 액티비티를 주어진 시간 간격 이내에 넣을 수 있는가?
		//
		// startTime <= acts[현재녀석].m_StartTime < acts[현재녀석].m_EndTime <= endTime
		//
		// 이러면 넣을 수 있는 거다.
		if ( acts[startId].m_StartTime >= startTime && acts[startId].m_EndTime <= endTime )
		{
			// 넣을 수 있다면 1 리턴
			return 1;
		}
		else
		{
			// 못 넣으면 0 리턴
			return 0;
		}
	}

	// 쭉 전채 배열을 돌면서 확인
	for ( int i = startId; i <= endId; ++i )
	{
		maxCountOfAct = __max( maxCountOfAct,

							   // 맨 앞부터 지금까지의 사이에 대해서 카운트 하고
							   ActivitySelectionProblemRecursion( acts, startId, i - 1, startTime, acts[i].m_StartTime )

							   // 현재 인덱스를 현재 위치에 넣어 보고
							   + ActivitySelectionProblemRecursion( acts, i, i, startTime, endTime )

							   // 현재 다음부터 맨 끝까지 사이에 대해서 카운트를 하고
							   + ActivitySelectionProblemRecursion( acts, i + 1, endId, acts[i].m_EndTime, endTime )

							   // 위의 값들을 더한 것들 중 맥스 카운트를 찾아서 리턴하자
							   );
	}

	return maxCountOfAct;
}

int ActivitySelectionProblemRecursiveGreedy( Activity* acts, int count, int firstId, int endTimeOfLastAdded )
{
	// 범위 초과 방어
	if ( firstId >= count )
	{
		return 0;
	}

	int nextId = firstId;

	// 직전 추가 된 Activity의 종료 시점보다 빠르게 시작하는 것은 걷어낸다.
	// 즉 겹치는 건 걷어낸다.
	while ( nextId < count && acts[nextId].m_StartTime < endTimeOfLastAdded )
	{
		++nextId;
	}

	if ( nextId == count )
	{
		// 더 이상 추가할 수가 없다!
		return 0;
	}
	else
	{
		// 현재 액티비티를 1개 더하고, 나머지 최적해를 구하자.
		return ( 1 + ActivitySelectionProblemRecursiveGreedy( acts, count, nextId + 1, acts[nextId].m_EndTime ) );
	}
}

int ActivitySelectionProblemIterativeGreedy( Activity* acts, int count )
{
	// 방어 코드
	if ( count <= 0 )
	{
		return 0;
	}

	// 가장 앞의 것 하나를 카운트 하고 들어가자
	int maxNum = 1;

	// 직전에 추가 된 Activity
	int lastInsertedActionId = 0;

	// 가장 앞의 것 하나는 채워져 있고, 앞에서부터 채워 나가는거다.
	for ( int i = 1; i < count; ++i )
	{
		// 이전 액션의 종료시점 이후에 들어갈 수 있는 가장 빠른 것을 뽑아보자.
		if ( acts[i].m_StartTime >= acts[lastInsertedActionId].m_EndTime )
		{
			// 집어 넣는다

			// 개수 증가
			++maxNum;

			// 마지막으로 추가 된 Activity 번호 갱신
			lastInsertedActionId = i;
		}
	}

	return maxNum;
}


