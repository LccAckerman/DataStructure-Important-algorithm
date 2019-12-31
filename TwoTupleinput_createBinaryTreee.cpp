#include <iostream>
using namespace std;
//孩子兄弟表示法
typedef struct  CSNode{
    int data;
    struct CSNode *firstchild, *nextsibling; // 分别指向左孩子和右兄弟
}CSNode, *CSTree;

void CreateTree(CSTree &T){
    // 按自上而下自左至右的次序输入双亲-孩子的有序对，建立树的二叉链表。
    // 输入时，以一对'#'字符作为结束标志，根结点的双亲空，亦以'#'表示之。
    T = nullptr;
    char fa, ch;
    CSNode *p;
    for ( cin>>fa>>ch ; ch!='#' ;) {
        p = new CSNode;
        p->data = ch;
        p->firstchild = p->nextsibling = nullptr; // 创建结点
        
    }
}
int main() {
    CSTree T;
    CreateTree(T);
    return 0;
}