#include <iostream>
using namespace std;

const int N = 8;
int chessboard[N][N] = {0};
int solve_num = 0;

bool check(int row, int col){
    if( row == 0 ) return true;
    for (int i = 0; i != row; ++i) {
        if (chessboard[i][col] == 1) return false;
    }
    for (int j = 0; j != col; ++j) {
        if(chessboard[row][j] == 1) return false;
    }
    for (int i = row - 1, j = col - 1; i >= 0 && j >= 0 ; i--, j--) {
        if( chessboard[i][j] == 1) return false;
    }
    for (int i = row - 1, j = col + 1; i >= 0 && j != N ; --i, ++j) {
        if(chessboard[i][j] == 1) return false;
    }
    return true;
}

void print(){
    int row, col;
    ++solve_num;
    cout<<"Solution"<<solve_num<<": "<<endl;
    for (row = 0; row != N ; row++) {
        for (col = 0; col != N ; col++) {
            cout<<chessboard[row][col] <<" ";
        }
        cout<<endl;
    }
}

void queen(int row){
    int col;
    for (col = 0; col != N ; col++) {
        chessboard[row][col] = 1;
        if (check(row, col)){
            if( row == N - 1 ) print();
            else queen(row + 1);
        }
        chessboard[row][col] = 0;
    }
}

int main(){
    queen(0);
    return 0;
}