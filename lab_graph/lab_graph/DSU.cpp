#include "DSU.h"

DSU::DSU()
{
}

DSU::~DSU()
{
}

DSU::DSU(int num)
{
	parent.resize(num);
	for (int i = 0; i < parent.size(); i++) {
		parent[i] = i;
	}
	rank.resize(num);
	fill(rank.begin(), rank.end(), 1);
}

int DSU::find(int x)
{
	return (x == parent[x] ? x : parent[x] = find(parent[x]));
}

void DSU::unite(int x, int y)
{
	if ((x = find(x)) == (y = find(y)))
		return;

	if (rank[x] <  rank[y])
		parent[x] = y;
	else
		parent[y] = x;

	rank[x] += rank[y];
}

