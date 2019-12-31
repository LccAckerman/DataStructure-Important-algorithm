#include <iostream>
#include <cstring>
using namespace std;
typedef struct {
    int weight;
    int lchild, rchild;
    int parent;
}Node, *HuffmanTree;
typedef char *HuffmanCode;

//选择两个parent为0，且weight最小的结点s1和s2的方法实现
//n 为叶子结点的总数，s1和 s2两个指针参数指向要选取出来的两个权值最小的结点
void select(HuffmanTree *HT, int n, int *s1, int *s2){
    int min; //记录最小权值
    for (int i = 0; i<n; i++){
        if((*HT)[i].parent == 0){
            min = i;
            break;
        }
    }
    //继续遍历全部结点，找出权值最小的单节点
    for (int j = 0; j < n; ++j) {
        if((*HT)[j].parent == 0){
            if((*HT)[j].weight < (*HT)[min].weight){min = j;}
        }
    }
    //找到了最小权值的结点，s1指向
    *s1 = min;
    //遍历全部结点
    for (int k = 0; k < n; ++k) { //找出下一个单节点，且没有被 s1指向，那么i 赋值给 min，跳出循环
        if((*HT)[k].parent == 0 && k != (*s1)){
            min = k;
            break;
        }
    }
    //继续遍历全部结点，找到权值最小的那个
    for (int l = 0; l < n; ++l) {
        if((*HT)[l].parent == 0 && l != *s1){
            if ((*HT)[l].weight < (*HT)[min].weight){min = l;}
    }
    *s2 = min;        }

}

void CreateHuffmsnTree(HuffmanTree *HT, int *w, int n){
    int m = 2 * n -1;
    int s1, s2;
    *HT = new Node[m+1];
    for (int i = 0; i < n; ++i) {
        (*HT)[i].weight = w[i];
        (*HT)[i].lchild = 0;
        (*HT)[i].parent = 0;
        (*HT)[i].rchild = 0;    }
    for (int j = n; j < m; ++j) {
        (*HT)[j].weight = 0;
        (*HT)[j].lchild = 0;
        (*HT)[j].parent = 0;
        (*HT)[j].rchild = 0;
    }
    cout<<"\nHuffmanTree: \n";
    for (int k = n; k < m; ++k) {
        select(HT, k, &s1, &s2); //选出的两个权值最小的叶子结点，组成一个新的二叉树，根为 i 结点
        (*HT)[s1].parent = k;
        (*HT)[s2].parent = k;
        (*HT)[k].lchild = s1;
        (*HT)[k].rchild = s2;
        (*HT)[k].weight = (*HT)[s1].weight + (*HT)[s2].weight;
        cout<<(*HT)[k].weight<<"("<<(*HT)[s1].weight<<","<<(*HT)[s2].weight<<")"<<endl;
    }
    cout<<endl;
}

void CreateHuffmanCode(HuffmanTree *HT, HuffmanCode *HC, int n){
    int start, p, c;//编码的起始指针 指向当前结点的父节点 遍历 n 个叶子结点的指示标记 c
    HC = new char*[n+1]; //分配n个编码的头指针
    char *cd = new char[n]; //分配求当前编码的工作空间
    //从右向左逐位存放编码，首先存放编码结束符
    cd[n] = '\0'; //从右向左逐位存放编码，首先存放编码结束符
    for (int i = 0; i < n; ++i) {
        start = n - 2; //初始化编码起始指针
        for (c = i, p = (*HT)[i].parent; p != 0 ; c=p, p=(*HT)[p].parent) {
            //从叶子到根节点求编码
            if ((*HT)[p].lchild == c){cd[--start] = '0';}
            else{cd[--start] = '1';}
        }
        HC[i] = (char *)malloc((n-start) * sizeof(char)) ;
        strcpy(HC[i], &cd[start]);
    }
    free(cd);
    for (int j = 0; j < n; ++j) {
        cout<<"HuffmanCode of "<<(*HT)[j].weight<<" is "<<HC[j]<<endl;
    }
}
int main() {
    HuffmanTree HT;
    HuffmanCode HC;
    int *w ;
    cout<<"Total numbers:";
    int n;
    cin>>n;
    w = new int[n+1];
    cout<<"\ninput the numbers' weight:"<<endl;
    for (int i = 0; i < n; ++i) {
        cin>>w[i];
    }
    CreateHuffmsnTree(&HT, w, n);
    CreateHuffmanCode(&HT, &HC, n);
    return 0;
}