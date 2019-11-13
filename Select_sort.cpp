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
void SelectPass(Sqlist &S)
{
    for (int i = 0; i < S.length; ++i) {
        int j = i;  // j 指示关键字最小记录的位置，初值设为i
        for (int k = i+1; k < S.length; ++k) {
            if (S.elem[k] < S.elem[j]) j=k; // 暂不进行记录交换，只记录位置
        }
        if (i != j) 
        { // 最后互换记录R[j] 和R[i]
            int temp = S.elem[i];
            S.elem[i] = S.elem[j];
            S.elem[j] = temp;
        }
    }
}


int main() {
    Sqlist S;
    int arr[] = {23,14,54,22,34,44};
    createlist(S, arr, 6);
    SelectPass(S);
    for (int i = 0; i < S.length; ++i) {
        cout<<S.elem[i]<<endl;
    }
    DestroyList(S);
    return 0;
}
