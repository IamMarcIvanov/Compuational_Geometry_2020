#include "Andrew1.h"
#include "jarvis.h"
#include "quickhull.h"
#include <iostream>
#include <fstream>
using namespace std;

int main()
{
	cout << "happy";
	ConvexHull c_hull;
	int choice;
	cin >> choice;
	freopen("input.txt","r",stdin);
	switch (choice)
	{
	case 1:
		AndrewAlgorithm(c_hull);
		break;
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
