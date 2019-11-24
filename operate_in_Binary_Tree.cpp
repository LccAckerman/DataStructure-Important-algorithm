#include <iostream>
using namespace std;

typedef struct Node{
    int data;
    Node * lchild, *rchild;
}BiTNode, *BiTree;

void CreateBiTree(BiTree &T){ //按先序遍历序列建立二叉树的二叉链表A B C # # D E # G # # F # # #
    char ch;
    cin>>ch;
    if(ch == '#') T=nullptr;
    else{
        T = new BiTNode;
        T->data = ch;
        CreateBiTree(T->lchild);
        CreateBiTree(T->rchild);
    }
}

void Pre_BiTreeDepth(BiTree T, int h, int &depth){ //在先序遍历二叉树的过程中求每个结点的层次数，其中的最大值即为二叉树的深度
    if (T){ //h为T指向的结点所在层次，调用之前 h 的初值为 1, depth 为当前求得的最大层次，初值为 0
        if( h>depth) depth = h; // 将自身层次与当前最大层次进行比较
        Pre_BiTreeDepth(T->lchild, h+1, depth);
        Pre_BiTreeDepth(T->rchild, h+1, depth);
    } // 此处depth是引用，所以不断在改变值
}

int Post_BiTreeDepth(BiTree T){ //二叉树的深度应为其左、右子树深度的最大值加1
    if(!T) return 0; //return的是0，为空的那一层，所以每一个return之后的那一层都要+1
    else{
        int hL = Post_BiTreeDepth(T->lchild);
        int hR = Post_BiTreeDepth(T->rchild);
        if(hL >= hR)
            return hL+1;
        else return hR+1;
    }
}

BiTNode * GetTreeNode(char item, BiTNode *lptr, BiTNode* rptr){ //生成一个元素值为item，左指针为lptr，右指针为rptr的结点
    BiTNode *T = new BiTNode;
    T->data = item;
    T->lchild = lptr;
    T->rchild = rptr;
    return T;
}

BiTNode* CopyTree(BiTNode *T){
    if(!T) return nullptr; // 复制一棵空树
    BiTNode* newlptr;
    if(T->lchild)
        newlptr = CopyTree(T->lchild); // 复制遍历左子数
    else newlptr = nullptr;
    BiTNode* newrptr;
    if(T->rchild)
        newrptr = CopyTree(T->rchild); // 复制遍历右子树
    else newrptr = nullptr;
    BiTNode* newnode = GetTreeNode(T->data, newlptr, newrptr); // 生成根节点
    return newnode;
}

float opndd[] = {3.1, 4.2, 2.4, 3.8, 7.2, 2.4};
double value(BiTree T, float opnd[] = opndd){
    if(!T) return 0; // 空树的值是0
    if(T->data >= 0) return opnd[T->data];
    double Lv = value(T->lchild, opnd); // 遍历左子树求第一操作数
    double Rv = value(T->rchild, opnd); // 遍历右子树求第二操作数
    double v;
    switch (T->data){
        case -1: v = Lv + Rv;
            break;
        case -2: v = Lv- Rv;
            break;
        case -3: v = Lv * Rv;
            break;
        case -4: v = Lv / Rv;
            break;
        default:
            cout<<"不合法的运算符";
            break;
    }
    return v;
}

int main() {
    BiTree T;
    CreateBiTree(T);
    int h = Post_BiTreeDepth(T);
    BiTree TT = CopyTree(T);
    int hh = Post_BiTreeDepth(TT);
    cout<<h<<hh;
    return 0;
}