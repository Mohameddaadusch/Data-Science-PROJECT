# Data Science Project

This repository contains three separate projects created as part of the Software Project course at Tel Aviv University. Each project is located in its respective Folder:

1. [Assignment 1](assignment1): K-means Clustering
2. [Assignment 2](assignment2): K-means++ Clustering
3. [Final Project](project): Symmetric Non-negative Matrix Factorization Clustering

<br />

## Assignment 1: K-means Clustering

**Description**: This project implements the K-means clustering algorithm in Python and C.

**Files**:

- `kmeans.c`: C implementation of the K-means algorithm.
- `kmeans.py`: Python implementation of the K-means algorithm.

  <br />

## Assignment 2: K-means++ Clustering

**Description**: In this assignment, the K-means++ algorithm is used to choose initial centroids for the K-means algorithm. The task is to implement this algorithm in Python and integrate it with the K-means algorithm from Assignment 1 using a C extension.

**Files**:

- `kmeans_pp.py`: Main interface for the K-means++ algorithm.
- `kmeansmodule.c`: C extension containing the K-means implementation from Assignment 1.
- `setup.py`: Setup file for building the C extension.

  <br />

## Final Project: Symmetric Non-negative Matrix Factorization Clustering

**Description**: This project implements a clustering algorithm based on symmetric Non-negative Matrix Factorization (SymNMF). It further applies this algorithm to various datasets and compares it to K-means. The README provides details about the algorithm, code structure, and requirements.

**Files**:

- `symnmf.py`: Python interface of the SymNMF algorithm.
- `symnmf.c`: C implementation of the SymNMF algorithm.
- `symnmfmodule.c`: Python C API wrapper.
- `symnmf.h`: C header file.
- `analysis.py`: Script to compare SymNMF and K-means.
- `setup.py`: Setup file for building the C extension.
- `Makefile`: Make script for the C implementation.
- `kmeans.py`: The kmeans algorithm implementation from assignment 1.

  <br />

## Getting Started

Each subproject has its own set of instructions for building and running the code. Please refer to the respective subproject's README for detailed information.

<br />

## Contributors

- [Obaida Haj Yahya](https://github.com/ObaidaHY)
- [Mohammad Daadusch](https://github.com/Mohameddaadusch)
