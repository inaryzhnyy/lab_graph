#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <tuple>
//#include <algorithm>
#include <set>
//#include <queue>
//#include <stack>

//ТEТ Ч индикатор представлени€ список ребер, LOE//ТLТ Ч индикатор представлени€ список смежных вершин AdjList
//ТCТ Ч индикатор представлени€ матрица смежности AdjMatx

//using namespace std;

class Graph
{
public:
	Graph();
	~Graph();
	void readGraph(std::string fileName);
	void addEdge(int from, int to, int weight=0);
	void removeEdge(int from, int to);
	int changeEdge(int from, int to, int newWeight=0);
	void transformToAdjList();
	void transformToAdjMatrix();
	void transformToListOfEdges();
	void writeGraph(std::string fileName);
	//char type_g();

private:
	std::vector <std::vector<int>> AdjLst;//список смежных сершин
	std::vector <std::vector <std::pair <int, int>>> AdjLst_W;//список смежных вершин взвешенный

	std::vector<std::pair<int, int> >          LOE; // список ребер
	std::vector<std::tuple<int, int, int> >    LOE_W; // список ребер, взвешенный

	std::vector<std::vector<int>>             AdjMatx;  // матрица смежности



	char gtype;
	int direct;//ориентированный/нет
	int gweight;//взвешенный/нет
	int n;//количество вершин графа
	int m;//количество рЄбер

	//внутренние функции
	Graph(int num, char intype);
	// считывание
	void readAdjMatx(FILE&);
	void readAdjList(FILE&);
	void readLOE(FILE&);

	// вывод

	void writeAdjMatx(FILE&);
	void writeAdjList(FILE&);
	void writeLOE(FILE&);

	// добавление ребра
	void addEdgeAdjMatx(int from, int to, int weight=0);
	void addEdgeAdjList(int from, int to, int weight=0);
	void addEdgeLOE(int from, int to, int weight=0);
	
	//удаление ребра

	void rmEdgeAdjMatx(int from, int to);
	void rmEdgeAdjList(int from, int to);
	void subRmEAL(int from, int to);
	void rmEdgeLOE(int from, int to);
	void subRmELOE(int from, int to);

	//преобразование
	
	//список смежных вершин в матрицу смежности+
	void transfAdjLToAdjMatx();
	//список ребер вершин в матрицу смежности+
	void transfLOEToAdjMatx();
	//матрица в список вершин+
	void transfAdjMatxToAdjList(); 
	//рЄбра в список вершин+
	void transfLOEToAdjList(); 
	//—писок смежности в список ребер- in3/ou3
	void transfAdjListToLOE();
	//ћатрица смежности в список ребер- in1/ou3
	void transfAdjMatxToLOE();

	//change
	int changeAdjMatx(int from, int to, int weight=0);
	int changeAdjList(int from, int to, int weight=0);
	int changeLOE(int from, int to, int weight=0);

	int getmax();
	int getmaxMatx(int result);
	int getmaxAList(int result);
	int getmaxLOE(int result);
};

