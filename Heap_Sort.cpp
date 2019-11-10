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

void heappass(Sqlist &S, int n, int i)
{
    int largest = i;
    int left = 2*i + 1;
    int right = 2*i +2;
    if (left<n && S.elem[left] > S.elem[largest])
        largest = left;
    if (right<n && S.elem[right]>S.elem[largest])
        largest = right;
    if (largest != i){
        int temp = S.elem[i];
        S.elem[i] = S.elem[largest];
        S.elem[largest] = temp;
        heappass(S, n, largest);
    }
}

void HeapSort(Sqlist &S, int n)
{
    for (int i = n/2 - 1; i >= 0 ; --i) {
        heappass(S, n, i);
    }
    for (int i = n-1; i >= 0 ; --i) {
        swap(S.elem[0], S.elem[i]);
        heappass(S, i, 0);
    }
}

int main() {
    int arr[] = {23,87,34,56,11,29};
    Sqlist S;
    createlist(S, arr, 6);
    HeapSort(S,6);
    for (int i = 0; i < 6; ++i) {
        cout<<S.elem[i]<<endl;
    }
    DestroyList(S);
    return 0;
}