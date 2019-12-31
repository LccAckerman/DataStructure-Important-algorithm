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

void swap(int &a, int &b){
    int temp = a;
    a = b;
    b = temp;
}

void QuickSort(Sqlist &S, int left, int right){
    if(!S.elem || right <= left) return;
    int less = left;
    int greater = right;
    int pivot = S.elem[left];
    int it = left;
    while(it <= greater){
        if(S.elem[it] == pivot) ++it;
        else if (S.elem[it] < pivot){
            swap(S.elem[less], S.elem[it]);
            ++it;
            ++less;
        } else{
            swap(S.elem[greater], S.elem[it]);
            --greater;
        }
        QuickSort(S, left, less-1);
        QuickSort(S, greater+1, right);
    }
}

void Qsort(Sqlist &S)
{
    QuickSort(S, 1, S.length);
}

int main() {
    int arr[] = {98, 34, 43, 56, 77, 35};
    Sqlist S;
    createlist(S, arr, 6);
    Qsort(S);
    for (int i = 1; i <= S.length ; ++i) {
        cout<<S.elem[i]<<endl;
    }
    DestroyList(S);
    return 0;
}