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
{ // 本算法返回串string1和string2的最长公共子串sub的长度
    char *p1 = string1;
    char *p2 = string2;
    maxlen = 0;
    jpos = 0;
    for (int i = 0; i < ROW; ++i) { //求出两个串的对应矩阵mat[ ][ ]
        for (int j = 0; j < COL; ++j) {
            if (*(p1 + i) == *(p2 + j))
                mat[i][j] = 1;
            else mat[i][j] = 0;
        }
    }
    diagmax1( maxlen, jpos); // 求得string1和string2的最长公共子串的长度以及它在string1中的起始位置jpos
    if (maxlen == 0) *sub = '\0';
    else SubString(sub, string1, jpos, maxlen); // 求得最长公共子串（以jpos作为起始字符的下标，到string1中取长度为maxlen的子串）
    return maxlen;
}

void diagmax1( int &maxlen, int &jpos)
{
    jpos = -1;
    int istart = 0; // 第一条对角线起始元素行下标
    for (int k = -(COL-1); k <= ROW-1 ; ++k) { // 当前对角线特征量为k，其上元素mat[i][j]满足i-j=k
        int i = istart; // 主对角线及与之平行的右上方对角线起始行坐标istart都为0
        int j = i - k; // 由特征量关系求出对应的列坐标
        diagscan(i, j); // 求该对角线上各段连续1的长度，并分别以maxlen和jpos记下到目前为止已经找到的最大公共子串的长度以及串
                                // 中的起始位置，maxlen和jpos作为diagscan函数的外部变量使用
        if (k >= 0) istart++; // 与主对角线平行的左下方对角线起始行坐标istart为12、、、
    }
}

void diagscan(int i, int j)
{
    int eq = 0; 
    int len = 0; // 在一次扫描开始时，对eq和len进行初始化，eq作为标志变量
    int sj = 0;
    while (i < ROW && j < COL)
    {
        if (mat[i][j] == 1)
        {
            len++;
            if (!eq){  // eq == 0，出现的第一个1，用sj记下起始位置，改变状态
                sj = j;eq = 1;
            }
        } else if (eq){ // 即 mat[i][j] == 0 且 eq == 1，求得一个公共子串
            if (len > maxlen)
            {
                maxlen = len;
                jpos = sj;
            }
            eq = 0; len = 0; // 重新开始求新的一段连续出现的1
        }
        i++; j++; // 继续考察该对角线上当前的下一个元素
    }
}

void SubString(char *&sub, char *str, int s, int len)
{
    char *p;
    int k;
    sub = new char[len + 1]; // 为子串分配空间
    p = str+s-1;
    k = len;
    while (k)
    { // 复制字符序列
        *sub++ = *p++;
        k--;
    }
    *sub = '\0'; // 添加串结束符
    sub = sub - len; // 指针复位
}
int main() {
    char *s1 = "wewryt";
    char *s2 = "ew";
    char *sub;
    std::cout<<maxsamesubstring(s1, s2, sub);
    return 1;
}
