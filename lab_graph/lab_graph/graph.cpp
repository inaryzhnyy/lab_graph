#include "graph.h"

//using namespace std;
bool comapre(const std::tuple<int, int, int>& first, const std::tuple<int, int, int>& second);
Graph::Graph()
{
	gtype = 0;
	direct = 0;
	gweight = 0;
	n = m = 0;
}

Graph::Graph(int num, char intype)
{
	n = num;
	m = 0;
	gtype = intype;
	direct = 0;
	gweight = 1;

	switch (gtype)
	{
	case 'C':
	{
		AdjMatx.resize(n);
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				AdjMatx[i].push_back(0);
			}
		}
	}
	break;
	case 'L': { AdjLst_W.resize(n); break; }
	case 'E':
		break;
	}
}

Graph::~Graph()
{
}

void Graph::readGraph(std::string fileName)
{
	FILE *file;
	file = fopen(fileName.c_str(), "r");

	fscanf(file, "%c", &gtype);

	switch (gtype) {
	case 'E': // список ребер
		readLOE(*file);
		break;
	case 'C': // ћатрица смежности
		readAdjMatx(*file);
		break;
	case 'L': // —писок смежных вершин
		readAdjList(*file);
		break;
	}
	fclose(file);
}

void Graph::readAdjMatx(FILE & file) {
	fscanf(&file, "%d%d%d", &n, &direct, &gweight);

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
	m = m / 2;
}

void Graph::readAdjList(FILE & file) {
	const int max_el = 200000;
	char str[max_el];

	fscanf(&file, "%d%d%d", &n, &direct, &gweight);
	fgets(str, max_el, &file);

	AdjLst.resize(n);
	AdjLst_W.resize(n);
	for (int i = 0; i < n; i++) {
		fgets(str, max_el, &file);
		std::vector<std::string> arr;
		std::string digit = "";
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
		if (gweight) {
			for (int j = 0; j < arr.size(); j += 2) {
				if (stoi(arr[j])) {
					AdjLst_W[i].push_back(std::make_pair(stoi(arr[j]), stoi(arr[j + 1])));
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
	fscanf(&file, "%d%d%d%d", &n, &m, &direct, &gweight);

	int firstv, secondv, weightv;
	if (gweight) {
		while (!feof(&file)) {
			fscanf(&file, "%d%d%d", &firstv, &secondv, &weightv);
			LOE_W.push_back(std::make_tuple(firstv, secondv, weightv));
		}
		if (LOE_W.size() > 1) {
			int pre_frst = std::get<0>(LOE_W[LOE_W.size() - 2]);
			int pre_sec = std::get<1>(LOE_W[LOE_W.size() - 2]);
			int curr_frst = std::get<0>(LOE_W[LOE_W.size() - 1]);
			int curr_sec = std::get<1>(LOE_W[LOE_W.size() - 1]);
			if (pre_frst == curr_frst && pre_sec == curr_sec)
				LOE_W.pop_back();
		}
	}
	else {
		while (!feof(&file)) {
			fscanf(&file, "%d%d", &firstv, &secondv);
			LOE.push_back(std::make_pair(firstv, secondv));
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

void Graph::writeGraph(std::string fileName) {

	FILE *file;
	file = fopen(fileName.c_str(), "w");

	fprintf(file, "%c", gtype);

	switch (gtype) {
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
	fprintf(&file, " %d\n%d %d\n", n, direct, gweight);

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			fprintf(&file, "%d ", AdjMatx[i][j]);
		}
		fprintf(&file, "\n");
	}
}

void Graph::writeAdjList(FILE & file) {
	fprintf(&file, " %d\n%d %d\n", n, direct, gweight);

	if (gweight) {
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
					fprintf(&file, "%d ", AdjLst[i][j]);
			}
			fprintf(&file, "\n");
		}
	}
}

void Graph::writeLOE(FILE & file) {
	fprintf(&file, " %d %d\n%d %d\n", n, m, direct, gweight);

	if (gweight) {
		for (int i = 0; i < m; i++) {
			if (std::get<0>(LOE_W[i]) && std::get<1>(LOE_W[i]))
				fprintf(&file, "%d %d %d\n", std::get<0>(LOE_W[i]), std::get<1>(LOE_W[i]), std::get<2>(LOE_W[i]));
		}
	}
	else {
		for (int i = 0; i < m; i++) {
			if (LOE[i].first && LOE[i].second)
				fprintf(&file, "%d %d\n", LOE[i].first, LOE[i].second);
		}
	}
}

//добавление ребра

void Graph::addEdge(int from, int to, int weight)
{
	if (!weight) weight = 1;
	--from;
	--to;
	switch (gtype)
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
	if (gweight) {
		AdjLst_W[from].push_back(std::make_pair(to + 1, weight));
		if (!direct)
			AdjLst_W[to].push_back(std::make_pair(from + 1, weight));
	}
	else {
		AdjLst[from].push_back(to + 1);
		if (!direct)
			AdjLst[to].push_back(from + 1);
	}
}

void Graph::addEdgeLOE(int from, int to, int weight)
{
	if (gweight)
	{
		LOE_W.push_back(std::make_tuple(from + 1, to + 1, weight));
	}
	else
	{
		LOE.push_back(std::make_pair(from + 1, to + 1));
	}
	m++;
}

//удаление ребра

void Graph::removeEdge(int from, int to) {

	--from;
	--to;
	switch (gtype) {
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
	if (gweight)
	{
		for (int i = 0; i < AdjLst_W[from].size(); i++)
		{
			if (AdjLst_W[from][i].first == to + 1) {
				AdjLst_W[from][i].first = 0;
				AdjLst_W[from][i].second = 0;
			}
		}
		if (!direct) {
			for (int i = 0; i < AdjLst_W[to].size(); i++)
			{
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
	if (gweight) {
		for (int i = 0; i < LOE_W.size(); i++) {
			if (std::get<0>(LOE_W[i]) == from + 1 && std::get<1>(LOE_W[i]) == to + 1) {
				std::get<0>(LOE_W[i]) = 0;
				std::get<1>(LOE_W[i]) = 0;
				std::get<2>(LOE_W[i]) = 0;
				return;
			}
			if (!direct) {
				if (std::get<0>(LOE_W[i]) == to + 1 && std::get<1>(LOE_W[i]) == from + 1) {
					std::get<0>(LOE_W[i]) = 0;
					std::get<1>(LOE_W[i]) = 0;
					std::get<2>(LOE_W[i]) = 0;
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

//перевод в матрицу смежности
void Graph::transformToAdjMatrix()
{
	if (gtype == 'C') return;
	AdjMatx.clear();
	AdjMatx.resize(n);
	for (int i = 0; i < AdjMatx.size(); i++)
	{
		AdjMatx[i].resize(n);
		for (int j = 0; j < AdjMatx[i].size(); j++)
		{
			AdjMatx[i][j] = 0;
		}
	}
	switch (gtype)
	{
	case 'L':
		transfAdjLToAdjMatx();
		break;
	case 'E':
		transfLOEToAdjMatx();
		break;
	}
	gtype = 'C';
}
//перевод в список смежности
void Graph::transformToAdjList()
{
	if (gtype == 'L') return;
	AdjLst.clear();
	AdjLst_W.clear();

	if (gweight)
	{
		AdjLst_W.resize(n);
	}
	else
	{
		AdjLst.resize(n);
	}

	switch (gtype)
	{
	case 'C':
		transfAdjMatxToAdjList();
		break;
	case 'E':
		transfLOEToAdjList();
		break;
	}

	gtype = 'L';
}
//перевод в список рЄбер
void Graph::transformToListOfEdges()
{
	if (gtype == 'E') return;

	LOE.clear();
	LOE_W.clear();

	switch (gtype)
	{
	case 'C':
		transfAdjMatxToLOE();
		break;
	case 'L':
		transfAdjListToLOE();
		break;
	}
	gtype = 'E';
}

void Graph::transfAdjLToAdjMatx()
{
	if (gweight)
	{
		for (int i = 0; i < AdjLst_W.size(); i++)
		{
			for (int j = 0; j < AdjLst_W[i].size(); j++)
			{
				if (AdjLst_W[i][j].first)
				{
					AdjMatx[i][AdjLst_W[i][j].first - 1] = AdjLst_W[i][j].second;
					if (!direct)
						AdjMatx[AdjLst_W[i][j].first - 1][i] = AdjLst_W[i][j].second;
				}
			}
		}
	}
	else
	{
		for (int i = 0; i < AdjLst.size(); i++)
		{
			for (int j = 0; j < AdjLst[i].size(); j++)
			{
				if (AdjLst[i][j])
				{
					AdjMatx[i][AdjLst[i][j] - 1] = 1;
					if (!direct)
						AdjMatx[AdjLst[i][j] - 1][i] = 1;
				}
			}
		}
	}
}

void Graph::transfLOEToAdjMatx()
{
	if (gweight)
	{
		for (int i = 0; i < LOE_W.size(); i++)
		{
			AdjMatx[std::get<0>(LOE_W[i]) - 1][std::get<1>(LOE_W[i]) - 1] = std::get<2>(LOE_W[i]);
			if (!direct)
				AdjMatx[std::get<1>(LOE_W[i]) - 1][std::get<0>(LOE_W[i]) - 1] = std::get<2>(LOE_W[i]);
		}
	}
	else
	{
		for (int i = 0; i < LOE.size(); i++)
		{
			AdjMatx[LOE[i].first - 1][LOE[i].second - 1] = 1;
			if (!direct)
				AdjMatx[LOE[i].second - 1][LOE[i].first - 1] = 1;
		}
	}
}

void Graph::transfAdjMatxToAdjList()
{
	if (gweight)
	{
		for (int i = 0; i < AdjMatx.size(); i++)
		{
			for (int j = 0; j < AdjMatx[i].size(); j++)
			{
				if (AdjMatx[i][j])
					AdjLst_W[i].push_back(std::make_pair(j + 1, AdjMatx[i][j]));
			}
		}
	}
	else
	{
		for (int i = 0; i < AdjMatx.size(); i++)
		{
			for (int j = 0; j < AdjMatx[i].size(); j++)
			{
				if (AdjMatx[i][j])
					AdjLst[i].push_back(j + 1);
			}
		}
	}
}

void Graph::transfLOEToAdjList()
{
	if (gweight)
	{
		AdjLst_W.resize(n);
		for (int i = 0; i < LOE_W.size(); i++)
		{
			bool next = false;
			for (int j = 0; j < AdjLst_W[std::get<0>(LOE_W[i]) - 1].size(); j++)
			{
				if (AdjLst_W[std::get<0>(LOE_W[i]) - 1][j].first == std::get<1>(LOE_W[i]))
				{
					next = true;
					break;
				}
			}
			if (next)
				continue;
			AdjLst_W[std::get<0>(LOE_W[i]) - 1].push_back(std::make_pair(std::get<1>(LOE_W[i]), std::get<2>(LOE_W[i])));
			if (!direct) {
				AdjLst_W[std::get<1>(LOE_W[i]) - 1].push_back(std::make_pair(std::get<0>(LOE_W[i]), std::get<2>(LOE_W[i])));
			}
		}
	}
	else
	{
		AdjLst.resize(n);
		for (int i = 0; i < LOE.size(); i++)
		{
			bool next = false;
			for (int j = 0; j < AdjLst[LOE[i].first - 1].size(); j++)
			{
				if (AdjLst[LOE[i].first - 1][j] == LOE[i].second)
				{
					next = true;
					break;
				}
			}
			if (next)
				continue;

			AdjLst[LOE[i].first - 1].push_back(LOE[i].second);
			if (!direct)
			{
				AdjLst[LOE[i].second - 1].push_back(LOE[i].first);
			}
		}
	}
}

void Graph::transfAdjMatxToLOE()
{
	gtype = 'E';
	int k = m;
	for (int i = 0; i < AdjMatx.size(); i++)
	{
		for (int j = 0; j < AdjMatx[i].size(); j++)
		{
			if (AdjMatx[i][j])
			{
				if (direct) {
					addEdge(i + 1, j + 1, AdjMatx[i][j]);
				}
				else
				{
					if (i <= j)
						addEdge(i + 1, j + 1, AdjMatx[i][j]);
				}
			}
		}
	}
	if (direct) m = k; else { m -= k; };
}

void Graph::transfAdjListToLOE()
{
	gtype = 'E';
	int k = m;
	if (direct)//in direct
	{
		if (gweight)
		{
			for (int i = 0; i < AdjLst_W.size(); i++)
			{
				for (int j = 0; j < AdjLst_W[i].size(); j++)
				{
					if (AdjLst_W[i][j].first)
						addEdge(i + 1, AdjLst_W[i][j].first, AdjLst_W[i][j].second);
				}
			}
		}
		else
		{
			for (int i = 0; i < AdjLst.size(); i++)
			{
				for (int j = 0; j < AdjLst[i].size(); j++)
				{
					if (AdjLst[i][j])
						addEdge(i + 1, AdjLst[i][j]);
				}
			}
		}
		m = k;
	}
	else {
		if (gweight)
		{
			for (int i = 0; i < AdjLst_W.size(); i++)
			{
				for (int j = 0; j < AdjLst_W[i].size(); j++)
				{
					if ((AdjLst_W[i][j].first) && (i <= j))
						addEdge(i + 1, AdjLst_W[i][j].first, AdjLst_W[i][j].second);
				}
			}
		}
		else
		{
			for (int i = 0; i < AdjLst.size(); i++)
			{
				for (int j = 0; j < AdjLst[i].size(); j++)
				{
					if ((AdjLst[i][j]) && (i <= j))
						addEdge(i + 1, AdjLst[i][j]);
				}
			}
		}
		m = m - k;
	};
}

int Graph::changeEdge(int from, int to, int weight) {

	--from;
	--to;

	switch (gtype)
	{
	case 'C':
		return changeAdjMatx(from, to, weight);
		break;
	case 'L':
		return changeAdjList(from, to, weight);
		break;
	case 'E':
		return changeLOE(from, to, weight);
		break;
	}

	return 0;
}

int Graph::changeAdjMatx(int from, int to, int weight) {
	int origin_weight = AdjMatx[from][to];

	if (AdjMatx[from][to]) {
		AdjMatx[from][to] = weight;
		if (!direct) {
			AdjMatx[to][from] = weight;
		}
	}

	return origin_weight;
}

int Graph::changeAdjList(int from, int to, int weight) {
	int origin_weight = 0;

	if (gweight) {
		for (int i = 0; i < AdjLst_W[from].size(); i++) {
			if (AdjLst_W[from][i].first == to + 1) {
				origin_weight = AdjLst_W[from][i].second;
				AdjLst_W[from][i].second = weight;
			}
		}
		if (!direct) {
			for (int i = 0; i < AdjLst_W[to].size(); i++) {
				if (AdjLst_W[to][i].first == from + 1) {
					AdjLst_W[to][i].second = weight;
				}
			}
		}
	}

	return origin_weight;
}

int Graph::changeLOE(int from, int to, int weight)
{
	int origin_weight = 0;
	if (gweight) {
		for (int i = 0; i < LOE_W.size(); i++) {
			if (std::get<0>(LOE_W[i]) == from + 1 && std::get<1>(LOE_W[i]) == to + 1) {
				origin_weight = std::get<2>(LOE_W[i]);
				std::get<2>(LOE_W[i]) = weight;
			}
			if (!direct) {
				if (std::get<0>(LOE_W[i]) == to + 1 && std::get<1>(LOE_W[i]) == from + 1) {
					std::get<2>(LOE_W[i]) = weight;
				}
			}
		}
	}
	return origin_weight;
}

int Graph::getmax()
{
	int result = 0;
	switch (gtype)
	{
	case 'C': {return getmaxMatx(result); };
	case 'L': {return getmaxAList(result); };
	case 'E': {return getmaxLOE(result); };
	}
}
int Graph::getmaxMatx(int result)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (AdjMatx[i][j] > result)
			{
				result = AdjMatx[i][j];
			}
		}
	}
	return result;
}
int Graph::getmaxAList(int result)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < AdjLst_W[i].size(); j++)
		{
			if (AdjLst_W[i][j].second > result)
			{
				result = AdjLst_W[i][j].second;
			}
		}
	}
	return result;
}
int Graph::getmaxLOE(int result)
{
	for (int i = 0; i < LOE_W.size(); i++)
	{
		if (std::get<2>(LOE_W[i]) > result)
		{
			result = std::get<2>(LOE_W[i]);
		}
	}
	return result;
}
//јлгоритм ѕрима
Graph Graph::getSpaingTreePrima()
{
	switch (gtype)
	{
	case 'C':
	{
		return PrimMatx();
		break;
	}
	case 'L':
	{
		return PrimAdjList();
		break;
	}
	case 'E':
	{
		this->transformToAdjList();
		return PrimAdjList();
		break;
	}
	}
	return *this;
}
Graph Graph::PrimMatx()
{
	Graph result_graph = Graph(n, gtype);
	std::vector <bool> visited(n, false);			 // посещенные вершины
	std::vector <int> min_edge(n, getmax() + 1);     // мин ребра
	std::vector <int> selected(n, -1);				 // вершины
	min_edge[0] = 0;

	for (int i = 0; i < n; i++) {
		int v = -1;
		for (int j = 0; j < n; j++) {
			if (!visited[j] && (v == -1 || min_edge[j] < min_edge[v])) {
				v = j;
			}
		}
		visited[v] = true;
		for (int to = 0; to < n; to++) {
			if (!visited[to] && AdjMatx[v][to] != 0 && AdjMatx[v][to] < min_edge[to]) {
				min_edge[to] = AdjMatx[v][to];
				selected[to] = v;
			}
		}
	}

	for (int i = 0; i < n; i++) {
		if (selected[i] != -1) {
			result_graph.addEdge(selected[i] + 1, i + 1, AdjMatx[selected[i]][i]);
		}
	}
	return result_graph;
}
Graph Graph::PrimAdjList()
{
	Graph result_graph = Graph(n, gtype);
	std::vector <bool> visited(n, false);			 // посещенные вершины
	std::vector <int> min_edge(n, getmax() + 1);     // мин ребра
	std::vector <int> selected(n, -1);				 // вершины
	std::set <std::pair<int, int>> newset;
	int prim = 0;
	while (prim < n) {
		min_edge[prim] = 0;
		newset.insert(std::make_pair(0, prim));

		while (!newset.empty()) {
			int v = newset.begin()->second;
			newset.erase(newset.begin());
			visited[v] = true;

			for (size_t j = 0; j < AdjLst_W[v].size(); j++)
			{
				int to = AdjLst_W[v][j].first - 1,
					sec = AdjLst_W[v][j].second;
				if (!visited[to] && sec < min_edge[to])
				{
					newset.erase(std::make_pair(min_edge[to], to));
					min_edge[to] = sec;
					selected[to] = v;
					newset.insert(std::make_pair(min_edge[to], to));
				}
			}
		}

		while (prim < n && visited[prim]) {
			prim++;
		}
	}
	for (int i = 0; i < n; i++) {
		if (selected[i] != -1) {
			result_graph.addEdge(selected[i] + 1, i + 1, min_edge[i]);
		}
	}
	return result_graph;
}
void Graph::reverseTransform(char type)
{
	switch (type)
	{
	case 'C': {this->transformToAdjMatrix(); break; }
	case 'L': {this->transformToAdjList(); break; }
	case 'E': {this->transformToListOfEdges(); break; }
	}
}

Graph Graph::getSpaingTreeKruscal()
{
	char old_type = gtype;
	this->transformToListOfEdges();
	Graph result = Graph(n, gtype);
	int val = 0;
	std::vector <std::pair<int, int> > res;
	DSU n_dsu = DSU(n);


	sort(LOE_W.begin(), LOE_W.end(), comapre);

	for (int i = 0; i < LOE_W.size(); i++) {
		int first = std::get<0>(LOE_W[i]) - 1,
			second = std::get<1>(LOE_W[i]) - 1,
			weight = std::get<2>(LOE_W[i]);

		if (n_dsu.find(first) != n_dsu.find(second))
		{
			val += weight;
			res.push_back(std::make_pair(first, second));
			n_dsu.unite(first, second);
			result.addEdge(first + 1, second + 1, weight);
		}
	}
	reverseTransform(old_type);
	return result;
}

Graph Graph::getSpaingTreeBoruvka()
{
	switch (gtype)
	{
	case 'C':
	{
		return BoruvkaMatx();
		break;
	}
	case 'L':
	{
		return BoruvkaAList();
		break;
	}
	case 'E':
	{
		return BoruvkaLOE();
		break;
	}
	}
	return *this;
}

Graph Graph::BoruvkaMatx()
{
	Graph result = Graph(n, gtype);
	DSU dsu = DSU(n);
	int val = 0;
	int max = getmax() + 1;
	int comp = 0;
	while (comp < n - 1) {
		int breaker = n;
		std::vector <int> min_edge(n, getmax() + 1);
		std::vector <int> selected(n, -1);
		for (int i = 0; i < AdjMatx.size(); i++) {
			for (int j = 0; j < AdjMatx[i].size(); j++) {
				int first = dsu.find(i);
				int second = dsu.find(j);
				int weight = AdjMatx[i][j];
				if (weight != 0 && first != second)
				{
					if (min_edge[first] > weight)
					{
						min_edge[first] = weight;
						selected[first] = second;
						breaker--;
					}
					if (min_edge[second] > weight)
					{
						min_edge[second] = weight;
						selected[second] = first;
						breaker--;
					}
				}
			}
		}
		if (!breaker)
			break;

		for (int i = 0; i < min_edge.size(); i++)
		{
			if (min_edge[i] != max && selected[i] != -1 && dsu.find(i) != dsu.find(selected[i]))
			{
				result.addEdge(i + 1, selected[i] + 1, min_edge[i]);
				val += min_edge[i];
				dsu.unite(i, selected[i]);
				comp++;
			}
		}
	}
	return result;
}

Graph Graph::BoruvkaAList()
{
	Graph result = Graph(n, gtype);
	DSU dsu = DSU(n);
	int val = 0;
	int max = getmax() + 1;
	int comp = 0;
	while (comp < n - 1) {
		int breaker = n;
		std::vector <int> min_edge(n, getmax() + 1);
		std::vector <int> selected(n, -1);
		{
			for (int i = 0; i < AdjLst_W.size(); i++) {
				for (int j = 0; j < AdjLst_W[i].size(); j++) {
					int first = dsu.find(i);
					int second = dsu.find(AdjLst_W[i][j].first - 1);
					int weight = AdjLst_W[i][j].second;
					if (first != second) {
						if (min_edge[first] > weight) {
							min_edge[first] = weight;
							selected[first] = second;
							breaker--;
						}
						if (min_edge[second] > weight) {
							min_edge[second] = weight;
							selected[second] = first;
							breaker--;
						}
					}
				}
			}
		}
		if (!breaker)
			break;

		for (int i = 0; i < min_edge.size(); i++)
		{
			if (min_edge[i] != max && selected[i] != -1 && dsu.find(i) != dsu.find(selected[i]))
			{
				result.addEdge(i + 1, selected[i] + 1, min_edge[i]);
				val += min_edge[i];
				dsu.unite(i, selected[i]);
				comp++;
			}
		}
	}
	return result;
}

Graph Graph::BoruvkaLOE()
{

}
//дополнительно
bool comapre(const std::tuple<int, int, int>& first, const std::tuple<int, int, int>& second)
{
	return std::get<2>(first) < std::get<2>(second);
}
