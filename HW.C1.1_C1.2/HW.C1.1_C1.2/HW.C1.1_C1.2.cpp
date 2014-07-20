/*
	HW.C1.1
	HW.C1.2

	작성자 : 131009 김덕철
*/

#include "stdafx.h"
#include "BinarySearchTree.h"

int _tmain(int argc, _TCHAR* argv[])
{
	BinarySearchTree bst;

	bst.Insert( 5 );				//					5
	bst.Insert( 3 );				//		3						9
	bst.Insert( 9 );				//	1		4			6			10
	bst.Insert( 1 );				//							7
	bst.Insert( 4 );
	bst.Insert( 6 );
	bst.Insert( 7 );
	bst.Insert( 10 );
	
	printf_s( "Node Count Number = %d \n", bst.NodeCount() );
	printf_s( "Press Any Key... \n" );
	getchar();

	Node* node = nullptr;

	for ( int i = 1; i <= 10; ++i )
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

	// 5 -> 3 -> 9 -> 1 -> 4 -> 6 -> 10 -> 7
	bst.BreadthFirstSearch();

	printf_s( "Press Any Key... \n" );
	getchar();
	return 0;
}