# Code source: Gaël Varoquaux
# Modified for documentation by Jaques Grobler
# License: BSD 3 clause

import sys
import numpy as np
import matplotlib.pyplot as plt
import pandas as pd

# Though the following import is not directly being used, it is required
# for 3D projection to work with matplotlib < 3.2
import mpl_toolkits.mplot3d  # noqa: F401

from sklearn.cluster import KMeans
from sklearn import datasets
from scipy.cluster.hierarchy import linkage, dendrogram

np.random.seed(0)

# 데이터 불러오기
iris = datasets.load_iris()
x = iris.data
y = iris.target # 정수화(인덱스화)된 클래스들

# KMeans의 인자
# n_clusters 는 클러스터(군집) 개수이자 초기 중심점 개수가 된다.
# n_init 은 중심점 선정을 위한 시도의 횟수이다.
# init의 경우 중심점 선택 방식이며 k-means++와 random의 두가지 선택지가 있다. k-means++는 똑똑한 방식으로 중심점을 찾아가며 random의 경우 완전히 무작위의 중심점을 찾는다.

kmeans = KMeans(n_clusters=3)

fig = plt.figure(1, figsize=(4, 5))
ax = fig.add_subplot(111, projection="3d", elev=48, azim=134)
ax.set_position([0, 0, 0.95, 1])
kmeans.fit(x) # 위에서 선택한 kmeans 클러스터링 실행
labels = kmeans.labels_

ax.scatter(x[:, 3], x[:, 0], x[:, 2], c=labels.astype(int), edgecolor="k")

ax.w_xaxis.set_ticklabels([])
ax.w_yaxis.set_ticklabels([])
ax.w_zaxis.set_ticklabels([])
ax.set_xlabel("Petal width")
ax.set_ylabel("Sepal length")
ax.set_zlabel("Petal length")
ax.set_title("Clustering")
ax.dist = 12

# 미리 클래스별 분류되어 있던 값 표시(클러스터링 아님)
fig = plt.figure(2, figsize=(4, 5))
ax = fig.add_subplot(111, projection="3d", elev=48, azim=134)
ax.set_position([0, 0, 0.95, 1])

for name, label in [("Setosa", 0), ("Versicolour", 1), ("Virginica", 2)]:
    ax.text3D(
        x[y == label, 3].mean(),
        x[y == label, 0].mean(),
        x[y == label, 2].mean() + 2,
        name,
        horizontalalignment="center",
        bbox=dict(alpha=0.2, edgecolor="w", facecolor="w"),
    )

# 클러스터링 결과에 나온 클래스와 같은 색으로 표시하기 위해 순서 조정
Y = np.choose(y, [1, 0, 2]).astype(int)
print(Y)
ax.scatter(x[:, 3], x[:, 0], x[:, 2], c=Y, edgecolor="k")

ax.w_xaxis.set_ticklabels([])
ax.w_yaxis.set_ticklabels([])
ax.w_zaxis.set_ticklabels([])
ax.set_xlabel("Petal width")
ax.set_ylabel("Sepal length")
ax.set_zlabel("Petal length")
ax.set_title("Ground Truth")
ax.dist = 12

#dendrogram
plt.figure(3, figsize=(8, 8))
dfx = pd.DataFrame(x)
dfy = pd.DataFrame(Y)
data = pd.concat([dfx, dfy], axis=1)
mergings = linkage(data, method='single') #클러스터간 거리를 잴 때 서로 가장 가까이 있는 점의 거리를 기준으로 한다.
dendrogram(mergings, labels=dfy.values,
           leaf_rotation=0,
           leaf_font_size=7)

plt.show()