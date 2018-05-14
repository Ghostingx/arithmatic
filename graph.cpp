#include <time.h>
#include <iostream>
#include <string>
#include<stack>
#include <queue>
using namespace std;

#define MAXVEX 100
#define INFINITY 0XFFFF
#define SUCCESS 1
#define UNSUCCESS 0
#define WHITE	-1
#define	GRAY	0
#define BLACK   1
#define NIL     -1
typedef int Status;

short	color[MAXVEX];
int t = 0;
int d[MAXVEX];
int f[MAXVEX];
int path[100][100];
vector<int> cb;
int parent[MAXVEX];
int low[MAXVEX];

bool visited[MAXVEX]; //全局数组，记录结点是否已补访问

int vLength[MAXVEX];//全局数组,节点最长路径;

typedef int EdgeWeight;
typedef struct EdgeNode
{
	int adjvex; //邻接点
	EdgeWeight weight; //权值
	struct EdgeNode* next; //指向下一条边

}EdgeNode;

typedef int VertexType; //顶点类型
typedef struct
{
	VertexType data;
	EdgeNode* pFirstEdge; //指示第一条边
}VertexNode;

typedef VertexNode AdjList[MAXVEX];//邻接表

typedef struct
{
	AdjList adjList; //邻接表
	int iVexNum; //顶点个数
	int iEdgeNum; //边数


}AdjListGraph;

void copyGraph(const AdjListGraph & s, AdjListGraph & d)
{
	d.iEdgeNum = s.iEdgeNum;
	d.iVexNum = s.iVexNum;

	EdgeNode *pEdge;
	EdgeNode *dEdge;
	for (int i = 0; i < d.iVexNum; i++)
	{
		EdgeNode *edge = new EdgeNode;
		pEdge = s.adjList[i].pFirstEdge;
		d.adjList[i].data = i;
		edge->adjvex = pEdge->adjvex;
		edge->next = NULL;
		edge->weight = pEdge->weight;
		d.adjList[i].pFirstEdge = edge;
		pEdge = pEdge->next;
		dEdge = d.adjList[i].pFirstEdge;
		while (pEdge)
		{
			EdgeNode *edge = new EdgeNode;
			edge->adjvex = pEdge->adjvex;
			edge->next = NULL;
			edge->weight = pEdge->weight;
			dEdge->next = edge;
			pEdge = pEdge->next;
			dEdge = dEdge->next;
		}
	}


}

int ExistEdge(const AdjListGraph& G, VertexType s, VertexType d);
//由顶点值得到顶点索引
int GetIndexByVertexVal(const AdjListGraph& G, VertexType val)
{
	for (int i = 0; i < G.iVexNum; ++i)
	{
		if (val == G.adjList[i].data)
			return i;
	}
	return -1;
}

//创建有向图
int CreateAdjListGraph(AdjListGraph& G,int v , int e)
{

	G.iVexNum = v;
	G.iEdgeNum = e;
	for (int i = 0; i < G.iVexNum; ++i)
	{

		G.adjList[i].data = i;

		G.adjList[i].pFirstEdge = NULL;
	}

	int m;
	int n;
	srand((unsigned int)time(NULL));
	for (int i = 0; i < G.iEdgeNum; ++i)
	{
		//VertexType first;
		//VertexType second;

		m = (int)(v * (rand() / (RAND_MAX + 1.0)));
		n = (int)(v * (rand() / (RAND_MAX + 1.0)));

    ////    cout<<m<<","<<n<<endl;
		while (ExistEdge(G, m, n) > 0  || m == n) {
			//m = (int)100 * rand() / (RAND_MAX + 1);
			//cout << "(" << m << "," << n << ")";
			n = (int)(v * (rand() / (RAND_MAX + 1.0)));

		}
		EdgeNode* pEdgeNode = new EdgeNode;
		pEdgeNode->adjvex = n;
		//pEdgeNode->weight = (int)30 * rand() / (RAND_MAX + 1) +1;;  //权值
		pEdgeNode->weight = 1;
								//插入头部
		pEdgeNode->next = G.adjList[m].pFirstEdge;
		G.adjList[m].pFirstEdge = pEdgeNode;
	}
	return SUCCESS;
}


//销毁图
void DestroyGraph(AdjListGraph& G)
{
	for (int i = 0; i < G.iVexNum; ++i)
	{
		EdgeNode* pEdge = G.adjList[i].pFirstEdge;
		while (pEdge)
		{
			EdgeNode* q = pEdge;
			pEdge = pEdge->next;
			delete q;
		}
		G.adjList[i].pFirstEdge = NULL;
	}
	G.iVexNum = 0;
	G.iEdgeNum = 0;
}

int ExistEdge(const AdjListGraph& G,VertexType s,VertexType d) {
	EdgeNode* en = G.adjList[s].pFirstEdge;
	while (en)
	{
		if (en->adjvex == d)
			return en->weight;
		else
		{
			en = en->next;
		}
	}
	return 0;
}

//得到顶点的度
int GetVertexDegree(const AdjListGraph& G, VertexType val)
{
	//int m = GetIndexByVertexVal(G, val);//得到顶点的下标
	int m = val;
	int iCount = 0; //顶点的度

	for (int i = 0; i < G.iVexNum; ++i)
	{
		if (i == m)
		{
			EdgeNode* pEdgeOut = G.adjList[i].pFirstEdge;
			while (pEdgeOut)
			{
				++iCount;//累加出度
				pEdgeOut = pEdgeOut->next;
			}
		}
		else
		{
			EdgeNode* pEdgeIn = G.adjList[i].pFirstEdge;
			while (pEdgeIn)
			{
				if (pEdgeIn->adjvex == m)
					++iCount;   //累加入度
				pEdgeIn = pEdgeIn->next;
			}
		}
	}
	return iCount;
}

void printPath(int path[] , int i, int v)
{
	int k;
	k = path[i];
	if (v == k)
	{
		return;
	}
	printPath(path,k,v);
	cout << k << "-";
}

void displayPath(int dist[],int path[],bool s[],int n,int v)
{
	int i;
	for ( i = 0; i < n; i++)
	{
		if (s[i])
		{
			cout << v << "---->" <<i<<":"<<dist[i]<<endl;
			cout << v << "-";
			printPath(path,i,v);
			cout << i <<endl;
		}
		else
		{
			cout << v << "无法到达" << i <<endl;
		}

	}
}


//距离
void distanceFromV(const AdjListGraph &G,VertexType v) {
	int i, j, u, distance,n;
	bool s[MAXVEX];
	int dist[MAXVEX], path[MAXVEX];
	for ( i = 0; i < G.iVexNum; i++)
	{
		s[i] = false;
		n = ExistEdge(G, v, i);
		dist[i] = n == 0 ? INFINITY : n;
		dist[i] = v == i ? 0 : dist[i];
		if (dist[i] < INFINITY)
		{
			path[i] = v;
		}
		else
		{
			path[i] = -1;
		}
	}
	s[v] = true;
	path[v] = 0;
	for ( i = 0; i < G.iVexNum; i++)
	{
		distance = INFINITY;
		for ( j = 0; j < G.iVexNum; j++)
		{
			if (s[j] == false && dist[j] < distance)
			{
				distance = dist[j];
				u = j;
			}
		}
		s[u] = true;

		for ( j = 0; j < G.iVexNum; j++)
		{
			if (s[j] == false)
			{
				n = ExistEdge(G, u, j);
				n = n == 0 ? INFINITY : n;
				if (n < INFINITY && dist[u] + n < dist[j])
				{
					dist[j] = dist[u] + n;
					path[j] = u;
				}
			}
		}
	}displayPath(dist ,path ,s ,G.iVexNum,v);
}

//深度优先遍历图
void DFSLoop(const AdjListGraph& G, int i)
{
	cout << G.adjList[i].data << " ";
	//visited[i] = true;
	color[i] = GRAY;
	d[i] = ++t;
	EdgeNode* pEdge = G.adjList[i].pFirstEdge;
	while (pEdge)
	{
		int j = pEdge->adjvex;
		if (color[j] == WHITE)
		{
			DFSLoop(G, j);
		}
		else if (color[j] == GRAY)
		{
			//后向边
		}
		else
		{
			if (d[i] < d[j])
			{
				//前向边
			}
			else if (d[i] > d[j])
			{
				//交叉边
			}

		}


		pEdge = pEdge->next;
	}
	f[i] = ++t;
	color[i] = BLACK;
}
void DFS(const AdjListGraph& G, VertexType v)
{
	for (int i = 0; i < G.iVexNum; ++i)
	{
		color[i] = WHITE;
	}

	DFSLoop(G, v);

	for (int i = 0; i < G.iVexNum; ++i)
	{
		if (color[i] == WHITE)
			DFSLoop(G, i);
	}
}





//DFS 无递归

void DFSNoRecursion(const AdjListGraph& G, int i)
{
	stack<VertexType> s;
	VertexType vv;
	EdgeNode * pEdge;
	s.push(i);
	color[i] = GRAY;
	while (!s.empty())
	{
		vv = s.top();
		s.pop();
		d[vv] = ++t;
		cout << G.adjList[vv].data << " ";
		pEdge = G.adjList[vv].pFirstEdge;
		while (pEdge)
		{
			int j = pEdge->adjvex;
			if (color[j] == WHITE)
			{
				s.push(j);
				color[j] = GRAY;

			}
			else if (color[j] == GRAY)
			{
				//后向边
			}
			else
			{
				if (d[vv] < d[j])
				{
					//前向边
				}
				else if (d[vv] > d[j])
				{
					//交叉边
				}

			}
			pEdge = pEdge->next;
		}

		f[vv] = ++t;
		color[vv] = BLACK;
	}
}
void DFS2(const AdjListGraph& G, VertexType v)
{
	for (int i = 0; i < G.iVexNum; ++i)
	{
		color[i] = WHITE;
	}

	DFSNoRecursion(G, v);

	for (int i = 0; i < G.iVexNum; ++i)
	{
		if (color[i] == WHITE)
			DFSNoRecursion(G, i);
	}
}




//广度优先遍历
void BFS(const AdjListGraph& G, VertexType v)
{
	for (int i = 0; i < G.iVexNum; ++i)
	{
		visited[i] = false;
	}

	queue<int> Q;

	if (!visited[v])
	{
		cout << G.adjList[v].data << " ";
		visited[v] = true;
		Q.push(v);
		while (!Q.empty())
		{
			int iVex = Q.front();
			Q.pop();

			EdgeNode* pEdge = G.adjList[iVex].pFirstEdge;
			while (pEdge)
			{
				if (!visited[pEdge->adjvex])
				{
					cout << G.adjList[pEdge->adjvex].data << " ";
					visited[pEdge->adjvex] = true;
					Q.push(pEdge->adjvex);
				}
				pEdge = pEdge->next;
			}
		}
	}

	for (int i = 0; i < G.iVexNum; ++i)
	{
		if (!visited[i])
		{
			cout << G.adjList[i].data << " ";
			visited[i] = true;
			Q.push(i);
			while (!Q.empty())
			{
				int iVex = Q.front();
				Q.pop();

				EdgeNode* pEdge = G.adjList[iVex].pFirstEdge;
				while (pEdge)
				{
					if (!visited[pEdge->adjvex])
					{
						cout << G.adjList[pEdge->adjvex].data << " ";
						visited[pEdge->adjvex] = true;
						Q.push(pEdge->adjvex);
					}
					pEdge = pEdge->next;
				}
			}
		}
	}
}

void DAGDFS(AdjListGraph& G, int i)
{
	//cout << G.adjList[i].data << " ";
	visited[i] = true;

	EdgeNode* pEdge = G.adjList[i].pFirstEdge;
	EdgeNode* lastEdge = pEdge;
	if (pEdge) {
		while(pEdge && visited[pEdge->adjvex]) {
			G.adjList[i].pFirstEdge = pEdge->next;
			delete pEdge;
			pEdge = G.adjList[i].pFirstEdge;
		}

	}

	while (pEdge)
	{
		int j = pEdge->adjvex;
		if (!visited[j])
		{
			DAGDFS(G, j);
			lastEdge = pEdge;
			pEdge = pEdge->next;
		}
		else
		{
			lastEdge->next = pEdge->next;
			delete pEdge;
			pEdge = lastEdge->next;
		}


	}
}
void DAG(AdjListGraph& G)
{
	for (int i = 0; i < G.iVexNum; ++i)
	{
		visited[i] = false;
	}

	for (int i = 0; i < G.iVexNum; ++i)
	{
		if (!visited[i])
			DAGDFS(G, i);
	}
}


//DAG 无递归



void DAGDFSLoop2(AdjListGraph& G, int i)
{
	//cout << G.adjList[i].data << " ";
	//visited[i] = true;
	color[i] = GRAY;
	d[i] = ++t;
	EdgeNode* pEdge = G.adjList[i].pFirstEdge;
	EdgeNode* lastEdge;
	lastEdge = pEdge;
	if (pEdge) {
		while (pEdge && color[pEdge->adjvex] == GRAY) {
			G.adjList[i].pFirstEdge = pEdge->next;
			delete pEdge;
			pEdge = G.adjList[i].pFirstEdge;
		}

	}

	while (pEdge)
	{
		int j = pEdge->adjvex;
		if (color[j] == WHITE)
		{
			DAGDFSLoop2(G, j);
			lastEdge = pEdge;
			pEdge = pEdge->next;
		}
		else if (color[j] == GRAY)
		{
			//后向边
			lastEdge->next = pEdge->next;
			delete pEdge;
			pEdge = lastEdge->next;
		}
		else
		{
			if (d[i] < d[j])
			{
				//前向边
			}
			else if (d[i] > d[j])
			{
				//交叉边
			}
			lastEdge = pEdge;
			pEdge = pEdge->next;
		}
	}
	f[i] = ++t;
	color[i] = BLACK;
}
void DAG2(AdjListGraph& G)
{
	for (int i = 0; i < G.iVexNum; ++i)
	{
		color[i] = WHITE;
	}

	for (int i = 0; i < G.iVexNum; ++i)
	{
		if (color[i] == WHITE)
			DAGDFSLoop2(G, i);
	}
}


void DFSNoRecursion3(AdjListGraph& G, int i)
{
	stack<VertexType> s;
	VertexType vv;
	EdgeNode * pEdge;
	EdgeNode* lastEdge;
	s.push(i);
	color[i] = GRAY;
	while (!s.empty())
	{
		vv = s.top();
		s.pop();
		d[vv] = ++t;
		pEdge = G.adjList[vv].pFirstEdge;

		lastEdge = pEdge;
		while ((pEdge && color[pEdge->adjvex] == GRAY) ) {
				//if (color[pEdge->adjvex] == GRAY)

				G.adjList[vv].pFirstEdge = pEdge->next;
				delete pEdge;
				pEdge = G.adjList[vv].pFirstEdge;

		}


		while (pEdge)
		{
			int j = pEdge->adjvex;
			if (color[j] == WHITE)
			{
				s.push(j);
				color[j] = GRAY;
				lastEdge = pEdge;
				pEdge = pEdge->next;
				//d[j] = ++t;

			}
			else if (color[j] == GRAY)
			{
				//后向边
				lastEdge->next = pEdge->next;
				delete pEdge;
				pEdge = lastEdge->next;
			}
			else
			{
				if (d[vv] < d[j])
				{
					//前向边
				}
				else if (d[vv] > d[j])
				{
					//交叉边
				}
				pEdge = pEdge->next;
			}

		}

		f[vv] = ++t;
		color[vv] = BLACK;
	}
}
void DAG3(AdjListGraph& G)
{
	for (int i = 0; i < G.iVexNum; ++i)
	{
		color[i] = WHITE;
	}

	for (int i = 0; i < G.iVexNum; ++i)
	{
		if (color[i] == WHITE)
			DFSNoRecursion3(G, i);
	}
}





int pathLengthFromV(const AdjListGraph &G, VertexType v)
{
	EdgeNode * pEdge;
	if (vLength[v]>0)
	{
		return vLength[v];
	}
	pEdge = G.adjList[v].pFirstEdge;
	int temp;

	while (pEdge)
	{
		temp = pathLengthFromV(G, pEdge->adjvex) + pEdge->weight;
		if (temp > vLength[v])
		{
			vLength[v] = temp;
		}
		pEdge = pEdge->next;
	}
	return vLength[v];
}

int LSTPath(const AdjListGraph& G)
{
	for (int i = 0; i < G.iVexNum; i++)
	{
		vLength[i] = 0;
	}
	int pathLength = 0;
	int n;
	for (int i = 0; i < G.iVexNum; i++)
	{
		n = pathLengthFromV(G, i);
		if (n > pathLength)
			pathLength = n;
	}
	//delete lPath;
	return pathLength;
}

void topoSort(const AdjListGraph &G,VertexType v, stack<VertexType> &s) {
	visited[v] = true;
	EdgeNode* e = G.adjList[v].pFirstEdge;
	while (e)
	{
		if (!visited[e->adjvex])
		{
			topoSort(G,e->adjvex,s);
		}
		e = e->next;
	}
	s.push(v);
}

int  longestPathToPo(const AdjListGraph &G) {
	stack<VertexType> stack;
	int dist[100];
	for (int i = 0; i < G.iVexNum; i++)
	{
		visited[i] = false;
	}
	for (int i = 0; i < G.iVexNum; i++)
	{
		if (!visited[i])
		{
			topoSort(G,i,stack);
		}
	}
	for (int  i = 0; i < G.iVexNum; i++)
	{
		dist[i] = INFINITY;
	}
	//vector<int> path;
	dist[stack.top()] = 0;
	//path.push_back(stack.top());
	while (!stack.empty())
	{
		VertexType u = stack.top();
		stack.pop();

		EdgeNode *pEdge = G.adjList[u].pFirstEdge;
		if (dist[u] < INFINITY)
		{
	//		path.push_back(pEdge->adjvex);

			while (pEdge)
			{
				dist[pEdge->adjvex] = (dist[pEdge->adjvex] == INFINITY || dist[u] + pEdge->weight > dist[pEdge->adjvex]) ? dist[u] + pEdge->weight : dist[pEdge->adjvex];
				pEdge = pEdge->next;
			}
		}

	}
	int max = 0,index;
	for (int i = 0; i < G.iVexNum; i++)
	{
		//cout << dist[i] <<" ";

		max = (dist[i] < INFINITY && max < dist[i]) ? dist[i] : max;
	}

	//for (int i = 0; i < path.size(); i++)
	{
		//cout << path[i] << " ";
	}
	return max;
}

bool inverseGraph(const AdjListGraph &s, AdjListGraph &d) {
	d.iEdgeNum = s.iEdgeNum;
	d.iVexNum = s.iVexNum;
	for (int i = 0; i < d.iVexNum; ++i)
	{

		d.adjList[i].data = i;

		d.adjList[i].pFirstEdge = NULL;
	}


	EdgeNode *pEdge;
	EdgeNode *dEdge;
	for (int i = 0; i < d.iVexNum; i++)
	{
		EdgeNode *edge = new EdgeNode();
		pEdge = s.adjList[i].pFirstEdge;
        if(!pEdge)
            continue;
		d.adjList[i].data = i;
		edge->adjvex = i;
		edge->next = d.adjList[pEdge->adjvex].pFirstEdge;;
		edge->weight = pEdge->weight;

		d.adjList[pEdge->adjvex].pFirstEdge = edge;
		pEdge = pEdge->next;
		//dEdge = d.adjList[i].pFirstEdge;
		while (pEdge)
		{
			EdgeNode *edge = new EdgeNode;
			edge->adjvex = i;
			edge->next = d.adjList[pEdge->adjvex].pFirstEdge;
			edge->weight = pEdge->weight;

			d.adjList[pEdge->adjvex].pFirstEdge = edge;

			pEdge = pEdge->next;

		}
	}

	return true;
}
void dfsCB(const AdjListGraph &G,int i){

    cb.push_back(i);
	color[i] = GRAY;
	d[i] = ++t;
	EdgeNode* pEdge = G.adjList[i].pFirstEdge;
	while (pEdge)
	{
		int j = pEdge->adjvex;
		if (color[j] == WHITE)
		{
			dfsCB(G, j);
		}
		pEdge = pEdge->next;
	}
	f[i] = ++t;
	color[i] = BLACK;
}
void DFSCB(const AdjListGraph &G){

	for (int i = 0; i < G.iVexNum; ++i)
	{
		color[i] = WHITE;
	}
    t = 0;
	//DFSLoop(G, v);

	for (int i = 0; i < G.iVexNum; ++i)
	{
		if (color[i] == WHITE)
			dfsCB(G, i);
	}
}
int maxUnvisited(int _v,int _f[MAXVEX]){
    int _max = 0;
    for(int _i =1;_i<_v;_i++){
        if(color[_i] == WHITE && _f[_max] < _f[_i])
            _max = _i;
    }
    return _max;
}
void findCB(const AdjListGraph &G){

    DFSCB(G);
    int finish[MAXVEX];
    for(int i = 0;i<MAXVEX;i++){
        finish[i] = f[i];
        if(f[i] > 0)
        cout<<f[i]<<endl;
    }
    AdjListGraph F;
    inverseGraph(G,F);
    int max;
    cb.clear();
    for(int i = 0;i<MAXVEX;i++){
        color[i] = WHITE;
    }
    max = maxUnvisited(F.iVexNum,finish);
    while(color[max] == WHITE){
        dfsCB(F,max);
        cb.push_back(-1);
        max = maxUnvisited(F.iVexNum,finish);
    }
    //cb.push_back(-100);
    cout<<"CB:";
    cout<<cb.size()<<endl;
    for(int i  = 0;i<cb.size();i++){
        if(cb[i] == -1)
            cout<<endl;
        else
            cout<<cb[i]<<"  ";
    }
    cout<<"CB:";
    cout<<endl;
}

int min(int _a,int _b){
    return _a>_b?_a:_b;
}

void findCutPoint(const AdjListGraph &_G,int _u) {
    //记录dfs遍历次序
    static int counter = 0;

    //记录节点u的子树数
    int children = 0;

    EdgeNode *p = _G.adjList[_u].pFirstEdge;
    visited[_u] = 1;

    //初始化d与low
    d[_u] = low[_u] = ++counter;

    for(; p != NULL; p = p->next) {
        int v = p->adjvex;

        //节点v未被访问，则(u,v)为树边
        if(!visited[v]) {
            children++;
            parent[v] = _u;
            findCutPoint(_G,v);
            low[_u] = min(low[_u], low[v]);
            //case (1)
            if(parent[_u] == NIL && children > 1) {
                printf("articulation point: %d\n", _u);
            }
            //case (2)
            if(parent[_u] != NIL && low[v] >= d[_u]) {
                printf("articulation point: %d\n", _u);
            }
        }

        //节点v已访问，则(u,v)为回边
        else if(v != parent[_u]) {
            low[_u] = min(low[_u], d[v]);
        }
    }
}

void FCP(const AdjListGraph &_G){
    for(int i = 0;i<_G.iVexNum;i++){
        visited[i] = false;
        parent[i] = NIL;
    }
    findCutPoint(_G,0);
};

int main()
{
	//创建有向图
	AdjListGraph G,F;
	CreateAdjListGraph(G,10,20);
	//inverseGraph(G,F);
	//深度优先遍历图
//	DFS(G,10);
    findCB(G);

	cout << endl << endl;

	//广度优先遍历图
	//BFS(G,10);

//	cout << endl << endl;

//	DFS2(G,10);
//	cout << endl << endl;
	//DFSTraverse(F, 10);
//	cout << endl << endl;
	EdgeNode *en;
	for (int i = 0; i < G.iVexNum; i++)
	{
        cout<<i<<" ";
		en = G.adjList[i].pFirstEdge;
		while (en)
		{
			cout <<" "<<en->adjvex ;
			en = en->next;
		}
		cout << endl;
	}
		cout << endl;
	/*for (int i = 0; i <F.iVexNum; i++)
	{
        cout<<i<<" ";
        if(F.adjList[i].pFirstEdge == NULL)
            continue;
		cout<<F.adjList[i].pFirstEdge->adjvex;
		en = F.adjList[i].pFirstEdge->next;
		while (en)
		{
			cout <<" "<<en->adjvex ;
			en = en->next;
		}
        cout<<endl;
    }*/
//	distanceFromV(G,10);
//	cout << endl << endl;
	/*int d = 0,dc=0;
	for (int i = 0; i < 100; i++)
	{
		d = GetVertexDegree(G, i);
		dc += d;
		cout << d << "  ";
/	}*/
//	cout << dc <<endl;
    int d = 0;
    int dc = 0;
	/*for (int i = 0; i < 100; i++)
	{
		d = GetVertexDegree(F, i);
		dc += d;
		cout << d << "  ";
	}
	cout << dc << endl;*/
	cout << endl << endl;
	DAG2(G);
	//DAG(G);
	cout << endl << endl;

	d = 0; dc = 0;
	for (int i = 0; i < 100; i++)
	{
		d = GetVertexDegree(G, i);
		dc += d;
		cout << d << "  ";
	}
	cout << dc << endl;
	cout << endl << endl;

	cout <<"最长路径为："<< LSTPath(G);

	cout << endl << endl;

	cout << "最长路径为：" <<longestPathToPo(G);

	cout << endl << endl;
	//DFSTraverse(G, 10);
	//结点的度
//	cout << "输入求度的结点:";
	//VertexType v;


//	VertexType v;
//	cin >> v;
//	cout << "度为：" << GetVertexDegree(G, v) << endl;

	//销毁有向图
	DestroyGraph(G);
//	DestroyGraph(F);
	return 0;
}
