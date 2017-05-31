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
	int changeEdge(int from, int to, int newWeight);//���������� ������ �������� ���� �����
	void transformToAdjList();
	void transformToAdjMatrix();
	void transformToListOfEdges();
	void writeGraph(std::string fileName);	char type_g();

private:
	vector <vector<pair <int, int>>> AdjLst;//������ ������� ������
	vector <vector <tuple <int, int, int>>> AdjLst_W;//������ ������� ������ ����������

	vector<pair<int, int> >          LOE; // ������ �����
	vector<tuple<int, int, int> >    LOE_W; // ������ �����, ����������

	vector<vector<int>>             AdjMatx;  // ������� ���������

	char type;
	bool direct;//���������������/���
	bool weight;//����������/���
	int n;//���������� ������ �����
	int m;//���������� ����

};

