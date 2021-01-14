#include "primitives.hpp"

/** Checks the angle made by three points to see clockwise or countercockwise.
*/
int orient(Point p, Point q, Point r);

/** Compares the position of 2 points relative to leftmost point.
*/
int compare(const void *v1, const void *v2);

/** Finds the convex hull using Graham's Algorithm.
*/
void grahamAlgorithm(ConvexHull ch);
