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
{
    S.elem[0] = S.elem[low];
    int pivotkey = S.elem[low];
    while (low < high){
        while (low<high && S.elem[high] >= pivotkey){
            high--;
        }
        if (low<high){
            S.elem[low++] = S.elem[high];
        }
        while (low<high && S.elem[low] <= pivotkey){
            low++;
        }
        if (low<high)
            S.elem[high--] = S.elem[low];
    }
    S.elem[low] = S.elem[0];

    return low;
}

void QSort(Sqlist &S, int s, int t)
{ //对记录序列[s,...,t]进行快速排序
    if(s <t){
        int pivotloc = Partition(S, s, t);
        QSort(S, s, pivotloc-1);
        QSort(S, pivotloc+1, t);
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