#define PY_SSIZE_T_CLEAN
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Python.h>
#include "symnmf.h"

PyObject *build_output(double **mat, int n, int d)
{ /* function to build the PyObject output */
    PyObject *py_result, *tmp;
    Py_ssize_t i, j;

    py_result = PyList_New(n);
    for (i = 0; i < n; i++)
    {
        tmp = PyList_New(d);
        for (j = 0; j < d; j++)
        {
            PyList_SetItem(tmp, j, PyFloat_FromDouble(mat[i][j]));
        }
        PyList_SetItem(py_result, i, tmp);
    }
    free_mat(mat, n);
    return py_result;
}

double **build_input(PyObject *mat, int N, int d)
{ /* function to build the appropriate C representation of the input */
    PyObject *py_vector;
    double **matrix;
    Py_ssize_t i, j;
    matrix = (double **)malloc(N * sizeof(double *));

    if (matrix == NULL)
    {
        return NULL;
    }
    for (i = 0; i < N; i++)
    {
        matrix[i] = (double *)malloc(d * sizeof(double));
        if (matrix[i] == NULL)
        {
            return NULL;
        }
    }

    for (i = 0; i < N; i++)
    {
        py_vector = PyList_GetItem(mat, i);
        for (j = 0; j < d; j++)
        {
            matrix[i][j] = PyFloat_AsDouble(PyList_GetItem(py_vector, j));
        }
    }

    return matrix;
}

static PyObject *sym_run(PyObject *X, int n, int d)
{ /* calculating similarity matrix using C code */
    double **A;
    PyObject *output;
    double **input = build_input(X, n, d);
    if (input == NULL)
    {
        PyErr_SetString(PyExc_MemoryError, "An Error Has Occurred");
        return PyList_New(0);
    }
    A = sym(input, n, d);
    if (A == NULL)
    {
        PyErr_SetString(PyExc_MemoryError, "An Error Has Occurred");
        return PyList_New(0);
    }

    output = build_output(A, n, n);
    free_mat(input, n);
    return output;
}

static PyObject *ddg_run(PyObject *X, int n, int d)
{ /* calculating Diagonal Degree matrix using C code */
    double **D;
    PyObject *output;
    double **input = build_input(X, n, d);
    if (input == NULL)
    {
        PyErr_SetString(PyExc_MemoryError, "An Error Has Occurred");
        return PyList_New(0);
    }
    D = ddg(input, n, d);
    if (D == NULL)
    {
        PyErr_SetString(PyExc_MemoryError, "An Error Has Occurred");
        return PyList_New(0);
    }

    output = build_output(D, n, n);
    free_mat(input, n);
    return output;
}

static PyObject *norm_run(PyObject *X, int n, int d)
{ /* calculating normalized similarity matrix using C code */
    double **W;
    PyObject *output;
    double **input = build_input(X, n, d);
    if (input == NULL)
    {
        PyErr_SetString(PyExc_MemoryError, "An Error Has Occurred");
        return PyList_New(0);
    }
    W = norm(input, n, d);
    if (W == NULL)
    {
        PyErr_SetString(PyExc_MemoryError, "An Error Has Occurred");
        return PyList_New(0);
    }

    output = build_output(W, n, n);
    free_mat(input, n);
    return output;
}

static PyObject *symnmf_run(PyObject *H, PyObject *W, int n, int k)
{ /* calculating the final solution amtrix (H) using C code */

    double **H_p, **W_p, **result;
    PyObject *output;

    H_p = build_input(H, n, k);
    W_p = build_input(W, n, n);
    if (H_p == NULL)
    {
        PyErr_SetString(PyExc_MemoryError, "An Error Has Occurred");
        return PyList_New(0);
    }
    if (W_p == NULL)
    {
        PyErr_SetString(PyExc_MemoryError, "An Error Has Occurred");
        return PyList_New(0);
    }
    result = update_H(H_p, W_p, n, k, 0, 0);
    if (result == NULL)
    {
        PyErr_SetString(PyExc_MemoryError, "An Error Has Occurred");
        return PyList_New(0);
    }

    output = build_output(result, n, k);
    free_mat(W_p, n);
    return output;
}

static PyObject *symmod(PyObject *self, PyObject *args)
{ /* interfacing with python to compute A */
    int n, d;
    PyObject *X;
    if (!PyArg_ParseTuple(args, "Oii", &X, &n, &d))
    {
        return NULL;
    }
    return Py_BuildValue("O", sym_run(X, n, d));
}

static PyObject *ddgmod(PyObject *self, PyObject *args)
{ /* interfacing with python to compute D */
    int n, d;
    PyObject *X;
    if (!PyArg_ParseTuple(args, "Oii", &X, &n, &d))
    {
        return NULL;
    }
    return Py_BuildValue("O", ddg_run(X, n, d));
}

static PyObject *normmod(PyObject *self, PyObject *args)
{ /* interfacing with python to compute W */
    int n, d;
    PyObject *X;
    if (!PyArg_ParseTuple(args, "Oii", &X, &n, &d))
    {
        return NULL;
    }
    return Py_BuildValue("O", norm_run(X, n, d));
}

static PyObject *symnmfmod(PyObject *self, PyObject *args)
{ /* interfacing with python to compute H */
    int n, k;
    PyObject *W, *H;
    if (!PyArg_ParseTuple(args, "OOii", &H, &W, &n, &k))
    {
        return NULL;
    }
    return Py_BuildValue("O", symnmf_run(H, W, n, k));
}

static PyMethodDef symnmfModMethods[] = {
    {"sym", (PyCFunction)symmod, METH_VARARGS,
     PyDoc_STR("symnmf project sym")},
    {"ddg", (PyCFunction)ddgmod, METH_VARARGS,
     PyDoc_STR("symnmf project ddg")},
    {"norm", (PyCFunction)normmod, METH_VARARGS,
     PyDoc_STR("symnmf project norm")},
    {"symnmf", (PyCFunction)symnmfmod, METH_VARARGS,
     PyDoc_STR("symnmf project symnmf")},
    {NULL, NULL, 0, NULL}};

static struct PyModuleDef moduledef = {
    PyModuleDef_HEAD_INIT,
    "symnmfmodule",
    NULL,
    -1,
    symnmfModMethods};

PyMODINIT_FUNC
PyInit_symnmfmodule(void)
{
    PyObject *m;
    m = PyModule_Create(&moduledef);
    if (!m)
    {
        return NULL;
    }
    return m;
}