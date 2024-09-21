# importing symnmf, kmeans (from HW1), and necessary functions
from symnmf import symnmf
from kmeans import k_means, read_data_from_file, euclidean_distance
from sklearn.metrics import silhouette_score
import sys

if __name__ == "__main__":

    k, file_name, epsilon, max_iter = 0, None, 0.0001, 300
    k, file_name = int(sys.argv[1]), sys.argv[2]

    X = read_data_from_file(file_name)

    try:
        H = symnmf('symnmf', k, X)
    except:
        print("An Error Has Occurred")
    centroids = k_means(X, k, max_iter, epsilon)

    # assign clusters for symnmf as explained in 1.5 (to which cluster each vector belong)
    assign_sym = [(max([(cl) for cl in range(len(H[0]))], key=lambda x: H[i][x]))
                  for i in range(len(H))]

    # assign cluster for each vector (to which cluster each vector belong)
    assign_kmeans = [(min([k for k in range(len(centroids))], key=lambda k: euclidean_distance(
        X[i], centroids[k]))) for i in range(len(X))]

    print("nmf:", '%.4f' % silhouette_score(X, assign_sym))
    print("kmeans:", '%.4f' % silhouette_score(X, assign_kmeans))
