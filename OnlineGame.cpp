#include <bits/stdc++.h>
using namespace std;
const int n = 3;
const int type = 5; // 圆圈个数
int nowcircle = 0;  // 当前圆圈数
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
// 限定位置生成十进制数字 试图优化
int generateRandomDecimal(int binaryArray[][8])
{
    int minDecimal = 0;
    int maxDecimal = 255;

    for (int i = 0; i < 8; i++)
    {
        if (binaryArray[nowcircle][i] == 1)
        {
            minDecimal += (1 << (7 - i));
        }
    }

    int randomDecimal = minDecimal + rand() % (maxDecimal - minDecimal + 1);
    return randomDecimal;
}
// 二进制转十进制
int binaryToDecimal(int binaryArray[][8])
{
    int decimal = 0;

    for (int i = 7; i >= 0; i--)
    {
        decimal += binaryArray[nowcircle][i] * pow(2, 7 - i);
    }

    return decimal;
}
bool X_Occupancy_detection(int x, int i, int circleX[])
{
    for (int j = 0; j < type && j <= i; j++) // 检查X是否被占用
    {
        if (x == circleX[j])
        {
            return true;
        }
    }
    return false;
}
bool Y_Occupancy_detection(int y, int i, int circleY[])
{
    for (int j = 0; j < type && j <= i; j++) // 检查Y是否被占用
    {
        if (y == circleY[j])
        {
            return true;
        }
    }
    return false;
}
int main()
{
    srand(time(0));
    // 构造xy轴
    int circleX[type] = {-1};
    int circleY[type] = {-1};
    // 二进制位
    int binaryArray[n][8];
    // 各个圆圈的类型
    int circletype[type];
    for (int i = 0; i < type; i++)
    {
        int decimal = rand() % 256 + 1;

        // 将一个8位的十进制数字转换成二进制数，用数组存储每一位,例如，定义a[8]数组，十进制128转换为a数组{1,0,0,0,0,0,0,0}。
        decimalToBinary(decimal, binaryArray);

        // 圆圈的位置
        int x = rand() % n;
        int y = rand() % n;
        bool Xflag = false;
        bool Yflag = false;
        // 检测占用
        Xflag = X_Occupancy_detection(x, i, circleX);
        Yflag = Y_Occupancy_detection(y, i, circleY);
    Again:
        if (!(Xflag && Yflag)) // 当前位置没有被占用
        {
            circleX[i] = x;
            circleY[i] = y;
            // 限制条件,剪枝
            {
                if (y == 0) // 最左边不应该有指向左边的箭头
                {
                    binaryArray[nowcircle][5] == 0;
                    binaryArray[nowcircle][6] == 0;
                    binaryArray[nowcircle][7] == 0;
                }
                if (y == n - 1) // 最右边不应该有指向右边的箭头
                {
                    binaryArray[nowcircle][1] == 0;
                    binaryArray[nowcircle][2] == 0;
                    binaryArray[nowcircle][3] == 0;
                }
                if (x == n - 1) // 最上
                {
                    binaryArray[nowcircle][0] == 0;
                }
                if (x == 0) // 最下
                {
                    binaryArray[nowcircle][4] == 0;
                }
            }

            // 限制条件后重新转回十进制,方便存储
            circletype[i] = binaryToDecimal(binaryArray);
            // 必须存在的分支
            //表示是否对应成功（至少一次）
            bool Correct_path = false;
            for (int i = 0; i < 8; i++)
            {
                if (binaryArray[nowcircle - 1][i] == 1 && nowcircle != 0 && !Correct_path)
                {
                    // 对角线为1（必须有一个元素与其对应）
                    binaryArray[nowcircle][(i + 4) % 8] == 1;
                    //有一个对应即可
                    Correct_path = true;
                }
            }
            nowcircle++;
        }
        else // 如果是x被占用就重置x，是y被占用就重置y
        {
            while (Xflag && Yflag)
            {
                x = rand() % n;
                Xflag = X_Occupancy_detection(x, i, circleX);
            }
            while (Xflag && Yflag)
            {
                y = rand() % n;
                Yflag = Y_Occupancy_detection(y, i, circleY);
            }
            goto Again;
        }
    }
    // 输出测试
    for (int j = 0; j < type; j++)
    {
        cout << "j:" << j << endl;
        for (int i = 0; i < 8; i++)
        {
            cout << binaryArray[j][i] << " ";
        }
        cout << "\n"
             << circleX[j] << " " << circleY[j] << " ";
        cout << endl;
    }
    // 打表 初始化
    char View[3 * n][3 * n]; // 视图
    for (int i = 0; i < 3 * n; i++)
    {
        for (int j = 0; j < 3 * n; j++)
            View[i][j] = '*';
    }

    // 放置圆
    for (int i = 0; i < type; i++)
    {
        for (int j = 0; j < 8; j++)
            View[circleX[i] * n + 1][circleY[i] * n + 1] = 'A';
    }
    cout << endl;

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
    return 0;
}