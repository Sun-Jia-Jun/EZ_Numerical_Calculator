#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#ifndef FUNC_H
#define FUNC_H

void calculate_divided_difference(double x[], double fx[], double diff[][10], int n);
double newton_interpolation(double x[], double fx[], double diff[][10], int n, double value);
void Newton_Interpolation();

double Lagrange_diff(double x[], double fx[], int n, double value);
void Lagrange_Interpolation();

bool Dichotomy_Find_Root(double left, double right, double value, double a, double b, double c, double d, double precision);
void Dichotomy();

void Qin9Shao_Algorithm();

void Menu();

#endif