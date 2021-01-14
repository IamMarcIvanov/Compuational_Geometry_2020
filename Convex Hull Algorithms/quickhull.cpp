#include <cmath>
#include <iostream>
#include <iomanip>
#include "quickhull.hpp"

using namespace std;

Node::Node (Point p){
  this->p=p;
  this->next = nullptr;
}

void Node::insertAfter (Point P, Point R, Node* list){
  Node* temp=list;
  while(!temp->p.equals(P)){
    temp=temp->next;
  }
  Node* newPoint = new Node(R);
  newPoint->next = temp->next;
  temp->next = newPoint;
}

double signedDistance (Point P, Point A, Point B){
  return (B.y - A.y)*(P.x - A.x) - (B.x - A.x)*(P.y - A.y);
}

void findHull (vector <Point>& sk, Point P, Point Q, Node* list){
  if (sk.size() == 0) return;
  double distance = 0;
  Point farthestPoint;
  for(auto it: sk) {
    double newDistance = abs(signedDistance(it, P, Q));
    if(distance < newDistance){
      distance = newDistance;
      farthestPoint = it;
    }
  }
  list->insertAfter(P, farthestPoint, list);
  vector <Point> s1, s2;
  for(auto it: sk) {
    if(signedDistance(it, P, farthestPoint) > 0){
      s1.push_back(it);
    }
    if(signedDistance(it, farthestPoint, Q) > 0){
      s2.push_back(it);
    }
  }
  findHull(s1, P, farthestPoint, list);
  findHull(s2, farthestPoint, Q, list);
}

void quickHull (ConvexHull ch){
  ch.input();
  clock_t tStart = clock();       /**<Start time of the algo*/
  if (ch.point_set.size() < 3) {
    for (auto it: ch.point_set){
      ch.convex_hull.push_back(it);
    }
    ch.output();
    return ;
  }
  Point leftMost = ch.point_set[0], rightMost = ch.point_set[0];
  for (auto it: ch.point_set) {
    if (it.operator<(leftMost)) {
      leftMost=it;
    }
    if (rightMost.operator<(it)) {
      rightMost=it;
    }
  }
  ///We store the points in a circular linked list. 
  Node *l = new Node(leftMost), *r= new Node(rightMost);
  Node* head;
  head=l;
  l->next=r;
  r->next=l;

  vector <Point> s1, s2; 
  for(auto it: ch.point_set){
    if(signedDistance(it, leftMost, rightMost) > 0){
      s1.push_back(it);
    }
    if(signedDistance(it, leftMost, rightMost) < 0){
      s2.push_back(it);
    }
  }
  findHull(s1, leftMost, rightMost, head);
  findHull(s2, rightMost, leftMost, head);
  Node *traverse = l;
  while(traverse->next!=l){
    ch.convex_hull.push_back(traverse->p);
    traverse = traverse->next;
  }
  ch.convex_hull.push_back(traverse->p);
  ///Print time taken.
  printf("Time taken: %.2fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);   
  ch.output();
}