#include <iostream>
#include <stack>
#define NUM 100
using namespace std;

typedef struct Node{
    char data;
    struct Node *lchild, *rchild;
}TreeNode, *PTreeNode;

PTreeNode CreateTree(char *str){
    stack<PTreeNode*> st;
    PTreeNode *p;
    PTreeNode TP, pre;
    int popflag = 0;
    if (str[0] != '#'){
        TP = new TreeNode ;
        TP->data = str[0];
        TP->lchild = TP->rchild = nullptr;
        st.push(&TP->rchild);
        pre = TP;
    } else{
        return nullptr;
    }
    int i = 1;
    while(str[i] != '\0' || !st.empty()){
        if(str[i] != '#' && str[i] != '\0') { //'#'表示空
            PTreeNode np = new TreeNode ;
            np->data = str[i];
            np->lchild = np->rchild = nullptr;
            if(popflag){
                *p = np;
                popflag = 0;
            } else{
                pre->lchild = np;
            }
            st.push(&np->rchild); // pre的右孩子入栈
            pre = np;
        } else if (str[i] == '#' && !st.empty()){ //遇见空出栈p指向右孩子
            p = st.top();
            st.pop();
            popflag = 1;
        }
        i++;
    }
    return TP;
}

void preOrder(PTreeNode pt)
{
    if(pt)
    {
        cout<<pt->data;
        preOrder(pt->lchild);
        preOrder(pt->rchild);
    }
    else
        cout<<'#';
}
int main() {
    char *str = "ABC##DE#G##F###";
    PTreeNode tp = CreateTree(str);
    preOrder(tp);
    cout<<endl;
    return 0;
}
