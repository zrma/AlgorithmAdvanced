#include "stdafx.h"
#include "BinarySearchTree.h"

void BinarySearchTree::Insert( int key )
{
	if ( m_Root )
	{
		Insert( key, m_Root );
	}
	else
	{
		m_Root = new Node;
		m_Root->data = key;
	}
}

Node* BinarySearchTree::Search( int key )
{
	return Search( key, m_Root );
}

void BinarySearchTree::DestroyTree()
{
	DestroyTree( m_Root );
}

void BinarySearchTree::Insert( int key, Node* node )
{
	if ( key < node->data )
	{
		if ( node->left )
		{
			Insert( key, node->left );
		}
		else
		{
			node->left = new Node;
			node->left->data = key;
		}
	}
	else if ( key >= node->data )
	{
		if ( node->right )
		{
			Insert( key, node->right );
		}
		else
		{
			node->right = new Node;
			node->right->data = key;
		}
	}
}

Node* BinarySearchTree::Search( int key, Node *node )
{
	if ( node )
	{
		if ( key == node->data )
		{
			return node;
		}
		if ( key < node->data )
		{
			return Search( key, node->left );
		}
		else
		{
			return Search( key, node->right );
		}
	}
	else
	{
		return nullptr;
	}
}

void BinarySearchTree::DestroyTree( Node *node )
{
	if ( node != nullptr )
	{
		DestroyTree( node->left );
		DestroyTree( node->right );

		delete node;
		node = nullptr;
	}
}

int BinarySearchTree::NodeCount()
{
	return NodeCount( m_Root );
}

int BinarySearchTree::NodeCount( Node *node )
{
	if ( !node )
	{
		return 0;
	}

	return NodeCount( node->left ) + NodeCount( node->right ) + 1;
}

void BinarySearchTree::BreadthFirstSearch()
{
	if ( !m_Root )
	{
		printf_s( "Queue is Empty \n" );
		return;
	}

	std::queue<Node*>	tempQueue;
	Node* tempNode = nullptr;

	tempQueue.push( m_Root );
	while ( !tempQueue.empty() )
	{
		tempNode = tempQueue.front();
		printf_s( "Data -> %d \n", tempNode->data );

		if ( tempNode->left )
		{
			tempQueue.push( tempNode->left );
		}
		if ( tempNode->right )
		{
			tempQueue.push( tempNode->right );
		}

		tempQueue.pop();
	}
}
