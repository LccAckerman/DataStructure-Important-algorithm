#include <iostream>

using namespace std;

typedef struct TNode{
    char data;
    struct TNode *lchild, *rchild; // 左右指针
    struct TNode *pred, *succ; //(左)前驱、（右）后继线索
}BiThrNode, *BiThrTree;

void InThreading(BiThrTree p, BiThrTree &pre); //函数声明
/*在二叉树的中序全线索链表上添加一个“头结点”，该结点的“左指针”指向二叉树的根结点，
 * “右指针”为空；“右线索”指向中序遍历的第一个结点，“左线索”指向中序遍历的最后一个结点。
 * */
void InOrderThreading(BiThrTree &H, BiThrTree T){
    // 建立根指针T所指二叉树的中序全线索链表，H指向该线索链表的头结点
    H = new BiThrNode; // 创建线索链表的头结点
    H->lchild = T;
    H->rchild = nullptr;
    if(!T){ //空树头结点的线索指向头结点
        H->pred = H;
        H->succ = H;
    } else{
        BiThrTree pre = H;
        InThreading(T, pre); // 对二叉树进行中序遍历，在遍历过程中进行线索化
        pre->succ = H; // 此时pre指向中序遍历的最后一个结点
        H->pred = pre;
    }
}

void InThreading(BiThrTree p, BiThrTree &pre){ //带着一个前驱结点指针（pre）去遍历一棵二叉树。
    if(p){ //“前驱”的指针pre，而访问操作就是“在当前访问的结点与它的前驱之间建立线索”
        InThreading(p->lchild, pre); // 左子树线索化
        pre->succ = p; p->pred = pre; // 建立线索，此时的pre为中序遍历
        pre = p; //保持pre指向形参p的前驱
        InThreading(p->rchild, pre);
    }
}
void CreateBiTree(BiThrTree &T){ //按先序遍历序列建立二叉树的二叉链表A B C # # D E # G # # F # # #
    char ch;
    cin>>ch;
    if(ch == '#') T=nullptr;
    else{
        T = new BiThrNode;
        T->data = ch;
        CreateBiTree(T->lchild);
        CreateBiTree(T->rchild);
    }
}

void InOrder(BiThrTree H, void(*visit)(BiThrTree)){
    // H 为指向中序线索链表中头结点的指针，
    // 本算法中序遍历以H->lchild所指结点为根的二叉树
    BiThrTree p = H->succ;
    while (p != H){
        visit(p);
        p = p->succ;
    }
}

void In_Order(BiThrTree T, void(*visit)(BiThrTree)){  //前序递归遍历
    if(T){
        In_Order(T->lchild, visit);
        visit(T);
        In_Order(T->rchild, visit);
    }
}

void visit(BiThrTree H){
    cout<<H->data;
}
int main() {
    void (*p)(BiThrTree);
    p = visit;
    BiThrTree  T;
    CreateBiTree(T);
    In_Order(T, p);
    cout<<endl;
    BiThrTree  H;
    InOrderThreading(H, T);
    InOrder(H, p);
    return 0;
}