#include <iostream>
#include <cstdlib>
#include <cmath>
#include <bits/stdc++.h>
#include <vector>
#include <algorithm>
using namespace std;

class Point
{
	public:
	int x, y;
	Point()
	{
		x = 0;
		y = 0;
	}
	Point(int x_coord, int y_coord)
	{
		x = x_coord;
		y = y_coord;
	}
	
	bool operator < (const Point& p)
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
};

class Line: public Point
{
	public:
	Point start;
	Point end;
	Line(Point s, Point e)
	{
		start.x = s.x;
		start.y = s.y;
		end.x = e.x;
		end.y = e.y;
	}
	double length()
	{
		double x_diff = abs(start.x - end.x);
		double y_diff = abs(start.y - end.y);
		return sqrt(x_diff * x_diff + y_diff * y_diff);
	}
};

vector<Point> input()
{
	int n;
	cout << "Enter number of points: ";
	cin >> n;
	
	vector<Point> points;
	for( int i=0 ; i<n ; i++ )
	{
		int x;
		cout << "Enter x coordinate: ";
		cin >> x;
		
		int y;
		cout << "Enter y coordinate: ";
		cin >> y;
		
		Point p(x, y);
		points.push_back(p);
	}
	return points;
}

bool right_turn(Point p, Point q, Point r)
{
	int det = p.x * (q.y - r.y) - q.x * (p.y - r.y) + r.x * (p.y - q.y);
	if( det > 0 )
		return false;
	return true;
}

int main()
{
	vector<Point> pts = input();
	sort(pts.begin(), pts.end());
	int n = pts.size();
	
	vector<Point> upper;
	upper.push_back(pts[0]);
	upper.push_back(pts[1]);
	for( int i=2 ; i<n ; i++)
	{
		upper.push_back(pts[i]);
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
	lower.push_back(pts[n - 1]);
	lower.push_back(pts[n - 2]);
	for( int i=n-3 ; i>=0 ; i--)
	{
		lower.push_back(pts[i]);
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
		cout << "(" << p.x << "," << p.y << ") ";
	}
	cout << endl ;
	return 0;
}
