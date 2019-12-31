#include <iostream>
#define MAX 5
#define INF 0x3f3f3f
using namespace std;

typedef struct graph{
    int vexnum;
    int arcnum;
}Graph, *PGraph;

typedef struct EdgeData{
    char start;
    char end;
    int weight;
}EData;

int matrix[MAX][MAX] = {
        0,10,INF,30,100,
        INF,0,50,INF,INF,
        INF,INF,0,INF,10,
        INF,INF,20,0,60,
        INF,INF,INF,INF,0
};
int vexs[MAX] = {0,1,2,3,4};
void Dijkstra(Graph G, int StrtVex, int prev[], int dist[]){
    int i, j, k=0;
    int min;
    int tmp;
    int flag[MAX]; //flaf[i]=1表示StartVex到i的最短路径获取成功
    for (i = 0; i < G.vexnum; ++i) {
        flag[i] = 0;
        prev[i] = 0; // 顶点i的前驱顶点为0。
        dist[i] = matrix[StrtVex][i]; // 顶点i的最短路径为"顶点vs"到"顶点i"的权。
    }
    flag[StrtVex] = 1;
    dist[StrtVex] = 0;
    for (i = 1; i < G.vexnum; ++i) {
        min = INF;
        for (j = 0; j < G.vexnum; j++) {
            if(flag[j] == 0 && dist[j] < min){
                min = dist[j];
                k = j;
            }
        }
        flag[k] = 1;
        // 修正当前最短路径和前驱顶点
        // 即，当已经"顶点k的最短路径"之后，更新"未获取最短路径的顶点的最短路径和前驱顶点"。
        for (j = 0; j < G.vexnum; ++j) {
            tmp = (matrix[k][j] == INF? INF: (min + matrix[k][j]));
            if(flag[j] == 0 && (tmp < dist[j])){
                dist[j] = tmp;
                prev[j] = k;
            }
        }
    }
    for (int l = 0; l < G.vexnum; ++l) {
        cout<<vexs[StrtVex]<<"-"<<vexs[l]<<": "<<dist[l]<<endl;
    }
}

int main(){
    Graph g;
    g.vexnum  = MAX;
    g.arcnum = 7;
    int Start = 0;
    int prev[MAX];
    int dist[MAX];
    Dijkstra(g, Start, prev, dist);
    return 0;
}