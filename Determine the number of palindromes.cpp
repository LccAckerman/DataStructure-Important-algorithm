#include <iostream>
#include <tgmath.h>

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
int main()
{
    std::cout<<"What's the number?"<<std::endl;
    int long num;
    std::cin>>num;
    SqStack s;
    int long mynum = num;
    Init(s, 10, 10);
    while (mynum != 0){
        int data = mynum%10;
        push(s, data);
        mynum /= 10;
    }
    int long reverse_num = 0;
    int mytop = 0;
    while(!is_empty(s)){
        int poped = pop(s);
        reverse_num += pow(10, mytop++) *poped;
    }
    if(reverse_num == num)
        std::cout<<"YES"<<std::endl;
    else
        std::cout<<"NO"<<std::endl;
}



