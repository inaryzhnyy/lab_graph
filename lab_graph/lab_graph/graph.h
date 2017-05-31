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
	int changeEdge(int from, int to, int newWeight);//���������� ������ �������� ���� �����
	void transformToAdjList();
	void transformToAdjMatrix();
	void transformToListOfEdges();
	void writeGraph(std::string fileName);	char type_g();

private:
	vector <vector<int>> AdjLst;//������ ������� ������
	vector <vector <pair <int, int>>> AdjLst_W;//������ ������� ������ ����������

	vector<pair<int, int> >          LOE; // ������ �����
	vector<tuple<int, int, int> >    LOE_W; // ������ �����, ����������

	vector<vector<int>>             AdjMatx;  // ������� ���������

	char type;
	int direct;//���������������/���
	int weight;//����������/���
	int n;//���������� ������ �����
	int m;//���������� ����

	//���������� �������

	// ����������
	void readAdjMatx(FILE&);
	void readAdjList(FILE&);
	void readLOE(FILE&);

	// �����

	void writeAdjMatx(FILE&);
	void writeAdjList(FILE&);
	void writeLOE(FILE&);
};

