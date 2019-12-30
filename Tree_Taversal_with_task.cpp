#include <iostream>
#include <stack>
using namespace std;

typedef enum{Travel = 1, Visit = 0}TaskType;

typedef int NodeType;

typedef struct Node{
    NodeType data;
    Node *lchild, *rchild;
}BiNode, *BiTree;

typedef struct {
    BiTree ptr;
    TaskType task;
}SElemType;

void visit(BiTree BT){
    cout<<BT->data;
}
void InOrder_iter(BiTree BT, void(*visit)(BiTree)){ // 非递归实现遍历”带任务“
    stack<SElemType> s;
    SElemType e;
    e.ptr = BT;
    e.task = Travel;
    if(BT){
        s.push(e);
    }
    while (!s.empty()){
        e = s.top();
        s.pop();
        if(e.task == Visit) visit(e.ptr);
        else
            if(e.ptr){
                BiTree p;
                p = e.ptr;
                e.ptr = p->rchild;
                s.push(e); // 右边的不着急处理所以压到最下面, e是遍历
                e.ptr = p;
                e.task = Visit;
                s.push(e);
                e.ptr = p->lchild;
                e.task = Travel;
                s.push(e);
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
