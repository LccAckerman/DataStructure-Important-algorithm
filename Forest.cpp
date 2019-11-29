#include <iostream>
#define MAX_TREE_SIZE 100
#define STACK_INIT_SIZE 20
#define STACKINCREMENT 20

typedef struct PTNode{ //双亲表示法
    int data;
    int parents;
}PTNode;
typedef struct{ //双亲表示法
    PTNode nodes[MAX_TREE_SIZE];
    int rpos, num; // 根结点的位置和结点个数 T.nodes[r].data为该树的根的值
}PTree;

//孩子链表表示法
typedef struct CTNode{ //孩子结点结构
    int child;
    struct CTNode *next;
}*ChildPtr;
typedef struct { // 双亲结点结构
    int data;
    ChildPtr firstchild;
}CTBox;
typedef struct { //树结构
    CTBox nodes[MAX_TREE_SIZE];
    int num, rpos;
}CTree;

//孩子兄弟表示法
typedef struct  CSNode{
    int data;
    struct CSNode *firstchild, *nextsibling; // 分别指向左孩子和右兄弟
}CSNode, *CSTree;

// 需要用到的栈结构
typedef struct {
    int *elem;
    int top;
    int stacksize;
    int incrementsize;
} SqStack;

void incrementStacksize(SqStack &s);

void Init(SqStack &s, int maxsize = STACK_INIT_SIZE, int incrementsize = STACKINCREMENT) {
    s.elem = new int[maxsize];
    s.top = -1;
    s.stacksize = maxsize;
    s.incrementsize = incrementsize;
}

void push(SqStack &s, int data) {
    if (s.top == s.stacksize - 1)
        incrementStacksize(s);
    s.elem[++s.top] = data;
}

int pop(SqStack &s) {
    int e = s.elem[s.top];
    s.top--;
    return e;
}

bool is_empty(SqStack &s) {
    return s.top == -1;
}

void incrementStacksize(SqStack &s) {
    SqStack news;
    Init(news, s.stacksize, s.incrementsize);
    while (!is_empty(s))
        push(news, pop(s));
    s.elem = new int[s.stacksize + s.incrementsize];
    while (!is_empty(news))
        push(s, pop(news));
    s.stacksize += s.incrementsize;
}

void StackTraverse(SqStack &s) {
    SqStack news;
    Init(news);
    while (s.top != -1) {
        push(news, pop(s));
    }
    while (news.top != -1) {
        int t = pop(news);
        push(s, t);
        std::cout << t << " ";
    }
    std::cout << std::endl;
}

//设树的存储结构为孩子-兄弟链表，下面是树的遍历举例
//求森林的深度
int TreeDepth(CSTree T){ //树的深度定义为子树森林的深度+1
    if(!T) return 0;
    else{
        int h1 = TreeDepth(T->firstchild);
        int h2 = TreeDepth(T->nextsibling);
        return ((h1+1)>h2? h1+1:h2);
    }
}
// 输出树中从根结点到所有叶子结点的路径
void OutPath_with_recursion(CSTree T, SqStack &S){ // 输出树T中从根到所有叶子结点的路径，引入参数栈s暂存路径
    while (T){
        push(S, T->data); // 将当前访问的结点记入路径[根]
        if(!T->firstchild) //无左孩子，当前结点为叶子结点
           StackTraverse(S); //输出（并非出栈）从栈底到栈顶的一条路径
        else OutPath_with_recursion(T->firstchild, S); //继续遍历左子树
        int e = pop(S); //将当前层访问的结点从路径中退出
        T = T->nextsibling;  //继续遍历右子树求其他叶子结点路径
    }
}

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}