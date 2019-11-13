#include <iostream>
using namespace std;

typedef struct {
    int *elem;
    int length;
}Sqlist;

void createlist(Sqlist &S, int arr[], int n)
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

void BubbleSort(Sqlist &S)
{
    int i = S.length;
    while(i > 1)  //表示上一趟曾进行过记录的交换
    {
        int lastExchangeIndex = 1;
        for (int j = 0; j < i; ++j) {
            if (S.elem[j+1] < S.elem[j])
            {
                int temp = S.elem[j+1];
                S.elem[j+1] = S.elem[j];
                S.elem[j] = temp;
                lastExchangeIndex = j;
            }
        }
        i = lastExchangeIndex;  // 一趟排序中无序序列中最后一个记录的位置
    }
}
int main() {
    int arr[] = {76,45,23,98,33,24};
    Sqlist S;
    createlist(S, arr, 6);
    BubbleSort(S);
    for (int i = 0; i < S.length; ++i) {
        cout<<S.elem[i]<<endl;
    }
    DestroyList(S);
    return 0;
}
