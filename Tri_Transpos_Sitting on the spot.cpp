#include <iostream>
//my
using namespace std;


#define MAXSIZE 100
#define ROW 4
#define COL 4

static int num[COL];
static int rpos[COL];

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

TsMatrix * Init(int flag, int mat[ROW][COL]){
    TsMatrix *A = (TsMatrix *)malloc(sizeof(TsMatrix));
    int p = 0;
    A->ROWu = ROW;
    A->COLu = COL;
    for (int i = 0; i < ROW; ++i) {
        for (int j = 0; j < COL; ++j) {
            if (mat[i][j] != 0){
                p++;
                A->data[p].e = mat[i][j];
                A->data[p].i = i;
                A->data[p].j = j;

            }
        }
    }
    A->TOTALu = p;
    return A;
}

void createRpos(TsMatrix M)
{
    for (int col = 0; col < M.COLu; ++col) {
        num[col] = 0;
    }
    for (int t = 1; t <= M.TOTALu; ++t) {
        ++num[M.data[t].j];
    }
    rpos[0] = 1;
    for (int col = 1; col < M.COLu; ++col) {
        rpos[col] = rpos[col - 1] + num[col - 1];
    }
}

bool FastTransposeSMatrix(TsMatrix M, TsMatrix &T){
    T.ROWu = M.COLu;
    T.COLu = M.ROWu;
    T.TOTALu = M.TOTALu;
    if (T.TOTALu)
    {
        createRpos(M);
        for (int p = 1; p <= M.TOTALu; ++p) {
            int col = M.data[p].j;
            int q = rpos[col];
            T.data[q].i = M.data[p].j;
            T.data[q].j = M.data[p].i;
            T.data[q].e = M.data[p].e;
            ++rpos[col];
        }
    }
    return true;
}

int main(){
    int mat[ROW][COL] = {1,2,0,0,
                         0,6,0,0,
                         0,0,0,3,
                         1,0,0,3};
    TsMatrix *M = Init(1, mat);
    TsMatrix T;
    FastTransposeSMatrix(*M, T);
    for (int i = 1; i <= T.TOTALu; ++i) {
        std::cout<<T.data[i].i<<" "<<T.data[i].j<<" "<<T.data[i].e<<std::endl;
    }
    cout<<endl;
    for (int i = 1; i <= M->TOTALu; +i) {
        std::cout<<M->data[i].i<<" "<<M->data[i].j<<" "<<M->data[i].e<<std::endl;
    }
    return 0;
}
