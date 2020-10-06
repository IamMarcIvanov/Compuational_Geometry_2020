#include <iostream>
#include <cstdlib>
#include <cmath>
#include <bits/stdc++.h>
#include <vector>
#include <algorithm>
#include "andrew1.h"

using namespace std;

bool right_turn(Point p, Point q, Point r)
{
	double det = p.x * (q.y - r.y) - q.x * (p.y - r.y) + r.x * (p.y - q.y);
	if( det > 0 )
		return false;
	return true;
}

void AndrewAlgorithm(ConvexHull ch)
{
	ch.input();
	if (ch.point_set.size() < 3) {
    for (auto it: ch.point_set){
      ch.convex_hull.push_back(it);
    }
    ch.output();
    return ;
  }
	sort(ch.point_set.begin(), ch.point_set.end());
	int n = ch.point_set.size();
	
	vector<Point> upper;
	upper.push_back(ch.point_set[0]);
	upper.push_back(ch.point_set[1]);
	for( int i=2 ; i<n ; i++)
	{
		upper.push_back(ch.point_set[i]);
		int k = upper.size();
		while( k > 2 && !right_turn(upper[k - 3], upper[k - 2], upper[k - 1]) )
		{
			Point temp = upper[k - 1];
			upper.pop_back();
			upper.pop_back();
			upper.push_back(temp);
			k--;
		}
	}
	
	vector<Point> lower;
	lower.push_back(ch.point_set[n - 1]);
	lower.push_back(ch.point_set[n - 2]);
	for( int i=n-3 ; i>=0 ; i--)
	{
		lower.push_back(ch.point_set[i]);
		int k = lower.size();
		while( k > 2 && !right_turn(lower[k - 3], lower[k - 2], lower[k - 1]) )
		{
			Point temp = lower[k - 1];
			lower.pop_back();
			lower.pop_back();
			lower.push_back(temp);
			k--;
		}
	}	
	upper.insert( upper.end(), lower.begin() + 1, lower.end() - 1 );
	
	for( Point p : upper )
	{
		ch.convex_hull.push_back(p);
	}
	ch.output();
}
