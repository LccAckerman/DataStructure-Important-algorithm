#include <iostream>

const int QUENCE_INIT_SIZE = 100;
const int QUENCEINCREMENT = 10;

typedef struct {
    int *elem;
    int front;
    int rear;
    int queuesize;
    int incrementsize;
}SqQueue;

void incrementQuencesize(SqQueue &Q);

void InitQueue_L(SqQueue &Q, int maxsize = QUENCE_INIT_SIZE, int incrementsize = QUENCEINCREMENT)
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
int main() {
    SqQueue Q;
    InitQueue_L(Q);
    enqueue_L(Q, 2);
    std::cout<<Q.elem[0]<<std::endl<<DeQueue_L(Q);
    return 0;
}
