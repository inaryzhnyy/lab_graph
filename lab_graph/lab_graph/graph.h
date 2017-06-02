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

//�E� � ��������� ������������� ������ �����, LOE//�L� � ��������� ������������� ������ ������� ������ AdjList
//�C� � ��������� ������������� ������� ��������� AdjMatx

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
	std::vector <std::vector<int>> AdjLst;//������ ������� ������
	std::vector <std::vector <std::pair <int, int>>> AdjLst_W;//������ ������� ������ ����������

	std::vector<std::pair<int, int> >          LOE; // ������ �����
	std::vector<std::tuple<int, int, int> >    LOE_W; // ������ �����, ����������

	std::vector<std::vector<int>>             AdjMatx;  // ������� ���������



	char gtype;
	int direct;//���������������/���
	int gweight;//����������/���
	int n;//���������� ������ �����
	int m;//���������� ����

	//���������� �������
	Graph(int num, char intype);
	// ����������
	void readAdjMatx(FILE&);
	void readAdjList(FILE&);
	void readLOE(FILE&);

	// �����

	void writeAdjMatx(FILE&);
	void writeAdjList(FILE&);
	void writeLOE(FILE&);

	// ���������� �����
	void addEdgeAdjMatx(int from, int to, int weight=0);
	void addEdgeAdjList(int from, int to, int weight=0);
	void addEdgeLOE(int from, int to, int weight=0);
	
	//�������� �����

	void rmEdgeAdjMatx(int from, int to);
	void rmEdgeAdjList(int from, int to);
	void subRmEAL(int from, int to);
	void rmEdgeLOE(int from, int to);
	void subRmELOE(int from, int to);

	//��������������
	
	//������ ������� ������ � ������� ���������+
	void transfAdjLToAdjMatx();
	//������ ����� ������ � ������� ���������+
	void transfLOEToAdjMatx();
	//������� � ������ ������+
	void transfAdjMatxToAdjList(); 
	//���� � ������ ������+
	void transfLOEToAdjList(); 
	//������ ��������� � ������ �����- in3/ou3
	void transfAdjListToLOE();
	//������� ��������� � ������ �����- in1/ou3
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

