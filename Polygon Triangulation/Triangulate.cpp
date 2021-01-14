#include "Triangulate.hpp"

using namespace std;

/** Get vertices in CCW order.
*/
vector<PolyVertex*> MonotoneTriangulation::GetAllVertices(PolyFace *i_poPolyFace)
{
	vector<PolyVertex*> AllVertices;

	HalfEdge* StartEdge = i_poPolyFace->getEdge();

	AllVertices.push_back(StartEdge->getOrigin());

	HalfEdge* IndexEdge = StartEdge->getNext();

	while( *IndexEdge != *StartEdge)
	{
		AllVertices.push_back(IndexEdge->getOrigin());

		IndexEdge = IndexEdge ->getNext();
	};

	sort(AllVertices.begin(), AllVertices.end(), PolyVertex::PolyVertexDescendingOrder());

	return AllVertices;
};

/** Get vertices in left chain.
*/
vector<PolyVertex*> MonotoneTriangulation::GetLeftChain(vector<PolyVertex*> i_oAllVertices, PolyFace *i_poPolyFace)
{
	vector<PolyVertex*> LeftChain;

	PolyVertex *LastVertex = (i_oAllVertices[i_oAllVertices.size()-1]);

	PolyVertex *IndexVertex = (i_oAllVertices[0]);

	HalfEdge *StartEdge = IndexVertex->getEdge();
	HalfEdge *IndexEdge = IndexVertex->getEdge();
	do{
		if(IndexEdge->getFace() == i_poPolyFace)
			break;
		else
			IndexEdge = IndexEdge->getTwin()->getNext();
	}while(IndexEdge != StartEdge);

	while(*IndexVertex != *LastVertex)
	{
		LeftChain.push_back(IndexVertex);

		IndexEdge = IndexEdge ->getNext();
		IndexVertex = IndexEdge->getOrigin();
	};

	LeftChain.push_back(LastVertex);

	return LeftChain;
};

/** Get vertices in right chain.
*/
vector<PolyVertex*> MonotoneTriangulation::GetRightChain(vector<PolyVertex*> i_oAllVertices, PolyFace *i_poPolyFace)
{
	vector<PolyVertex*> RightChain;

	PolyVertex *LastVertex = (i_oAllVertices[i_oAllVertices.size()-1]);

	PolyVertex *IndexVertex = (i_oAllVertices[0]);

	HalfEdge *StartEdge = IndexVertex->getEdge();
	HalfEdge *IndexEdge = IndexVertex->getEdge();
	do{
		if(IndexEdge->getFace() == i_poPolyFace)
			break;
		else
			IndexEdge = IndexEdge->getTwin()->getNext();
	}while(IndexEdge != StartEdge);

	while(*IndexVertex != *LastVertex)
	{
		RightChain.push_back(IndexVertex);

		IndexEdge = IndexEdge ->getPrev();
		IndexVertex = IndexEdge->getOrigin();
	};

	RightChain.push_back(LastVertex);

	return RightChain;
};

/** Determine if a vertex is in a chain.
*/
bool MonotoneTriangulation::IsInChain(PolyVertex *i_poVertex, vector<PolyVertex*> i_oChain)
{
	for(unsigned int i = 0; i < i_oChain.size(); i++)
	{
		if(*i_poVertex == *i_oChain[i])
			return true;
	};

	return false;

};

/** If two vertices are in same chain or not.
*/
bool MonotoneTriangulation::NotInSameChain(PolyVertex *i_poVertex1, PolyVertex *i_poVertex2, vector<PolyVertex*> i_oChain)
{
	if (IsInChain(i_poVertex1, i_oChain) && IsInChain(i_poVertex2, i_oChain))
		return false;
	else if (IsInChain(i_poVertex1, i_oChain) && !IsInChain(i_poVertex2, i_oChain))
		return true;
	else if (!IsInChain(i_poVertex1, i_oChain) && IsInChain(i_poVertex2, i_oChain))
		return true;
	else
		return false;
};

/** Loop through each monotone face and call private function to triangulate.
*/
void MonotoneTriangulation::TriangulatePolygon()
{
	int nNumFaces = m_poMonotoneDCEL->getNumFaces();

	vector<PolyFace*> Vector_Faces = m_poMonotoneDCEL->getFaces();

	for(int i = 1; i < nNumFaces; i++)
	{
		TriangulateMonotonePolygon(Vector_Faces[i], m_poMonotoneDCEL);
	};

};

/** Private function to triangulate a monotnoe polygon.
*/
void MonotoneTriangulation::TriangulateMonotonePolygon(PolyFace *&i_poPolyFace, DCEL *&io_poMonotoneDCEL)
{
	/// Sort Vertices in descending order
	vector<PolyVertex*> AllVertices = GetAllVertices(i_poPolyFace);
	/// Create Left Chain of vertices 
	vector<PolyVertex*> LeftChain = GetLeftChain(AllVertices, i_poPolyFace);
	/// Create Right Chain of vertices (not necessary?)
	vector<PolyVertex*> RightChain = GetRightChain(AllVertices, i_poPolyFace);

	/// Initialize an empty stack
	vector<PolyVertex*> VertexStack;

	int nNumVert = AllVertices.size();

	/// push top two vertices to the stack
	VertexStack.push_back(AllVertices[0]);
	VertexStack.push_back(AllVertices[1]);

	for(int i = 2; i < nNumVert - 1; i++) 
	{
		if(NotInSameChain(AllVertices[i], VertexStack[VertexStack.size()-1], LeftChain))
		{ /// Vertices are not in the same chain
			for(int j = VertexStack.size()-1; j > 0; j--)
			{
				/// Get vertex from the stack
				PolyVertex *NewVertex = VertexStack.back();

				/// create new edge
				PolyVertex* MaxVert = GetMax(AllVertices[i], NewVertex);
				PolyVertex* MinVert = GetMin(AllVertices[i], NewVertex);
				io_poMonotoneDCEL -> InsertNewEdge(MaxVert, MinVert);

				/// pop vertex from the stack
				VertexStack.pop_back();
			};

			/// pop last vertex (stack should be empty)
			VertexStack.pop_back();

			/// push last two vertices to the stack
			VertexStack.push_back(AllVertices[i-1]);
			VertexStack.push_back(AllVertices[i]);
			
		}
		else /// vertices are in the same chain
		{
			PolyVertex *TestVertex = VertexStack.back();

			VertexStack.pop_back();

			while(!VertexStack.empty())
			{
				/// Get vertex from the stack
				PolyVertex *NewVertex = VertexStack.back();

				if(IsInChain(AllVertices[i], LeftChain))
				{/// if vertex is in left chain, insert new edge if orientation > 0
					if(Orientation(TestVertex, AllVertices[i], NewVertex) > 0)
					{
						PolyVertex* MaxVert = GetMax(AllVertices[i], NewVertex);
						PolyVertex* MinVert = GetMin(AllVertices[i], NewVertex);
						io_poMonotoneDCEL -> InsertNewEdge(MaxVert, MinVert);
					}
					else
					{
						break;
					};
				}
				else
				{/// if vertex is in right chain, insert new edge if orientation < 0
					if(Orientation(TestVertex, AllVertices[i], NewVertex) < 0)
					{
						PolyVertex* MaxVert = GetMax(AllVertices[i], NewVertex);
						PolyVertex* MinVert = GetMin(AllVertices[i], NewVertex);
						io_poMonotoneDCEL -> InsertNewEdge(MaxVert, MinVert);
					}
					else
					{
						break;
					};
				};
				
				/// Switch test vertex to most recently popped
				TestVertex = NewVertex;

				/// pop it from the stack
				VertexStack.pop_back();

			};/// end of same chain loop

			/// push last verted that has been popped to stack
			VertexStack.push_back(TestVertex);

			/// push current vertex to stack
			VertexStack.push_back(AllVertices[i]);
		
		}; /// end of major conditional check
	
	}; 

	/// pop last vertex in stack
	VertexStack.pop_back();

	/// Need to connect last verted to all vertices remaining in the stack
	for(int j = VertexStack.size()-1; j > 0; j--)
	{
		/// Get vertex from the stack
		PolyVertex *NewVertex = VertexStack.back();

		/// create new edge
		PolyVertex* MaxVert = GetMax(AllVertices[AllVertices.size()-1], NewVertex);
		PolyVertex* MinVert = GetMin(AllVertices[AllVertices.size()-1], NewVertex);
		io_poMonotoneDCEL -> InsertNewEdge(MaxVert, MinVert);

		/// pop vertex from the stack
		VertexStack.pop_back();
	};

	/// triangulation complete
};