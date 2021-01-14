/// BST for event handling during make monotone part of the program.

#pragma once

#include<iostream>
#include <vector>
#include <algorithm>

#include "DCEL.hpp"

static const int ALLOWED_IMBALANCE = 1;

class EdgeNode
{
public:
	/**Some constructors.
	*/
	EdgeNode( HalfEdge* i_poElement ) : m_pElement(i_poElement), m_pLeftElement(0), m_pRightElement(0), m_pHelperVertex(i_poElement->getOrigin()), m_nHeight(0){}

	EdgeNode( HalfEdge* i_poElement, EdgeNode *i_poLeft, EdgeNode *i_poRight, int i_nHeight = 0)
	{
		m_pElement = i_poElement;
		m_pLeftElement = i_poLeft;
		m_pRightElement = i_poRight;
		m_pHelperVertex = i_poElement->getOrigin();
		m_nHeight = i_nHeight;
	}

	/**Destructor.
	*/
	~EdgeNode(){}

	EdgeNode(const EdgeNode &i_oRHSEdgeNode)
	{
		m_pElement = i_oRHSEdgeNode.m_pElement;
		m_pLeftElement = i_oRHSEdgeNode.m_pLeftElement;
		m_pRightElement = i_oRHSEdgeNode.m_pRightElement;
		m_pHelperVertex = i_oRHSEdgeNode.m_pHelperVertex;
	}

	///Operators on the objects
	EdgeNode &operator=(const EdgeNode &i_oRHSEdgeNode)
	{
		if(this != &i_oRHSEdgeNode)
		{
			m_pElement = i_oRHSEdgeNode.m_pElement;
			m_pLeftElement = i_oRHSEdgeNode.m_pLeftElement;
			m_pRightElement = i_oRHSEdgeNode.m_pRightElement;
			m_pHelperVertex = i_oRHSEdgeNode.m_pHelperVertex;
		};
		return *this;
	}

	bool operator==(const EdgeNode& i_oOtherEdgeNode)
	{
		return (*m_pElement == *(i_oOtherEdgeNode.m_pElement));
	}

	///Set and get helpers.
	void setHelper(PolyVertex* i_oHelper){ m_pHelperVertex = i_oHelper; }

	PolyVertex* getHelper() { return m_pHelperVertex; }

	HalfEdge *m_pElement;
	EdgeNode *m_pLeftElement;
	EdgeNode *m_pRightElement;
	PolyVertex *m_pHelperVertex;
	int m_nHeight;
};

/**Height of the BST.
*/
int Height(EdgeNode *i_poEdgeNode); 


class EdgeSearchTree
{
public:
	EdgeSearchTree(): m_pEdgeTreeRoot(0) {};

	/**Destructor.
	*/
	~EdgeSearchTree()
	{
		//makeEmpty();
		//if(m_pEdgeTreeRoot != nullptr)
			//cout << "Search Tree delete \n" << endl;
	};

	/**Find left most node.
	*/
	HalfEdge* FindMostLeft();

	/**Node which is the closest to left of a vertex.
	*/
	EdgeNode* FindClosestLeft(PolyVertex *i_oPolyVertex);

	/**Insert half edge.
	*/
	void InsertHalfEdge(HalfEdge* i_poHalfEdge);

	/**Remove half edge.
	*/
	void RemoveHalfEdge(HalfEdge* i_poHalfEdge);

	/**Insert edge node.
	*/
	void InsertEdgeNode(EdgeNode* i_poEdgeNode);

	/**Remove edge node.
	*/
	void RemoveEdgeNode(EdgeNode* i_poEdgeNode);

	/**Find node that holds half edge.
	*/
	EdgeNode* FindEdgeNode(HalfEdge* i_poHalfEdge);

	/**Check if empty.
	*/
	bool isEmpty() const;

	/**Empty the BST.
	*/
	void makeEmpty();

	/**Rotate with left child for balancing.
	*/
	void rotateWithLeftChild(EdgeNode *& i_poEdgeNode);

	/**Rotate with right child for balancing.
	*/
	void rotateWithRightChild(EdgeNode *& i_poEdgeNode);

	/** Double rotate with left child for balancing.
	*/
	void doubleWithLeftChild(EdgeNode *& i_poEdgeNode);

	/** Double rotate with right child for balancing.
	*/
	void doubleWithRightChild(EdgeNode *& i_poEdgeNode);

	/** Balance the BST.
	*/
	void BalanceTree(EdgeNode *& i_poEdgeNode);

private:

	/** Recursively insert half edge.
	*/
	void InsertHalfEdge(HalfEdge* i_poHalfEdge, EdgeNode *&i_oEdgeNode);

	/** Recursively remove half edge.
	*/
	void RemoveHalfEdge(HalfEdge* i_poHalfEdge, EdgeNode *&i_oEdgeNode);

	/** Recursively insert edge node.
	*/
	void InsertEdgeNode(EdgeNode* i_poNewEdgeNode, EdgeNode *&i_oEdgeNode);

	/** Recursively remove edge node.
	*/
	void RemoveEdgeNode(EdgeNode* i_poNewEdgeNode, EdgeNode *&i_oEdgeNode);

	/** Empty recursively.
	*/
	void makeEmpty( EdgeNode* &i_poEdgeNode);

	/** Return edge node that holds the half edge.
	*/
	EdgeNode*FindEdgeNode(HalfEdge* i_poHalfEdge, EdgeNode* i_poEdgeNode);

	/** Find most left edge.
	*/
	EdgeNode* FindMostLeft(EdgeNode *i_oEdgeNode);

	/** Find closest left edge.
	*/
	EdgeNode* FindClosestLeft(PolyVertex *i_oPolyVertex, EdgeNode *i_oEdgeNode);
	
	/** Member of teh search tree.
	*/
	EdgeNode *m_pEdgeTreeRoot; //root of tree
};