#include <fstream>
#include <string>
#include <iostream>
#include "graph.h"

using namespace std;

Graph::Graph()
{
}

Graph::~Graph()
{
}
void Graph::readGraph(string fileName)
{
	char s;
	int n, m;
	
}
//добавлеие ребра
void Graph::addEdge(int from, int to, int weight)
{
}
//удаление ребра
void Graph::removeEdge(int from, int to)
{
}
//изменение веса ребра
int Graph::changeEdge(int from, int to, int newWeight)
{
}
//перевод в список смежных вершин
void Graph::transformToAdjList()
{};
//перевод в матрицу смежности
void Graph::transformToAdjMatrix()
{};
//перевод в список рёбер
void Graph::transformToListOfEdges()
{};
//вывод графа
void Graph::writeGraph(std::string fileName)
{};
char Graph::type_g()
{	
	return this->type;
};