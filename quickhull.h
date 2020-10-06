#include "primitives.h"

class Node  
{ 
  public:
  Point p;        /**<Value what each node stores.*/
  Node *next;     /**<Pointer to the next point.*/
  
  /** Constructor
  */ 
  Node(Point );
  
  /** Inserts a point after a given point in the linked list.
  */ 
  void insertAfter (Point, Point, Node* );
}; 

/** Finds points on the convex hull from a set of points which are on the right side of a given line.
*/ 
void findHull (vector <Point>&, Point, Point, Node* );

/** Finds the convex hull using Quickhull algorithm.
*/ 
void quickHull (ConvexHull );