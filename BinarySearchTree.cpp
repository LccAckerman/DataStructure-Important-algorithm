#include <iostream>
using namespace std;

typedef struct Node {
    int data;
    Node *lchild;
    Node *rchild;
}BitNode, *BiTree;

typedef int KeyType;

// 在根指针T所指二叉查找树中查找其关键字等于kval的数据元素
//若查找成功，则指针p指向该数据元素结点，并返回TRUE，否则返回FALSE，指针p为NULL
//T非空时，无论查找成功与否，f 总是指向 p 所指结点的双亲，其初始调用值为NULL
bool Search_BST(BiTree T, KeyType kval, BiTree &p, BiTree &f){
    p = T; // p 指向树中某个结点，f指向其双亲结点
    while(p){
        if(kval == p->data)
            return true;
        else if (kval < p->data){
            f = p;
            p = p->lchild;
        } else{
            f = p;
            p = p->rchild;
        }
    }
    return false;
}

bool Insert_BST(BiTree &T, KeyType e){
    BiTree f = nullptr;
    BiTree p = T;
    if(Search_BST(T, e, p, f)){
        return false;
    } else{
        BiTree s = new BitNode ;
        s->data = e;
        s->rchild = s->lchild = nullptr;
        if(!f) T = s;
        else if (e < f->data) f->lchild = s;
        else f->rchild = s;
        return true;
    }
}

void Delete_BST(BiTree &T, KeyType kval) {
    BiTree f = nullptr;
    BiTree p = nullptr;
    BiTree q;
    BiTree s;
    if (Search_BST(T, kval, p, f)) {
        if (p->lchild && p->rchild) {
            q = p;
            s = p->lchild; // 在p的左子树寻找最大结点
            while (s->rchild) {
                q = s;
                s = s->rchild;
            }
            p->data = s->data;
            if (q != p) q->rchild = s->lchild; // s是前驱结点，q是s的父节点，q接上s的左孩子，因为现在没有右孩子的
            else q->lchild = s->lchild; // s就是p的左孩子，s覆盖p接上s的左孩子就ok
            delete s;
        } else {
            if (!p->rchild) {
                q = p;
                p = p->lchild;
            } else {
                q = p;
                p = p->rchild;
            }// 此时p已指向被删结点的子树结点，接下来将指针p所指子树挂接到被删结点的双亲(指针f所指的)结点上
            if (!f) T = p;
            else if (q == f->lchild) f->lchild = p;
            else f->rchild = p;
            delete q;
        }
    }
}

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
