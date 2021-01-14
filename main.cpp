#include <iostream>
#include <vector>
#include "PolygonTriangulation.hpp"

using namespace std;

vector<double> ReadCSV(ifstream &file)
{
	vector<double> Data;
	while(!file.eof())
		{
			double a, b, c;
			char ch;
			file >> a >> b;

			Data.push_back(b);
			Data.push_back(a);
		};
	return Data;
};

int main()
{
	ifstream infile("input.txt");

	vector<double> TestPoly1_vec = ReadCSV(infile);

	clock_t tStart = clock();
	reverse(TestPoly1_vec.begin(), TestPoly1_vec.end());

	infile.close();
	/// Initialize a Monotone Polygon from the vector of nodes (not yet monotone)
	MonotonePolygon TestPoly1_Monotone(TestPoly1_vec);

	DCEL* test123 = TestPoly1_Monotone.getDCEL();

	///Create a monotone subdivision of this polygon
	TestPoly1_Monotone.MakeMonotone();

	DCEL* LakeMonotone = TestPoly1_Monotone.getDCEL();

	/// Initialize a triangulation from this monotone polygon
	MonotoneTriangulation TestPoly1_Triangulation(TestPoly1_Monotone);

	ofstream outputFileMono;
	outputFileMono.open("intermediate.txt");
	LakeMonotone->WriteToFile(outputFileMono);
	outputFileMono.close();

	/// Triangulate this polygon
	TestPoly1_Triangulation.TriangulatePolygon();

	DCEL* LakeTriangle = TestPoly1_Triangulation.getDCEL();

	printf("Time taken: %.2fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);  

	ofstream outputFileTri;
	outputFileTri.open("output.txt");
	LakeTriangle->WriteToFile(outputFileTri);
	outputFileTri.close();

	return 0;

};