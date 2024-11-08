#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include "menu.h"
#include "func.h"

void Menu()
{
    while (1)
    {
        int choice;
        printf("------------------------------------------------------------------------------------------------\n");
        printf("欢迎使用简单的数值计算器 by sjj\n");
        printf("------------------------------------------------------------------------------------------------\n");
        printf("请选择功能：\n");
        printf("------------------------------------------------------------------------------------------------\n");
        printf("0. 退出程序\n");
        printf("1. 牛顿插值法\n");
        printf("2. 拉格朗日插值法\n");
        printf("3. 二分法\n");
        printf("4. 秦九韶算法\n");
        printf("------------------------------------------------------------------------------------------------\n");
        printf("------------------------------------------------------------------------------------------------\n");
        printf("请输入选择: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 0:
            exit(0);
            break;
        case 1:
            Newton_Interpolation();
            break;
        case 2:
            Lagrange_Interpolation();
            break;
        case 3:
            Dichotomy();
            break;
        case 4:
            Qin9Shao_Algorithm();
            break;
        default:
            printf("输入错误！sjj懒得开发新功能了，请重新选择！\n");
            break;
        }
        // 刷新
        system("pause");
        system("cls");
    }
}