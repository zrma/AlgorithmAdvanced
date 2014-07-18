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

void BinarySearchTree::Insert( int key, Node* leaf )
{
	if ( key < leaf->data )
	{
		if ( leaf->left )
		{
			Insert( key, leaf->left );
		}
		else
		{
			leaf->left = new Node;
			leaf->left->data = key;
		}
	}
	else if ( key >= leaf->data )
	{
		if ( leaf->right )
		{
			Insert( key, leaf->right );
		}
		else
		{
			leaf->right = new Node;
			leaf->right->data = key;
		}
	}
}

Node* BinarySearchTree::Search( int key, Node *leaf )
{
	if ( leaf )
	{
		if ( key == leaf->data )
		{
			return leaf;
		}
		if ( key < leaf->data )
		{
			return Search( key, leaf->left );
		}
		else
		{
			return Search( key, leaf->right );
		}
	}
	else
	{
		return nullptr;
	}
}

void BinarySearchTree::DestroyTree( Node *leaf )
{
	if ( leaf != nullptr )
	{
		DestroyTree( leaf->left );
		DestroyTree( leaf->right );

		delete leaf;
		leaf = nullptr;
	}
}