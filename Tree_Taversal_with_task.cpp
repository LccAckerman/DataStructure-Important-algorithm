#include <iostream>

using namespace std;
typedef enum{ Travel=1, Visit=0}TaskType;

typedef struct Node{
    int data;
    struct Node *lchild, *rchild;
}BiTNode, *BiTree;

typedef struct {
    BiTree ptr; //指向二叉树结点的指针 BiTNode *ptr
    TaskType task; // 任务的性质
}SElemType;

typedef struct{
    SElemType *elem;
    int top;
    int stacksize;
    int incrementsize;
}SqStack;

void incrementStacksize(SqStack &s);

void Init(SqStack &s, int maxsize = 100, int incrementsize = 100){
    s.elem = new SElemType[maxsize];
    s.top = -1;
    s.stacksize = maxsize;
    s.incrementsize = incrementsize;
}

void push(SqStack &s, SElemType data){
    if(s.top == s.stacksize-1)
        incrementStacksize(s);
    s.elem[++s.top] = data;
}

SElemType pop(SqStack &s){
    SElemType e = s.elem[s.top];
    s.top--;
    return e;
}

bool isEmpty(SqStack &s){
    return s.top == -1;
}

void incrementStacksize(SqStack &s){
    SqStack news;
    Init(news, s.stacksize, s.incrementsize);
    while(!isEmpty(s))
        push(news, pop(s));
    s.elem = new SElemType[s.stacksize + s.incrementsize];
    while(!isEmpty(news))
        push(s, pop(news));
    s.stacksize += s.incrementsize;
}

void InOrder_iter(BiTree BT, void(*visit)(BiTree)){  // 非递归实现遍历”带任务“
    SqStack S;
    Init(S);
    SElemType e;
    e.ptr = BT;
    e.task = Travel;
    if(BT) push(S, e);
    while (!isEmpty(S)){
        e = pop(S);
        if(e.task == Visit) visit(e.ptr);
        else
            if(e.ptr){
                BiTree p;
                p = e.ptr;
                e.ptr = p->rchild;
                push(S, e); // 右边的不着急处理所以压到最下面, e是遍历
                e.ptr = p;
                e.task = Visit;
                push(S, e);
                e.ptr = p->lchild;
                e.task = Travel;
                push(S, e);
            }
    }
}


void Preorder(BiTree T, void(*visit)(BiTree)){  //前序递归遍历
    if(T){
        visit(T);
        Preorder(T->lchild, visit);
        Preorder(T->rchild, visit);
    }
}

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}