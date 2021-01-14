#pragma once

#include "DCEL.hpp"
#include "Partition.hpp"

using namespace std;

/** Class to triangulate y-monotone polygons.
*/
class MonotoneTriangulation
{
public:

	/** Default constuctor.
	*/
	MonotoneTriangulation() : m_poMonotoneDCEL(0) {}

	/** Construct from DCEL..
	*/
	explicit MonotoneTriangulation(DCEL *&i_poInputDCEL)
	{
		m_poMonotoneDCEL = i_poInputDCEL;
	}

	/** Construct from monotone polygon object.
	*/
	explicit MonotoneTriangulation(MonotonePolygon &i_poMonotonePolygon)
	{
		m_poMonotoneDCEL = i_poMonotonePolygon.getDCEL();
	}

	/** Destructor.
	*/
	~MonotoneTriangulation()
	{
		if(!((m_poMonotoneDCEL->getNumVertex() == 0) &&(m_poMonotoneDCEL->getNumEdges() == 0) &&(m_poMonotoneDCEL->getNumFaces() == 0)))
		{
			delete m_poMonotoneDCEL;
			m_poMonotoneDCEL = nullptr;
		};
	};

	/** Copy constuctor.
	*/
	MonotoneTriangulation(const MonotoneTriangulation &i_oRHSMonoTriangle)
	{
		m_poMonotoneDCEL = i_oRHSMonoTriangle.m_poMonotoneDCEL;
	}

	/** Assigment operator.
	*/
	MonotoneTriangulation &operator= (const MonotoneTriangulation &i_oRHSMonoTriangle)
	{
		if(this != &i_oRHSMonoTriangle)
			m_poMonotoneDCEL = i_oRHSMonoTriangle.m_poMonotoneDCEL;
		return *this;
	}

	/** Get pointer to DCEL.
	*/
	DCEL* getDCEL() {return m_poMonotoneDCEL;}

	/** Public funciton which will call the private function to triangulate.
	*/
	void TriangulatePolygon();

private:

	vector<PolyVertex*> GetAllVertices(PolyFace *i_poPolyFace);

	vector<PolyVertex*> GetLeftChain(vector<PolyVertex*> i_oAllVertices, PolyFace *i_poPolyFace);

	vector<PolyVertex*> GetRightChain(vector<PolyVertex*> i_oAllVertices, PolyFace *i_poPolyFace);

	bool IsInChain(PolyVertex *i_poVertex, vector<PolyVertex*> i_oChain);

	bool NotInSameChain(PolyVertex *i_poVertex1, PolyVertex *i_poVertex2, vector<PolyVertex*> i_oChain);

	void TriangulateMonotonePolygon(PolyFace *&i_poFace, DCEL *&io_poMonotoneDCEL);

	DCEL *m_poMonotoneDCEL; /// the doubly connected edge list which holds the triangulation.
};