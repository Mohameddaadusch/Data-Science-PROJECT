import symnmfmodule as symnmfmod
import numpy as np
import pandas as pd
import sys
np.random.seed(0)


def symnmf(goal, k, X):
    n, d = len(X), len(X[0])
    result = None
    try:
        # Parse the goal and perform the appropriate action
        if goal == 'symnmf':
            W = calculate_normalized_similarity_matrix(X, n, d)
            H = initialize_H(W, n, k)
            result = calculate_H(H, W, n, k)

        elif goal == 'sym':
            result = calculate_similarity_matrix(X, n, d)

        elif goal == 'ddg':
            result = calculate_diagonal_degree_matrix(X, n, d)

        elif goal == 'norm':
            result = calculate_normalized_similarity_matrix(X, n, d)

        else:
            print("An Error Has Occurred")
            return 0
        return (result)

    except:
        raise Exception("")


def initialize_H(W, n, k):
    # Initializing H using random values (as described in 1.4.1)
    try:
        m = (np.sum(np.array(W))) / (pow(n, 2))  # Calculate m from your data
        H = np.random.uniform(0, 2 * np.sqrt(m / k), size=(n, k))
        return H.tolist()
    except:
        raise Exception("")


def calculate_similarity_matrix(X, n, d):
    # Implementing the code to calculate the similarity matrix (goal 'sym') (using C)
    try:
        return symnmfmod.sym(X, n, d)
    except:
        raise Exception("")


def calculate_diagonal_degree_matrix(X, n, d):
    # Implementing the code to calculate the diagonal degree matrix (goal 'ddg') (using C)
    try:
        return symnmfmod.ddg(X, n, d)
    except:
        raise Exception("")


def calculate_normalized_similarity_matrix(X, n, d):
    # Implementing the code to calculate the normalized similarity matrix (goal 'norm') (using C)
    try:
        return symnmfmod.norm(X, n, d)
    except:
        raise Exception("")


def calculate_H(H, W, n, k):
    # Implementing the code to calculate the normalized similarity matrix (goal 'symnmf') (using C)
    try:
        return symnmfmod.symnmf(H, W, n, k)
    except:
        raise Exception("")


def read_file(input_file):
    # building X using pandas
    X = pd.read_csv(input_file, header=None)
    return X.values.tolist()


def print_mat(mat):
    # printing the matrix
    for i in range(len(mat)):
        print(','.join([format(mat[i][j], ".4f")
                        for j in range(len(mat[i]))]))


if __name__ == "__main__":
    if len(sys.argv) != 4:
        print("An Error Has Occurred")
        sys.exit(1)

    k = int(sys.argv[1])
    goal = sys.argv[2]
    file_name = sys.argv[3]

    X = read_file(file_name)
    try:
        print_mat(symnmf(goal, k, X))
    except:
        print("An Error Has Occurred")
