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

int GetMax(Sqlist &S, int n)
{
    int max = S.elem[0];
    for (int i = 1; i < n; ++i) {
        if (S.elem[i] > max){
            max = S.elem[i];
        }
    }
    return max;
}

void countSort(Sqlist &S, int n, int exp)
{
    int output[n];
    int i, count[10] = {0};
    // Store count of occurrences in count[]
    for (i = 0; i < n; ++i) {
        count[(S.elem[i]/exp%10)]++;
    }
    // Change count[i] so that count[i] now contains actual
    //  position of this digit in output[]
    for (int i = 1; i < 10; ++i) {
        count[i] += count[i-1];
    }
    // Build the output array
    for (i = n-1; i >= 0; --i) {
        output[count[S.elem[i]/exp%10] - 1] = S.elem[i];
        count[(S.elem[i]/exp)%10]--;
    }
    // Copy the output array to arr[], so that arr[] now
    // contains sorted numbers according to current digit
    for (i = 0; i < n; i++) {
        S.elem[i] = output[i];
    }
}

void RadixSort(Sqlist &S, int n)
{
    int m = GetMax(S, n);
    for (int exp = 1; m/exp > 0; exp *= 10) {
        countSort(S, n , exp);
    }
}

int main() {
    int arr[] = {12,56,45,987,35,243};
    int n = sizeof(arr)/ sizeof(arr[0]);
    Sqlist S;
    createlist(S, arr, n);
    RadixSort(S, n);
    for (int i = 0; i < n; ++i) {
        cout<<S.elem[i]<<endl;
    }
    DestroyList(S);
    return 0;
}