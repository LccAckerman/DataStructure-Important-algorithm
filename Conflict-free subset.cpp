#include <iostream>
using namespace std;

const int QUENCEINCREMENT = 10;

const int RAW = 9;
const int COL = 9;

int R[RAW][COL] = {                                                      //该矩阵用来存储待划分集合中元素之间的冲突关系，0代表不冲突，1代表冲突
        {0, 1, 0, 0, 0, 0, 0, 0, 0},
        {1, 0, 0, 0, 1, 1, 0, 1, 1},
        {0, 0, 0, 0, 0, 1, 1, 0, 0},
        {0, 0, 0, 0, 1, 0, 0, 0, 1},
        {0, 1, 0, 1, 0, 1, 1, 0, 1},
        {0, 1, 1, 0, 1, 0, 1, 0, 0},
        {0, 0, 1, 0, 1, 1, 0, 0, 0},
        {0, 1, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 0, 1, 1, 0, 0, 0, 0}};


typedef struct {
    int *elem;
    int front;
    int rear;
    int queuesize;
    int incrementsize;
}SqQueue;

void incrementQuencesize(SqQueue &Q);

void InitQueue_L(SqQueue &Q, int maxsize , int incrementsize = QUENCEINCREMENT)
{
    Q.elem = new int[maxsize+1];
    Q.queuesize = maxsize+1;
    Q.incrementsize = incrementsize;
    Q.front = Q.rear = 0;
}

int QuenceLength_Sq(SqQueue Q)
{
    return (Q.rear - Q.front + Q.queuesize) % Q.queuesize;
}

void enqueue_L(SqQueue &Q, int e)
{
    if ( (Q.rear + 1) % Q.queuesize == Q.front) incrementQuencesize(Q);
    Q.elem[Q.rear] = e;
    Q.rear = (Q.rear + 1)% Q.queuesize;
}

int DeQueue_L(SqQueue &Q)
{
    if (Q.front == Q.rear) return false;
    int e = Q.elem[Q.front];
    Q.front = (Q.front+1) % Q.queuesize;
    return e;
}

int GetHead_Sq(SqQueue Q)
{
    return Q.elem[Q.front];
}

bool isEmpty(SqQueue Q)
{
    return (Q.front == Q.rear);
}

void incrementQuencesize(SqQueue &Q)
{
    int *a = new int[Q.queuesize + Q.incrementsize];
    for (int k = 0; k < Q.queuesize - 1; ++k) {
        a[k] = Q.elem[(Q.front + k) % Q.queuesize];
    }
    delete[](Q.elem);
    Q.elem = a;
    Q.front = 0;
    Q.rear = Q.queuesize - 1;
    Q.queuesize += Q.incrementsize;
}

void division( int n, int result[])
{
    int pre = n; // 前一个出队列的元素序号
    int group = 0;
    SqQueue Q;
    InitQueue_L(Q, n);
    for (int e = 0; e < n; ++e) {
        enqueue_L(Q, e);
    }
    int cur_index;
    int clash[RAW];
    while (! isEmpty(Q)){
        cur_index = DeQueue_L(Q);
        if (cur_index <= pre){
            ++group;
            for (int i = 0; i < n; ++i) {
                clash[i] = 0;
            }
        }
        if (clash[cur_index] == 0){
            result[cur_index] = group;
            for (int i = 0; i < n; ++i) {
                clash[i] += R[cur_index][i];
            }
        } else{
        enqueue_L(Q, cur_index);}
        pre = cur_index;
    }
}

int main() {
    int res[RAW];
    division(RAW, res);
    for (int re : res) {
        cout<<re<<endl;
    }

}