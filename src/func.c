#include "func.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

// #ţ�ٲ�ֵ��
/*  ԭ��
f[x0,x1] = (fx0 - fx1) / (x0 - x1) -->һ�ײ���
f[x0,x1,x2] = (f[x0,x1] - f[x1,x2]) / (x0 - x2) -->���ײ���
...
ţ�ٲ�ֵ����ʽ��Nx = fx0 + f[x0,x1](x - x0) + f[x0,x1,x2](x - x0)(x - x1) + ... + f[x0,x1,...,x(n-1)](x - x0)(x - x1)...(x - x(n-2))
*/
void calculate_divided_difference(double x[], double fx[], double diff[][10], int n) // �������
{
    for (int i = 0; i < n; i++)
    {
        diff[i][0] = fx[i]; // �Ѻ���ֵ������һ��
    }
    /*(x,fx)
    ��i-1��        ��i��        ��i+1��
    (j-1,i-1)     (j-1,i)     (j-1,i+1)
    (j,i-1)       (j,i)       (j,i+1)
    (j+1,i-1)     (j+1,i)     (j+1,i+1)
    */
    for (int i = 1; i < n; i++) // �����i�ײ���
    {
        for (int j = 0; j < n - i; j++)
        {
            diff[j][i] = (diff[j + 1][i - 1] - diff[j][i - 1]) / (x[j + i] - x[j]);
        }
    }
}
double newton_interpolation(double x[], double fx[], double diff[][10], int n, double value) // ţ�ٲ�ֵ����ʽ
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
void Newton_Interpolation() // ţ�ٲ�ֵ�����
{
    int n;
    printf("������֪�������: ");
    scanf("%d", &n);

    double x[10], fx[10], diff[10][10];

    // �����Ա����������
    for (int i = 0; i < n; i++)
    {
        printf("�����%d������Ա���x�������f(x): ", i + 1);
        scanf("%lf %lf", &x[i], &fx[i]);
    }

    // �������
    calculate_divided_difference(x, fx, diff, n);

    // ����Ҫ��ֵ�ĵ�
    double value;
    printf("����Ҫ��ֵ�ĵ�: ");
    scanf("%lf", &value);

    // �����ֵ���
    double result = newton_interpolation(x, fx, diff, n, value);
    printf("��ֵ���: f(%.5lf) = %.5lf\n", value, result);
}

// #�������ղ�ֵ��
/*  ԭ��
�������ղ�ֵ������Ln(x) = f(x0)*L0(x) + f(x1)*L1(x) + f(x2)*L2(x) + ... + f(xn)*Ln(x)
���У�
L0(x) = 1,
L1(x) = (x-x0) / (x1-x0)
L2(x) = ((x-x0) * (x-x1)) / ((x2-x0)*(x2-x1))
L3(x) = ((x-x0) * (x-x1) * (x-x2)) / ((x3-x0) * (x3-x1) * (x3-x2))  ---> (x-x0)/(x3-x0) * (x-x1)/(x3-x1) * (x-x2)/(x3-x2) ---> (x-xj)*(xi-xj)
...
*/
double Lagrange_diff(double x[], double fx[], int n, double value) // �����������ղ�ֵ����ʽ
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
    printf("������֪�������: ");
    scanf("%d", &n);

    // ������֪����
    double x[n], fx[n];
    for (int i = 0; i < n; i++)
    {
        printf("�����%d������Ա���x�������f(x): ", i + 1);
        scanf("%lf %lf", &x[i], &fx[i]);
    }

    // ��������ĺ�����
    double value;
    printf("����Ҫ��ֵ�ĵ�: ");
    scanf("%lf", &value);

    // �����ֵ����ʽ
    double result = Lagrange_diff(x, fx, n, value);

    printf("��ֵ���: f(%.5lf) = %.5lf\n", value, result);
}

// ���ַ��������
bool Dichotomy_Find_Root(double left, double right, double value, double a, double b, double c, double d, double precision)
{
    int count = 1;
    double mid = (left + right) / 2;
    double fx = a * pow(mid, 3) + b * pow(mid, 2) + c * mid + d;
    if (fabs(fx - value) <= precision)
    {
        printf("������%d�Σ��е�midΪ%.5lf������ֵfxΪ%.5lf�����С��%.5lf���ҵ�����\n", count, mid, fx, precision);
        return true;
    }
    else if (fabs(fx - value) > precision)
    {
        if (right - left < precision)
        {
            printf("������%d�Σ��е�midΪ%.5lf������ֵfxΪ%.5lf��������%.5lf��δ�ҵ�����\n", count, mid, fx, precision);
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
void Dichotomy() // �����㷨���
{
    // �������
    double a, b, c, d, value;
    printf("���������κ������ĸ�ϵ����\n");
    scanf("%lf %lf %lf %lf", &a, &b, &c, &d);
    printf("�����뺯��ֵ��\n");
    scanf("%lf", &value);
    printf("������Ҫ��������䣺\n");
    double left, right;
    scanf("%lf %lf", &left, &right);
    double precision = 1e-6;
    printf("�����뾫��(Ĭ��Ϊ1e-6)��\n");
    scanf("%lf", &precision);
    if (precision <= 0)
    {
        printf("���ȱ������0��\n");
        precision = 1e-6;
    }

    // ���ַ����
    Dichotomy_Find_Root(left, right, value, a, b, c, d, precision);
}

// �ؾ����㷨���
void Qin9Shao_Algorithm()
{
    // �������ʽ����
    int n;
    printf("���������ʽ�Ĵ���n:\n");
    scanf("%d", &n);
    double term[n + 1];
    printf("��Ӹߴε��ʹ��������ʽ�����ϵ��:\n");
    for (int i = 0; i < n + 1; i++)
    {
        scanf("%lf", term + i);
    }
    printf("������Ҫ���ĵ�x:\n");
    double value;
    scanf("%lf", &value);

    // �ؾ����㷨
    double result = term[n]; // ��ֵΪ������
    for (int i = 0; i < n; i++)
    {
        result = result * value + term[i];
    }
    printf("f(%.5lf) = %.5lf\n", value, result);
}
