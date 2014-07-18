// HW.C1.1.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"

#include "BinarySearchTree.h"

int _tmain(int argc, _TCHAR* argv[])
{
	BinarySearchTree bst;

	for ( int i = 0; i < 20; ++i )
	{
		bst.Insert( i );
	}

	Node* node = nullptr;

	for ( int i = 0; i < 30; i += 2 )
	{
		node = bst.Search( i );

		if ( node )
		{
			printf_s( "Search %d and Result is %d \n", i, node->data );

			if ( node->data != i )
			{
				assert( false );
				printf_s( "Search Data and Result is not Match Error \n" );
			}
		}
		else
		{
			printf_s( "There is not %d in BST \n", i );
		}
	}
	
	printf_s( "Press Any Key... \n" );
	getchar();
	return 0;
}