#pragma once
#include <vector>
class DSU
{
public:
	DSU();
	DSU(int N);//конструктор системы непересекающихся множеств из N элементов
	int find(int x);
	void unite(int x, int y);
	~DSU();
private:
	std::vector <int> parent;
	std::vector <int> rank;
};