#include <iostream>
#define STACK_INIT_SIZE 100
#define NUM 6
using namespace std;

typedef struct {
    int *elem;
    int top;
    int stacksize;
}Stack, *PStack;

typedef struct ArcCell{
    int adj;
}ArcCell, AdjMatrix[NUM][NUM];

typedef struct {
    char vexs[NUM];
    AdjMatrix arcs;
}MGragh;

void Init(Stack &S){
    S.elem = new int[STACK_INIT_SIZE];
    S.top = -1;
    S.stacksize = STACK_INIT_SIZE;
}

void push(Stack &S, int e){
    if(S.top == S.stacksize - 1 ){
        cout<<"Stack is full."<<endl;
        return;
    }
    e = S.elem[++S.top];
}

void pop(Stack &S, int &e){
    if(S.top == -1){
        cout<<"Stack is empty."<<endl;
        return;
    }
    e = S.elem[S.top--];
}

bool isEmpty(Stack &S){
    return S.top == -1;
}

void DFS(MGragh &G, int n, int *output){
    int visited[NUM] = {0}; //记录哪些被访问过
    int i, j, p = n - 1; // n-1是因为第一个顶点开始就是第零行
    Stack S; //记录哪些访问过然后回溯
    Init(S);
    push(S, p);
    output[0] = p; //第一个访问的就是p哇
    visited[p] = 1; //嘿嘿嘿我访问过你咯
    i = 1;
    while (i < NUM) {
        for (j = 0; j < NUM; ++j) { //搜寻可访问的邻接点ing
            if (!visited[j] && G.arcs[p][j].adj == 1)
                break;
        }
        if (j < NUM) { //可访问的找到啦
            p = j; // 下次就找j的邻接点了
            push(S, p); // 访问找到了的j
            output[i++] = p;
            visited[p] = 1; // 访问过的记1
        } else{
            if(!isEmpty(S)) // 没找到哇，回溯回溯
                pop(S, p);
            else
                return;
        }
    }
    return;
}

int main(){
    int matrix[NUM][NUM] = {0,1,1,1,0,0,
                            1,0,0,0,1,0,
                            1,0,0,0,1,0,
                            1,0,0,0,0,1,
                            0,1,1,0,0,0,
                            0,0,0,1,0,0};
    MGragh G;
    int output[NUM]; //用来记录访问次序哒
    for (int i = 0; i < NUM; ++i) {
        for (int j = 0; j < NUM; ++j) {
            G.arcs[i][j].adj = matrix[i][j];
        }
    }
    for (int i = 0; i < NUM; ++i) { // 给顶点标序号辣
        G.vexs[i] = '1' + i;
    }
    for (int i = 0; i < NUM; ++i) {
        output[i] = -1;
    }
    DFS(G, 1, output);
    for (int k = 0; k < NUM && output[k] != -1; ++k) {
        cout<<G.vexs[output[k]]<<" ";
    }
    cout<<endl;
    return 0;
}

