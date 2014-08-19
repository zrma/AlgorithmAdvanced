/*
	HW.C1.3

	작성자 : 131009 김덕철
*/

#include "stdafx.h"

#define TEST_NUMBER		35
#define NOT_A_NUMBER	-1

int FiboByRecursion( int n );
int FiboByTopDown( int n, int* array );
int FiboByBottomUp( int n );

int _tmain( int argc, _TCHAR* argv[] )
{
	printf_s( "Recursion Fibo(%d) : %d \n", TEST_NUMBER, FiboByRecursion( TEST_NUMBER ) );
	
	int* array = new int[TEST_NUMBER + 1];
	
	memset( array, NOT_A_NUMBER, sizeof( int )*( TEST_NUMBER + 1 ) );
	printf_s( "Top Down  Fibo(%d) : %d \n", TEST_NUMBER, FiboByTopDown( TEST_NUMBER, array ) );
	
	delete[] array;

	printf_s( "Bottom Up Fibo(%d) : %d \n", TEST_NUMBER, FiboByBottomUp( TEST_NUMBER ) );
	
	printf_s( "Press Any Key... \n" );
	getchar();

	return 0;
}

int FiboByRecursion( int n )
{
	if ( n < 2 )
	{
		return n;
	}

	return FiboByRecursion( n - 1 ) + FiboByRecursion( n - 2 );
}

int FiboByTopDown( int n, int* array )
{
	if ( array[n] != NOT_A_NUMBER )
	{
		return array[n];
	}

	if ( n < 2 )
	{
		array[n] = n;
	}
	else
	{
		array[n] = FiboByTopDown( n - 1, array ) + FiboByTopDown( n - 2, array );
	}

	return array[n];
}

int FiboByBottomUp( int n )
{
	int* array = new int[n + 1];
	ZeroMemory( array, sizeof( int ) * ( n + 1 ) );

	array[0] = 0;
	array[1] = 1;

	for ( int i = 2; i <= n; ++i )
	{
		array[i] = array[i - 1] + array[i - 2];
	}

	int result = array[n];
	delete[] array;

	return result;
}

