#include<iostream>
#include <algorithm>
#include "BST.hpp"
#include "Partition.hpp"

using namespace std;

void EdgeSearchTree::InsertHalfEdge(HalfEdge* i_poHalfEdge)
{
	InsertHalfEdge(i_poHalfEdge, m_pEdgeTreeRoot);
};

void EdgeSearchTree::RemoveHalfEdge(HalfEdge* i_poHalfEdge)
{
	RemoveHalfEdge(i_poHalfEdge, m_pEdgeTreeRoot);
};

void EdgeSearchTree::InsertEdgeNode(EdgeNode* i_poEdgeNode)
{
	InsertEdgeNode(i_poEdgeNode, m_pEdgeTreeRoot);
};

void EdgeSearchTree::RemoveEdgeNode(EdgeNode* i_poEdgeNode)
{
	RemoveEdgeNode(i_poEdgeNode, m_pEdgeTreeRoot);
};

bool EdgeSearchTree::isEmpty() const
{
	return m_pEdgeTreeRoot == nullptr;
};

void EdgeSearchTree::makeEmpty()
{
	makeEmpty(m_pEdgeTreeRoot);
};

void EdgeSearchTree::makeEmpty( EdgeNode* &i_poEdgeNode)
{
	if(!i_poEdgeNode)
	{
		makeEmpty(i_poEdgeNode->m_pLeftElement);
		makeEmpty(i_poEdgeNode->m_pRightElement);
		delete i_poEdgeNode;
	};
	i_poEdgeNode = nullptr;
};

EdgeNode* EdgeSearchTree::FindEdgeNode(HalfEdge* i_poHalfEdge)
{
	return FindEdgeNode(i_poHalfEdge, m_pEdgeTreeRoot);
};

EdgeNode* EdgeSearchTree::FindEdgeNode(HalfEdge* i_poHalfEdge, EdgeNode* i_poEdgeNode)
{
	if(!i_poEdgeNode)
		return nullptr;
	else if(*i_poHalfEdge % *(i_poEdgeNode->m_pElement))
		return FindEdgeNode(i_poHalfEdge, i_poEdgeNode->m_pLeftElement);
	else if(*(i_poEdgeNode->m_pElement) % *i_poHalfEdge)
		return FindEdgeNode(i_poHalfEdge, i_poEdgeNode->m_pRightElement);
	else
		return i_poEdgeNode;
};

HalfEdge* EdgeSearchTree::FindMostLeft()
{
	return FindMostLeft(m_pEdgeTreeRoot)->m_pElement;
};

EdgeNode* EdgeSearchTree::FindClosestLeft(PolyVertex *i_oPolyVertex)
{
	return FindClosestLeft(i_oPolyVertex, m_pEdgeTreeRoot);
};

EdgeNode* EdgeSearchTree::FindMostLeft(EdgeNode *i_oEdgeNode)
{
	if(!i_oEdgeNode)
		return nullptr;
	if(!(i_oEdgeNode->m_pLeftElement))
		return i_oEdgeNode;
	return FindMostLeft(i_oEdgeNode->m_pLeftElement);
};


EdgeNode* EdgeSearchTree::FindClosestLeft(PolyVertex *i_oPolyVertex, EdgeNode *i_oEdgeNode)
{
	if(!i_oEdgeNode)
		return nullptr;
	else 
	{
		EdgeNode* ReturnNode = i_oEdgeNode;
		EdgeNode* CurrentNode = i_oEdgeNode;

		while(CurrentNode)
		{
			if(IsVertexLeftofEdge(i_oPolyVertex, CurrentNode->m_pElement))
				CurrentNode = CurrentNode -> m_pLeftElement;
			else
			{
				ReturnNode = CurrentNode;
				CurrentNode = CurrentNode -> m_pRightElement;
			};
		};

		return ReturnNode;
	};
};


void EdgeSearchTree::InsertHalfEdge(HalfEdge* i_poHalfEdge, EdgeNode *&i_oEdgeNode)
{
	///if(i_oEdgeNode == nullptr)
	if(!i_oEdgeNode)
	{
		i_oEdgeNode = new EdgeNode(i_poHalfEdge, nullptr, nullptr);
	}
	else if (*i_poHalfEdge % *(i_oEdgeNode->m_pElement))
		InsertHalfEdge(i_poHalfEdge, i_oEdgeNode->m_pLeftElement);
	else if (*(i_oEdgeNode->m_pElement) % *i_poHalfEdge)
		InsertHalfEdge(i_poHalfEdge, i_oEdgeNode->m_pRightElement);
	else
		;

	BalanceTree(i_oEdgeNode);
};

void EdgeSearchTree::RemoveHalfEdge(HalfEdge* i_poHalfEdge, EdgeNode *&i_oEdgeNode)
{
	if(!i_oEdgeNode)
		return; /// do nothing

	if (*i_poHalfEdge % *(i_oEdgeNode->m_pElement))
		RemoveHalfEdge(i_poHalfEdge, i_oEdgeNode->m_pLeftElement);
	else if (*(i_oEdgeNode->m_pElement) % *i_poHalfEdge)
		RemoveHalfEdge(i_poHalfEdge, i_oEdgeNode->m_pRightElement);
	else if( i_oEdgeNode->m_pLeftElement != nullptr && i_oEdgeNode->m_pRightElement != nullptr )
	{
		i_oEdgeNode->m_pElement = FindMostLeft(i_oEdgeNode->m_pRightElement)->m_pElement;
		RemoveHalfEdge(i_oEdgeNode->m_pElement,i_oEdgeNode->m_pRightElement);
	}
	else
	{
		EdgeNode *pOldNode = i_oEdgeNode;
		i_oEdgeNode = (i_oEdgeNode->m_pLeftElement != nullptr) ? i_oEdgeNode->m_pLeftElement : i_oEdgeNode->m_pRightElement;
		delete pOldNode;
	};

	BalanceTree(i_oEdgeNode);
	
};

void EdgeSearchTree::InsertEdgeNode(EdgeNode* i_poNewEdgeNode, EdgeNode *&i_oEdgeNode)
{
	if(!i_oEdgeNode)
	{
		i_oEdgeNode = i_poNewEdgeNode;
	}
	else if (*(i_poNewEdgeNode->m_pElement) % *(i_oEdgeNode->m_pElement))
		InsertEdgeNode(i_poNewEdgeNode, i_oEdgeNode->m_pLeftElement);
	else if (*(i_oEdgeNode->m_pElement) % *(i_poNewEdgeNode->m_pElement))
		InsertEdgeNode(i_poNewEdgeNode, i_oEdgeNode->m_pRightElement);
	else
		;

	BalanceTree(i_oEdgeNode);
};


void EdgeSearchTree::RemoveEdgeNode(EdgeNode* i_poNewEdgeNode, EdgeNode *&i_oEdgeNode)
{
	if(!i_oEdgeNode)
		return; /// do nothing

	if (*(i_poNewEdgeNode->m_pElement) % *(i_oEdgeNode->m_pElement))
		RemoveEdgeNode(i_poNewEdgeNode, i_oEdgeNode->m_pLeftElement);
	else if (*(i_oEdgeNode->m_pElement) % *(i_poNewEdgeNode->m_pElement))
		RemoveEdgeNode(i_poNewEdgeNode, i_oEdgeNode->m_pRightElement);
	else if( i_oEdgeNode->m_pLeftElement != nullptr && i_oEdgeNode->m_pRightElement != nullptr )
	{
		i_oEdgeNode->m_pElement = FindMostLeft(i_oEdgeNode->m_pRightElement)->m_pElement;
		i_oEdgeNode->m_pHelperVertex = FindMostLeft(i_oEdgeNode->m_pRightElement)->m_pHelperVertex;
		RemoveEdgeNode(i_oEdgeNode,i_oEdgeNode->m_pRightElement);
	}
	else
	{
		EdgeNode *pOldNode = i_oEdgeNode;
		i_oEdgeNode = (i_oEdgeNode->m_pLeftElement != nullptr) ? i_oEdgeNode->m_pLeftElement : i_oEdgeNode->m_pRightElement;
		delete pOldNode;
	};

	BalanceTree(i_oEdgeNode);
};

int Height(EdgeNode *i_poEdgeNode) 
{/// Find height of node, if null return -1
	return i_poEdgeNode == nullptr ? -1 : i_poEdgeNode->m_nHeight;
}


void EdgeSearchTree::rotateWithLeftChild(EdgeNode *& i_poEdgeNode)
{
	EdgeNode *OtherEdge = i_poEdgeNode -> m_pLeftElement;
	i_poEdgeNode->m_pLeftElement = OtherEdge->m_pRightElement;
	OtherEdge->m_pRightElement = i_poEdgeNode;

	/// adjust heights
	i_poEdgeNode->m_nHeight = max(Height(i_poEdgeNode->m_pLeftElement), Height(i_poEdgeNode->m_pRightElement)) + 1;
	OtherEdge->m_nHeight = max(Height(OtherEdge->m_pLeftElement), i_poEdgeNode->m_nHeight) + 1;

	i_poEdgeNode = OtherEdge;
};


void EdgeSearchTree::rotateWithRightChild(EdgeNode *& i_poEdgeNode)
{
	EdgeNode *OtherEdge = i_poEdgeNode -> m_pRightElement;
	i_poEdgeNode->m_pRightElement = OtherEdge->m_pLeftElement;
	OtherEdge->m_pLeftElement = i_poEdgeNode;

	/// adjust heights
	i_poEdgeNode->m_nHeight = max(Height(i_poEdgeNode->m_pLeftElement), Height(i_poEdgeNode->m_pRightElement)) + 1;
	OtherEdge->m_nHeight = max(Height(OtherEdge->m_pRightElement), i_poEdgeNode->m_nHeight) + 1;

	i_poEdgeNode = OtherEdge;
};


void EdgeSearchTree::doubleWithLeftChild(EdgeNode *& i_poEdgeNode)
{
	rotateWithRightChild(i_poEdgeNode->m_pLeftElement);
	rotateWithLeftChild(i_poEdgeNode);
};


void EdgeSearchTree::doubleWithRightChild(EdgeNode *& i_poEdgeNode)
{
	rotateWithLeftChild(i_poEdgeNode->m_pRightElement);
	rotateWithRightChild(i_poEdgeNode);
};


void EdgeSearchTree::BalanceTree(EdgeNode *& i_poEdgeNode)
{
	if(!i_poEdgeNode)
		return;

	if( Height(i_poEdgeNode->m_pLeftElement) - Height(i_poEdgeNode->m_pRightElement) > ALLOWED_IMBALANCE)
	{
		if(Height(i_poEdgeNode->m_pLeftElement->m_pLeftElement) >= Height(i_poEdgeNode->m_pLeftElement->m_pRightElement))
			rotateWithLeftChild(i_poEdgeNode);
		else
			doubleWithLeftChild(i_poEdgeNode);
	}
	else if( Height(i_poEdgeNode->m_pRightElement) - Height(i_poEdgeNode->m_pLeftElement) > ALLOWED_IMBALANCE)
	{
		if(Height(i_poEdgeNode->m_pRightElement->m_pRightElement) >= Height(i_poEdgeNode->m_pRightElement->m_pLeftElement))
			rotateWithRightChild(i_poEdgeNode);
		else
			doubleWithRightChild(i_poEdgeNode);
	};

	i_poEdgeNode->m_nHeight = max(Height(i_poEdgeNode->m_pLeftElement), Height(i_poEdgeNode->m_pRightElement)) + 1;
};

/** Determine type of vertex.
*/
unsigned int MonotonePolygon::VertexKind(PolyVertex *i_poInputVertex, PolyFace *i_poFace)
{
	HalfEdge *StartEdge = i_poInputVertex->getEdge();
	HalfEdge *IndexEdge = i_poInputVertex->getEdge();
	do{
		if(IndexEdge->getFace() == i_poFace)
			break;
		else
			IndexEdge = IndexEdge->getTwin()->getNext();
	}while(IndexEdge != StartEdge);
	///Get neighbouring Verticies. v1 = left, v2 = right.
	PolyVertex Vertex1 = *( IndexEdge->getTwin()->getOrigin());
	PolyVertex Vertex2 = *( IndexEdge->getPrev()->getOrigin());

	///Get coords of verticies to created edges.
	double *Vertex0Node = i_poInputVertex->getNode();
	double *Vertex1Node = Vertex1.getNode();
	double *Vertex2Node = Vertex2.getNode();

	/// define edge direction vectors in 2D
	double edge1[2]; 
	double edge2[2];
	edge1[0] = Vertex1Node[0] - Vertex0Node[0];
	edge1[1] = Vertex1Node[1] - Vertex0Node[1];
	edge2[0] = Vertex2Node[0] - Vertex0Node[0];
	edge2[1] = Vertex2Node[1] - Vertex0Node[1];

	/// Define dot product and determinate between two direction vectors 
	double Dot = edge1[0]*edge2[0] + edge1[1]*edge2[1];
	double Det = edge1[0]*edge2[1] - edge1[1]*edge2[0];

	double Angle = atan2(Det, Dot);

	if((Vertex1 < *i_poInputVertex)&&(Vertex2 < *i_poInputVertex))
	{
		if( Angle > 0.0)
			return START_VERTEX;
		else
			return SPLIT_VERTEX;
	}
	else if ((Vertex1 > *i_poInputVertex)&&(Vertex2 > *i_poInputVertex))
	{
		if( Angle > 0.0)
			return END_VERTEX;
		else
			return MERGE_VERTEX;
	}
	else if ((edge1[1] <= 0) && (-edge2[1] <= 0))
	{
		return REGULAR_VERTEX_LEFT;
	}
	else ///((edge1[1] > 0) && (-edge2[1] > 0));
	{
		return REGULAR_VERTEX_RIGHT;
	};
};

/** Call to private fixup funciton.
*/
void MonotonePolygon::FixUp(EdgeNode *i_poEdgeNode, PolyVertex *i_poVertex)
{/// Calls private fix up function which can alter the DCEL
	FixUp(i_poEdgeNode, i_poVertex, m_poPolygonDCEL);
};

/** Check fixup to handle merge vertex.
*/
void MonotonePolygon::FixUp(EdgeNode *i_poEdgeNode, PolyVertex *i_poVertex, DCEL *&i_poDCEL)
{
	unsigned int TYPE = VertexKind(i_poEdgeNode->getHelper(), i_poVertex->getEdge()->getFace());

	if (TYPE == MERGE_VERTEX)
	{
		PolyVertex* HelperVertex = i_poEdgeNode->getHelper();

		PolyVertex* MaxVert = GetMax(HelperVertex, i_poVertex);
		PolyVertex* MinVert = GetMin(HelperVertex, i_poVertex);
		i_poDCEL -> InsertNewEdge(MaxVert, MinVert);
	};
};

/** Handle start vertex.
*/
void MonotonePolygon::HandleStartVertex(PolyVertex *i_poInputVertex, EdgeSearchTree *&i_poTree)
{
	/// insert both incident edges
	EdgeNode *pNewEdgeLeft = new EdgeNode(i_poInputVertex->getEdge());

	/// insert these nodes into the search tree
	i_poTree->InsertEdgeNode(pNewEdgeLeft);
};

/** Handle end vertex.
*/
void MonotonePolygon::HandleEndVertex(PolyVertex *i_poInputVertex, EdgeSearchTree *&i_poTree)
{
	/// Find corresponding edge node in search tree to edge leading into vertex
	EdgeNode* PrevEdgeNode = i_poTree->FindEdgeNode(i_poInputVertex->getEdge()->getPrev());

	/// if diagonal can be added, add it
	FixUp(PrevEdgeNode, i_poInputVertex);

	/// remove edges leading into and out of vertex from search tree
	i_poTree->RemoveEdgeNode(PrevEdgeNode);
};

/** Handle split vertex.
*/
void MonotonePolygon::HandleSplitVertex(PolyVertex *i_poInputVertex, EdgeSearchTree *&i_poTree)
{
	/// Find edge closest to the left of the vertex
	EdgeNode* ClosestEdge = i_poTree->FindClosestLeft(i_poInputVertex);
	/// Get Helper vertex for this edge
	PolyVertex* HelperVertex = ClosestEdge->getHelper();

	/// Insert diagonal from helper to this vertex
	PolyVertex* MaxVert = GetMax(HelperVertex, i_poInputVertex);
	PolyVertex* MinVert = GetMin(HelperVertex, i_poInputVertex);
	m_poPolygonDCEL -> InsertNewEdge(MaxVert, MinVert);

	ClosestEdge->setHelper(i_poInputVertex);

	/// Find both edges incident to the vertex and add them to search tree
	EdgeNode *pNewEdgeRight = new EdgeNode(i_poInputVertex->getEdge());
	/// set right edge helper to current vertex
	pNewEdgeRight -> setHelper(i_poInputVertex);

	/// insert these nodes into the search tree
	i_poTree->InsertEdgeNode(pNewEdgeRight);
};

/** Handle merge vertex.
*/
void MonotonePolygon::HandleMergeVertex(PolyVertex *i_poInputVertex, EdgeSearchTree *&i_poTree)
{
	/// get edge nodes incident to vertex. They will both be in the search tree
	///EdgeNode* pLeftEdgeNode = i_poTree->FindEdgeNode(i_poInputVertex->getEdge());
	EdgeNode* pRightEdgeNode = i_poTree->FindEdgeNode(i_poInputVertex->getEdge()->getPrev());

	/// if diagonal can be added to the right edge node, add it
	FixUp(pRightEdgeNode, i_poInputVertex);

	/// remove them both from the search tree
	i_poTree->RemoveEdgeNode(pRightEdgeNode);

	/// Find edge closest to the left of the vertex
	EdgeNode* ClosestEdge = i_poTree->FindClosestLeft(i_poInputVertex);
	/// Insert Edge if Possible
	if(ClosestEdge)
		FixUp(ClosestEdge, i_poInputVertex);

	/// Set helper of the closest edge to V
	ClosestEdge->setHelper(i_poInputVertex);
};

/** Handle regular vertex on left chain.
*/
void MonotonePolygon::HandleRegularVertexLeft(PolyVertex *i_poInputVertex, EdgeSearchTree *&i_poTree)
{
	/// Find edge leading into current vertex
	/// HalfEdge* PreviousEdge = i_poInputVertex->getEdge()->getPrev();
	/// Find corresponding edge node in search tree.
	EdgeNode* PrevEdgeNode = i_poTree->FindEdgeNode(i_poInputVertex->getEdge()->getPrev());

	/// if diagonal can be added, add it
	FixUp(PrevEdgeNode, i_poInputVertex);

	/// adjust search tree
	i_poTree->RemoveEdgeNode(PrevEdgeNode);
	i_poTree->InsertHalfEdge(i_poInputVertex->getEdge());
};

/** Handle regular vertex on right chain.
*/
void MonotonePolygon::HandleRegularVertexRight(PolyVertex *i_poInputVertex, EdgeSearchTree *&i_poTree)
{
	/// Find edge closest to the left of the vertex
	EdgeNode* ClosestEdge = i_poTree->FindClosestLeft(i_poInputVertex);

	/// Insert Edge if Possible
	if(ClosestEdge)
		FixUp(ClosestEdge, i_poInputVertex);

	ClosestEdge->setHelper(i_poInputVertex);
};

/** Public make monotone.
*/
void MonotonePolygon::MakeMonotone()
{
	MakeMonotone(m_poPolygonDCEL);
};

/** Private make monotone.
*/
void MonotonePolygon::MakeMonotone(DCEL *&i_poDCEL)
{
	/// Extract vertices from DCEL
	vector<PolyVertex*> SortedVertices = i_poDCEL->getVertices();	

	/// Store them in a sorted (top to bottom) list since we do not need to add any more vertices
	sort(SortedVertices.begin(), SortedVertices.end(), PolyVertex::PolyVertexDescendingOrder());

	/// Get number of vertices.
	int nNumVertex = SortedVertices.size();

	///cout << "Creation of search tree \n" << endl;
	/// initialize an empty search tree
	EdgeSearchTree *pEdgeSearchTree = new EdgeSearchTree();

	for(int i = 0; i < nNumVertex; i++)
	{
		/// Determine what flavour of vertex we are dealing with
		unsigned int TYPE = VertexKind(SortedVertices[i], SortedVertices[i]->getEdge()->getFace());

		/// handle vertex accordingly
		switch(TYPE) 
		{
		case START_VERTEX : HandleStartVertex(SortedVertices[i], pEdgeSearchTree); break;
		case SPLIT_VERTEX : HandleSplitVertex(SortedVertices[i],pEdgeSearchTree); break;
		case END_VERTEX : HandleEndVertex(SortedVertices[i], pEdgeSearchTree); break;
		case MERGE_VERTEX : HandleMergeVertex(SortedVertices[i], pEdgeSearchTree); break;
		case REGULAR_VERTEX_LEFT : HandleRegularVertexLeft(SortedVertices[i], pEdgeSearchTree); break;
		case REGULAR_VERTEX_RIGHT : HandleRegularVertexRight(SortedVertices[i], pEdgeSearchTree); break;
		};

	}; /// end of loop

	/// delete memory allocated for the binary search tree as it is no longer needed
	delete pEdgeSearchTree;
}; /// end of makemonotone
