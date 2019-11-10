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

void InsertPass(Sqlist &S)
{
    for(int i=2;i<=S.length;i++){
        if (S.elem[i] < S.elem[i-1]){
            S.elem[0] = S.elem[i];
            for (; S.elem[0] < S.elem[i-1]; --i) {
                S.elem[i] = S.elem[i-1];
            }
            S.elem[i] = S.elem[0];
        }
    }
}

int main(){
    int arr[] = {99,66,13,22,56,87};
    Sqlist S;
    createlist(S, arr, 6);
    InsertPass(S);
    for (int i = 1; i <= S.length; ++i) {
        cout<<S.elem[i]<<endl;
    }
    DestroyList(S);
    return 0;
}