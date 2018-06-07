#pragma once
#include <queue>
#include <iostream>
#include <algorithm>
#include <list>
#include <stack>
#include <iostream>
#include <fstream>

static int graph[1002][1002];
static int marked[1002];

void Initialize();
void GenerateGraph(int graphSize);
void PrintGraph(int (&gr)[1002][1002], int graphSize);
void Shimbell(int pathlength, int graphSize);
bool bfs(int v, int endv, int graphSize);
void GiveLengths(int graphSize);
int ReadGraph(std::string filename, int graphSize);

static int floyd[1002][1002];
static int distances[1002];

void Floyd(int graphSize);
void Dijkstra(int v, int graphSize);
void FordBellman(int v, int graphSize);

struct Edge{
public:
    int from;
    int to;
    int length;
    Edge(int from, int to, int length) : from(from), to(to), length(length) {}
    bool operator<(Edge& e){ return this->length < e.length; }
};

static int parent[1002];
static int tree[1002][1002];
static int checktree[1002][1002];
static double kMatrix[1002][1002];
static int pruf[1002];
static int deg[1002];

int get(int v, int op);

void Kruskal(int graphSize);
void Prim(int graphSize);
void Kirhgoff(int graphSize);
void Pruffer(int graphSize);

static int cycles[1002][1002];
static int numb = 0;
static int full = 0;
static std::vector<std::vector<int>> hamc;

void MakeHamilton(int graphSize);
void Hamilton(int graphSize, int A, int v);
void PrintHamilton();
void MakeEuler(int graphSize);
void Euler(int graphSize);

struct FlowEdge{
public:
    int from;
    int to;
    int length;
    int flow;
    int capacity;
    int next;
    FlowEdge(int from, int to, int length, int capacity, int next) : from(from), to(to),
        length(length), flow(0), capacity(capacity), next(next) {}
};

static int cap[1002][1002];
static std::vector<FlowEdge> flowedges;
static int head[1002];
static int flows[1002][1002];
static int prev[1002];
static int maxflow = 0;
static int flow = 0;
static int fm[1002];
static int cc = 0;

void InitializeFlows(int graphSize);
void FindMincostFlow(int graphSize);
void FindMaxFlow(int graphSize);
bool Flowdfs(int graphSize, int fl, int v);
bool FlowFordBellman(int graphSize, int fl);
void BuildFlow(int v, int fl);
