#include <bits/stdc++.h>
using namespace std;
const int n = 3;
const int type = 5; // 圆圈个数
int nowcircle = 0;  // 当前圆圈数
int binaryArray[n][8];
char View[3 * n][3 * n]; // 视图
// 核心思路：二进制数，每个数字都是不重复的。顺时针八个方向对应2进制，比如：正北，1000 0000 = 128

// 不限制位置，十进制转二进制
void decimalToBinary(int decimal, int binaryArray[][8])
{
    for (int i = 7; i >= 0; i--)
    {
        binaryArray[nowcircle][i] = decimal % 2;
        decimal /= 2;
    }
}
// // 限定位置生成十进制数字 试图优化
// int generateRandomDecimal(int binaryArray[][8])
// {
//     int minDecimal = 0;
//     int maxDecimal = 255;

//     for (int i = 0; i < 8; i++)
//     {
//         if (binaryArray[nowcircle][i] == 1)
//         {
//             minDecimal += (1 << (7 - i));
//         }
//     }

//     int randomDecimal = minDecimal + rand() % (maxDecimal - minDecimal + 1);
//     return randomDecimal;
// }
// // 二进制转十进制
// int binaryToDecimal(int binaryArray[][8])
// {
//     int decimal = 0;

//     for (int i = 7; i >= 0; i--)
//     {
//         decimal += binaryArray[nowcircle][i] * pow(2, 7 - i);
//     }

//     return decimal;
// }
bool Occupancy_detection(int x, int y, int circleX[], int circleY[])
{
    for (int j = 0; j < type; j++) // 检查是否被占用
    {
        if (x == circleX[j])
        {
            if (y == circleY[j])
            {
                return true;
            }
        }
    }
    return false;
}
void View_init()
{
    // 显示
    for (int i = 0; i < 3 * n; i++)
    {
        if (i % 3 == 0)
        {
            cout << endl;
        }
        for (int j = 0; j < 3 * n; j++)
        {
            if (j % 3 == 0)
            {
                cout << "\t";
            }
            cout << View[i][j];
        }
        cout << endl;
    }
}
int main()
{
    system("chcp 65001");
    srand(time(0));
    // 构造xy轴
    int circleX[type];
    int circleY[type];
    // 初始化
    for (int i = 0; i < type; i++)
    {
        circleX[i] = -1;
        circleY[i] = -1;
    }
    // // 二进制位

    // 各个圆圈的类型
    int circletype[type];
    for (int i = 0; i < type; i++)
    {
        int decimal = rand() % 255;

        // 将一个8位的十进制数字转换成二进制数，用数组存储每一位,例如，定义a[8]数组，十进制128转换为a数组{1,0,0,0,0,0,0,0}。
        decimalToBinary(decimal, binaryArray);

        // 圆圈的位置
        int x = rand() % n;
        int y = rand() % n;
        bool XYflag = false;
        // 检测占用
        XYflag = Occupancy_detection(x, y, circleX, circleY);
    Again:
        if (!(XYflag)) // 当前位置没有被占用
        {
            circleX[i] = x;
            circleY[i] = y;
            // 限制条件,剪枝
            {
                if (y == 0) // 最左边不应该有指向左边的箭头
                {
                    binaryArray[nowcircle][5] = 0;
                    binaryArray[nowcircle][6] = 0;
                    binaryArray[nowcircle][7] = 0;
                }
                if (y == n - 1) // 最右边不应该有指向右边的箭头
                {
                    binaryArray[nowcircle][1] = 0;
                    binaryArray[nowcircle][2] = 0;
                    binaryArray[nowcircle][3] = 0;
                }
                if (x == n - 1) // 最上
                {
                    binaryArray[nowcircle][0] = 0;
                }
                if (x == 0) // 最下
                {
                    binaryArray[nowcircle][4] = 0;
                }
            }

            // // 限制条件后重新转回十进制,方便存储
            // circletype[i] = binaryToDecimal(binaryArray);
            // 必须存在的分支
            // 表示是否对应成功（至少一次）
            bool Correct_path = false;
            for (int i1 = 0; i1 < 8; i1++)
            {
                if (binaryArray[nowcircle - 1][i1] == 1 && nowcircle != 0 && !Correct_path)
                {
                    // 对角线为1（必须有一个元素与其对应）
                    binaryArray[nowcircle][(i1 + 4) % 8] = 1;
                    // 有一个对应即可
                    Correct_path = true;
                }
            }
            nowcircle++;
        }
        else // 被占用就重置
        {
            while (XYflag)
            {
                x = rand() % n;
                y = rand() % n;
                XYflag = Occupancy_detection(x, y, circleX, circleY);
            }
            goto Again;
        }
    }
    // 输出测试
    for (int j = 0; j < type; j++)
    {
        cout << "j:" << j << " ";
        for (int i = 0; i < 8; i++)
        {
            cout << binaryArray[j][i] << " ";
        }

        cout << "\n"
             << circleX[j] << " " << circleY[j] << " ";
        cout << endl
             << endl;
    }
    // 打表 初始化

    for (int i = 0; i < 3 * n; i++)
    {
        for (int j = 0; j < 3 * n; j++)
            View[i][j] = '-';
    }

    // 放置圆
    for (int i = 0; i < type; i++)
    {
        for (int j = 0; j < 8; j++)
            View[circleX[i] * n + 1][circleY[i] * n + 1] = 'A';
    }
    cout << endl;
    // 放置箭头
    for (int i = 0; i < type; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            binaryArray[0][0] = 1;
            if (binaryArray[i][j] == 1)
            {
                switch (j)
                {
                case 0:
                    View[circleX[i] * n][circleY[i] * n + 1] = '1';
                    break;
                case 1:
                    View[circleX[i] * n][circleY[i] * n + 2] = '2';
                    break;
                case 2:
                    View[circleX[i] * n + 1][circleY[i] * n + 2] = '3';
                    break;
                case 3:
                    View[circleX[i] * n + 2][circleY[i] * n + 2] = '4';
                    break;
                case 4:
                    View[circleX[i] * n + 2][circleY[i] * n + 1] = '5';
                    break;
                case 5:
                    View[circleX[i] * n + 2][circleY[i] * n] = '6';
                    break;
                case 6:
                    View[circleX[i] * n + 1][circleY[i] * n] = '7';
                    break;
                case 7:
                    View[circleX[i] * n][circleY[i] * n] = '8';
                    break;
                }
            }
        }
    }
    View_init();

    while (true)
    {
        // 交换元素
        cout << endl;
        cout << "输出两个元素的坐标以交换,从上到下是X，从左到右是Y,如(1,1)(2,2)，不用加括号，用Enter或空格分隔:";
        int X1, X2, Y1, Y2;
        cin >> X1;
        //循环直到#结束
        if (X1 == '#')
        {
            break;
        }
        cin >> Y1 >> X2 >> Y2;
        cout << endl;
        // 全部交换，包括圆心（圆心相同所以没关系）
        char temp;
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                temp = View[X1 * n + i][Y1 * n + j];
                View[X1 * n + i][Y1 * n + j] = View[X2 * n + i][Y2 * n + j];
                View[X2 * n + i][Y2 * n + j] = temp;
            }
        }
        View_init();
        system("pause");
    }
    return 0;
}