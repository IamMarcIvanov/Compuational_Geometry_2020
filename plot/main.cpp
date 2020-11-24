#include<GL/glut.h>
#include <iostream>
#include <vector>
#include <fstream>	///for file handling
#include <sstream>	///for splitting and parsing strings

using namespace std;

//double stof(string s){
//	stringstream stream(s); 
//	double x = 0; 
//	stream >> x; 
//	return x;
//}

stof_user(string s){
	stringstream stream(s); 
	float x = 0; 
	stream >> x; 
	return x;
}

void plotPoints(double x, double y){
	glBegin(GL_POINTS);
	glVertex2f(x,y);
	glEnd();
}

void init(){
	glClearColor(0.0,0.0,0.0,1.0);
}

void display(){
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	
//	glColor3f(1, 0, 0); 	
//	glPointSize(5);
//	ifstream fin;
//	fin.open("../input.txt");
//	int n;
//	fin>>n;
//	glBegin(GL_POINTS);
//	while(n--){
//		double a, b;
//		fin>>a>>b;
//		glVertex2f(a,b);
////		cout<<a<<" "<<b<<endl;
//	}
//	glEnd();
//	fin.close();
	glColor3f(1, 1, 1);
	glPointSize(3);
	ifstream fin;
	fin.open("input.txt");
	int n;
	fin>>n;
	glBegin(GL_LINES);
	double a,b;
	fin>>a>>b;
	double c=a, d=b;
	n--;
	while(n--){
//		double a, b;
		glVertex2f(a,b);
		fin>>a>>b;
		glVertex2f(a,b);
//		cout<<a<<" "<<b<<endl;
	}
	glVertex2f(a,b);
	glVertex2f(c,d);
	glEnd();
	fin.close();
	
	glColor3f(1, 1, 0);
	glPointSize(3);
//	ifstream fin;
	fin.open("output.txt");
//	int n;
	fin>>n;
	glBegin(GL_LINES);
//	double a,b;
	fin>>a>>b;
//	double c=a, d=b;
	n--;
	while(n--){
//		double a, b;
		glVertex2f(a,b);
		fin>>a>>b;
		glVertex2f(a,b);
//		cout<<a<<" "<<b<<endl;
	}
//	glVertex2f(a,b);
//	glVertex2f(c,d);
	glEnd();
	fin.close();
	
//	glColor3f(0, 1, 0);
////	glBegin(GL_LINES);
//	fin.open("LakeMonotone.lin");
//	string str;
//	int f=10, g=1;
//	getline(fin,str);
//	while(fin){
////		cout<<"monotone file reading starts\n";
//		string line;
//		vector<string> result;
//		stringstream data(str);
//		while(getline(data,line,' ')){
//			result.push_back(line);
//		}
//		if(f){
//				cout<<result[0]<<endl;
////			cout<<"monotone file reading starts\n";	
//			f--;	
//		}
//		if(result.size()==3 and fin){
//			if(g){
//				cout<<"two points found\n";
//				g=0;	
//			}
//			getline(fin,str);
//			vector<string> result_next;
//			stringstream data2(str);
//			while(getline(data2,line,' ')){
//				result_next.push_back(line);
//			}
//			if(result_next.size()==3){
////				if(g){
////					cout<<"three points found\n";
////					g=0;	
////				}
//				float a = stof_user(result[0]), b = stof_user(result[1]), c = stof_user(result_next[0]), d = stof_user(result_next[1]);
//	        	glVertex2f(a,b);
//	        	glVertex2f(c,d);
//			}
//		}
//		getline(fin,str);
//	}
//
////	glEnd();
//	fin.close();
//	
//	glColor3f(1, 1, 0);
////	glBegin(GL_LINES);
//	fin.open("LakeTriangulation.lin");
//	getline(fin,str);
//	f=10;
//	while(fin){
//		string line;
//		vector<string> result;
//		stringstream data(str);
//		while(getline(data,line,' ')){
//			result.push_back(line);
//		}
//		if(f){
//				cout<<result[0]<<endl;
////			cout<<"monotone file reading starts\n";	
//			f--;	
//		}
//		if(result.size()==3 and fin){
////			cout<<"two points found for triangulation\n";
//			getline(fin,str);				
//			vector<string> result_next;
////			stringstream data(str);
//			while(getline(data,line,' ')){
//				result_next.push_back(line);
//			}
//			if(result_next.size()==3){
////				cout<<"three points found for triangulation\n";
//				float a = stof_user(result[0]), b = stof_user(result[1]), c = stof_user(result_next[0]), d = stof_user(result_next[1]);
//	        	glVertex2f(a,b);
//	        	glVertex2f(c,d);
//			}
//		}
//		getline(fin,str);
//	}
//
//	glEnd();
//	fin.close();

	



	glFlush();	 
}

void reshape(int w,int h){
	glViewport(0,0,(GLsizei)w,(GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-3020,3020,-3020,3020);
	glMatrixMode(GL_MODELVIEW);
}


int main(int argc, char** argv) { 
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGB);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(500,500);
	
	glutCreateWindow("Polygon Triangulation");
	
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	init();
	
	
	
	glutMainLoop();   
}

















