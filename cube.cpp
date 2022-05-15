#include <iostream>
#include <cstring>
#include <fstream>
#include <string>
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <ctime>

using namespace std;

// 预编译指令
// #define RotateDebug
#define CrossDebug
#define OutputFormula

int OptsNum = 0;
namespace DataStructure
{
    // 数据结构
    // 分别用来存放魔方各个面的颜色
    /*
    各个面的放置情况guide中所示
    1-6分别为前后左右上下
    cube[7][4][4]
    
    一些约定：
    数组下标从1开始，每个cube[i]中保存一个3*3矩阵
    魔方状态用对应单词首字母表示
    char opts[] : 保存各种操作
    char StandardColor[] : 保存各个面的标准颜色
*/

    char ***cube;
    char opts[] = "RrUuFfDdLlBb";
    char StandardColor[] = "GBORWY";

    // 初始化cube数组
    void init()
    {
        cube = new char **[7];
        for (int i = 1; i <= 6; i++)
        {
            cube[i] = new char *[10];
            for (int j = 1; j <= 3; j++)
                cube[i][j] = new char[10];
        }
    }

    // 用来将魔方重置到标准状态的函数
    void ReSet()
    {
        for (int k = 1; k <= 6; k++)
            for (int i = 1; i <= 3; i++)
                for (int j = 1; j <= 3; j++)
                    cube[k][i][j] = StandardColor[k - 1];
    }
} // namespace DataStructure
using namespace DataStructure;
// 输入输出函数
namespace IO
{
    // 从标准输入流中读入一个魔方，标准如guide文件所示
    void Sread()
    {
        for (int i = 1; i <= 6; i++)
            for (int j = 1; j <= 3; j++)
                for (int k = 1; k <= 3; k++)
                    cin >> cube[i][j][k];
    }

    // 将当前魔方的状态输出的到标准输出流中
    void Sprint()
    {
        for (int i = 1; i <= 6; i++)
        {
            for (int j = 1; j <= 3; j++)
                for (int k = 1; k <= 3; k++)
                    cout << cube[i][j][k];
            cout << endl;
        }
    }

    void SpiltPrint()
    {
        cout << endl;
        for (int i = 1; i <= 3; i++)
        {
            for (int j = 1; j <= 6; j++)
            {
                for (int k = 1; k <= 3; k++)
                    cout << cube[j][i][k];
                cout << ' ';
            }
            cout << endl;
        }
    }

} // namespace IO
using namespace IO;

// 12个旋转函数的名称空间
namespace Rotate
{
    // 辅助旋转函数：用于实现12个操作的辅助函数

    // 对一个3*3的方阵进行顺时针旋转
    void ClockwiseRotate(char **a)
    {
        char b[4][4];
        for (int i = 1; i <= 3; i++)
            for (int j = 1; j <= 3; j++)
                b[j][3 - i + 1] = a[i][j];
        for (int i = 1; i <= 3; i++)
            for (int j = 1; j <= 3; j++)
                a[i][j] = b[i][j];
    }

    // 对一个3*3的方阵进行逆时针旋转
    void antiClockwiseRotate(char **a)
    {
        char b[4][4];
        for (int i = 1; i <= 3; i++)
            for (int j = 1; j <= 3; j++)
                b[3 - j + 1][i] = a[i][j];
        for (int i = 1; i <= 3; i++)
            for (int j = 1; j <= 3; j++)
                a[i][j] = b[i][j];
    }

    // 交换a,b,c,d ---> d,a,b,c
    void Exchange(char *a[4], char *b[4], char *c[4], char *d[4])
    {
        char tmp[4] = {0};
        for (int i = 1; i <= 3; i++)
            tmp[i] = *a[i];

        for (int i = 1; i <= 3; i++)
            *(a[i]) = *(d[i]);
        for (int i = 1; i <= 3; i++)
            *(d[i]) = *(c[i]);
        for (int i = 1; i <= 3; i++)
            *(c[i]) = *(b[i]);
        for (int i = 1; i <= 3; i++)
            *(b[i]) = tmp[i];
    }

    // 旋转函数，分别实现了12个旋转函数，对应魔方的12种旋转操作

    void R()
    {
        char *a[4], *b[4], *c[4], *d[4];
        for (int i = 1; i <= 3; i++)
            a[i] = &(cube[1][i][3]);
        for (int i = 1; i <= 3; i++)
            b[i] = &(cube[5][i][3]);
        for (int i = 1; i <= 3; i++)
            c[i] = &(cube[2][3 - i + 1][1]);
        for (int i = 1; i <= 3; i++)
            d[i] = &(cube[6][i][3]);

        Exchange(a, b, c, d);
        ClockwiseRotate(cube[4]);
#ifdef RotateDebug
        Sprint();
#endif
    }

    void Ri()
    {
        char *a[4], *b[4], *c[4], *d[4];
        for (int i = 1; i <= 3; i++)
            a[i] = &(cube[1][i][3]);
        for (int i = 1; i <= 3; i++)
            b[i] = &(cube[5][i][3]);
        for (int i = 1; i <= 3; i++)
            c[i] = &(cube[2][3 - i + 1][1]);
        for (int i = 1; i <= 3; i++)
            d[i] = &(cube[6][i][3]);

        Exchange(d, c, b, a);
        antiClockwiseRotate(cube[4]);
#ifdef RotateDebug
        Sprint();
#endif
    }

    void U()
    {
        char *a[4], *b[4], *c[4], *d[4];
        for (int i = 1; i <= 3; i++)
            a[i] = &(cube[1][1][i]);
        for (int i = 1; i <= 3; i++)
            b[i] = &(cube[4][1][i]);
        for (int i = 1; i <= 3; i++)
            c[i] = &(cube[2][1][i]);
        for (int i = 1; i <= 3; i++)
            d[i] = &(cube[3][1][i]);

        Exchange(d, c, b, a);
        ClockwiseRotate(cube[5]);
#ifdef RotateDebug
        Sprint();
#endif
    }

    void Ui()
    {
        char *a[4], *b[4], *c[4], *d[4];
        for (int i = 1; i <= 3; i++)
            a[i] = &(cube[1][1][i]);
        for (int i = 1; i <= 3; i++)
            b[i] = &(cube[4][1][i]);
        for (int i = 1; i <= 3; i++)
            c[i] = &(cube[2][1][i]);
        for (int i = 1; i <= 3; i++)
            d[i] = &(cube[3][1][i]);

        Exchange(a, b, c, d);
        antiClockwiseRotate(cube[5]);
#ifdef RotateDebug
        Sprint();
#endif
    }

    void F()
    {
        char *a[4], *b[4], *c[4], *d[4];
        for (int i = 1; i <= 3; i++)
            a[i] = &(cube[5][3][i]);
        for (int i = 1; i <= 3; i++)
            b[i] = &(cube[3][3 - i + 1][3]);
        for (int i = 1; i <= 3; i++)
            c[i] = &(cube[6][1][3 - i + 1]);
        for (int i = 1; i <= 3; i++)
            d[i] = &(cube[4][i][1]);

        Exchange(d, c, b, a);
        ClockwiseRotate(cube[1]);
#ifdef RotateDebug
        Sprint();
#endif
    }

    void Fi()
    {
        char *a[4], *b[4], *c[4], *d[4];
        for (int i = 1; i <= 3; i++)
            a[i] = &(cube[5][3][i]);
        for (int i = 1; i <= 3; i++)
            b[i] = &(cube[3][3 - i + 1][3]);
        for (int i = 1; i <= 3; i++)
            c[i] = &(cube[6][1][3 - i + 1]);
        for (int i = 1; i <= 3; i++)
            d[i] = &(cube[4][i][1]);

        Exchange(a, b, c, d);
        antiClockwiseRotate(cube[1]);
#ifdef RotateDebug
        Sprint();
#endif
    }

    void L()
    {
        char *a[4], *b[4], *c[4], *d[4];
        for (int i = 1; i <= 3; i++)
            a[i] = &(cube[1][i][1]);
        for (int i = 1; i <= 3; i++)
            b[i] = &(cube[6][i][1]);
        for (int i = 1; i <= 3; i++)
            c[i] = &(cube[2][3 - i + 1][3]);
        for (int i = 1; i <= 3; i++)
            d[i] = &(cube[5][i][1]);

        Exchange(a, b, c, d);
        ClockwiseRotate(cube[3]);
#ifdef RotateDebug
        Sprint();
#endif
    }

    void Li()
    {
        char *a[4], *b[4], *c[4], *d[4];
        for (int i = 1; i <= 3; i++)
            a[i] = &(cube[1][i][1]);
        for (int i = 1; i <= 3; i++)
            b[i] = &(cube[6][i][1]);
        for (int i = 1; i <= 3; i++)
            c[i] = &(cube[2][3 - i + 1][3]);
        for (int i = 1; i <= 3; i++)
            d[i] = &(cube[5][i][1]);

        Exchange(d, c, b, a);
        antiClockwiseRotate(cube[3]);
#ifdef RotateDebug
        Sprint();
#endif
    }

    void D()
    {
        char *a[4], *b[4], *c[4], *d[4];
        for (int i = 1; i <= 3; i++)
            a[i] = &(cube[1][3][i]);
        for (int i = 1; i <= 3; i++)
            b[i] = &(cube[4][3][i]);
        for (int i = 1; i <= 3; i++)
            c[i] = &(cube[2][3][i]);
        for (int i = 1; i <= 3; i++)
            d[i] = &(cube[3][3][i]);

        Exchange(a, b, c, d);
        ClockwiseRotate(cube[6]);
#ifdef RotateDebug
        Sprint();
#endif
    }

    void Di()
    {
        char *a[4], *b[4], *c[4], *d[4];
        for (int i = 1; i <= 3; i++)
            a[i] = &(cube[1][3][i]);
        for (int i = 1; i <= 3; i++)
            b[i] = &(cube[4][3][i]);
        for (int i = 1; i <= 3; i++)
            c[i] = &(cube[2][3][i]);
        for (int i = 1; i <= 3; i++)
            d[i] = &(cube[3][3][i]);

        Exchange(d, c, b, a);
        antiClockwiseRotate(cube[6]);
#ifdef RotateDebug
        Sprint();
#endif
    }

    void B()
    {
        char *a[4], *b[4], *c[4], *d[4];
        for (int i = 1; i <= 3; i++)
            a[i] = &(cube[5][1][i]);
        for (int i = 1; i <= 3; i++)
            b[i] = &(cube[3][3 - i + 1][1]);
        for (int i = 1; i <= 3; i++)
            c[i] = &(cube[6][3][3 - i + 1]);
        for (int i = 1; i <= 3; i++)
            d[i] = &(cube[4][i][3]);

        Exchange(a, b, c, d);
        ClockwiseRotate(cube[2]);
#ifdef RotateDebug
        Sprint();
#endif
    }

    void Bi()
    {
        char *a[4], *b[4], *c[4], *d[4];
        for (int i = 1; i <= 3; i++)
            a[i] = &(cube[5][1][i]);
        for (int i = 1; i <= 3; i++)
            b[i] = &(cube[3][3 - i + 1][1]);
        for (int i = 1; i <= 3; i++)
            c[i] = &(cube[6][3][3 - i + 1]);
        for (int i = 1; i <= 3; i++)
            d[i] = &(cube[4][i][3]);

        Exchange(d, c, b, a);
        antiClockwiseRotate(cube[2]);
#ifdef RotateDebug
        Sprint();
#endif
    }

} // namespace Rotate
using namespace Rotate;

namespace Operate
{

    // ops -> operator 进行char变量对应操作
    void StringToRotate(const char ops)
    {
        if (ops == 'R')
            R();
        else if (ops == 'r')
            Ri();
        else if (ops == 'U')
            U();
        else if (ops == 'u')
            Ui();
        else if (ops == 'F')
            F();
        else if (ops == 'f')
            Fi();
        else if (ops == 'L')
            L();
        else if (ops == 'l')
            Li();
        else if (ops == 'D')
            D();
        else if (ops == 'd')
            Di();
        else if (ops == 'B')
            B();
        else if (ops == 'b')
            Bi();
        else
        {
            cout << "Wrong Rotate Type in Function " << endl;
        }
    }

    // 用于进行与ops反方向旋转的函数
    void StringToAntirotate(const char ops)
    {
        if (ops == 'R')
            Ri();
        else if (ops == 'r')
            R();
        else if (ops == 'U')
            Ui();
        else if (ops == 'u')
            U();
        else if (ops == 'F')
            Fi();
        else if (ops == 'f')
            F();
        else if (ops == 'L')
            Li();
        else if (ops == 'l')
            L();
        else if (ops == 'D')
            Di();
        else if (ops == 'd')
            D();
        else if (ops == 'B')
            Bi();
        else if (ops == 'b')
            B();
        else
        {
            cout << "Wrong Rotate Type" << endl;
        }
    }

    // 获取相反的操作
    char GetRevOpt(char ops)
    {
        if (ops == 'R')
            return 'r';
        else if (ops == 'r')
            return 'R';
        else if (ops == 'U')
            return 'u';
        else if (ops == 'u')
            return 'U';
        else if (ops == 'F')
            return 'f';
        else if (ops == 'f')
            return 'F';
        else if (ops == 'L')
            return 'l';
        else if (ops == 'l')
            return 'L';
        else if (ops == 'D')
            return 'd';
        else if (ops == 'd')
            return 'D';
        else if (ops == 'B')
            return 'b';
        else if (ops == 'b')
            return 'B';
        else
        {
            cout << "Wrong Rotate Type in function GetRevOpt" << ' ' << ops << ' ' << '.' << endl;
        }
    }

    void PrintChar(const char x)
    {
        if (x == 'r')
            cout << "Ri";
        else if (x == 'l')
            cout << "Li";
        else if (x == 'b')
            cout << "Bi";
        else if (x == 'd')
            cout << "Di";
        else if (x == 'u')
            cout << "Ui";
        else if (x == 'f')
            cout << "Fi";
        else
        {
            cout << x;
        }
    }
    // 执行一段公式，Formula为公式对应数组，len为公式长度
    void RunFormula(char *Formula, int len)
    {
        for (int i = 0; i < len; i++)
        {
            StringToRotate(Formula[i]);
            OptsNum++;
#ifdef OutputFormula
            PrintChar(Formula[i]);
            cout << ' ';
#endif
        }
    }

} // namespace Operate
using namespace Operate;

namespace Cross
{
    // 判断两个操作是否相关,若相关，返回1，不相关返回0
    bool JudgeRelevance(char x, char y)
    {
        if ((x == 'u' || x == 'U') && (y == 'D' || y == 'd'))
            return 0;
        if ((x == 'R' || x == 'r') && (y == 'L' || y == 'l'))
            return 0;
        if ((x == 'F' || x == 'f') && (y == 'B' || y == 'b'))
            return 0;

        swap(x, y);

        if ((x == 'u' || x == 'U') && (y == 'D' || y == 'd'))
            return 0;
        if ((x == 'R' || x == 'r') && (y == 'L' || y == 'l'))
            return 0;
        if ((x == 'F' || x == 'f') && (y == 'B' || y == 'b'))
            return 0;

        return 1;
    }

    // 判断是否已经完成了底层十字 已完成则返回1，未完成返回0
    bool IsCross()
    {
        char std = cube[6][2][2];
        bool res = (cube[6][1][2] == std && cube[6][2][1] == std && cube[6][2][3] == std && cube[6][3][2] == std);
        res = (res && cube[1][3][2] == cube[1][2][2]);
        res = (res && cube[2][3][2] == cube[2][2][2]);
        res = (res && cube[3][3][2] == cube[3][2][2]);
        res = (res && cube[4][3][2] == cube[4][2][2]);
#ifdef CrossDebug
        if (res)
        {
            //Sprint();
        }
#endif
        return res;
    }

// 进行底层十字的函数
/*
    尝试使用迭代加深搜索寻找底层十字公式
*/
#ifdef CrossDebug
    double Sumtime = 0;
    double Maxtime = 0;
#endif

    int lim = 0;
    char stack[10] = {0};
    bool flag = 0;
    bool IDFS(int deep)
    {
        //cout << deep << endl;
        if (IsCross())
            return 1;
        if (deep > lim)
            return 0;
        bool res = 0;
        for (int i = 0; i < 12; i++)
        {
            char op = opts[i];
            // 剪枝 ：连续两次进行了相反的操作
            if (deep >= 2 && op == GetRevOpt(stack[deep - 1]))
                continue;
            // 剪枝 ：连续进行了三次同一方向的旋转
            if (deep >= 3 && op == stack[deep - 1] && op == stack[deep - 2])
                continue;
            // 剪枝 : 该步操作与上一步操作无关且与上两步操作相反
            if (deep >= 3 && op == GetRevOpt(stack[deep - 2]) && !JudgeRelevance(op, stack[deep - 1]))
                continue;
            StringToRotate(op);
            stack[deep] = op;
            res = res || IDFS(deep + 1);
            if (res == 1)
            {
#ifdef CrossDebug
                if (flag == 0)
                {
                    cout << "成功找到底层十字公式" << endl;
                    for (int i = 1; i <= deep; i++)
                        cout << stack[i] << ' ';
                    cout << endl;
                    flag = 1;
                }
#endif
                stack[deep] = 0;
                return 1;
            }
            stack[deep] = 0;
            StringToAntirotate(op);
        }
        return 0;
    }

    void SearchCross()
    {
        flag = 0;
        double start, finish;
        start = clock();
        if (IsCross())
            return;
        for (int i = 1; i <= 8; i++)
        {
            lim = i;
            if (IDFS(1))
            {
                break;
            }
        }
        finish = clock();
#ifdef CrossDebug
        cout << "本次SearchCross用时为 ： " << (finish - start) / CLOCKS_PER_SEC << endl;
        if ((finish - start) / CLOCKS_PER_SEC > 1)
            cout << "More than One Second !" << endl;
        double time = 0;
        time = (finish - start) / CLOCKS_PER_SEC;
        Sumtime += time;
        Maxtime = max(Maxtime, time);
#endif
    }
} // namespace Cross
using namespace Cross;

// 主函数 BruteCross::BruteCross();
namespace BruteCross
{
    struct state
    {
        int from[3];
        int to[3];
        char Formula[10];
    };

    state Case1[] = {
        {{6, 1, 2}, {5, 3, 2}, "FF"},
        {{6, 2, 1}, {5, 2, 1}, "LL"},
        {{6, 2, 3}, {5, 2, 3}, "RR"},
        {{6, 3, 2}, {5, 1, 2}, "BB"}};

    state Case2[] = {
        {{1, 3, 2}, {5, 3, 2}, "FUl"},
        {{2, 3, 2}, {5, 1, 2}, "BUr"},
        {{3, 3, 2}, {5, 2, 1}, "LUb"},
        {{4, 3, 2}, {5, 2, 3}, "RUf"}};

    state Case3[] = {
        {{1, 2, 1}, {5, 2, 1}, "l"},
        {{1, 2, 3}, {5, 2, 3}, "R"},
        {{2, 2, 1}, {5, 2, 3}, "r"},
        {{2, 2, 3}, {5, 2, 1}, "L"},
        {{3, 2, 1}, {5, 1, 2}, "b"},
        {{3, 2, 3}, {5, 3, 2}, "F"},
        {{4, 2, 1}, {5, 3, 2}, "f"},
        {{4, 2, 3}, {5, 1, 2}, "B"}};

    state Case4[] = {
        {{1, 1, 2}, {5, 3, 2}, "FuR"},
        {{2, 1, 2}, {5, 1, 2}, "BuL"},
        {{3, 1, 2}, {5, 2, 1}, "LuF"},
        {{4, 1, 2}, {5, 2, 3}, "RuB"}};

    void RunState(state x)
    {
        if (cube[x.from[0]][x.from[1]][x.from[2]] == 'Y')
        {
            for (int i = 1; i <= 4; i++)
            {
                if (cube[x.to[0]][x.to[1]][x.to[2]] != 'Y')
                {
                    RunFormula(x.Formula, strlen(x.Formula));
                    break;
                }
                RunFormula("U", 1);
            }
        }
    }

    void BruteCross()
    {
        // 分四层将棱块旋转到顶面上
        for (int j = 0; j < sizeof(Case1) / sizeof(state); j++)
        {
            for (int i = 0; i < sizeof(Case1) / sizeof(state); i++)
                RunState(Case1[i]);
            for (int i = 0; i < sizeof(Case2) / sizeof(state); i++)
                RunState(Case2[i]);
            for (int i = 0; i < sizeof(Case3) / sizeof(state); i++)
                RunState(Case3[i]);
            for (int i = 0; i < sizeof(Case4) / sizeof(state); i++)
                RunState(Case4[i]);
        }

        for (int i = 1; i <= 4; i++)
        {
            if (cube[1][1][2] == 'G' && cube[5][3][2] == 'Y')
            {
                RunFormula("FF", 2);
                break;
            }
            RunFormula("U", 1);
        }

        for (int i = 1; i <= 4; i++)
        {
            if (cube[3][1][2] == 'O' && cube[5][2][1] == 'Y')
            {
                RunFormula("LL", 2);
                break;
            }
            RunFormula("U", 1);
        }

        for (int i = 1; i <= 4; i++)
        {
            if (cube[4][1][2] == 'R' && cube[5][2][3] == 'Y')
            {
                RunFormula("RR", 2);
                break;
            }
            RunFormula("U", 1);
        }

        for (int i = 1; i <= 4; i++)
        {
            if (cube[2][1][2] == 'B' && cube[5][1][2] == 'Y')
            {
                RunFormula("BB", 2);
                break;
            }
            RunFormula("U", 1);
        }
    }
} // namespace BruteCross

//接口函数名SecondEdge，作用：将已经还原底层的魔方还原好第二层棱块，无参数，直接作用与全局数组Cube；
namespace SecondEdge
{
    void Out(int number)
    {
        char *out1 = "fufufUFUF";
        char *out2 = "rururURUR";
        char *out3 = "bububUBUB";
        char *out4 = "lululULUL";
        if (number == 1)
            RunFormula(out1, 9);
        if (number == 2)
            RunFormula(out2, 9);
        if (number == 3)
            RunFormula(out3, 9);
        if (number == 4)
            RunFormula(out4, 9);
    }

    void Back(int num1, int num2)
    {
        char *Back11 = "UFufulUL";
        char *Back12 = "ulULUFuf";
        char *Back21 = "URurufUF";
        char *Back22 = "ufUFURur";
        char *Back31 = "UBuburUR";
        char *Back32 = "urURUBub";
        char *Back41 = "ULulubUB";
        char *Back42 = "ubUBULul";
        if (num1 == 1 && num2 == 1)
            RunFormula(Back11, 8);
        if (num1 == 1 && num2 == 2)
            RunFormula(Back12, 8);
        if (num1 == 2 && num2 == 1)
            RunFormula(Back21, 8);
        if (num1 == 2 && num2 == 2)
            RunFormula(Back22, 8);
        if (num1 == 3 && num2 == 1)
            RunFormula(Back31, 8);
        if (num1 == 3 && num2 == 2)
            RunFormula(Back32, 8);
        if (num1 == 4 && num2 == 1)
            RunFormula(Back41, 8);
        if (num1 == 4 && num2 == 2)
            RunFormula(Back42, 8);
    }

    void outThe(char color1, char color2)
    {
        if ((cube[1][2][1] == color1 && cube[3][2][3] == color2) || ((cube[1][2][1] == color2 && cube[3][2][3] == color1)))
            Out(1);
        else if ((cube[1][2][3] == color1 && cube[4][2][1] == color2) || ((cube[1][2][3] == color2 && cube[4][2][1] == color1)))
            Out(2);
        else if ((cube[4][2][3] == color1 && cube[2][2][1] == color2) || ((cube[4][2][3] == color2 && cube[2][2][1] == color1)))
            Out(3);
        else if ((cube[2][2][3] == color1 && cube[3][2][1] == color2) || ((cube[2][2][3] == color2 && cube[3][2][1] == color1)))
            Out(4);
    }

    void aligment(char color1, char color2)
    {
        if ((cube[1][1][2] == color1 && cube[5][3][2] == color2) || ((cube[1][1][2] == color2 && cube[5][3][2] == color1)))
            ;
        else if ((cube[4][1][2] == color1 && cube[5][2][3] == color2) || ((cube[4][1][2] == color2 && cube[5][2][3] == color1)))
            RunFormula("U", 1);
        else if ((cube[2][1][2] == color1 && cube[5][1][2] == color2) || ((cube[2][1][2] == color2 && cube[5][1][2] == color1)))
            RunFormula("UU", 2);
        else if ((cube[3][1][2] == color1 && cube[5][2][1] == color2) || ((cube[3][1][2] == color2 && cube[5][2][1] == color1)))
            RunFormula("u", 1);
    }

    void SecondEdge()
    {
        char color1 = 'O', color2 = 'G';
        outThe(color1, color2);
        aligment(color1, color2);
        if (cube[1][1][2] == color2)
            Back(1, 2);
        else
        {
            RunFormula("U", 1);
            Back(1, 1);
        }
        color1 = 'G', color2 = 'R';
        outThe(color1, color2);
        aligment(color1, color2);
        if (cube[1][1][2] == color2)
        {
            RunFormula("u", 1);
            Back(2, 2);
        }
        else
        {
            Back(2, 1);
        }
        color1 = 'R', color2 = 'B';
        outThe(color1, color2);
        aligment(color1, color2);
        if (cube[1][1][2] == color2)
        {
            RunFormula("UU", 2);
            Back(3, 2);
        }
        else
        {
            RunFormula("u", 1);
            Back(3, 1);
        }
        color1 = 'B', color2 = 'O';
        outThe(color1, color2);
        aligment(color1, color2);
        if (cube[1][1][2] == color2)
        {
            RunFormula("U", 1);
            Back(4, 2);
        }
        else
        {
            RunFormula("UU", 2);
            Back(4, 1);
        }
    }
} // namespace SecondEdge

//接口函数名perform， 作用：将已经还原第二层的魔方还原好顶层十字，无参数，直接作用与全局数组Cube；
namespace TopCross
{

    bool matchtopcross() //判断完成顶面十字
    {
        if (cube[5][1][2] == 'W' && cube[5][2][1] == 'W' && cube[5][2][3] == 'W' && cube[5][3][2] == 'W')
            return 1;
        return 0;
    }

    bool yizima()
    {
        if (cube[5][2][2] == cube[5][1][2] && cube[5][2][2] == cube[5][2][1])
            return 1;
        return 0;
    }

    bool litcon()
    {
        if (cube[5][2][1] == cube[5][2][2] && cube[5][2][3] == cube[5][2][2])
            return 1;
        return 0;
    }

    void perform()
    {
        if (matchtopcross() == 1)
            return;

        bool check = false;
        for (int i = 1; i <= 4; i++)
        {
            if (yizima() || litcon()) //一字马、小拐角
            {
                check = true;
                break;
            }
            RunFormula("U", 1);
        }

        RunFormula("FRUruf", 6);
        perform();
    }

} // namespace TopCross

//接口函数名crossTran，作用：将已经还原顶层十字的魔方顶层还原，无参数，直接作用与全局数组Cube；
namespace TopReduction
{
    int count()
    {
        int num = 0;
        for (int i = 1; i < 4; i++)
            for (int j = 1; j < 4; j++)
                if (cube[5][i][j] == 'W')
                    num++;
        return num;
    }

    void aligment1()
    {
        if (cube[1][1][1] != 'W' && cube[1][1][3] != 'W')
            return;
        else
        {
            RunFormula("U", 1);
            aligment1();
        }
    }

    void Back(int number)
    {
        char *back1 = "BUbUBUUb";
        char *back2 = "buBubuuB"; //右下
        if (number == 1)
            RunFormula(back1, 8);
        else if (number == 2)
            RunFormula(back2, 8);
    }

    void Backsix()
    {
        aligment1();
        if (cube[5][3][3] == 'W')
            Back(1);
        else if (cube[5][3][1] == 'W')
            Back(2);
    }

    void aligment2()
    {
        if (cube[2][1][3] == 'W')
            return;
        else
        {
            RunFormula("U", 1);
            aligment2();
        }
    }

    void aligment3()
    {
        if (cube[4][1][3] == 'W' && cube[3][1][1] == 'W')
            return;
        else
        {
            RunFormula("U", 1);
            aligment3();
        }
    }

    void crossTran()
    {
        int num = count();
        if (num == 8)
            return;
        else if (num == 6)
        {
            Backsix();
        }
        else if (num == 7)
        {
            aligment2();
            RunFormula("u", 1);
            Back(2);
            Backsix();
        }
        else if (num == 5)
        {
            aligment3();
            RunFormula("u", 1);
            Back(2);
            Backsix();
        }
    }
} // namespace TopReduction

//接口函数名TestSecondEdge, 作用：测试将已经还原底层的魔方还原好第二层棱块；已经通过测试；
namespace TestSecondEdge
{
    char optss[9][9] = {"UFufulUL", "ulULUFuf", "URurufUF", "ufUFURur", "UBuburUR", "urURUBub", "ULulubUB", "ubUBULul", "FRUrufUU"};

    void TestSecondEdgeGenerator(int len, int Seed = 0)
    {
        ReSet();
        if (Seed == 0)
            Seed = int(time(0));
        cout << "生成测试数据所用的随机数种子为：" << Seed << endl;
        srand(Seed);
        cout << "生成测试案例的打乱公式为" << endl;
        for (int i = 1; i <= len; i++)
        {
            char *op = optss[rand() % 9];
            //cout << op << ' ';
            RunFormula(op, 8);
            cout << op;
            SpiltPrint();
        }
        cout << endl
             << "生成魔方的状态为：" << endl;
    }

    bool Right()
    {
        for (int i = 1; i < 4; i++)
            for (int j = 1; j < 4; j++)
                if (cube[6][i][j] != 'Y')
                    return 0;
        for (int i = 1; i < 4; i++)
        {
            if (cube[1][3][i] != 'G' || cube[1][2][i] != 'G')
                return 0;
            if (cube[2][3][i] != 'B' || cube[2][2][i] != 'B')
                return 0;
            if (cube[3][3][i] != 'O' || cube[3][2][i] != 'O')
                return 0;
            if (cube[4][3][i] != 'R' || cube[4][2][i] != 'R')
                return 0;
        }
        return 1;
    }

    void TestSecondEdge()
    {
        TestSecondEdge::TestSecondEdgeGenerator(500, 0);
        SecondEdge::SecondEdge();
        SpiltPrint();
        cout << Right();
    }

} // namespace TestSecondEdge

//接口函数名TestTopReduction, 作用： 测试将已经还原好第二层棱块的魔方还原顶层十字与顶层还原
namespace TestTopReduction
{
    char optss[3][10] = {"BUbUBUUb", "buBubuuB", "FRUrufUU"};

    void TestTopReductionGenerator(int len, int Seed = 0)
    {
        ReSet();
        if (Seed == 0)
            Seed = int(time(0));
        cout << "生成测试数据所用的随机数种子为：" << Seed << endl;
        srand(Seed);
        cout << "生成测试案例的打乱公式为" << endl;
        for (int i = 1; i <= len; i++)
        {
            char *op = optss[rand() % 3];
            RunFormula(op, 8);
            /*cout << op;
            SpiltPrint();*/
        }
        cout << endl
             << "生成魔方的状态为：" << endl;
    }

    bool Right()
    {
        for (int i = 1; i < 4; i++)
            for (int j = 1; j < 4; j++)
                if (cube[6][i][j] != 'Y')
                    return 0;
        for (int i = 1; i < 4; i++)
            for (int j = 1; j < 4; j++)
                if (cube[5][i][j] != 'W')
                    return 0;
        for (int i = 1; i < 4; i++)
        {
            if (cube[1][3][i] != 'G' || cube[1][2][i] != 'G')
                return 0;
            if (cube[2][3][i] != 'B' || cube[2][2][i] != 'B')
                return 0;
            if (cube[3][3][i] != 'O' || cube[3][2][i] != 'O')
                return 0;
            if (cube[4][3][i] != 'R' || cube[4][2][i] != 'R')
                return 0;
        }
        return 1;
    }

    void TestTopReduction()
    {
        TestTopReductionGenerator(10000, 0);
        TopCross::perform();
        TopReduction::crossTran();
        cout << Right();
    }
} // namespace TestTopReduction
namespace bottomcorner
{
    int amt = 0;
    bool flag[5] = {1, 0, 0, 0, 0};
    //判断底面各角是否归位

    bool matchcorner()
    {
        char std[6] = {};
        std[1] = cube[1][2][2]; //1面
        std[2] = cube[2][2][2]; //2面
        std[3] = cube[3][2][2]; //3面
        std[4] = cube[4][2][2]; //4面
        std[5] = cube[6][2][2]; //6面

        //按照题目规定各个面的标号
        bool bingo = (cube[6][1][1] == std[5] && cube[6][1][3] == std[5] && cube[6][3][1] == std[5] && cube[6][1][3] == std[5]      //6面归位
                      && cube[1][3][1] == std[1] && cube[1][3][3] == std[1] && cube[2][3][1] == std[2] && cube[2][3][3] == std[2]   //1面和3面归位
                      && cube[3][3][1] == std[3] && cube[3][3][3] == std[3] && cube[4][3][1] == std[4] && cube[4][3][3] == std[4]); //3面和4面归位

        if (bingo == 1)
            return 1;
        return 0;
    }

    //进行底面各角归位

    //把底层角块转到顶层

    //对顶层角块归位
    void flag1() //1面    (1,3)
    {
        if (cube[4][1][1] == 'Y' && cube[1][1][3] == 'G' && cube[5][3][3] == 'R')
        {
            RunFormula("RUru", 4);
            amt++;
            flag[1] = 1;
        }
        if (cube[1][1][3] == 'Y' && cube[5][3][3] == 'G' && cube[4][1][1] == 'R')
        {
            RunFormula("URur", 4);
            amt++;
            flag[1] = 1;
        }
        if (cube[5][3][3] == 'Y' && cube[4][1][1] == 'G' && cube[1][1][3] == 'R')
        {
            RunFormula("RUru", 4);
            RunFormula("RUru", 4);
            RunFormula("RUru", 4);
            amt++;
            flag[1] = 1;
        }
        return;
    }

    void flag2() //2面     (3,1)
    {
        if (cube[3][1][1] == 'Y' && cube[2][1][3] == 'B' && cube[5][1][1] == 'O')
        {
            RunFormula("LUlu", 4);
            amt++;
            flag[2] = 1;
        }
        if (cube[2][1][3] == 'Y' && cube[5][1][1] == 'B' && cube[3][1][1] == 'O')
        {
            RunFormula("ULul", 4);
            amt++;
            flag[2] = 1;
        }
        if (cube[5][1][1] == 'Y' && cube[3][1][1] == 'B' && cube[2][1][3] == 'O')
        {
            RunFormula("LUlu", 4);
            RunFormula("LUlu", 4);
            RunFormula("LUlu", 4);
            amt++;
            flag[2] = 1;
        }
        return;
    }

    void flag3() //3面      (1,1)
    {
        if (cube[1][1][1] == 'Y' && cube[3][1][3] == 'O' && cube[5][3][1] == 'G')
        {
            RunFormula("FUfu", 4);
            amt++;
            flag[3] = 1;
        }
        if (cube[3][1][3] == 'Y' && cube[5][3][1] == 'O' && cube[1][1][1] == 'G')
        {
            RunFormula("UFuf", 4);
            amt++;
            flag[3] = 1;
        }
        if (cube[5][3][1] == 'Y' && cube[1][1][1] == 'O' && cube[3][1][3] == 'G')
        {
            RunFormula("FUfu", 4);
            RunFormula("FUfu", 4);
            RunFormula("FUfu", 4);
            amt++;
            flag[3] = 1;
        }
        return;
    }

    void flag4() //4面       (3,3)
    {
        if (cube[2][1][1] == 'Y' && cube[4][1][3] == 'R' && cube[5][1][3] == 'B')
        {
            RunFormula("BUbu", 4);
            amt++;
            flag[4] = 1;
        }
        if (cube[4][1][3] == 'Y' && cube[5][1][3] == 'R' && cube[2][1][1] == 'B')
        {
            RunFormula("UBub", 4);
            amt++;
            flag[4] = 1;
        }
        if (cube[5][1][3] == 'Y' && cube[2][1][1] == 'R' && cube[4][1][3] == 'B')
        {
            RunFormula("BUbu", 4);
            RunFormula("BUbu", 4);
            RunFormula("BUbu", 4);
            amt++;
            flag[4] = 1;
        }
    }

    //次数可以减少！！！！！
    void TurnupCorner()
    {
        for (int i = 1; i <= 16; i++)
        {
            //如果还原了，记录
            if (flag[1] == 0)
                flag1();

            if (flag[2] == 0)
                flag2();

            if (flag[3] == 0)
                flag3();

            if (flag[4] == 0)
                flag4();

            if (amt == 4)
                break;
            //还没有恢复4个 但有恢复的了
            RunFormula("U", 1);
        }
    }

    //恢复底角的主函数
    void botcongw()
    {
        amt = 0;
        memset(flag, 0, sizeof flag);
        flag[0] = 1;

        //顶层有  则还原
        TurnupCorner();
        //此时4块中已经还原了 amt 块
        //不在顶层，说明必在底层             将底层翻上顶层，归位
        int tmp = amt;
        for (int i = 1; i <= 4 - tmp; i++)
        {
            if (flag[1] == 0) //1面的没归位
            {
                RunFormula("RUr", 3);
                RunFormula("RUr", 3);
                RunFormula("RUr", 3);
                TurnupCorner();
            }
            if (flag[2] == 0) //2面的没归位
            {
                RunFormula("LUl", 3);
                RunFormula("LUl", 3);
                RunFormula("LUl", 3);
                TurnupCorner();
            }
            if (flag[3] == 0) //3面的没归位
            {
                RunFormula("FUf", 3);
                RunFormula("FUf", 3);
                RunFormula("FUf", 3);
                TurnupCorner();
            }
            if (flag[4] == 0) //4面的没归位
            {
                RunFormula("BUb", 3);
                RunFormula("BUb", 3);
                RunFormula("BUb", 3);
                TurnupCorner();
            }
        }
    }
} // namespace bottomcorner

// 顶层角块 主函数 TopCorner::TopCorner();
namespace TopCorner
{

    bool IsTopCorner()
    {
        return cube[1][1][1] == cube[1][1][3] && cube[2][1][1] == cube[2][1][3] && cube[3][1][1] == cube[3][1][3] && cube[4][1][1] == cube[4][1][3];
    }

    bool IsColorMarch()
    {
        return cube[1][1][1] == cube[1][2][2];
    }

    void MarchColor()
    {
        for (int i = 1; i <= 4; i++)
        {
            if (IsColorMarch())
            {
                return;
            }
            RunFormula("U", 1);
        }
    }

    void TopCorner()
    {
        if (IsTopCorner())
        {
            MarchColor();
            return;
        }

        int flag = 0;
        for (int i = 1; i <= 4; i++)
        {
            if (cube[1][1][1] == cube[1][1][3])
            {
                flag = 1;
                RunFormula("RbRFFrBRFFRR", 12);
                break;
            }
            RunFormula("U", 1);
        }
        if (!flag)
        {
            RunFormula("RbRFFrBRFFRR", 12);
            for (int i = 1; i <= 4; i++)
            {
                if (cube[1][1][1] == cube[1][1][3])
                {
                    flag = 1;
                    RunFormula("RbRFFrBRFFRR", 12);
                    break;
                }
                RunFormula("U", 1);
            }
        }
    }
} // namespace TopCorner

// 顶层棱块 未施工完成
namespace TopMid
{

    bool IsTopMid()
    {
        for (int i = 1; i <= 4; i++)
        {
            if (cube[i][1][2] != cube[i][1][1])
                return 0;
        }
        return 1;
    }

    bool IsColorMarch()
    {
        for (int i = 1; i <= 4; i++)
        {
            if (cube[i][1][2] != cube[i][2][2])
                return 0;
        }
        return 1;
    }

    void MarchColor()
    {
        for (int i = 1; i <= 4; i++)
        {
            if (IsColorMarch())
            {
                return;
            }
            RunFormula("U", 1);
        }
    }

    void TopMid()
    {
        if (IsTopMid())
        {
            MarchColor();
        }

        int flag = 0;

        for (int i = 1; i <= 4; i++)
        {
            if (cube[1][1][2] == cube[3][1][1] && cube[3][1][2] == cube[4][1][1] && cube[4][1][2] == cube[1][1][1])
            {
                RunFormula("RUrURUUr", 8);
                RunFormula("U", 1);
                RunFormula("luLulUUL", 8);
                flag = 1;
                break;
            }
            else if (cube[1][1][2] == cube[4][1][1] && cube[4][1][2] == cube[3][1][1] && cube[3][1][2] == cube[1][1][1])
            {
                RunFormula("luLulUUL", 8);
                RunFormula("u", 1);
                RunFormula("RUrURUUr", 8);
                flag = 1;
                break;
            }
            RunFormula("U", 1);
        }

        if (!flag)
        {
            RunFormula("RUrURUUr", 8);
            RunFormula("U", 1);
            RunFormula("luLulUUL", 8);
        }
        else
        {
            MarchColor();
            return;
        }

        for (int i = 1; i <= 4; i++)
        {
            if (cube[1][1][2] == cube[3][1][1] && cube[3][1][2] == cube[4][1][1] && cube[4][1][2] == cube[1][1][1])
            {
                RunFormula("RUrURUUr", 8);
                RunFormula("U", 1);
                RunFormula("luLulUUL", 8);
                break;
            }
            else if (cube[1][1][2] == cube[4][1][1] && cube[4][1][2] == cube[3][1][1] && cube[3][1][2] == cube[1][1][1])
            {
                RunFormula("luLulUUL", 8);
                RunFormula("u", 1);
                RunFormula("RUrURUUr", 8);
                break;
            }
            RunFormula("U", 1);
        }

        MarchColor();
    }
} // namespace TopMid

namespace TestTools
{

    // 用于手动测试旋转函数的函数
    void TestRotate()
    {
        char op = 0;
        while (1)
        {
            cin >> op;
            StringToRotate(op);
        }
    }

    // 用于生成测试数据的函数
    /*
    生成测试案例的方法：
    将魔方状态初始化为已还原状态，并对其进行随机打乱
    向标准输出流中输出打乱后的魔方状态并输出打乱公式
    
    打乱步数作为参数传入TestCaseGenerator函数
    TestCaseGenerator函数同时提供一个Seed参数，若传入的Seed值为零，会以运行程序时的系统时间作为随机数种子，否则以传入的Seed值作为种子。
*/

    // 生成测试案例的函数
    void TestCaseGenerator(int len, int Seed = 0)
    {
        ReSet();
        if (Seed == 0)
            Seed = int(time(0));
        cout << "生成测试数据所用的随机数种子为：" << Seed << endl;
        srand(Seed);
        cout << "生成测试案例的打乱公式为" << endl;
        for (int i = 1; i <= len; i++)
        {
            char op = opts[rand() % 12];
            cout << op << ' ';
            StringToRotate(op);
        }
        cout << endl
             << "生成魔方的状态为：" << endl;
        //Sprint();
    }

    //用于测试底层十字的函数
    void CrossTester()
    {
        int n = 30000;
        int success = 0;
        lim = 0;
        for (int i = 0; i <= 9; i++)
            stack[i] = 0;
        freopen("CrossResult.txt", "w", stdout);
        for (int i = 1; i <= n; i++)
        {
            ReSet();
            cout << "---------------------------------------" << endl;
            cout << "TestCase " << i << endl;
            TestCaseGenerator(10, time(0) + i * 5);

            BruteCross::BruteCross();

            if (IsCross())
            {
                ++success;
                cout << "Right Cross" << endl;
            }
            else
                cout << "Wrong Cross" << endl;

            SpiltPrint();
            cout << "---------------------------------------" << endl;
        }
        cout << endl;
        cout << "Average : " << Sumtime / n << endl;
        cout << "Maxtime : " << Maxtime << endl
             << endl;
        cout << success << '/' << n << endl;
        fclose(stdout);
    }

    bool JudgeFloorCorner()
    {
        if (!IsCross)
            return 0;
        bool res = 1;
        for (int i = 1; i <= 4; i++)
            for (int j = 1; j <= 3; j++)
                if (cube[i][3][j] != StandardColor[i - 1])
                    return 0;
        return 1;
    }

    bool FloorCornerGenerator(int num, int Seed = 0)
    {
        ReSet();
        int n;
        ifstream fin("FloorCornerData.txt");
        fin >> n;

        char **F = new char *[n];
        for (int i = 0; i < n; i++)
            F[i] = new char[10];
        for (int i = 0; i < n; i++)
            fin >> F[i];

        fin.close();

        Seed = int(time(0));
        srand(Seed);
        for (int i = 1; i <= num; i++)
        {
            int x = rand() % n;
            RunFormula(F[x], strlen(F[x]));
        }
    }

    void FloorCornerTester()
    {
        cout << "-----------------------------------------------------------" << endl;
        FloorCornerGenerator(50);
        cout << "生成底层角块" << endl;
        SpiltPrint();
        // 底层角块主函数
        bottomcorner::botcongw();

        if (JudgeFloorCorner())
        {
            cout << "测试底层角块结果正确" << endl;
        }
        else
        {
            cout << "测试底层角块结果不正确" << endl;
        }
        cout << "操作结果为：" << endl;
        SpiltPrint();
        cout << "-----------------------------------------------------------" << endl;
    }

} // namespace TestTools
using namespace TestTools;

void MainFunction()
{
    // Step1 : 底层十字
    //SpiltPrint();
    //Sprint();
    BruteCross::BruteCross();
    //SpiltPrint();

    // Step2 :
    bottomcorner::botcongw();
    //SpiltPrint();

    // Step3 : 第二层棱块归位
    SecondEdge::SecondEdge();
    //SpiltPrint();

    // Step4 : 顶层十字
    TopCross::perform();
    //SpiltPrint();

    // Step5 : 顶面还原
    TopReduction::crossTran();
    //SpiltPrint();

    // Step6 : 顶层角块
    TopCorner::TopCorner();
    //SpiltPrint();

    // Step7 : 顶层棱块
    TopMid::TopMid();
    //SpiltPrint();
}

bool IsEnd()
{
    for (int i = 1; i <= 6; i++)
        for (int j = 1; j <= 3; j++)
            for (int k = 1; k <= 3; k++)
                if (cube[i][j][k] != cube[i][2][2])
                    return 0;
    return 1;
}

void FinalTest()
{
    int n = 10000;

    freopen("Result.txt", "w", stdout);

    int success = 0;
    int out = 0;
    int maxStep = 0;
    for (int i = 1; i <= n; i++)
    {
        OptsNum = 0;
        cout << "TestCase:" << i << endl;
        TestCaseGenerator(50, time(0) + i * 5);
        MainFunction();
        if (IsEnd())
        {
            cout << "Right" << endl;
            success++;
        }
        else
        {
            cout << "Wrong" << endl;
        }
        cout << OptsNum << endl;
        maxStep = max(maxStep,OptsNum);
        if (OptsNum > 1000)
        {
            cout << "Too Long !!!" << endl;
            out++;
        }
    }

    cout << success << '/' << n << endl;
    cout << out << '/' << n << endl;
    cout << maxStep << endl;
    fclose(stdout);
}

int main()
{
    // 初始化动态数组cube
    init();

    Sread();
    // 随机生成测试数据
    //TestCaseGenerator(60);

    //SearchCross();
    //TestTopReduction::TestTopReduction();

    //TestTools::FloorCornerTester();

    //TestCaseGenerator(50, time(0));
    // MainFunction();
    // SpiltPrint();
    //bottomcorner::amt = 0;
    //FinalTest();

    MainFunction();
    // cout << endl << OptsNum << endl;
}