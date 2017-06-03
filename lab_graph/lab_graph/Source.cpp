#include "graph.h"
#include <iostream>

//using namespace std;

int main()
{
	Graph temp = Graph();
	Graph res = Graph();
	temp.readGraph("test/test_al_min.txt");
	//temp.readGraph("in2.txt");
	//temp.writeGraph("out3.txt");
	//temp.transformToAdjList();
	//temp.writeGraph("out2.txt");
	//temp.transformToListOfEdges();
	//temp.writeGraph("out3.txt");
	//temp.transformToAdjMatrix();
	//temp.writeGraph("out1.txt");
	//res = temp.getSpaingTreeKruscal();
	//res = temp.getSpaingTreePrima();
	res = temp.getSpaingTreeBoruvka();
	//res.transformToAdjMatrix();
	//res.writeGraph("out4.txt");
	system("pause");
	return 0;
}