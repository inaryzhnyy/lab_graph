#include "graph.h"
#include <iostream>

//using namespace std;

int main()
{
	Graph temp = Graph();
	Graph res = Graph();
	temp.readGraph("in3.txt");
	//temp.writeGraph("out3.txt");
	//temp.transformToAdjList();
	//temp.writeGraph("out2.txt");
	//temp.transformToListOfEdges();
	//temp.writeGraph("out3.txt");
	//temp.transformToAdjMatrix();
	//temp.writeGraph("out1.txt");
	//res = temp.getSpaingTreePrima();	
	//temp.writeGraph("out1.txt");
	res = temp.getSpaingTreeKruscal();
	res.transformToAdjMatrix();
	res.writeGraph("out4.txt");
	return 0;
}