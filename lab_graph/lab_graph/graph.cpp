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
//��������� �����
void Graph::addEdge(int from, int to, int weight)
{
}
//�������� �����
void Graph::removeEdge(int from, int to)
{
}
//��������� ���� �����
int Graph::changeEdge(int from, int to, int newWeight)
{
}
//������� � ������ ������� ������
void Graph::transformToAdjList()
{};
//������� � ������� ���������
void Graph::transformToAdjMatrix()
{};
//������� � ������ ����
void Graph::transformToListOfEdges()
{};
//����� �����
void Graph::writeGraph(std::string fileName)
{};
char Graph::type_g()
{	
	return this->type;
};