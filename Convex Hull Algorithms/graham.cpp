#include <iostream>
#include <stack>
#include <stdlib.h>
#include <iomanip>
#include "graham.hpp"

Point p0;

int orient(Point p, Point q, Point r) 
{ 
    int val=(q.y-p.y)*(r.x-q.x)-(q.x-p.x)*(r.y-q.y); 
    if (val == 0)  /// Colinear
	{
		return 0;	
	}
	if(val>0)
	{
		return 1;
	}
	return 2;
    /// clock or counterclock wise 
} 

int compare(const void *v1, const void *v2) 
{ 
   Point *p1=(Point *)v1; 
   Point *p2=(Point *)v2; 
   /// Find orientation 
   int o = orient(p0, *p1, *p2); 
   if (o == 0) 
   {
   	    int d1=(p0.x-(*p1).x)*(p0.x-(*p1).x)+(p0.y-(*p1).y)*(p0.y-(*p1).y);
   	    int d2=(p0.x-(*p2).x)*(p0.x-(*p2).x)+(p0.y-(*p2).y)*(p0.y-(*p2).y);
   	    if(d1>=d2)
   	    {
   	    	return -1;
		}
		else
		{
			return 1;
		}
   }
  	if(o==2)
  	{
  		return -1;
	  }
   return 1;
}

void grahamAlgorithm(ConvexHull ch)
{
	ch.input();
	clock_t tStart = clock();
	int n=ch.point_set.size();
	/// For less than 3 elements
	if (ch.point_set.size() < 3) {
	    for (auto it: ch.point_set){
	      ch.convex_hull.push_back(it);
	    }
	    ch.output();
	    return;
	  }
	/// Find the bottommost point by sorting
	int ymin=ch.point_set[0].y,min=0;
	int i,j,k;
	for(i=1;i<n;i++)
	{
		int y=ch.point_set[i].y;
		if((y<min)|| (ymin==y&& ch.point_set[i].x<ch.point_set[min].x))
		{
			ymin=ch.point_set[i].y;
			min=i;
		}
	}
	Point temp = ch.point_set[0]; 
	ch.point_set[0] = ch.point_set[1]; 
	ch.point_set[1] = temp;
	p0= ch.point_set[0];
	qsort(&ch.point_set[1], n-1, sizeof(Point), compare);
	/// for removing the elements making same angle with the point
	int m=1;
	for(i=1;i<n;i++)
	{
		while(i<n-1&&orient(p0,ch.point_set[i],ch.point_set[i+1])==0)
		{
			i++;
		}
		ch.point_set[m]=ch.point_set[i];///only the last element with the same angle is stored
		m++;
	}
	stack<Point> store;
	///store the first 3 elements in stack
	for(i=0;i<3;i++)
	{
		store.push(ch.point_set[i]);
		// ch.convex_hull.push_back(ch.point_set[i]);
	}
	for(i=3;i<m;i++)
	{
		/// at each step check the orientation of the three points(clockwise or anticlockwise)
		while(true)
		{
			Point p = store.top(); 
		    store.pop(); 
		    Point res = store.top(); 
		    store.push(p); 
		    if(orient(res,p,ch.point_set[i])==2)
		    {
		    	break;
			}
			else
			{
				store.pop();
			}
		}
		///store the element int the stack after finding it
		store.push(ch.point_set[i]);
		// ch.convex_hull.push_back(ch.point_set[i]);
	}
	while (!store.empty()){
		Point p = store.top();
		store.pop();
		ch.convex_hull.push_back(p);
	}

	ch.output();
  printf("Time taken: %.2fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);
	for (auto it: ch.convex_hull)
	{
		// cout<<it.x<<" "<<it.y<<endl;
	}
	ch.output();
}
