#include "func.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

// #牛顿插值法
/*  原理：
f[x0,x1] = (fx0 - fx1) / (x0 - x1) -->一阶差商
f[x0,x1,x2] = (f[x0,x1] - f[x1,x2]) / (x0 - x2) -->二阶差商
...
牛顿插值多项式：Nx = fx0 + f[x0,x1](x - x0) + f[x0,x1,x2](x - x0)(x - x1) + ... + f[x0,x1,...,x(n-1)](x - x0)(x - x1)...(x - x(n-2))
*/
void calculate_divided_difference(double x[], double fx[], double diff[][10], int n) // 计算差商
{
    for (int i = 0; i < n; i++)
    {
        diff[i][0] = fx[i]; // 把函数值赋给第一列
    }
    /*(x,fx)
    第i-1阶        第i阶        第i+1阶
    (j-1,i-1)     (j-1,i)     (j-1,i+1)
    (j,i-1)       (j,i)       (j,i+1)
    (j+1,i-1)     (j+1,i)     (j+1,i+1)
    */
    for (int i = 1; i < n; i++) // 计算第i阶差商
    {
        for (int j = 0; j < n - i; j++)
        {
            diff[j][i] = (diff[j + 1][i - 1] - diff[j][i - 1]) / (x[j + i] - x[j]);
        }
    }
}
double newton_interpolation(double x[], double fx[], double diff[][10], int n, double value) // 牛顿插值多项式
{
    double result = fx[0];
    double term = 1.0;

    for (int i = 1; i < n; i++)
    {
        term *= (value - x[i - 1]); // (x - x0)(x - x1)...(x - xi-1)
        result += diff[0][i] * term;
    }

    return result;
}
void Newton_Interpolation() // 牛顿插值法入口
{
    int n;
    printf("输入已知点的数量: ");
    scanf("%d", &n);

    double x[10], fx[10], diff[10][10];

    // 输入自变量和因变量
    for (int i = 0; i < n; i++)
    {
        printf("输入第%d个点的自变量x和因变量f(x): ", i + 1);
        scanf("%lf %lf", &x[i], &fx[i]);
    }

    // 计算差商
    calculate_divided_difference(x, fx, diff, n);

    // 输入要插值的点
    double value;
    printf("输入要插值的点: ");
    scanf("%lf", &value);

    // 计算插值结果
    double result = newton_interpolation(x, fx, diff, n, value);
    printf("插值结果: f(%.5lf) = %.5lf\n", value, result);
}

// #拉格朗日插值法
/*  原理：
拉格朗日插值函数：Ln(x) = f(x0)*L0(x) + f(x1)*L1(x) + f(x2)*L2(x) + ... + f(xn)*Ln(x)
其中：
L0(x) = 1,
L1(x) = (x-x0) / (x1-x0)
L2(x) = ((x-x0) * (x-x1)) / ((x2-x0)*(x2-x1))
L3(x) = ((x-x0) * (x-x1) * (x-x2)) / ((x3-x0) * (x3-x1) * (x3-x2))  ---> (x-x0)/(x3-x0) * (x-x1)/(x3-x1) * (x-x2)/(x3-x2) ---> (x-xj)*(xi-xj)
...
*/
double Lagrange_diff(double x[], double fx[], int n, double value) // 计算拉格朗日插值多项式
{
    double result = 0.0;
    for (int i = 0; i < n; i++)
    {
        double term = 1.0;
        for (int j = 0; j < n; j++)
        {
            if (i != j)
            {
                term *= (value - x[j]) / (x[i] - x[j]);
            }
        }
        result += fx[i] * term;
    }
    return result;
}

void Lagrange_Interpolation()
{
    int n;
    printf("输入已知点的数量: ");
    scanf("%d", &n);

    // 输入已知点列
    double x[n], fx[n];
    for (int i = 0; i < n; i++)
    {
        printf("输入第%d个点的自变量x和因变量f(x): ", i + 1);
        scanf("%lf %lf", &x[i], &fx[i]);
    }

    // 输入插入点的横坐标
    double value;
    printf("输入要插值的点: ");
    scanf("%lf", &value);

    // 计算插值多项式
    double result = Lagrange_diff(x, fx, n, value);

    printf("插值结果: f(%.5lf) = %.5lf\n", value, result);
}

// 二分法求根函数
bool Dichotomy_Find_Root(double left, double right, double value, double a, double b, double c, double d, double precision)
{
    int count = 1;
    double mid = (left + right) / 2;
    double fx = a * pow(mid, 3) + b * pow(mid, 2) + c * mid + d;
    if (fabs(fx - value) <= precision)
    {
        printf("共迭代%d次！中点mid为%.5lf，函数值fx为%.5lf，误差小于%.5lf，找到根！\n", count, mid, fx, precision);
        return true;
    }
    else if (fabs(fx - value) > precision)
    {
        if (right - left < precision)
        {
            printf("共迭代%d次！中点mid为%.5lf，函数值fx为%.5lf，误差大于%.5lf，未找到根！\n", count, mid, fx, precision);
            return false;
        }
        else
        {
            count++;
            if (fx > value)
            {
                right = mid;
            }
            if (fx < value)
            {
                left = mid;
            }
            Dichotomy_Find_Root(left, right, value, a, b, c, d, precision);
        }
    }
}
void Dichotomy() // 二分算法入口
{
    // 输入参数
    double a, b, c, d, value;
    printf("请输入三次函数的四个系数：\n");
    scanf("%lf %lf %lf %lf", &a, &b, &c, &d);
    printf("请输入函数值：\n");
    scanf("%lf", &value);
    printf("请输入要求根的区间：\n");
    double left, right;
    scanf("%lf %lf", &left, &right);
    double precision = 1e-6;
    printf("请输入精度(默认为1e-6)：\n");
    scanf("%lf", &precision);
    if (precision <= 0)
    {
        printf("精度必须大于0！\n");
        precision = 1e-6;
    }

    // 二分法求根
    Dichotomy_Find_Root(left, right, value, a, b, c, d, precision);
}

// 秦九韶算法入口
void Qin9Shao_Algorithm()
{
    // 输入多项式参数
    int n;
    printf("请输入多项式的次数n:\n");
    scanf("%d", &n);
    double term[n + 1];
    printf("请从高次到低次输入多项式各项的系数:\n");
    for (int i = 0; i < n + 1; i++)
    {
        scanf("%lf", term + i);
    }
    printf("请输入要求解的点x:\n");
    double value;
    scanf("%lf", &value);

    // 秦九韶算法
    double result = term[n]; // 初值为常数项
    for (int i = 0; i < n; i++)
    {
        result = result * value + term[i];
    }
    printf("f(%.5lf) = %.5lf\n", value, result);
}
