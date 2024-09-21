# K-means Clustering Implementation

This is a project for the K-means clustering algorithm implemented in both Python and C. The K-means algorithm is a popular clustering method used to group unlabeled data into distinct clusters.

<br />

## Table of Contents

- [Introduction](#introduction)
- [Requirements](#requirements)
- [Usage](#usage)
- [Assumptions](#assumptions)
- [File Structure](#file-structure)
- [Contributors](#contributors)

<br />

## Introduction

The K-means clustering algorithm is used to group a set of data points into K distinct clusters, where K is a user-defined parameter. Each cluster is represented by its centroid, which is the mean of the cluster's members.

<br />

### K-means Clustering Algorithm

1. Initialize centroids as the first K data points.
2. Assign each data point to the closest cluster centroid.
3. Update the centroids as the mean of data points in the cluster.
4. Repeat the process until convergence (when centroids don't change significantly) or reach the maximum number of iterations.

<br />

## Requirements

### Input Variables

- K: Number of clusters (1 < K < N, K ∈ N)
- iter: Maximum number of iterations (1 < iter < 1000, iter ∈ N)
- input_data.txt file

<br />

## Usage

### C Implementation

1. Compile the C program:

```bash
$ gcc -ansi -Wall -Wextra -Werror -pedantic-errors kmeans.c -o kmeans -lm
```

2. Run the program:

```bash
$ ./kmeans 3 100 < input_data.txt
```

<br />

### Python Implementation

1. Execute the Python program:

```bash
$ python3 kmeans.py 3 100 input_data.txt
```

<br />

## Assumptions

1. Validate command-line arguments as per the requirements.
2. Outputs must be formatted to 4 decimal places.
3. Handle errors and exceptions as described in the assignment document.

<br />

## File Structure

- `kmeans.c`: C implementation of the K-means algorithm.
- `kmeans.py`: Python implementation of the K-means algorithm.
- `README.md`: This documentation.

<br />

## Contributors

- [Obaida Haj Yahya](https://github.com/ObaidaHY)
- [Mohammad Daadusch](https://github.com/Mohameddaadusch)
