#include <iostream>
#include <queue>
using namespace std;
#define MAX_VERTEX_NUM 20
typedef enum{DG, DN, AG, AN} GraphKind;
typedef int VertexType;
typedef struct ArcCell{
    int adj;  //顶点间关系，无权图取1或0；有权图取权值类型
}ArcCell, AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
typedef struct{
    VertexType vexs[MAX_VERTEX_NUM];
    AdjMatrix arcs;
    int vexnum, arcnum;
    GraphKind kind;
}Mgraph;
//void VisitFunc()
void BFSTraverse(Mgraph G){
    bool visited[G.vexnum];
    queue<int> Q;
    for (int i = 0; i < G.vexnum; ++i) {
        visited[i] = false;
    }
    for (int j = 0; j < G.vexnum; ++j) {
        if(!visited[j]){
            visited[j] = true;
            cout<<G.vexs[j]<<" "; // 访问图中第v个顶点
            Q.push(j);
            while(Q.empty()){
                int u = Q.front(); // 队头元素出队并置为u
                Q.pop();
                for (int w = 0; w < G.vexnum; ++w) {
                    if(G.arcs[u, w]->adj && !visited[w]){
                        visited[w] = true;
                        cout<<G.vexs[w]<<" ";
                        Q.push(w); // 当前访问的顶点w入队列Q
                    }
                }
            }
        }
    }
}
int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
