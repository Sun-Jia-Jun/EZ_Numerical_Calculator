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
        printf("��ӭʹ�ü򵥵���ֵ������ by sjj\n");
        printf("------------------------------------------------------------------------------------------------\n");
        printf("��ѡ���ܣ�\n");
        printf("------------------------------------------------------------------------------------------------\n");
        printf("0. �˳�����\n");
        printf("1. ţ�ٲ�ֵ��\n");
        printf("2. �������ղ�ֵ��\n");
        printf("3. ���ַ�\n");
        printf("4. �ؾ����㷨\n");
        printf("------------------------------------------------------------------------------------------------\n");
        printf("------------------------------------------------------------------------------------------------\n");
        printf("������ѡ��: ");
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
            printf("�������sjj���ÿ����¹����ˣ�������ѡ��\n");
            break;
        }
        // ˢ��
        system("pause");
        system("cls");
    }
}