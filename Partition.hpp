#pragma once

enum 
{
	START_VERTEX = 1U, SPLIT_VERTEX, END_VERTEX, MERGE_VERTEX, REGULAR_VERTEX_LEFT, REGULAR_VERTEX_RIGHT
};

#include <algorithm>
#include <iostream>
#include <math.h>
#include "DCEL.hpp"
#include "BST.hpp"

using namespace std;

/** Class to partition polygon to y-monotone polygons.
*/
class MonotonePolygon
{
public:
	/** Constructs class from CCW order of vertices.
	*/
	explicit MonotonePolygon(vector<double> i_adPolygonVertices) 
	{
		m_poPolygonDCEL = new DCEL(i_adPolygonVertices);
	}
	/** Constructs from pointer to DCEL.
	*/
	explicit MonotonePolygon(DCEL *&i_poInputDCEL) 
	{
		m_poPolygonDCEL = i_poInputDCEL;
	}

	/** Copy constructor.
	*/
	MonotonePolygon(const MonotonePolygon &i_oRHSMontonePolygon) 
	{
		m_poPolygonDCEL = i_oRHSMontonePolygon.m_poPolygonDCEL;
	};

	/** Assignment operator.
	*/
	MonotonePolygon &operator= (const MonotonePolygon &i_oRHSMontonePolygon) 
	{
		if(this != &i_oRHSMontonePolygon)
			m_poPolygonDCEL = i_oRHSMontonePolygon.m_poPolygonDCEL;
		return *this;
	};

	/** Destructor.
	*/
	~MonotonePolygon()
	{
		/// check to see if DCEL is empty
		if( !m_poPolygonDCEL)
		{
			delete m_poPolygonDCEL;
			m_poPolygonDCEL = nullptr;
		};
	};

	/** Return pointer to DCEL.
	*/
	DCEL* getDCEL() {return m_poPolygonDCEL;}

	/** Public make monotone.
	*/
	void MakeMonotone();

private:

	unsigned int VertexKind(PolyVertex *i_poInputVertex, PolyFace *i_poFace);

	void FixUp(EdgeNode *i_poEdgeNode, PolyVertex *i_poVertex);

	////Handles different types of vertices.
	void HandleStartVertex(PolyVertex *i_poInputVertex, EdgeSearchTree *&i_poTree);
	void HandleEndVertex(PolyVertex *i_poInputVertex, EdgeSearchTree *&i_poTree);
	void HandleSplitVertex(PolyVertex *i_poInputVertex, EdgeSearchTree *&i_poTree);
	void HandleMergeVertex(PolyVertex *i_poInputVertex, EdgeSearchTree *&i_poTree);
	void HandleRegularVertexLeft(PolyVertex *i_poInputVertex, EdgeSearchTree *&i_poTree);
	void HandleRegularVertexRight(PolyVertex *i_poInputVertex, EdgeSearchTree *&i_poTree);

	/** Private call to fixup.
	*/
	void FixUp(EdgeNode *i_poEdgeNode, PolyVertex *i_poVertex, DCEL *&i_poDCEL);

	/** Private call to make monotone.
	*/
	void MakeMonotone(DCEL *&i_poDCEL);

	DCEL *m_poPolygonDCEL; /// as a member we use the doubly connected edge list.
};

