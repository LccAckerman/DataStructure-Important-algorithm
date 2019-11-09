#include <iostream>

#define STACK_INIT_SIZE 20
#define STACKINCREMENT 20

typedef struct{
    int *elem;
    int top;
    int stacksize;
    int incrementsize;
}SqStack;

void incrementStacksize(SqStack &s);

void Init(SqStack &s, int maxsize = STACK_INIT_SIZE, int incrementsize = STACKINCREMENT){
    s.elem = new int[maxsize];
    s.top = -1;
    s.stacksize = maxsize;
    s.incrementsize = incrementsize;
}

void push(SqStack &s, int data){
    if(s.top == s.stacksize-1)
        incrementStacksize(s);
    s.elem[++s.top] = data;
}

int pop(SqStack &s){
    int e = s.elem[s.top];
    s.top--;
    return e;
}

void StackTraverse(SqStack &s)
{
    SqStack news;
    Init(news);
    while (s.top != -1){
        push(news, pop(s));
    }
    while (news.top != -1){
        int t = pop(news);
        push(s, t);
        std::cout<<t<<" ";
    }
    std::cout<<std::endl;

}

bool is_empty(SqStack &s){
    return s.top == -1;
}
void incrementStacksize(SqStack &s){
    SqStack news;
    Init(news, s.stacksize, s.incrementsize);
    while(!is_empty(s))
        push(news, pop(s));
    s.elem = new int[s.stacksize + s.incrementsize];
    while(!is_empty(news))
        push(s, pop(news));
    s.stacksize += s.incrementsize;
}

void knapsack(const int w[], int T, int n)
{
    SqStack S;
    Init(S);
    int k = 0;
    do {
        while (T>0 && k<n)
        {
            if (T-w[k] >= 0){
                push(S, k);
                T -= w[k];
            }
            k++;
        }
        if (T == 0)  StackTraverse(S);
        k = pop(S);
        T += w[k];
        k++;
    }while (!is_empty((S)) || k<n);
}

int main(){
    int w[] = {1,8,4,3,5,2};
    int T = 10;
    int n = 6;
    knapsack(w, T, n);
    return 0;
}