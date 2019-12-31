#include <iostream>
#include <queue>
#define MAX_VERTEX_NUM 20
using namespace std;


typedef enum{DG, DN, AG, AN} GraphKind;

typedef int VertexType;

typedef struct ArcNode{int adjvex;
    struct ArcNode *nextarcs;
}ArcNode;

typedef struct VNode{
    VertexType data;
    ArcNode *firstarc;
}VNode, AdjList[MAX_VERTEX_NUM];

typedef struct{
    AdjList  vertics;
    int vexnum, arcnum;
    int kind;
}ALGraph;

class Graph{
private:
public:
    //求顶点在图中的位置
    static int LocateVex(ALGraph G, int  u);
    //构造没有相关信息的无向
    static void CreateGraph(ALGraph &G);

    static void DestroyGraph(ALGraph &G);
    //返回序号是v的顶点值
    static VertexType GetVex(ALGraph G, int v);
    //对v赋新值value
    static void PutVex(ALGraph &G, VertexType v, VertexType value);
    //返回v的第一个邻接顶点的序号
    static int FirstAdjVex(ALGraph G, VertexType v);
    //返回v的（相对于w的）下一个邻接顶点的序号
    static int NextAdjVex(ALGraph G, VertexType v, VertexType w);
    //增加新的顶点
    static void InsertVex(ALGraph &G, VertexType v);
    //删除图G顶点v以及其相关的弧
    static void DeleteVex(ALGraph &G, VertexType v);
    //G中增加弧<v, w>
    static void InsertArc(ALGraph &G, VertexType v, VertexType w);
    //删除<v, w>
    static void DeleteArc(ALGraph &G, VertexType v, VertexType w);
    //从第v个顶点出发递归深度优先遍历
    static void DFS(ALGraph G, int v);
    //从第一个顶点出发深度优先遍历G
    static void DFSTraverse(ALGraph G);
    //从第一个顶点出发广度优先遍历G
    static void BFSTraverse(ALGraph G);

};

void Graph::CreateGraph(ALGraph &G) {
    cout<<"请输入顶点总数和弧总数："<<endl;
    cin>>G.vexnum>>G.arcnum;
    cout<<"请输入个顶点的值："<<endl;
    for (int i = 0; i < G.vexnum; ++i) {
        cin>>G.vertics[i].data;
        G.vertics[i].firstarc = nullptr;
    }
    cout<<"请输入各弧："<<endl;
    for (int j = 0; j < G.arcnum; ++j) {
        int v1, v2;
        cin>>v1>>v2;
        int k = LocateVex(G, v1);
        int l = LocateVex(G, v2);
        auto *pk = new ArcNode ;
        pk->adjvex = l;
        pk->nextarcs = G.vertics[k].firstarc;
        G.vertics[k].firstarc = pk;
        auto *pl = new ArcNode ;
        pl->adjvex = k;
        pl->nextarcs = G.vertics[l].firstarc;
        G.vertics[l].firstarc = pl;
    }
}

int Graph::LocateVex(ALGraph G, int u) {
    for (int i = 0; i < G.vexnum; ++i) {
        if(u == G.vertics[i].data)
            return i;
    }
    return -1;
}

void Graph::DestroyGraph(ALGraph &G) {
    ArcNode *cur, *next;
    for (int i = 0; i < G.vexnum; ++i) {
        next = G.vertics[i].firstarc;
        cur = G.vertics[i].firstarc;
        while (cur){
            next = cur->nextarcs;
            delete cur;
            cur = next;
        }
        G.vertics[i].firstarc = nullptr;
    }
    G.vexnum = 0;
    G.arcnum = 0;
}

VertexType Graph::GetVex(ALGraph G, int v) {
    if( v >= G.vexnum || v < 0)
        exit(1);
    return G.vertics[v].data;
}

void Graph::PutVex(ALGraph &G, VertexType v, VertexType value) {
    int i = LocateVex(G, v);
    if (i > -1)
        G.vertics[i].data = value;
}

int Graph::FirstAdjVex(ALGraph G, VertexType v) {
    ArcNode *p;
    int v1 = LocateVex(G, v);
    p = G.vertics[v1].firstarc;
    if(p) return p->adjvex;
    else return -1;
}

int Graph::NextAdjVex(ALGraph G, VertexType v, VertexType w) {
    ArcNode *p;
    int v1 = LocateVex(G, v);
    int w1 = LocateVex(G, w);
    p = G.vertics[v1].firstarc;
    while(p && p->adjvex != w1)
        p = p->nextarcs;
    if(!p || p->nextarcs)
        return -1;
    else
        return p->nextarcs->adjvex;
}

void Graph::InsertVex(ALGraph &G, VertexType v) {
    G.vertics[G.vexnum].data = v;
    G.vertics[G.vexnum].firstarc = nullptr;
    G.vexnum++;
}

void Graph::DeleteVex(ALGraph &G, VertexType v) {
    ArcNode *cur, *next, *temp, *pre;
    VNode anoVer;
    if(G.vexnum <= 0){
        cout<<"Have no vertex!"<<endl;
        return;
    }
    for (int i = 0; i < G.vexnum; ++i) {
        if(G.vertics[i].data == v){
            next = cur = G.vertics[i].firstarc;
            while(cur){
                anoVer = G.vertics[cur->adjvex];
                temp = anoVer.firstarc;
                pre = nullptr;
                while (temp){
                    if(temp->adjvex == i){
                        if (pre == nullptr){
                            anoVer.firstarc = temp->nextarcs;
                            delete temp;
                        } else{
                            pre->nextarcs = temp->nextarcs;
                            delete temp;
                        }
                        break;
                    }
                    pre = temp;
                    temp = temp->nextarcs;
                }
                next = cur->nextarcs;
                delete(cur);
                G.arcnum--;
                cur = next;
            }
        }
        for (int j = i; j < G.vexnum - 1; ++j) {
            G.vertics[j] = G.vertics[j+1];
        }
        G.vexnum--;
        break;
    }
}

void Graph::InsertArc(ALGraph &G, VertexType v, VertexType w) {
    ArcNode *p;
    int i, j;
    i = LocateVex(G, v);
    j = LocateVex(G, w);
    if(i<0 || j<0)
        return;
    G.arcnum++;
    p = new ArcNode ;
    p->adjvex = j;
    p->nextarcs = G.vertics[i].firstarc;
    G.vertics[i].firstarc = p;
    p->adjvex = i;
    p->nextarcs = G.vertics[j].firstarc;
    G.vertics[j].firstarc = p;
}

void Graph::DeleteArc(ALGraph &G, VertexType v, VertexType w) {
    ArcNode *p, *q;
    int i, j;
    i = LocateVex(G, v);
    j = LocateVex(G, w);
    if (i<0 || j<0 || i==j)
        return;
    p = new ArcNode;
    p = G.vertics[i].firstarc;
    while (p && p->adjvex != j){
        q = p;
        p = p->nextarcs;
    }
    if(p && p->adjvex == j){
        if (p == G.vertics[i].firstarc)
            G.vertics[i].firstarc = p->nextarcs;
        else
            q->nextarcs = p->nextarcs;
        G.arcnum--;
    }
    p = G.vertics[j].firstarc;
    while (p && p->adjvex != i){
        q = p;
        p = p->nextarcs;
    }
    if (p && p->adjvex == i){
        if (p == G.vertics[j].firstarc){
            G.vertics[j].firstarc = p->nextarcs;
        } else{
            q->nextarcs = p->nextarcs;
        }
    }
    delete p;
}

bool Visited[MAX_VERTEX_NUM];
void Graph::DFS(ALGraph G, int v) {
    Visited[v] = true;
    VertexType w1;
    cout<<G.vertics[v].data<<endl;
    VertexType v1 = GetVex(G, v);
    for (int w = FirstAdjVex(G, v1); w >= 0; w = NextAdjVex(G, v1, w1 = GetVex(G, w)))
        if(!Visited[w])
            DFS(G, w);
}

void Graph::DFSTraverse(ALGraph G) {
    for (int i = 0; i < G.vexnum; ++i) {
        Visited[i] = false;
    }
    for (int j = 0; j < G.vexnum; ++j) {
        if(!Visited[j]) DFS(G, j);
    }
}

void Graph::BFSTraverse(ALGraph G) {
    for (int i = 0; i < G.vexnum; ++i) {
        Visited[i] = false;
    }
    queue<int> Q;
    for (int j = 0; j < G.vexnum; ++j) {
        if(!Visited[j]){
            Visited[j] = true;
            cout<<G.vertics[j].data;
            Q.push(j);
            while (!Q.empty()){
                int u = Q.front();
                Q.pop();
                ArcNode *p;
                for (p = G.vertics[u].firstarc; p ; p = p->nextarcs) {
                    int w = p->adjvex;
                    if (!Visited[w]){
                        Visited[w] = true;
                        cout<<G.vertics[w].data;
                        Q.push(w);
                    }
                }
            }
        }
    }
}
int main()
{
    Graph g;
    ALGraph(G);
    g.CreateGraph(G);
    g.DestroyGraph(G);
    return 0;
}
