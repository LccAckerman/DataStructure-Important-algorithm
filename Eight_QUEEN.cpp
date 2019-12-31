#include <iostream>
#include <cstring>
#include <cmath>
#define NUM 8
using namespace std;

typedef struct{
    int *elem;
    int top;
    int stacksize;
}SqStack;

void Init(SqStack &s){
    s.elem = new int[NUM];
    s.top = -1;
    s.stacksize = NUM;
}

void push(SqStack &s, int data){
    s.elem[++s.top] = data;
}

int pop(SqStack &s){
    int e = s.elem[s.top];
    s.top--;
    return e;
}

bool isEmpty(SqStack &s){
    return s.top == -1;
}

bool isFull(SqStack &S){
    return S.top == S.stacksize - 1;
}

bool canPut(SqStack &S, int e){
    for (int i = 0; i <= S.top; ++i) {
        if(S.elem[i] == e || abs(S.elem[i] - e) == abs(i-(S.top+1))) //行之差绝对值等于列之差绝对值，则说明这两个皇后在同一斜线上
            return false;
    }
    return true;
}

void displayResult(SqStack S){
    for (int i = 0; i <= S.top; ++i) {
        cout<<S.elem[i];
    }
    cout<<endl;
}

int main() {
    SqStack s;
    int col = -1;
    Init(s);
    while (1){
        col++;
        while (col < NUM && !canPut(s, col)){
            col++;
        }
        if(col < NUM && !isFull(s)){
            push(s, col);
            if(isFull(s)){
                displayResult(s);
                return 0;
            }
            col = -1;
        }
        if(col >= NUM){
            if( isEmpty(s)){
                cout<<"no solution\n";
                return 0;
            }
            col = pop(s);
        }
    }
}
