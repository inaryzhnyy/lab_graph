#include "graph.h"
#include <iostream>

//using namespace std;

int main()
{
	Graph temp = Graph();
	temp.readGraph("in2.txt");
	temp.writeGraph("out3.txt");
	temp.transformToAdjList();
	temp.writeGraph("out2.txt");
	//transformToListOfEdges();
	//temp.writeGraph("out3.txt");
	temp.transformToAdjMatrix();
	temp.writeGraph("out1.txt");
	return 0;
}