# K-means++ Implementation and C Extension

This is a project that implements the K-means++ algorithm for selecting initial centroids in Python and integrates it with a K-means algorithm implemented in C. This project involves porting existing C code into a C extension using the C API and using external libraries such as Numpy and Pandas.

<br />

## Table of Contents

- [Introduction](#introduction)
- [Project Structure](#project-structure)
- [Requirements](#requirements)
- [Usage](#usage)
- [Assumptions](#assumptions)
- [File Structure](#file-structure)
- [Contributors](#contributors)

<br />

## Introduction

The project involves implementing the K-means++ algorithm for initializing centroids, which is used in conjunction with a K-means clustering algorithm. The primary goals are to port existing C code into a C extension and use external libraries like Numpy and Pandas.

<br />

## Project Structure

The project is divided into several components:

1. **kmeans_pp.py**: The main interface of the program, responsible for command-line argument handling, data processing, K-means++ implementation, interfacing with the C extension, and outputting results.

2. **kmeansmodule.c**: A C extension containing the K-means implementation from a previous assignment, with the initial centroid calculation step replaced by values passed from the K-means++ algorithm.

3. **setup.py**: The setup file used to build the C extension as a shared object (\*.so) file for importing into the Python program.

<br />

## Requirements

### Input Variables

- `K`: Number of required clusters (1 < K < N, K ∈ N)
- `iter`: Maximum number of K-means iterations (1 < iter < 1000, iter ∈ N)
- `eps`: The epsilon value for convergence
- `file_name_1`: Path to the first file containing N observations
- `file_name_2`: Path to the second file containing N observations

<br />

## Usage

1. **Building the C Extension**: Build the extension by running the following command:

```bash
python3 setup.py build_ext --inplace
```

2. **Running the K-means++ Program**: Run the Python program for K-means++ implementation and C integration:

```bash
python3 kmeans_pp.py K iter eps file_name_1 file_name_2
```

<br />

## Assumptions

This project assumes the following:

1. Command line arguments meet the specified requirements.
2. Outputs are formatted with 4 decimal places.
3. Input data files are provided and have an extra empty row.
4. Memory is properly deallocated.
5. No external includes or modules are used beyond what is mentioned in the document.

<br />

## File Structure

- `kmeans_pp.py`: Main Python program for K-means++ implementation and C integration.
- `kmeansmodule.c`: C extension for K-means clustering.
- `setup.py`: Setup file for building the C extension.
- `README.md`: This documentation.

<br />

## Contributors

- [Obaida Haj Yahya](https://github.com/ObaidaHY)
- [Mohammad Daadusch](https://github.com/Mohameddaadusch)
