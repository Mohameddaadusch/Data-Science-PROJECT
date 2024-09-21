# SymNMF Clustering Algorithm

This project implements a clustering algorithm based on symmetric Non-negative Matrix Factorization (SymNMF). It further applies this algorithm to various datasets and compares it to K-means clustering. This document provides an introduction to the mathematical foundation, algorithms, and code implementation requirements.
<br />

## Table of Contents

- [Introduction](#introduction)
- [SymNMF Algorithm](#symnmf-algorithm)
- [Code and File Structure](#code-and-file-structure)
- [Requirements](#requirements)
- [Usage](#usage)
- [Analysis](#analysis)
- [Assumptions](#assumptions)
- [Contributors](#contributors)
- [References](#references)
  <br />

## Introduction

This project introduces a clustering algorithm based on Symmetric Non-negative Matrix Factorization (SymNMF). SymNMF is applied to datasets for clustering and compared to the traditional K-means algorithm. The goal is to provide insights into the algorithm's performance in various scenarios.
<br />

## SymNMF Algorithm

SymNMF is a clustering algorithm based on the following steps:

1. Form a similarity matrix A from the data points.
2. Compute the Diagonal Degree Matrix (D).
3. Compute the normalized similarity matrix (W).
4. Find a non-negative matrix H that minimizes the Frobenius norm of kW - HHTk2.
   <br />

## Code and File Structure

The project consists of several components:

1. **symnmf.py**: The Python interface for the algorithm, allowing users to interact with SymNMF. It can perform full SymNMF, calculate the similarity matrix, the Diagonal Degree Matrix, or the normalized similarity matrix.

2. **symnmf.c**: The C implementation of SymNMF. This program handles SymNMF calculations, including constructing the similarity matrix and matrix factorization.

3. **symnmfmodule.c**: The Python C API wrapper that enables Python to call functions from the C implementation.

4. **symnmf.h**: The C header file, which defines function prototypes and constants used in the C implementation.

5. **analysis.py**: A script to compare SymNMF with K-means on given datasets and report silhouette scores for clustering quality assessment.

6. **setup.py**: The setup script for building the C extension as a shared object (\*.so) file for Python integration.

7. **Makefile**: The make script for building the C implementation.

8. **kmeans.py**: The kmeans algorithm implementation from assignment 1.
   <br />

## Requirements

### Command Line Arguments

1. **Python Program (symnmf.py)**:

   - `k` (int, < N): Number of required clusters.
   - `goal` (string):
     - `symnmf`: Perform SymNMF and output matrix H.
     - `sym`: Calculate and output the similarity matrix.
     - `ddg`: Calculate and output the Diagonal Degree Matrix.
     - `norm`: Calculate and output the normalized similarity matrix.
   - `file_name` (.txt): Path to the input file containing data points.

2. **C Program (symnmf.c)**:
   - `goal` (string):
     - `sym`: Calculate and output the similarity matrix.
     - `ddg`: Calculate and output the Diagonal Degree Matrix.
     - `norm`: Calculate and output the normalized similarity matrix.
   - `file_name` (.txt): Path to the input file containing data points.
     <br />

### Output Format

- The output matrices should be formatted with 4 decimal places (`'%.4f'`).
  <br />

## Usage

1. **Building the C Extension**: Build the extension by running the following command:

```bash
python3 setup.py build_ext --inplace
```

2. **Running the Python Program** (SymNMF):

```bash
python3 symnmf.py k goal file_name.txt
```

3. **Running the C Program** (SymNMF):

- First, compile the C program using the Makefile:
  ```
  $ make
  ```
- Then, run the program:
  ```
  $ ./symnmf goal file_name.txt
  ```

4. **Running the Analysis Script**:

```bash
python3 analysis.py k file_name.txt
```

<br />

## Analysis

The `analysis.py` script compares SymNMF to K-means on the given dataset and reports the silhouette scores for both methods. Silhouette scores measure clustering quality by comparing between-cluster distances to within-cluster distances. A higher silhouette score indicates better-defined clusters.
<br />

## Assumptions

This project makes the following assumptions:

1. Outputs are formatted with 4 decimal places.
2. There are no test files provided for this project. some created by students can be found [here](https://docs.google.com/spreadsheets/d/1-6MauHUQOco9jXE3B6dBwO4hImGQSyMZbodNBbdyvIw/edit#gid=0), [or here](https://github.com/tomeroron/comp).
3. In case of an error, "An Error Has Occurred" is printed.
4. All given data points are different.
5. Double is used in the C implementation, and float is used in the Python implementation for vector elements.
6. For K-means and NMF convergence, ε (epsilon) is set to 1e-4, and the maximum iteration is set to 300.
   <br />

## Contributors

- [Obaida Haj Yahya](https://github.com/ObaidaHY)
- [Mohammad Daadusch](https://github.com/Mohameddaadusch)
  <br />

## References

[1] Da Kuang, Chris Ding, and Haesun Park. Symmetric nonnegative matrix factorization for graph clustering. In Proceedings of the 2012 SIAM International Conference on Data Mining (SDM), Proceedings, pages 106–117. Society for Industrial and Applied Mathematics, April 2012.
