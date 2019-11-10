#include <iostream>

using namespace std;

const int QUENCEINCREMENT = 10;

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
    Q.elem = new int[maxsize + 1];
    Q.queuesize = maxsize + 1;
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

bool isempty(SqQueue Q)
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

void yanghui(int n)
{
    SqQueue Q;
    for (int i = 1; i <= n ; ++i) { // 输出第一行，n个空格和一个1
        cout<<' ';
    }
    cout<<"1"<<endl;
    InitQueue_L(Q, n+2);
    enqueue_L(Q, 0); enqueue_L(Q, 1); enqueue_L(Q, 1); // 第一行的0.1.1直接入队列
    int k = 1;
    // 外循环while的条件中，k的取值从1到n-1，表示行号
    while (k < n)
    {
        for (int i = 1; i <= n-k ; ++i) { // 对第k行，在外循环while中，首先要输出n-k个空格
            cout<<' ';
        }
        enqueue_L(Q, 0); // 将下一行的行首“0”入队
        do{
            int s = DeQueue_L(Q);
            int e = GetHead_Sq(Q);
            if (e) // 输出第k行的元素，同时计算第k+1行元素的值
            {
                cout<<e<<' ';
            } else{
                cout<<endl;
            }
            enqueue_L(Q, s+e);
        }while (GetHead_Sq(Q) != 0);
        k++;
    }
    DeQueue_L(Q);
    while (!isempty(Q)){
        cout<<DeQueue_L(Q)<<' ';
    }
}
int main() {
    yanghui(3);
    return 0;
}