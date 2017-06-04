#include "graph.h"
#include <iostream>
#include <ctime>
#include <omp.h>
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
	//al.readGraph("test/test_list.txt");
	am.readGraph("test/test_matx.txt");
	//le.readGraph("test/test_edge.txt");
	//test(1, temp);
	//test(1, le); test(2, le); test(3, le);
	//test(1, al); test(2, al); test(3, al);
	test(1, am); test(2, am); 
	test(3, am);

	system("pause");
	return 0;
}