#include <iostream>
#define SUCESS 1
#define UNSUCCRSS 0
#define HASHSIZE 16
#define NULLKEY -32768
using namespace std;

typedef struct {
    int *elem;
    int COUNT;
}HashTable;

int Hash(int key){
    return key % 13;
}
//Hi=(Hi+1)%HASHSIZE
void InsertHash(HashTable &H, int key){
    int addr = Hash(key);
    while (H.elem[addr] != NULLKEY)
        addr = (addr + 1) % HASHSIZE;
    H.elem[addr] = key;
}

bool SearchHash(HashTable *H, int key){
    int addr = Hash(key);
    while (H->elem[addr] != key){
        addr = (addr + 1) % HASHSIZE;
        if(H->elem[addr] == NULLKEY || addr == Hash(key))
            return UNSUCCRSS;
    }
    cout<<addr;
    return SUCESS;
}
int main() {
    HashTable H = {new int[HASHSIZE], HASHSIZE};
    for (int i = 0; i < HASHSIZE; ++i) {
        H.elem[i] = NULLKEY;
    }
    int arr[] = {19,14,23,1,68,20,84,27,55,11,10,79};
    for (int i = 0; i < 13; ++i) {
        InsertHash(H, arr[i]);
    }
    for (int j = 0; j < H.COUNT; ++j) {
        cout<<H.elem[j]<<" ";
    }
    cout<<endl;
    SearchHash(&H, 68);
    return 0;
}
