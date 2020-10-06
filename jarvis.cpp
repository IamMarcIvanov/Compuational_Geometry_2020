#include <cmath>
#include <iostream>
#include "jarvis.h"

using namespace std;

Point bottomleftPoint(vector <Point>& point_set) {
  Point p = point_set[0];
  for (auto it: point_set) {
    if (it.operator<(p)) {
      p = it;
    }
  }
  return p;
}

Point pointWithBiggestAngle (Point A, Point origin, ConvexHull ch) {
  double mex=0;
  Point p = A;
  for (auto it: ch.point_set){
    if(it.equals(A) or it.equals(origin)){
      continue;
    } 
    double angle = A.findAngle(A, origin, it);
    if(angle > mex){
      mex = angle;
      p=it;
    }
  }
  return p;
}

void jarvisMarch(ConvexHull ch) {
  ch.input();
  if (ch.point_set.size() < 3) {
    for (auto it: ch.point_set){
      ch.convex_hull.push_back(it);
    }
    ch.output();
    return ;
  }
  Point startPoint = bottomleftPoint(ch.point_set);
  Point dummy = Point(startPoint.x, startPoint.y+1);              /**<Dummy point just above the starting point*/
  ///Second point on the hull would make maximum angle with respect to dummy point and starting point (in order).
  Point secondPoint = pointWithBiggestAngle(dummy, startPoint, ch);
  ch.convex_hull.push_back(startPoint);
  ch.convex_hull.push_back(secondPoint);
  
  int i=2;
  while (1)
  {
    Point nextPoint = pointWithBiggestAngle(ch.convex_hull[i-2], ch.convex_hull[i-1], ch);
    if(nextPoint.equals(startPoint)){
      break;    
    }
    ch.convex_hull.push_back(nextPoint);
    i++;
  }
  ch.output();
}
