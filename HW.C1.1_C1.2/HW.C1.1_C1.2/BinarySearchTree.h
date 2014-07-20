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

	int		NodeCount();
	void	BreadthFirstSearch();

private:
	void	Insert( int key, Node *node );
	Node*	Search( int key, Node *node );
	void	DestroyTree( Node *node );

	int		NodeCount( Node *node );
	
	Node*	m_Root = nullptr;
};
