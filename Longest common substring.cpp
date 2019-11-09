#include <iostream>

#define ROW 6
#define COL 4

int mat[ROW][COL];
static int maxlen;
static int jpos;

void diagscan(int i, int j);
void diagmax1( int &maxlen, int &jpos);
void SubString(char *&sub, char *str, int s, int len);

int maxsamesubstring(char *string1, char *string2, char *&sub)
{
    char *p1 = string1;
    char *p2 = string2;
    maxlen = 0;
    jpos = 0;
    for (int i = 0; i < ROW; ++i) {
        for (int j = 0; j < COL; ++j) {
            if (*(p1 + i) == *(p2 + j))
                mat[i][j] = 1;
            else mat[i][j] = 0;
        }
    }
    diagmax1( maxlen, jpos);
    if (maxlen == 0) *sub = '\0';
    else SubString(sub, string1, jpos, maxlen);
    return maxlen;
}

void diagmax1( int &maxlen, int &jpos)
{
    jpos = -1;
    int istart = 0;
    for (int k = -(COL-1); k <= ROW-1 ; ++k) {
        int i = istart;
        int j = i - k;
        diagscan(i, j);
        if (k >= 0) istart++;
    }
}

void diagscan(int i, int j)
{
    int eq = 0;
    int len = 0;
    int sj = 0;
    while (i < ROW && j < COL)
    {
        if (mat[i][j] == 1)
        {
            len++;
            if (!eq){
                sj = j;eq = 1;
            }
        } else if (eq){
            if (len > maxlen)
            {
                maxlen = len;
                jpos = sj;
            }
            eq = 0; len = 0;
        }
        i++; j++;
    }
}

void SubString(char *&sub, char *str, int s, int len)
{
    char *p;
    int k;
    sub = new char[len + 1];
    p = str+s-1;
    k = len;
    while (k)
    {
        *sub++ = *p++;
        k--;
    }
    *sub = '\0';
    sub = sub - len;
}
int main() {
    char *s1 = "wewryt";
    char *s2 = "ew";
    char *sub;
    std::cout<<maxsamesubstring(s1, s2, sub);
    return 1;
}
