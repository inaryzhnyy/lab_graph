#pragma once
#include <string>
#include <vector>
#include <set>

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
	vector <vector<pair <int, int>>> AdjLst;//список смежных сершин
	vector <vector <tuple <int, int, int>>> AdjLst_W;//список смежных вершин взвешенный

	vector<pair<int, int> >          LOE; // список ребер
	vector<tuple<int, int, int> >    LOE_W; // список ребер, взвешенный

	vector<vector<int>>             AdjMatx;  // матрица смежности

	char type;
	bool direct;//ориентированный/нет
	bool weight;//взвешенный/нет
	int n;//количество вершин графа
	int m;//количество рёбер

};

