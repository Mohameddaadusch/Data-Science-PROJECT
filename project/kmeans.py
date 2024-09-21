import math
import sys


def euclidean_distance(p, q):
    return math.sqrt(sum((px - qx) ** 2 for px, qx in zip(p, q)))


def create_clusters(vectors, centroids):
    clusters = [[] for k in range(len(centroids))]
    for x_i in vectors:
        j = min([k for k in range(len(centroids))],
                key=lambda k: euclidean_distance(x_i, centroids[k]))
        clusters[j].append(x_i)
    return clusters


def update_centroids(clusters):
    updated_centroids = []
    for cluster in clusters:
        centroid = [sum(dim) / len(cluster) for dim in zip(*cluster)]
        updated_centroids.append(centroid)
    return updated_centroids


def k_means(vectors, K, iterations, epsilon):
    centroids = vectors[:K]
    for i in range(iterations):
        prev_centroids = centroids[:]
        clusters = create_clusters(vectors, centroids)
        centroids = update_centroids(clusters)
        if max([euclidean_distance(prev_centroids[j], centroids[j]) for j in range(K)]) < epsilon:
            break
    return centroids


def print_centroids(centroids):
    for centroid in centroids:
        print(','.join(['%.4f' % x for x in centroid]))
    print()


def read_data_from_file(file_path):
    data = []
    with open(file_path, 'r') as file:
        for line in file:
            data.append([float(x) for x in line.strip().split(',')])
    return data


if __name__ == "__main__":
    inputs = sys.argv
    K = int(inputs[1])
    file_path = inputs[-1]
    iterations = 200 if len(inputs) == 3 else int(inputs[2])
    epsilon = 0.001
    vectors = read_data_from_file(file_path)

    if not (1 < K < len(vectors)):
        print("Invalid number of clusters!")
    if not (1 < iterations < 1000):
        print("Invalid maximum iteration!")

    if 1 < K < len(vectors) and 1 < iterations < 1000:
        print_centroids(k_means(vectors, K, iterations, epsilon))
