#include <iostream>
using namespace std;

const int QUENCEINCREMENT = 10;

const int RAW = 9;
const int COL = 9;

int R[RAW][COL] = {                                                      // 该矩阵用来存储待划分集合中元素之间的冲突关系，0代表不冲突，1代表冲突
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
    int group = 0;  //表示当前分配的组的编号
    SqQueue Q;
    InitQueue_L(Q, n); //初始化一个队列，长度与被划分集合的基本元素个数相同
    for (int e = 0; e < n; ++e) { //该循环用来给分配的队列附上初值
        enqueue_L(Q, e);
    }
    int cur_index; //该变量用来表示当前待考察的队列中的一个元素
    int clash[RAW]; //该数组用来表示当前分配组的已经添加的元素与其它元素的关系，即是否产生冲突
    while (! isEmpty(Q)){ //该循环用来处理队列中的每一个元素，直到所有元素都分配完成时结束
        cur_index = DeQueue_L(Q); //取出一个元素进行处理
        if (cur_index <= pre){ //如果当前元素小于前一个，则表示队列已经循环遍历所有的元素，应该新建另一个组
            ++group;
            for (int i = 0; i < n; ++i) {
                clash[i] = 0;
            }
        }
        if (clash[cur_index] == 0){ //查询当前分配组的clash数组的值，当值为0时表示该元素没有与当前组中已经添加的元素产生冲突
            result[cur_index] = group; //将当前元素编入该组
            for (int i = 0; i < n; ++i) { //添加与被添加元素冲突的信息
                clash[i] += R[cur_index][i];
            }
        } else{ //如果该元素与当前组中的所有元素都冲突，将该元素继续入栈
        enqueue_L(Q, cur_index);}
        pre = cur_index;
    }
}

int main() {
    int res[RAW]; //该数组用来存放分组后的结果
    division(RAW, res);
    for (int re : res) {
        cout<<re<<endl;
    }

}
