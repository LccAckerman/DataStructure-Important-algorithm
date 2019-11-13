#include <iostream>
using namespace std;

typedef struct {
    int *elem;
    int length;
}Sqlist;

void createlist(Sqlist &S, int arr[], int n)
{
    S.elem = new int[n+1];
    for (int i = 1; i <= n; ++i) {
        S.elem[i] = arr[i-1];
    }
    S.length = n;
}

void insert(Sqlist &S, int pos, int e) // 在顺序线性表 L 的第 i 个元素之前插入新的元素 e
{
    if (pos<0 || pos>S.length)
        return;
    int item = S.length;
    for (int i = 0; i < S.length-pos; ++i) {
        S.elem[item] = S.elem[item-1];
        item--;
    }
    S.elem[pos-1] = e;
    S.length += 1;
}

int Listdelete(Sqlist &S, int pos)
{
    if (pos<1 || pos>S.length) return false;
    int e = S.elem[pos-1];
    for (int i = 0; i < S.length-pos; ++i) {
        S.elem[pos+i-1] = S.elem[pos+i];
    }
    S.length--;
    return e;
}

void DestroyList(Sqlist &S)
{
    delete[](S.elem);
    S.length = 0;
}

int Partition(Sqlist &S, int low, int high)
{ // 对记录子序列R[low..high]进行一趟快速排序，并返回枢轴记录所在位置
    S.elem[0] = S.elem[low]; // 将枢轴记录移至数组的闲置分量
    int pivotkey = S.elem[low]; // 枢轴记录关键字
    while (low < high){ // 从表的两端交替地向中间扫描
        while (low<high && S.elem[high] >= pivotkey){
            high--;
        }
        if (low<high){
            S.elem[low++] = S.elem[high]; // 将比枢轴记录小的记录移到低端
        }
        while (low<high && S.elem[low] <= pivotkey){
            low++;
        }
        if (low<high)
            S.elem[high--] = S.elem[low]; // 将比枢轴记录大的记录移到高端
    }
    S.elem[low] = S.elem[0];  // 枢轴记录移到正确位置
    return low; // 返回枢轴位置
}

void QSort(Sqlist &S, int s, int t)
{ //对记录序列[s,...,t]进行快速排序
    if(s <t){ // 长度大于1
        int pivotloc = Partition(S, s, t); // 对 R[s..t] 进行一次划分，并返回枢轴位置
        QSort(S, s, pivotloc-1); // 对低子序列递归排序
        QSort(S, pivotloc+1, t); // 对高子序列递归排序
    }
}

void Quicksort(Sqlist &S)
{
    QSort(S, 1, S.length);
}
int main() {
    int arr[] = {98, 34, 43, 56, 77, 35};
    Sqlist S;
    createlist(S, arr, 6);
    Quicksort(S);
    for (int i = 1; i <= S.length ; ++i) {
        cout<<S.elem[i]<<endl;
    }
    DestroyList(S);
    return 0;
}
