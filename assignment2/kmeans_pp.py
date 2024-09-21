import math
import numpy as np
import pandas as pd
import mykmeanssp as kmp
import argparse


def euclidean_distance(p, q):
    return math.sqrt(sum((px - qx) ** 2 for px, qx in zip(p, q)))


def closest_centroid(vector, curr_centroids):
    return min([euclidean_distance(vector, curr_centroids[i]) for i in range(len(curr_centroids))])


def compute_D(vectors, curr_centroids):
    P = [closest_centroid(vectors[i], curr_centroids) for i in range(len(vectors))]
    D_sum = sum(P)
    for i in range(len(vectors)):
        P[i] = P[i]/D_sum
    return P


def k_meanspp(vectors, K):
    n = len(vectors)
    np.random.seed(0)
    first_choice = np.random.choice(n)
    choosen_indices, curr_centroids = [first_choice], [vectors[first_choice]]

    while len(curr_centroids) < K:
        # step 2
        P = compute_D(vectors, curr_centroids)
        # step 3
        new_centroid_index = np.random.choice(range(n), p = P)
        choosen_indices.append(new_centroid_index)
        curr_centroids.append(vectors[new_centroid_index])
    return curr_centroids, (choosen_indices)


def k_means(vectors, K, iterations, epsilon):
    centroids, indices = k_meanspp(vectors, K)
    print(','.join([str(indices[j]) for j in range(len(indices))]))
    n, d = len(vectors), len(vectors[0])
    return Kmeans_c(vectors, centroids, iterations, K, epsilon, n, d)


def Kmeans_c(vectors, init_centroids, iterations, K, epsilon, n, d):
    try :
        centroids = kmp.fit(K, iterations, epsilon, d, vectors, init_centroids)
        for i in range(len(centroids)):
            print(','.join([format(centroids[i][j], ".4f") for j in range(len(centroids[i]))]))
        print('')
        return 0
    except:
        print("An Error Has Occurred")
        return 1


def merge_files(input_file1, input_file2):
    input1 = pd.read_csv(input_file1, header=None)
    input2 = pd.read_csv(input_file2, header=None)
    vectors = pd.merge(input1, input2, on=0)
    vectors.sort_values(by=[0], inplace=True, ascending=True)
    vectors = vectors.drop(columns=0)
    return vectors

def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("k", type=int)
    parser.add_argument("iterations", type=int, nargs='?', default=300, const=0)
    parser.add_argument("epsilon", type=float)
    parser.add_argument("file_1", type=str)
    parser.add_argument("file_2", type=str)
    args = parser.parse_args()


    input_args = [args.k, args.iterations, args.epsilon, args.file_1, args.file_2]
    file1 = merge_files(args.file_1, args.file_2)
    vectors = file1.values.tolist()
    if not (1 < args.k < len(vectors)):
        print("Invalid number of clusters!")
    if not (1 < args.iterations < 1000):
        print("Invalid maximum iteration!")
    if ((1 < args.k < len(vectors)) and (1 < args.iterations < 1000)):
        return k_means(vectors, input_args[0], input_args[1], input_args[2])

if __name__ == "__main__":
    main()