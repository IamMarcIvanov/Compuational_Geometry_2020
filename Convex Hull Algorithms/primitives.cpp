#include <iostream>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <cmath>
#include "primitives.hpp"

using namespace std;

const int eps = 1e-9;

Point::Point(){
  x = 0, y=0;
}

Point::Point(double x_coord, double y_coord)
{
  x = x_coord;
  y = y_coord;
}

bool Point::equals (Point p){
  ///If the points coincide, their distance is close to zero.
  // double distance = p.dotProduct(x-p.x, y-p.y, x-p.x, y-p.y);
  // if(distance < eps)
  //   return true;
  // return false;
  return x==p.x and y==p.y;
}

bool Point::operator< (const Point& p)
{
  if( x < p.x )
  {
    return true;
  }
  if( x == p.x && y < p.y )
  {
    return true;
  }
  return false;
}

double Point::dotProduct (double x1, double y1, double x2, double y2) {
  return x1*x2 + y1*y2;
}

double Point::findAngle (Point A, Point origin, Point B){
  ///Using formula A.B = |A||B|cos(theta), considering the middle argument as origin.
  ///Square of length of a vector is its product with itself.
  double lenAsquare = dotProduct(A.x-origin.x, A.y-origin.y, A.x-origin.x, A.y-origin.y);   
  double lenBsquare = dotProduct(B.x-origin.x, B.y-origin.y, B.x-origin.x, B.y-origin.y);   
  double dotProd = dotProduct(A.x-origin.x, A.y-origin.y, B.x-origin.x, B.y-origin.y);
  return (acos(dotProd/sqrt(lenAsquare*lenBsquare)));
}

void ConvexHull::input()
{
  int n;
  cin >> n;
  while(n--){
    double a, b;
    cin >> a >> b;
    Point p = Point(a, b);
    point_set.push_back(p);
  }
  // string line;
  // string s = "";
  // ifstream myfile;
  // myfile.open("./input.txt");
  // if (!myfile)
  // {
  //   while ( getline (myfile, line) )
  //   {
  //     int a, b;
  //     if( line.compare(0, 1, "(", 0, 1) != 0 ) 
  //     {
  //       cout << "err" << endl;
  //       break;
  //     }
  //     for(int i=1 ; i<line.length() ; i++)
  //     {
  //       if(line.compare(i, 1, ",", 0, 1) == 0)
  //       {
  //         a = stoi(s);
  //         s = "";
  //       }
  //       else if(line.compare(i, 1, ")", 0, 1) == 0)
  //       {
  //         b = stoi(s);
  //         s = "";
  //       }
  //       else s += line[i];
  //     }
  //     Point p(a, b);
  //     point_set.push_back(p);
  //   }
  //   myfile.close();
  // }
  // else cout << "Unable to open input file"; 
}

void ConvexHull::output()
{
  ofstream myfile ("output.txt");
  if (myfile.is_open())
  {
  myfile << convex_hull.size() << endl;
    for( int i=0 ; i<convex_hull.size() ; i++)
    {
      Point p = convex_hull[i];
      myfile << p.x << " " << p.y << " " << endl;
    }
    myfile.close();
  }
    else cout << "Unable to open output file";
}
