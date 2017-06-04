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


	std::vector <int> rank;
private:
	std::vector <int> parent;
};