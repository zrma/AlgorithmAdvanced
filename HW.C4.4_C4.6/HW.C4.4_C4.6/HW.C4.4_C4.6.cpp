// HW.C4.4_C4.6.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"

struct Item
{
	Item( int weight, int value ):mWeight( weight ), mValue( value )
	{
		if ( mWeight == 0 )
		{
			mDensity = 0;
		}
		else
		{
			mDensity = mValue / mWeight;
		}
	}
	~Item() {}

	int mWeight = 0;
	int mValue = 0;
	int mDensity = 0;
};

int KnapSack01Recursion( Item* items, int count, int capacity );

float KnapSackFractional( Item* items, int count, int capacity );
bool Compare( const Item& item1, const Item& item2 );
void SortItem( Item* items, int count );

int KnapSack01ButtomUp( Item* items, int maxCount, int maxCapacity );

int _tmain(int argc, _TCHAR* argv[])
{
	Item items[] =
	{
		Item( 10, 60 ),
		Item( 20, 100 ),
		Item( 30, 120 ),
		Item( 40, 130 ),
		Item( 50, 150 ),
	};

	int count = sizeof(items) / sizeof( Item );
	int capacity = 50;

	int maxNum = KnapSack01Recursion( items, count, capacity );

	printf_s( "Recursion -> KnapSack01 : %d \n", maxNum );

	printf_s( "Press Any Key... \n" );
	getchar();

	float maxNumFloat = KnapSackFractional( items, count, capacity );

	printf_s( "Iteration -> KnapSackFractional : %.0f \n", maxNumFloat );

	printf_s( "Press Any Key... \n" );
	getchar();

	maxNum = KnapSack01ButtomUp( items, count, capacity );

	printf_s( "Bottom Up -> KnapSack01 : %d \n", maxNum );

	printf_s( "Press Any Key... \n" );
	getchar();

	return 0;
}

int KnapSack01Recursion( Item* items, int count, int capacity )
{
	// 방어 코드
	if ( count <= 0 || capacity <= 0 )
	{
		return 0;
	}

	// 용량 초과라면 애초에 빼고 계산
	if ( items[count - 1].mWeight > capacity )
	{
		return KnapSack01Recursion( items, count - 1, capacity );
	}
	// 넣을 수 있는 상황이라고 하더라도...
	else
	{

		return __max(
			// 이 녀석을 넣었을 경우와
			KnapSack01Recursion( items, count - 1, capacity ),

			// 넣지 않았을 경우를 비교해야 한다.
			KnapSack01Recursion( items, count - 1, capacity - items[count - 1].mWeight )
			+ items[count - 1].mValue );
	}
}

float KnapSackFractional( Item* items, int count, int capacity )
{
	// 가치 밀도 순서대로 정렬(내림차순)
	SortItem( items, count );

	float totalValue = 0;

	// 가장 가치 높은 것부터 빼곡히 채우자
	for ( int i = 0; i < count; ++i )
	{
		// 다 넣을 수 있을 땐 통째로 다 넣고
		if ( capacity > items[i].mWeight )
		{
			totalValue += items[i].mValue;
			capacity -= items[i].mWeight;
		}
		// 못 넣게 되면 부분만 잘라서 넣고 종료
		else
		{
			totalValue += items[i].mDensity * capacity;
			break;
		}
	}

	return totalValue;
}

bool Compare( const Item& item1, const Item& item2 )
{
	return item1.mDensity > item2.mDensity;
}

void SortItem( Item* items, int count )
{
	std::vector<Item> itemVector( items, items + count );
	std::sort( itemVector.begin(), itemVector.end(), Compare );
	
	int i = 0;
	for ( auto iter : itemVector )
	{
		items[i++] = iter;
	}
}

int KnapSack01ButtomUp( Item* items, int maxCount, int maxCapacity )
{
	// 계산의 편이성을 위해서 배열의 0을 비워두고 1부터 시작
	int** knapSackTable = new int*[maxCount + 1];

	for ( int i = 0; i < maxCount + 1; ++i )
	{
		knapSackTable[i] = new int[maxCapacity + 1];
		ZeroMemory( knapSackTable[i], sizeof( int ) * ( maxCapacity + 1 ) );
	}

	//////////////////////////////////////////////////////////////////////////
	// 배열 채워나가기
	// Longest Common Subsequence 문제를 떠올리자!
	//////////////////////////////////////////////////////////////////////////

	// 1번째 물체부터 n번째 물체까지 따져보자
	for ( int count = 1; count <= maxCount; ++count )
	{
		// 용량은 조금 무식하게 체크한다...
		// 이를테면 1kg 부터 50kg까지 1kg 단위로 뚝뚝 끊어서 배열을 모두 만든다.
		for ( int capacity = 1; capacity <= maxCapacity; ++capacity )
		{
			// 1kg부터 50kg까지의 모든 무게에 대해서 확인하자
			//
			// 현재 물체를 for loop 중의 해당 무게에 넣을 수 없으면 이 녀석의 가격 증가량은 0이다.
			if ( items[count - 1].mWeight > capacity )
			{
				knapSackTable[count][capacity] = 0;
			}
			// 현재 번째 녀석을 넣을 수 있다면...?
			else
			{
				// 아래 두 케이스를 비교해서 최대값을 현재 가격 테이블에 저장.
				knapSackTable[count][capacity] = __max(

					// 이 물체를 넣지 않았을 때의 최대 가격의 경우와
					knapSackTable[count - 1][capacity],

					// 이 물체를 넣었을 경우(는 이 물체의 가격 + 이 물체 무게를 뺀 나머지 무게로 채울 수 있는 최대 가격)로 나뉜다.
					knapSackTable[count - 1][capacity - items[count - 1].mWeight] + items[count - 1].mValue );
			}
		}
	}

	return knapSackTable[maxCount][maxCapacity];
}
