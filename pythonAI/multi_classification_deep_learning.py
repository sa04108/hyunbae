import tensorflow as tf
import pandas as pd

from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import Dense
from sklearn.preprocessing import LabelEncoder
from sklearn.datasets import load_iris

df = pd.read_csv('iris.csv') #데이터는 sklearn.datasets의 load_iris 와 동일하나, 다중 분류를 위해 클래스도 포함
dataset = df.values
X = dataset[:,:4].astype(float) #클래스에 해당되는 string 값을 제외하기 위해 4번째 열까지만 입력
Y_obj = dataset[:,4]

e = LabelEncoder()
e.fit(Y_obj)
Y = e.transform(Y_obj) #분류에 사용되는 클래스들의 인덱스화(string -> int)

Y_encoded = tf.keras.utils.to_categorical(Y) #원핫인코딩

#모델 설정
model = Sequential()
model.add(Dense(16, input_dim=4, activation='relu'))
model.add(Dense(3, activation='softmax'))

#모델 컴파일
model.compile(loss='categorical_crossentropy',
              optimizer='adam',
              metrics=['accuracy'])

#모델 실행
model.fit(X, Y_encoded, epochs=50, batch_size=1)

print("\n Accuracy: %.4f" % (model.evaluate(X, Y_encoded)[1]))