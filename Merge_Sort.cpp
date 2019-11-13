#include <iostream>
using namespace std;

typedef struct {
    int *elem;
    int length;
}Sqlist;

void createlist(Sqlist &S, const int arr[], int n)
{
    S.elem = new int[n];
    for (int i = 0; i < n; ++i) {
        S.elem[i] = arr[i];
    }
    S.length = n;
}

void insert(Sqlist &S, int pos, int e) // 在顺序线性表 L 的第 i 个元素之前插入新的元素e
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

void Merge(Sqlist &S, Sqlist &T, int i, int m,int n)
{ //将有序的S[i...m] S[m+1...n] 归并为有序的T[i,n]
    int k = i;
    int j = m+1;
    for (; i<=m && j<=n; ++k) {
        if (S.elem[i] <= S.elem[j]) T.elem[k] = S.elem[i++];
        else T.elem[k] = S.elem[j++];
    }
    while (i <= m) T.elem[k++] = S.elem[i++];
    while (j <= n) T.elem[k++] = S.elem[j++];
}

void Msort(Sqlist &S, Sqlist &T, int s, int t)
{ //sort [s...t]
    Sqlist T2; 
    int arr[t-s+1];
    createlist(T2, arr, t-s+1); //开设用于存放归并排序中间结果的辅助空间
    if (s==t) T=S;
    else{
        int m = (s+t)/2; // 将SR[s..t]平分为SR[s..m]和SR[m+1..t]
        Msort(S, T2, s, m); // 递归地将SR[s..m]归并为有序的TR2[s..m]
        Msort(S, T2, m+1, t); // 递归地将SR[m+1..t]归并为有序的TR2[m+1..t]
        Merge(T2, T, s, m, t); // 将TR2[s..m]和TR2[m+1..t]归并到TR1[s..t]
    }
}

void MergeSort(Sqlist &S)
{
    Msort(S, S, 0, S.length-1);
};
int main() {
    Sqlist S;
    int arr[] = {23,76,22,56,98,12};
    createlist(S, arr, 6);
    MergeSort(S);
    for (int i = 0; i < S.length; ++i) {
        cout<<S.elem[i]<<endl;
    }
    DestroyList(S);
    return 0;
}
