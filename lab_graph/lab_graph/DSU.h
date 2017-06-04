#pragma once
#include <vector>
class DSU
{
public:
	DSU();
	DSU(int N);//����������� ������� ���������������� �������� �� N ���������
	int find(int x);
	void unite(int x, int y);
	~DSU();
private:
	std::vector <int> parent;
	std::vector <int> rank;
};