#ifndef SYM_NMF_H
#define SYM_NMF_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

double **sym(double **X, int n, int d);
double **ddg(double **X, int n, int d);
double **norm(double **X, int n, int d);
double **update_H(double **H, double **W, int n, int k, double epsilon, int max_iter);
void free_mat(double **mat, int n);

#endif
