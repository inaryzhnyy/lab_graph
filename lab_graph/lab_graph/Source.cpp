#include "graph.h"
#include <iostream>
#include <ctime>
//using namespace std;



void test(int n, Graph temp) {
	Graph res = Graph();
	clock_t t0, t1;
	switch (n)
	{

		case 1:
		{
		t0 = clock();
		res = temp.getSpaingTreeKruscal();
		t1 = clock();
		printf("%f\n", (double)(t1 - t0) / CLOCKS_PER_SEC);
		break;
		}
		case 2:
		{
			t0 = clock();
			res = temp.getSpaingTreePrima();
			t1 = clock();
			printf("%f\n", (double)(t1 - t0) / CLOCKS_PER_SEC);
			break;
		}
		case 3:
		{
			t0 = clock();
			res = temp.getSpaingTreeBoruvka();
			t1 = clock();
			printf("%f\n", (double)(t1 - t0) / CLOCKS_PER_SEC);
			break;
		}
}
}

int main()
{
	//std::vector<std::string> 
	Graph al = Graph();
	Graph le = Graph();
	Graph am = Graph();
	al.readGraph("test/test_al_big.txt");
	am.readGraph("test/test_am_big.txt");
	le.readGraph("test/test_le_big.txt");
	//test(1, temp);
	test(1, le); test(2, le); test(3, le);
	test(1, al); test(2, al); test(3, al);
	test(1, am); test(2, am); test(3, am);
	//test(3, temp);
	//temp.readGraph("in2.txt");
	//temp.writeGraph("out3.txt");
	//temp.transformToAdjList();
	//temp.writeGraph("out2.txt");
	//temp.transformToListOfEdges();
	//temp.writeGraph("out3.txt");
	//temp.transformToAdjMatrix();
	//temp.writeGraph("out1.txt");

	//res.transformToAdjMatrix();
	//res.writeGraph("out4.txt");
	system("pause");
	return 0;
}