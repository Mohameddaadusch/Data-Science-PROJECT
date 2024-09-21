#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "symnmf.h"

double **init_matrix(double **D, int n, int d)
{ /* initializing n*d matrix */
    int i;
    D = malloc(n * sizeof(double *));
    if (D == NULL)
    {
        printf("An Error Has Occurred");
        printf("\n");
        return NULL;
    }

    for (i = 0; i < n; i++)
    {
        D[i] = (double *)calloc(d, sizeof(double));
        if (D[i] == NULL)
        {
            printf("An Error Has Occurred");
            printf("\n");
            return NULL;
        }
    }
    return D;
}

double distance(double *vec1, double *vec2, int d)
{ /* calculating the euclidean distance */
    double dist = 0;
    int i = 0;

    for (i = 0; i < d; i++)
    {
        dist += (vec1[i] - vec2[i]) * (vec1[i] - vec2[i]);
    }
    return dist;
}

double **form_A(double **X, int n, int d)
{ /* forming similarity matrix as in 1.1 */
    double **A = NULL;
    int i, j;
    double res, dist;
    A = init_matrix(A, n, n);
    if (A == NULL)
    {
        return NULL;
    }

    for (i = 0; i < n; i++)
    {
        res = 0;
        for (j = i; j < n; j++)
        {
            if (i == j)
            {
                res = 0;
            }
            else
            {
                dist = ((-1) * (distance(X[i], X[j], d)) / 2);
                res = exp(dist);
            }
            A[i][j] = res;
            A[j][i] = res;
        }
    }
    return A;
}

double **diagonal_matrix(double **A, int n)
{ /* calculating the diagonal degree matrix as in 1.2 */
    double **D = NULL;
    int i, j;
    double res;
    D = init_matrix(D, n, n);
    if (D == NULL)
    {
        return NULL;
    }

    for (i = 0; i < n; i++)
    {
        res = 0;
        for (j = 0; j < n; j++)
        {
            res += A[i][j];
        }
        D[i][i] = res;
    }

    return D;
}

double **mat_mult(double **first, double **second, int a, int b, int c)
{ /* simple function for calculating the result of multiplying matrices*/
    double **C = NULL;
    int i, j, k;
    C = init_matrix(C, a, c);
    if (C == NULL)
    {
        return NULL;
    }
    for (i = 0; i < a; i++)
    {
        for (j = 0; j < c; j++)
        {
            C[i][j] = 0;
            for (k = 0; k < b; k++)
            {
                C[i][j] += first[i][k] * second[k][j];
            }
        }
    }
    return C;
}

void free_mat(double **mat, int n)
{ /*freeing dynamically allocated space*/
    int i = 0;
    for (i = 0; i < n; i++)
    {
        free(mat[i]);
    }
    free(mat);
}

double **normalized_matrix(double **D, double **A, int n)
{ /* computing the normalized similarity martix W */
    int i;
    double **W;
    double **tmp;
    for (i = 0; i < n; i++)
    {
        D[i][i] = pow(D[i][i], -0.5);
    }

    W = mat_mult(D, A, n, n, n);
    if (W == NULL)
    {
        return NULL;
    }
    tmp = W;
    W = mat_mult(W, D, n, n, n);
    free_mat(tmp, n);
    return W;
}

void subtract(double **mat1, double **mat2, int n, int k)
{ /*subtracting two matrices in place (saving the result in the second matrix) - only used in update_H function*/
    int i, j;
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < k; j++)
        {
            mat2[i][j] = mat1[i][j] - mat2[i][j];
        }
    }
}

double frobenius_norm(double **mat, int n, int k)
{ /* calculating frobenius norm and returning the result */
    double res = 0;
    int i, j;
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < k; j++)
        {
            res += (mat[i][j]) * (mat[i][j]);
        }
    }
    return (res);
}

double **transpose(double **mat, int n, int d)
{ /* returning the transpose of a matrix */
    int i, j;
    double **new = NULL;
    new = init_matrix(new, d, n);
    if (new == NULL)
    {
        return NULL;
    }

    for (i = 0; i < d; i++)
    {
        for (j = 0; j < n; j++)
        {
            new[i][j] = mat[j][i];
        }
    }
    return new;
}

double **update_H(double **H, double **W, int n, int k, double epsilon, int max_iter)
{ /* computing the solution after receiving the initial H as explained in 1.4 */
    double **old_H, **new_H = NULL, **W_mult_H, **H_mult_Ht, **trans, **Ht_mult_H, res;
    int m = 0, i = 0, j = 0;
    epsilon = 1e-4;
    max_iter = 300;
    old_H = H;

    while (m < max_iter)
    {
        m += 1;
        new_H = init_matrix(new_H, n, k);
        if (new_H == NULL)
        {
            return NULL;
        }
        trans = transpose(old_H, n, k);
        if (trans == NULL)
        {
            return NULL;
        }
        W_mult_H = mat_mult(W, old_H, n, n, k);
        if (W_mult_H == NULL)
        {
            return NULL;
        }
        H_mult_Ht = mat_mult(old_H, trans, n, k, n);
        if (H_mult_Ht == NULL)
        {
            return NULL;
        }
        Ht_mult_H = mat_mult(H_mult_Ht, old_H, n, n, k);
        if (Ht_mult_H == NULL)
        {
            return NULL;
        }
        for (i = 0; i < n; i++)
        {
            for (j = 0; j < k; j++)
            {
                new_H[i][j] = old_H[i][j] * (0.5 + (0.5 * ((W_mult_H[i][j]) / (Ht_mult_H[i][j]))));
            }
        }

        subtract(new_H, old_H, n, k);
        res = frobenius_norm(old_H, n, k);
        free_mat(trans, k);
        free_mat(H_mult_Ht, n);
        free_mat(old_H, n);
        free_mat(W_mult_H, n);
        free_mat(Ht_mult_H, n);

        if (res < epsilon)
        {
            return new_H;
        }
        old_H = new_H;
    }

    return new_H;
}

double **read_file(char *input_file, int *n, int *vDim)
{ /* reading from input file to build the matrix */
    FILE *in = NULL;
    int i;
    int j;
    char c;
    int dim = 0;
    double **vectors = NULL;
    double tmp;
    double b = 0;

    in = fopen(input_file, "r");
    if (in == NULL)
    {
        printf("An Error Has Occurred");
        printf("\n");
        return NULL;
    }

    while ((c = fgetc(in)) != EOF)
    {
        if (c == '\n')
        {
            n[0]++;
            dim++;
        }
        if (c == ',')
        {
            dim++;
        }
    }

    rewind(in);
    vDim[0] = dim / *n;
    vectors = init_matrix(vectors, n[0], vDim[0]);

    for (i = 0; i < n[0]; i++)
    {
        for (j = 0; j < vDim[0]; j++)
        {
            b = fscanf(in, "%lf", &tmp);
            b = 0;
            vectors[i][j] = (double)tmp;
            fgetc(in);
        }
    }
    b = b / 2;
    fclose(in);

    return vectors;
}

double **sym(double **X, int n, int d)
{
    return form_A(X, n, d);
}

double **ddg(double **X, int n, int d)
{
    double **D;
    double **A = form_A(X, n, d);
    if (A == NULL)
    {
        return NULL;
    }
    D = diagonal_matrix(A, n);
    free_mat(A, n);
    return D;
}

double **norm(double **X, int n, int d)
{
    double **D, **W;
    double **A = form_A(X, n, d);
    if (A == NULL)
    {
        return NULL;
    }
    D = diagonal_matrix(A, n);
    if (D == NULL)
    {
        free_mat(A, n);
        return NULL;
    }
    W = normalized_matrix(D, A, n);
    free_mat(A, n);
    free_mat(D, n);
    return W;
}

void print_mat(double **mat, int n, int d)
{ /* function to print the matrix */
    int i, j;
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < d; j++)
        {
            printf("%.4f", mat[i][j]);
            if (j < d - 1)
            {
                printf(",");
            }
        }
        printf("\n");
    }
}

int main(int argc, char *argv[])
{

    double **result = NULL, **X;
    int n = 0, d = 0;

    char *file_path = argv[2];
    char *function_name = argv[1];

    if (argc != 3)
    {
        return 1;
    }

    X = read_file(file_path, &n, &d);
    if (X == NULL)
    {
        return 1;
    }
    if (strcmp(function_name, "sym") == 0)
    {

        result = sym(X, n, d);
    }

    if (strcmp(function_name, "ddg") == 0)
    {
        result = ddg(X, n, d);
    }
    if (strcmp(function_name, "norm") == 0)
    {
        result = norm(X, n, d);
    }
    if (result == NULL)
    {
        free_mat(X, n);
        return 1;
    }
    print_mat(result, n, n);
    free_mat(result, n);
    free_mat(X, n);
    return 0;
}
