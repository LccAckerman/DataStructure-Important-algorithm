/* 测试数据：
输入连通网的边数：
6 10
输入连通网的顶点：
1
2
3
4
5
6
输入各边的起始点和终点及权重：
1,2,6
1,3,1
1,4,5
2,3,5
2,5,3
3,4,5
3,5,6
3,6,4
4,6,2
5,6,6*/
#include <iostream>
#define MAX_VERTEX_NUM 20
using namespace std;

typedef int VertexType;

typedef struct edge{
    VertexType initial;
    VertexType end;
    VertexType weight;
}Edge[MAX_VERTEX_NUM];

typedef struct{ // 定义辅助数据
    VertexType value; // 顶点数据
    int sign; // 每个顶点所属的集合
}assist[MAX_VERTEX_NUM];

assist AST;

int cmp(const void *a, const void *b){
    return ((struct edge*)a)->weight - ((struct edge*)b)->weight;
}

void CreateUDN(Edge *edges,int *vexnum, int *arcnum){
    cout<<"输入连通网的边数：\n";
    cin>>*vexnum>>*arcnum;
    cout<<"输入连通网的顶点:\n";
    for (int i = 0; i < (*vexnum); ++i) {
        cin>>AST[i].value;
        AST[i].sign = i;
    }
    cout<<"输入各边的起始点和终点及权重: \n";
    for (int j = 0; j < (*arcnum); ++j) {
        cin>>(*edges)[j].initial>>(*edges)[j].end>>(*edges)[j].weight;
    }
}

int Locatevex(int vexnum, int point){
    for (int i = 0; i < vexnum; ++i) {
        if (AST[i].value == point)
            return i;
    }
    return -1;
}
int main() {
    int arcnum, vexnum;
    Edge edges;
    CreateUDN(&edges, &vexnum, &arcnum);
    //对连通网中的所有边进行升序排序， 结果仍保存在edges数组里面
    qsort(edges, arcnum, sizeof(edges[0]), cmp);
    //设置一个空的结构体数组， 用于存放最小生成树
    Edge minTree;
    //用于记录最小生成树中边的数量的常亮
    int num = 0;
    //遍历所有边
    for (int i = 0; i < arcnum; ++i) {
        //找到边的起始顶点和结束顶点在数组AST中的位置
        int initial = Locatevex(vexnum, edges[i].initial);
        int end = Locatevex(vexnum, edges[i].end);
        //顶点位置存在且标记不同，说明不在一个集合
        if (initial != -1 && end != -1 && AST[initial].sign != AST[end].sign){
            minTree[num] = edges[i];
            num++;
            for (int j = 0; j < vexnum; ++j) { // 将新加入生成树的顶点标记全改成一样的
                if (AST[j].sign == AST[end].sign){
                    AST[j].sign = AST[initial].sign;
                }
            }
            //如果选择的边数量与顶点数差一， 证明已经生成
            if (num == vexnum - 1){
                break;
            }
        }
    }
    for (int k = 0; k < vexnum - 1; ++k) {
        cout<<minTree[k].initial<<" ,"<<minTree[k].end<<endl;
    }
    return 0;
}
