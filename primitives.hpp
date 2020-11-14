#ifndef POINT_H
#define POINT_H
///Defines the point if it is not defined before.
#include <vector>

using namespace std;

/** @brief Represents a point in the 2 dimensional plane
*/
class Point
{
	public:
  double x, y;       /**<coordinates of the point*/

  /** Default constructor.
  */
  Point();

  /** Constructor which takes the coordinates as arguments.
  */	
	Point (double, double );

  /** Returns if the points coincide.
  */
  bool equals (Point );
	
  /** Comparision operator for point type.
  */	
	bool operator< (const Point& );

  /**Finds dotProduct of vectors to points (x1,y1) and (x2,y2).
  */
  double dotProduct (double x1, double y1, double x2, double y2);

  /** Finds the angle made by three points taken in order.
  */  
  double findAngle (Point, Point, Point); 
};

/** @brief Primitives for finding the convex hull.
*/
class ConvexHull
{
	public:
	
	vector<Point> point_set;        /**<List of points on the plane*/
	vector<Point> convex_hull;      /**<Vertices of convex hull (in order)*/
	
  /** Inputs points from a file.
  */
	void input();
	
  /** Writes the ordered list of vertices of the convex hull to a file.
  */
	void output();   
};

#endif
