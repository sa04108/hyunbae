import sys
import numpy as np
import matplotlib.pyplot as plt
import pandas as pd

from sklearn.cluster import KMeans
from sklearn import datasets
from scipy.cluster.hierarchy import linkage, dendrogram

np.random.seed(0)

# 데이터 불러오기

# 무작위 데이터 생성
"""
x, y = datasets.make_blobs(n_samples=1000, centers=4, cluster_std=1.5)
plt.scatter(x[:, 0], x[:, 1], marker='.')
"""

wine = datasets.load_wine()
x = wine.data
y = wine.target

#sys.exit()

# KMeans의 인자
# n_clusters 는 클러스터(군집) 개수이자 초기 중심점 개수가 된다.
# n_init 은 중심점 선정을 위한 시도의 횟수이다.
# init의 경우 중심점 선택 방식이며 k-means++와 random의 두가지 선택지가 있다. k-means++는 똑똑한 방식으로 중심점을 찾아가며 random의 경우 완전히 무작위의 중심점을 찾는다.

kmeans = KMeans(n_clusters=3)
kmeans.fit(x)

linkage_methods = ['single', 'average', 'complete']

#dendrogram
plt.figure(figsize=(8, 8))
plt.title('KMeans Clustering')

for method in linkage_methods:
    plt.subplot(3, 1, linkage_methods.index(method) + 1)
    plt.gca().set_title(method)
    dfx = pd.DataFrame(x)
    dfy = pd.DataFrame(kmeans.labels_)
    data = pd.concat([dfx, dfy], axis=1)
    mergings = linkage(data, method=method)
    dendrogram(mergings, labels=dfy.values,
               leaf_rotation=0,
               leaf_font_size=7)

plt.figure(figsize=(8, 8))
plt.title('Ground Truth')
dfx = pd.DataFrame(x)
dfy = pd.DataFrame(y)
data = pd.concat([dfx, dfy], axis=1)
mergings = linkage(data, method='average')
dendrogram(mergings, labels=dfy.values,
           leaf_rotation=0,
           leaf_font_size=7)

plt.show()