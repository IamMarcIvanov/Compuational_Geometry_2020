///Demo file to show the use of the library.
#include "convexHullAlgos.hpp"
#include <iostream>
#include <fstream>
using namespace std;

class newClass : public ConvexHull {
	public:
	newClass(){
		cout<<"Hello from the inherited class!\n";
	}
};

/** Generates n random points of magnitude less than m.
*/
void generatePoints(int n, int m){
	freopen("input.txt", "w", stdout);
	cout<<n<<endl;
	// cout<<2000000<<" "<<2000000<<endl;
	// cout<<2000000<<" "<<2000000<<endl;
	while(n--){
		double x = rand()%m;
		double y = rand()%m;
		double xsign = rand()%2;
		double ysign = rand()%2;
		///To make negate the coordinates randomly.
		if(xsign) x *= -1;
		if(ysign) y *= -1;
		cout<<x<<" "<<y<<endl;
	}
}

int main()
{
	// newClass c_hull;
	ConvexHull c_hull;
	cout<<"Enter 1 for Graham Scan, 2 for Jarvis March and 3 for QuickHull\n";
	int choice;
	cin >> choice;
	// generatePoints(1000000, 1000);
	freopen("input.txt","r",stdin);
	switch (choice)
	{
	case 0:
		AndrewAlgorithm(c_hull);
		break;
	case 1:
		grahamAlgorithm(c_hull);
	case 2:
		jarvisMarch(c_hull);
		break;
	case 3:
		quickHull(c_hull);
		break;
	default:
		break;
	}
	return 0;
}
