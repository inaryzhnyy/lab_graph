#pragma once
#include <string>
#include <vector>
#include <set>
#include <tuple>
#include <algorithm>


using namespace std;
class Graph
{
public:
	Graph();
	~Graph();
	void readGraph(string fileName);
	void addEdge(int from, int to, int weight);
	void removeEdge(int from, int to);
	int changeEdge(int from, int to, int newWeight);//возвращает старое значение веса ребра
	void transformToAdjList();
	void transformToAdjMatrix();
	void transformToListOfEdges();
	void writeGraph(std::string fileName);	char type_g();

private:
	vector <vector<int>> AdjLst;//список смежных сершин
	vector <vector <pair <int, int>>> AdjLst_W;//список смежных вершин взвешенный

	vector<pair<int, int> >          LOE; // список ребер
	vector<tuple<int, int, int> >    LOE_W; // список ребер, взвешенный

	vector<vector<int>>             AdjMatx;  // матрица смежности

	char type;
	int direct;//ориентированный/нет
	int weight;//взвешенный/нет
	int n;//количество вершин графа
	int m;//количество рёбер

	//внутренние функции

	// считывание
	void readAdjMatx(FILE&);
	void readAdjList(FILE&);
	void readLOE(FILE&);

	// вывод

	void writeAdjMatx(FILE&);
	void writeAdjList(FILE&);
	void writeLOE(FILE&);

	// добавление ребра
	void addEdgeAdjMatx(int from, int to, int weight);
	void addEdgeAdjList(int from, int to, int weight);
	void addEdgeLOE(int from, int to, int weight);
	
	//удаление ребра

	void rmEdgeAdjMatx(int from, int to);
	void rmEdgeAdjList(int from, int to);
	void subRmEAL(int from, int to);
	void rmEdgeLOE(int from, int to);
	void subRmELOE(int from, int to);
};

