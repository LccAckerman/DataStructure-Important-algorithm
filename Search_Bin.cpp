#include <iostream>
using namespace std;
typedef int ElemType;
typedef struct {
    ElemType *elem;
    int length;
}SSTable;
int Search_Bin(SSTable ST, int kval){
    int low = 1;
    int high = ST.length;
    while (low <= high){
        int mid = (low + high) / 2;
        if(kval == ST.elem[mid])
            return mid;
        else if (kval < ST.elem[mid]){
            high = mid - 1;
        } else{
            low = mid + 1;
        }
    }
    return 0;
}
int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
