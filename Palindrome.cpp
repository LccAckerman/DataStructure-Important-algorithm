#include <iostream>
#include <stack>
using namespace std;

void Palindrome(int long a) {
    stack<int> S1, S2;
    int long num = a;
    while (num > 0) {
        S1.push(num % 10);
        num /= 10;
    }
    while (!S1.empty()) {
        S2.push(S1.top());
        S1.pop();
    }
    while (a > 0) {
        S1.push(a % 10);
        a /= 10;
    }
    while (!S1.empty()) {
        int b1 = S1.top();
        S1.pop();
        int b2 = S2.top();
        S2.pop();
        if (b1 != b2) {
            cout << "NO" << endl;
            break;
        } else {
            cout << "YES" << endl;
            break;
        }
    }
}

int main()
{
    cout<<"What's the number?"<<endl;
    int long num ;
    cin>>num;
    Palindrome(num);
    return 0;
}
