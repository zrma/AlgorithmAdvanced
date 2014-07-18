#pragma once


#define NOT_A_NUMBER	INT_MAX

struct Node
{
	int		data = NOT_A_NUMBER;
	Node	*left = nullptr;
	Node	*right = nullptr;
};

class BinarySearchTree
{
public:
	BinarySearchTree() { }
	~BinarySearchTree() { DestroyTree(); }

	void	Insert( int key );
	Node*	Search( int key );
	void	DestroyTree();

private:
	void	Insert( int key, Node *leaf );
	Node*	Search( int key, Node *leaf );
	void	DestroyTree( Node *leaf );

	Node*	m_Root = nullptr;
};
