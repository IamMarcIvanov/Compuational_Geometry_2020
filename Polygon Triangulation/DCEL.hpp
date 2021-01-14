#pragma once

#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>

using namespace std;

class HalfEdge;
class PolyFace;

/** Contains info about the vertices of the DCEL
*/
class PolyVertex
{

public:
	/** Default constructor.
	*/
	PolyVertex()
	{
		m_adNode[0] = 0;
		m_adNode[1] = 0;
		m_pEdge = 0;
	}

	/** Constructs from two points.
	*/
	explicit PolyVertex(double* i_adNode)
	{
		for(int i = 0; i < 2; i++)
		{
			m_adNode[i] = i_adNode[i];
		}

		m_pEdge = 0;
	}

	/** Construct from two coordinates.
	*/
	PolyVertex(double i_dCoorX, double i_dCoorY)
	{
		m_adNode[0] = i_dCoorX;
		m_adNode[1] = i_dCoorY;
		m_pEdge = 0;
	}

	/** Destructor.
	*/
	~PolyVertex()
	{
		///cout << "Vertex Delete \n" << endl;

		///delete m_pEdge;
		///m_pEdge = 0;
	}


	/** Copy constructor.
	*/
	PolyVertex(const PolyVertex &i_oPolyVertex)
	{

		m_adNode[0] = i_oPolyVertex.m_adNode[0];
		m_adNode[1] = i_oPolyVertex.m_adNode[1];
		m_pEdge = i_oPolyVertex.m_pEdge;
	};

	/** Assignment operator.
	*/
	PolyVertex &operator=(const PolyVertex &i_oPolyVertex)
	{
		if(this != &i_oPolyVertex)
		{
			m_adNode[0] = i_oPolyVertex.m_adNode[0];
			m_adNode[1] = i_oPolyVertex.m_adNode[1];
			m_pEdge = i_oPolyVertex.m_pEdge;
		};
		return *this;
	};

	/** Equals operator.
	*/
	bool operator==(const PolyVertex& i_oRHSPolyVertex) const
	{
		return ((m_adNode[0] == i_oRHSPolyVertex.m_adNode[0]) && (m_adNode[1] == i_oRHSPolyVertex.m_adNode[1]));
	}

	/** Boolean not equals.
	*/
	bool operator!=(const PolyVertex& i_oRHSPolyVertex) const
	{
		return ((m_adNode[0] != i_oRHSPolyVertex.m_adNode[0]) || (m_adNode[1] != i_oRHSPolyVertex.m_adNode[1]));
	}

	/** Defines ordering.
	*/
	bool operator<( const PolyVertex i_oOtherPolyVertex) const
	{
		if (m_adNode[1] < i_oOtherPolyVertex.m_adNode[1])
		{
			return true;
		}
		else if ((m_adNode[1] == i_oOtherPolyVertex.m_adNode[1])&&(i_oOtherPolyVertex.m_adNode[0] < m_adNode[0]))
		{
			return true;
		}
		else
		{
			return false;
		};
	}

	/** Defines reverse order.
	*/
	bool operator>( const PolyVertex i_oOtherPolyVertex) const
	{
		if (m_adNode[1] > i_oOtherPolyVertex.m_adNode[1])
		{
			return true;
		}
		else if ((m_adNode[1] == i_oOtherPolyVertex.m_adNode[1])&&(i_oOtherPolyVertex.m_adNode[0] > m_adNode[0]))
		{
			return true;
		}
		else
		{
			return false;
		};
	}

	/** Order vertices in ascending order.
	*/
	class PolyVertexAscendingOrder
	{
	public:
		bool operator() (const PolyVertex* i_poPolyVertex1,const PolyVertex* i_poPolyVertex2)
		{
			return *i_poPolyVertex1 < *i_poPolyVertex2;
		};
	};

	/** Order vertices in descending order.
	*/
	class PolyVertexDescendingOrder
	{
	public:
		bool operator() (const PolyVertex* i_poPolyVertex1,const PolyVertex* i_poPolyVertex2)
		{
			return *i_poPolyVertex1 > *i_poPolyVertex2;
		};
	};

	/** Set new edge for vertex node.
	*/
	void setEdge(HalfEdge* &i_poNewEdge){ this->m_pEdge = i_poNewEdge; }

	/** Get coordinates of node.
	*/
	double* getNode() { return m_adNode; }

	/** Pointer to arbitrary edge that has vertex as origin.
	*/
	HalfEdge* getEdge() const { return m_pEdge; }

private:

	double m_adNode[2]; /// (x,y) coordinate of node
	HalfEdge* m_pEdge; /// pointer to an edge from the PolyVertex
};

PolyVertex* GetMax(PolyVertex* i_poPolyVertex1, PolyVertex* i_poPolyVertex2);

PolyVertex* GetMin(PolyVertex* i_poPolyVertex1, PolyVertex* i_poPolyVertex2);

double Orientation(PolyVertex* i_poPolyVertex1, PolyVertex* i_poPolyVertex2, PolyVertex* i_poPolyVertex3);

/** Half edge class.
*/
class HalfEdge
{

public:

	/** Default constructor.
	*/
	HalfEdge() : m_pOrigin(0), m_pTwin(0),m_pNext(0), m_pPrev(0), m_pIncidentPolyFace(0){}

	/** Constructor from vertex.
	*/
	explicit HalfEdge(PolyVertex* i_poPolyVertex) :  m_pOrigin(0), m_pTwin(0), m_pNext(0), m_pPrev(0), m_pIncidentPolyFace(0)
	{
		m_pOrigin = i_poPolyVertex;
	}

	/** Destructor.
	*/
	~HalfEdge()
	{
	}

	/** Copy constructor.
	*/
	HalfEdge(const HalfEdge &i_oEdge)
	{
		m_pOrigin = i_oEdge.m_pOrigin;
		m_pNext = i_oEdge.m_pNext;
		m_pPrev = i_oEdge.m_pPrev;
		m_pTwin = i_oEdge.m_pTwin;
		m_pIncidentPolyFace = i_oEdge.m_pIncidentPolyFace;
	}

	/** Assignment operator.
	*/
	HalfEdge &operator=(const HalfEdge &i_oEdge)
	{
		if(this != &i_oEdge)
		{
			m_pOrigin = i_oEdge.m_pOrigin;
			m_pNext = i_oEdge.m_pNext;
			m_pPrev = i_oEdge.m_pPrev;
			m_pTwin = i_oEdge.m_pTwin;
			m_pIncidentPolyFace = i_oEdge.m_pIncidentPolyFace;
		};
		return *this;
	}

	/** Test if the edges are equal
	*/
	bool operator==(const HalfEdge& i_oRHSEdge) const
	{
		return ((*m_pOrigin == *(i_oRHSEdge.m_pOrigin)) && (*(m_pTwin->getOrigin()) == *(i_oRHSEdge.m_pTwin->getOrigin() ) )); 
	};

	/** Test if the edges are not equal
	*/
	bool operator!=(const HalfEdge& i_oRHSEdge) const
	{
		return ((*m_pOrigin != *(i_oRHSEdge.m_pOrigin)) || (*(m_pTwin->getOrigin()) != *(i_oRHSEdge.m_pTwin->getOrigin() ) )); 
	};

	/** Less than operator.
	*/
	bool operator<( const HalfEdge i_oOtherHalfEdge) const
	{
		if (*(m_pOrigin) < *(i_oOtherHalfEdge.getOrigin()))
		{
			return true;
		}
		else
		{
			return false;
		};
	}

	/** Greater than operator.
	*/
	bool operator>( const HalfEdge i_oOtherHalfEdge) const
	{
		if (*(m_pOrigin) > *(i_oOtherHalfEdge.getOrigin()))
		{
			return true;
		}
		else
		{
			return false;
		};
	}

	/** Order half edges in the BST.
	*/
	bool operator%( const HalfEdge i_oOtherHalfEdge) const
	{
		double* EdgeStart = m_pOrigin->getNode();
		double* EdgeEnd = m_pTwin->m_pOrigin->getNode();
		double* OtherEdgeStart = i_oOtherHalfEdge.getOrigin()->getNode();
		double* OtherEdgeEnd = i_oOtherHalfEdge.getTwin()->getOrigin()->getNode();

		double EdgeXMid = (EdgeStart[0] + EdgeEnd[0]) / 2.0;
		double OtherEdgeXMid = (OtherEdgeStart[0] + OtherEdgeEnd[0]) / 2.0;
		if(EdgeXMid < OtherEdgeXMid)
			return true;
		else
			return false;
		
	}

	/** Sort in ascending.
	*/
	class HalfEdgeAscendingOrder
	{
	public:
		bool operator() (const HalfEdge* i_poHalfEdge1,const HalfEdge* i_poHalfEdge2)
		{
			return *i_poHalfEdge1 < *i_poHalfEdge2;
		};
	};

	/** Sort in descending.
	*/
	class HalfEdgeDescendingOrder
	{
	public:
		bool operator() (const HalfEdge* i_poHalfEdge1,const HalfEdge* i_poHalfEdge2)
		{
			return *i_poHalfEdge1 > *i_poHalfEdge2;
		};
	};

	/** Set origin.
	*/
	void setOrigin(PolyVertex *i_poNewOrigin){ this->m_pOrigin = i_poNewOrigin; }

	/** Set twin.
	*/
	void setTwin(HalfEdge *i_poNewTwin){
		 this->m_pTwin = i_poNewTwin;
		i_poNewTwin->m_pTwin = this;
	}

	/** Set next half edge.
	*/
	void setNext(HalfEdge *i_poNewNext){
		 this->m_pNext = i_poNewNext;
	}

	/** Set previous half edge.
	*/
	void setPrev(HalfEdge *i_poNewPrev){
		 this->m_pPrev = i_poNewPrev;
	}

	/** Set incident face to the left of half edge.
	*/
	void setPolyFace(PolyFace *&i_poNewPolyFace){	this->m_pIncidentPolyFace = i_poNewPolyFace; }

	/** Get the pointer to origin vertex
	*/
	PolyVertex* getOrigin() const { return m_pOrigin; }

	/** Get the pointer to next half edge.
	*/
	HalfEdge* getNext() const { return m_pNext; }

	/** Get the pointer to previous half edge.
	*/
	HalfEdge* getPrev() const { return m_pPrev; }

	/** Get the pointer to twin half edge.
	*/
	HalfEdge* getTwin() const { return m_pTwin; }

	/** Get the pointer to incident face which lies to the left of half edge.
	*/
	PolyFace* getFace()	const { return m_pIncidentPolyFace; }

private:

	PolyVertex* m_pOrigin; /// pointer to origin of edge
	HalfEdge* m_pTwin; /// pointer to edge twin
	HalfEdge* m_pNext; /// pointer to next edge on PolyFace
	HalfEdge* m_pPrev; /// pointer to previous edge on PolyFace
	PolyFace* m_pIncidentPolyFace; /// pointer to PolyFace lying to the left of the edge
};

bool IsVertexLeftofEdge(PolyVertex *i_poVertex, HalfEdge *i_poHalfEdge);
bool IsVertexRightofEdge(PolyVertex *i_poVertex, HalfEdge *i_poHalfEdge);


/** Polyface class.
*/
class PolyFace
{
public:

	/** Default ctor.
	*/
	PolyFace() : m_pIncidentEdge(0) {}

	/** Ctor from half edge.
	*/
	explicit PolyFace(HalfEdge* i_poRHSEdge)
	{
		m_pIncidentEdge = i_poRHSEdge;
	}

	/** Destructor.
	*/
	~PolyFace()
	{
		///cout << "face delete \n" << endl;
		///delete m_pIncidentEdge;
		///m_pIncidentEdge = 0;
	}

	/** Assignment operator.
	*/
	PolyFace(const PolyFace &i_oRHSPolyFace)
	{
		m_pIncidentEdge = i_oRHSPolyFace.m_pIncidentEdge;
	}

	/** Assignment operator.
	*/
	PolyFace &operator=(const PolyFace &i_oRHSPolyFace)
	{
		if(this != &i_oRHSPolyFace)
			m_pIncidentEdge = i_oRHSPolyFace.m_pIncidentEdge;
		return *this;
	}

	/** Comparision operator.
	*/
	bool operator==(const PolyFace& i_oRHSPolyFace) const
	{
		return (*(m_pIncidentEdge) == *(i_oRHSPolyFace.m_pIncidentEdge)); 
	};

	/** Boolean not equals.
	*/
	bool operator!=(const PolyFace& i_oRHSPolyFace) const
	{
		return (*(m_pIncidentEdge) != *(i_oRHSPolyFace.m_pIncidentEdge)); 
	};

	/** Get edge.
	*/
	void setEdge(HalfEdge* &i_poNewEdge) { this->m_pIncidentEdge = i_poNewEdge; }

	/**Get edge.
	*/
	HalfEdge* getEdge() const { return m_pIncidentEdge; }

private:

	///int m_nAttribute; /// null?
	HalfEdge* m_pIncidentEdge; /// pointer to an edge on its bounday
};

/** DCEL class.
*/
class DCEL
{

public:

	/** Default ctor.
	*/
	DCEL()
		: m_pPolyVertexNodes(0),
		m_pHalfEdgeVect(0),
		m_pPolyFaceVect(0) {}

	/** Construct DCEL from CW order of vertices.
	*/
	explicit DCEL(vector<double> i_adPolygonVertices)
	{
		int nSize = i_adPolygonVertices.size() / 2;
		
		/// Calls private initialize function
		InitializeDCEL(i_adPolygonVertices, nSize);
	}

	/** Destructor.
	*/
	~DCEL()
	{
		///cout << "DCEL delete \n" << endl;

		for(unsigned int i = 0; i < m_pPolyVertexNodes.size(); i++)
		{
			delete m_pPolyVertexNodes[i];
			m_pPolyVertexNodes[i] = 0;
		};
		m_pPolyVertexNodes.clear();

		for(unsigned int i = 0; i < m_pHalfEdgeVect.size(); i++)
		{
			delete m_pHalfEdgeVect[i];
			m_pHalfEdgeVect[i] = 0;
		};
		m_pHalfEdgeVect.clear();

		for(unsigned int i = 0; i < m_pPolyFaceVect.size(); i++)
		{
			delete m_pPolyFaceVect[i];
			m_pPolyFaceVect[i] = 0;
		};
		m_pPolyFaceVect.clear();
	};
	
	/** Copy ctor.
	*/
	DCEL(const DCEL &i_oRHSDCEL)
	{
		m_pPolyVertexNodes = i_oRHSDCEL.m_pPolyVertexNodes;
		m_pHalfEdgeVect = i_oRHSDCEL.m_pHalfEdgeVect;
		m_pPolyFaceVect = i_oRHSDCEL.m_pPolyFaceVect;
	}

	/** Assignment operator.
	*/
	DCEL &operator=(const DCEL &i_oRHSDCEL)
	{
		if(this != &i_oRHSDCEL)
		{
			m_pPolyVertexNodes = i_oRHSDCEL.m_pPolyVertexNodes;
			m_pHalfEdgeVect = i_oRHSDCEL.m_pHalfEdgeVect;
			m_pPolyFaceVect = i_oRHSDCEL.m_pPolyFaceVect;
		};
		return *this;
	}

	/** Input edge to DCEL.
	*/
	void InsertNewEdge(PolyVertex* &i_poPolyVertex1, PolyVertex* &i_poPolyVertex2);

	/** Get vertices.
	*/
	vector<PolyVertex*> getVertices() {return  m_pPolyVertexNodes; }

	/** Get pointers to half edges.
	*/
	vector<HalfEdge*> getHalfEdges() {return  m_pHalfEdgeVect; }

	/** Get pointers to faces.
	*/
	vector<PolyFace*> getFaces() {return m_pPolyFaceVect; }

	/** Get number of vertices.
	*/
	int getNumVertex() {return m_pPolyVertexNodes.size();}

	/** Get number of edges.
	*/
	int getNumEdges() {return m_pHalfEdgeVect.size();}

	/** Get number of faces.
	*/
	int getNumFaces() {return m_pPolyFaceVect.size();}

	/** Write DCEL to output file.
	*/
	void WriteToFile(ofstream &outputFile);

private:
	
	/** Private initialization of DCEL
	*/
	void InitializeDCEL(vector<double> i_adPolygonVerticies, int i_nSize);

	vector<PolyVertex*> m_pPolyVertexNodes; /// vector of pointers to vertices
	vector<HalfEdge*> m_pHalfEdgeVect; /// vector of pointers to half edges
	vector<PolyFace*> m_pPolyFaceVect; /// vector of pointers to faces

};