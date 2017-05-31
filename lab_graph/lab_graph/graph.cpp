#include <fstream>
#include <string>
#include <iostream>
#include "graph.h"

using namespace std;

Graph::Graph()
{
	type = 0;
	direct = 0;
	weight = 0;
	n = m = 0;
}

Graph::~Graph()
{
}

void Graph::readGraph(string fileName) 
{
		FILE *file;
		file = fopen(fileName.c_str() , "r");

		fscanf(file, "%c", &type);

		switch (type) {
		case 'E': // ������ �����
			readLOE(*file);
			break;
		case 'C': // ������� ���������
			readAdjMatx(*file);
			break;
		case 'L': // ������ ������� ������
			readAdjList(*file);
			break;		
		}
		fclose(file);
	}

void Graph::readAdjMatx(FILE & file) {
	fscanf(&file, "%d%d%d", &n, &direct, &weight);

	int k;
	AdjMatx.resize(n);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			fscanf(&file, "%d", &k);
			AdjMatx[i].push_back(k);
			if (AdjMatx[i][j])
				m++;
		}
	}
	m = m/2;
}

void Graph::readAdjList(FILE & file) {
	const int max_el = 200000;
	char str[max_el];

	fscanf(&file, "%d%d%d", &n, &direct, &weight);
	fgets(str, max_el, &file);

	AdjLst.resize(n);
	AdjLst_W.resize(n);
	for (int i = 0; i < n; i++) {
		fgets(str, max_el, &file);
		vector<string> arr;
		string digit = "";
		for (int j = 0; j < max_el; j++) {
			if (str[j] == '\0' || str[j] == '\n') {
				if (digit != "")
					arr.push_back(digit);
				break;
			}

			if (str[j] == ' ' && digit != "") {
				arr.push_back(digit);
				digit = "";
				continue;
			}

			digit += str[j];
		}
		if (arr[arr.size() - 1] == "")
			arr.pop_back();
		if (weight) {
			for (int j = 0; j < arr.size(); j += 2) {
				if (stoi(arr[j])) {
					AdjLst_W[i].push_back(make_pair(stoi(arr[j]), stoi(arr[j + 1])));
					m++;
				}
			}
		}
		else {
			for (int j = 0; j < arr.size(); j++) {
				if (stoi(arr[j])) {
					AdjLst[i].push_back(stoi(arr[j]));
					m++;
				}
			}
		}
	}
	m /= 2;
}

void Graph::readLOE(FILE & file) {
	fscanf(&file, "%d%d%d%d", &n, &m, &direct, &weight);

	int firstv, secondv, weightv;
	if (weight) {
		while (!feof(&file)) {
			fscanf(&file, "%d%d%d", &firstv, &secondv, &weightv);
			LOE_W.push_back(make_tuple(firstv, secondv, weightv));
		}
		if (LOE_W.size() > 1) {
			int pre_frst = get<0>(LOE_W[LOE_W.size() - 2]);
			int pre_sec = get<1>(LOE_W[LOE_W.size() - 2]);
			int curr_frst = get<0>(LOE_W[LOE_W.size() - 1]);
			int curr_sec = get<1>(LOE_W[LOE_W.size() - 1]);
			if (pre_frst == curr_frst && pre_sec == curr_sec)
				LOE_W.pop_back();
		}
	}
	else {
		while (!feof(&file)) {
			fscanf(&file, "%d%d", &firstv, &secondv);
			LOE.push_back(make_pair(firstv, secondv));
		}
		if (LOE.size() > 1) {
			int pre_frst = LOE[LOE.size() - 2].first;
			int pre_sec = LOE[LOE.size() - 2].second;
			int curr_frst = LOE[LOE.size() - 1].first;
			int curr_sec = LOE[LOE.size() - 1].second;
			if (pre_frst == curr_frst && pre_sec == curr_sec)
				LOE.pop_back();
		}
	}
}

void Graph::writeGraph(string fileName) {

	FILE *file;
	file = fopen(fileName.c_str(), "w");

	fprintf(file, "%c", type);

	switch (type) {
	case 'C':
		writeAdjMatx(*file);
		break;

	case 'L':
		writeAdjList(*file);
		break;

	case 'E':
		writeLOE(*file);
		break;
	}

	fclose(file);
}

void Graph::writeAdjMatx(FILE & file) {
	fprintf(&file, " %d\n%d %d\n", n, direct, weight);

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			fprintf(&file, "%d ", AdjMatx[i][j]);
		}
		fprintf(&file, "\n");
	}
}

void Graph::writeAdjList(FILE & file) {
	fprintf(&file, " %d\n%d %d\n", n, direct, weight);

	if (weight) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < AdjLst_W[i].size(); j++) {
				if (AdjLst_W[i][j].first && AdjLst_W[i][j].second)
					fprintf(&file, "%d %d ", AdjLst_W[i][j].first, AdjLst_W[i][j].second);
			}
			fprintf(&file, "\n");
		}
	}
	else {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < AdjLst[i].size(); j++) {
				if (AdjLst[i][j])
					fprintf(&file, "%d ", &AdjLst[i][j]);
			}
			fprintf(&file, "\n");
		}
	}
}

void Graph::writeLOE(FILE & file) {
	fprintf(&file, " %d %d\n%d %d\n", n, m, direct, weight);

	if (weight) {
		for (int i = 0; i < m; i++) {
			if (get<0>(LOE_W[i]) && get<1>(LOE_W[i]))
				fprintf(&file, "%d %d %d\n", get<0>(LOE_W[i]), get<1>(LOE_W[i]), get<2>(LOE_W[i]));
		}
	}
	else {
		for (int i = 0; i < m; i++) {
			if (LOE[i].first && LOE[i].second)
				fprintf(&file, "%d %d\n", LOE[i].first, LOE[i].second);
		}
	}
}

//���������� �����

void Graph::addEdge(int from, int to, int weight) 
{	
	if (!weight) weight = 1;
	--from;
	--to;
	switch (type) 
	{
	case 'C':
		addEdgeAdjMatx(from, to, weight);
		break;

	case 'L':
		addEdgeAdjList(from, to, weight);
		break;

	case 'E':
		addEdgeLOE(from, to, weight);
		break;
	}

}

void Graph::addEdgeAdjMatx(int from, int to, int weight) 
{
	AdjMatx[from][to] = weight;
	if (!direct) 
	{
		AdjMatx[to][from] = weight;
	}
}

void Graph::addEdgeAdjList(int from, int to, int weight) {
	if (weight) {
		AdjLst_W[from].push_back(make_pair(to + 1, weight));
		if (!direct)
			AdjLst_W[to].push_back(make_pair(from + 1, weight));
	}
	else {
		AdjLst[from].push_back(to + 1);
		if (!direct)
			AdjLst[to].push_back(from + 1);
	}
}

void Graph::addEdgeLOE(int from, int to, int weight) 
{
	if (weight) 
	{
		LOE_W.push_back(make_tuple(from + 1, to + 1, weight));
	}
	else
	{
		LOE.push_back(make_pair(from + 1, to + 1));
	}
	m++;
}

//�������� �����

void Graph::removeEdge(int from, int to) {

	--from;
	--to;
	switch (type) {
	case 'C':
		rmEdgeAdjMatx(from, to);
		break;
	case 'L':
		rmEdgeAdjList(from, to);
		break;
	case 'E':
		rmEdgeLOE(from, to);
		break;
	}
}

void Graph::rmEdgeAdjMatx(int from, int to) {
	AdjMatx[from][to] = 0;
	if (!direct)
		AdjMatx[to][from] = 0;
}

void subRmEAL(int from, int to) {

}

void Graph::rmEdgeAdjList(int from, int to)
{
	if (weight)
	{
		for (int i = 0; i < AdjLst_W[from].size(); i++) {
			if (AdjLst_W[from][i].first == to + 1) {
				AdjLst_W[from][i].first = 0;
				AdjLst_W[from][i].second = 0;
			}
		}
		if (!direct) {
			for (int i = 0; i < AdjLst_W[to].size(); i++) {
				if (AdjLst_W[to][i].first == from + 1) {
					AdjLst_W[to][i].first = 0;
					AdjLst_W[to][i].second = 0;
					return;
				}
			}
		}
	}
	else {
		for (int i = 0; i < AdjLst[from].size(); i++) {
			if (AdjLst[from][i] == to + 1) {
				AdjLst[from][i] = 0;
				AdjLst[from][i] = 0;
			}
		}
		if (!direct) {
			for (int i = 0; i < AdjLst[to].size(); i++) {
				if (AdjLst[to][i] == from + 1) {
					AdjLst[to][i] = 0;
					AdjLst[to][i] = 0;
					return;
				}
			}
		}
	}
}

void Graph::rmEdgeLOE(int from, int to) {
	if (weight) {
		for (int i = 0; i < LOE_W.size(); i++) {
			if (get<0>(LOE_W[i]) == from + 1 && get<1>(LOE_W[i]) == to + 1) {
				get<0>(LOE_W[i]) = 0;
				get<1>(LOE_W[i]) = 0;
				get<2>(LOE_W[i]) = 0;
				return;
			}
			if (!direct) {
				if (get<0>(LOE_W[i]) == to + 1 && get<1>(LOE_W[i]) == from + 1) {
					get<0>(LOE_W[i]) = 0;
					get<1>(LOE_W[i]) = 0;
					get<2>(LOE_W[i]) = 0;
					return;
				}
			}
		}
	}
	else {
		for (int i = 0; i < LOE.size(); i++) {
			if (LOE[i].first == from + 1 && LOE[i].second == to + 1) {
				LOE[i].first = 0;
				LOE[i].second = 0;
				return;
			}
			if (!direct) {
				if (LOE[i].first == to + 1 && LOE[i].second == from + 1) {
					LOE[i].first = 0;
					LOE[i].second = 0;
					return;
				}
			}
		}
	}
}


int Graph::changeEdge(int from, int to, int newWeight)
{
	return 0;
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

char Graph::type_g()
{	
	return this->type;
};