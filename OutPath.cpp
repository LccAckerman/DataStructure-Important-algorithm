#include <iostream>
#define STACK_INIT_SIZE 20
#define STACKINCREMENT 20
//孩子兄弟表示法
typedef struct  CSNode{
    int data;
    struct CSNode *firstchild, *nextsibling; // 分别指向左孩子和右兄弟
}CSNode, *CSTree;
typedef struct{
    CSTree *elem;
    int top;
    int stacksize;
    int incrementsize;
}SqStack;

void incrementStacksize(SqStack &s);

void Init(SqStack &s, int maxsize = STACK_INIT_SIZE, int incrementsize = STACKINCREMENT){
    s.elem = new CSTree[maxsize];
    s.top = -1;
    s.stacksize = maxsize;
    s.incrementsize = incrementsize;
}

void push(SqStack &s, CSTree data){
    if(s.top == s.stacksize-1)
        incrementStacksize(s);
    s.elem[++s.top] = data;
}

CSTree pop(SqStack &s){
    CSTree e = s.elem[s.top];
    s.top--;
    return e;
}

CSTree getTop(SqStack &s){
    return s.elem[s.top];
}
bool isEmpty(SqStack &s){
    return s.top == -1;
}
void incrementStacksize(SqStack &s){
    SqStack news;
    Init(news, s.stacksize, s.incrementsize);
    while(!isEmpty(s))
        push(news, pop(s));
    s.elem = new CSTree[s.stacksize + s.incrementsize];
    while(!isEmpty(news))
        push(s, pop(news));
    s.stacksize += s.incrementsize;
}
void StackTraverse(SqStack &s)
{
    SqStack news;
    Init(news);
    while (s.top != -1){
        push(news, pop(s));
    }
    while (news.top != -1){
        CSTree t = pop(news);
        push(s, t);
        std::cout<<t<<" ";
    }
    std::cout<<std::endl;
}

void OutPath(CSTree T, SqStack &S){  //栈的元素为结点指针，而非结点的值
    if(T){
        push(S, T);
        while (!isEmpty(S)){
            CSTree e = getTop(S);
            while (e->firstchild){
                e = e->firstchild;
                push(S, e);
            }
            StackTraverse(S);
            e = pop(S); // 当前叶子结点指针出栈
            while (!e->nextsibling && !isEmpty(S))
                e = pop(S); // 回溯
            if (e->nextsibling)
                push(S, e->nextsibling);
        }
    }
}
int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}