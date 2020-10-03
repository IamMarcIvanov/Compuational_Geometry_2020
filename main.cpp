// #include "Andrew1.h"
#include "jarvis.h"
#include <iostream>
#include <fstream>
using namespace std;

int main()
{
	freopen("input.txt","r",stdin);
	cout << "happy";
	ConvexHull c_hull;
	// AndrewAlgorithm(c_hull);
	jarvisMarch(c_hull);
	return 0;
}
