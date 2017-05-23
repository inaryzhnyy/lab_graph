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
	void writeGraph(std::string fileName);
private:
	vector <set<pair <int, int>>> LOV;//список смежных сершин
	vector <set <tuple <int, int, int>>> LOV_W;//список смежных вершин взвешенный

	vector<pair<int, int> >          LOE; // список ребер
	vector<tuple<int, int, int> >    LOE_W; // список ребер, взвешенный

};

Graph::Graph()
{
}

Graph::~Graph()
{
}