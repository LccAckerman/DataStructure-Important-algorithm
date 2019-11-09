#include <iostream>

#define MAXSIZE 100
#define ROW 4
#define COL 4
typedef struct {
    int i;
    int j;
    int e;
}Triple;

typedef struct {
    Triple data[MAXSIZE+1];
    int ROWu;
    int COLu;
    int TOTALu;
}TsMatrix;

bool TransPoseSMatrix(TsMatrix M, TsMatrix &T)
{
    T.ROWu = M.COLu;
    T.COLu = M.ROWu;
    T.TOTALu = M.TOTALu;
    if (T.TOTALu)
    {
        int q = 1;
        for (int col = 0; col < M.COLu; ++col) {
            for ( int p = 1; p < M.TOTALu; ++p) {
                if (M.data[p].j == col){
                    T.data[q].i = M.data[p].j;
                    T.data[q].j = M.data[p].i;
                    T.data[q].e = M.data[p].e;
                    q++;
                }
            }
        }
    }
    return true;
}

TsMatrix * Init(int flag, int mat[ROW][COL]){
    TsMatrix *A = (TsMatrix *)malloc(sizeof(TsMatrix));
    int p = 1;
    A->ROWu = ROW;
    A->COLu = COL;
    for (int i = 0; i < ROW; ++i) {
        for (int j = 0; j < COL; ++j) {
            if (mat[i][j] != 0){
                A->data[p].e = mat[i][j];
                A->data[p].i = i;
                A->data[p].j = j;
                p++;
        }
    }
    }
    A->TOTALu = p;
    return A;
}
int main() {
    int mat[ROW][COL] = {1,2,0,0,
                         0,6,0,0,
                         0,0,0,3,
                         1,0,0,3};
    TsMatrix *M = Init(1, mat);
    TsMatrix T;
    TransPoseSMatrix(*M, T);
    for (int i = 1; i < M->TOTALu; ++i) {
        std::cout<<T.data[i].i<<" "<<T.data[i].j<<" "<<T.data[i].e<<std::endl;
    }
    return 0;
}