'''
데이터사이언스 과제6
nonlinear regression NN
201814224 임수빈
'''

import os
os.environ['TF_CPP_MIN_LOG_LEVEL'] = '2'

import numpy as np

import tensorflow as tf
from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import Input, Dense
from tensorflow.keras import initializers

# 데이터 샘플을 생성하는 함수
# y = a + b*x1 + c*x2^2 + d*x3^3 + e*x4^4
def gen_nonlinear_regression_dataset(numofsamples=500, a=1, b=3, c=5, d=10, e=20):
    np.random.seed(42)
    X = np.random.rand(numofsamples, 4)
    print(X)
    print(X.shape)

    # y값 만듦
    coef = np.array([b, c, d, e])
    bias = a

    print(coef)
    print(coef.shape)

    y = np.array([])

    for i in range(numofsamples):
        y = np.append(y, np.array([bias \
            + coef[0] * X[i][0] \
            + coef[1] * (X[i][1] ** 2) \
            + coef[2] * (X[i][2] ** 3) \
            + coef[3] * (X[i][3] ** 4)]))

    print(y)
    print(y.shape)

    return X, y


# KERAS NN으로 model을 구성하는 함수
def gen_sequential_model():
    tf.random.set_seed(42)

    model = Sequential([ # input, output을 하나의 레이어로만 구성
        Input(4, name='input_layer'), # 4개의 x값
        Dense(16, activation='sigmoid', name='hidden_layer1', # 16개의 뉴런
        kernel_initializer = initializers.RandomNormal(mean=0.0, stddev=0.05, seed=42)),
        Dense(1, activation='relu', name='output_layer', # 1개의 y값
        kernel_initializer = initializers.RandomNormal(mean=0.0, stddev=0.05, seed=42))
    ])

    model.summary()

    model.compile(optimizer='sgd', loss='mse')

    return model

# 화면 상에 출력하는 함수
def plot_loss_curve(history):
    import matplotlib.pyplot as plt

    plt.figure(figsize=(15, 10))

    plt.plot(history.history['loss'][1:])
    plt.plot(history.history['val_loss'][1:])
    plt.title('model loss')
    plt.ylabel('loss')
    plt.xlabel('epoch')
    plt.legend(['train', 'test'], loc='upper right')
    plt.show()

# 임의의 입력변수를 입력받아 y값을 예측하는 함수
def predict_new_sample(model, x, a=1, b=3, c=5, d=10, e=20):
    x = x.reshape(1, 4)
    y_pred = model.predict(x)[0][0]

    y_actual = a \
               + b * x[0][0] \
               + c * (x[0][1] ** 2) \
               + d * (x[0][2] ** 3) \
               + e * (x[0][3] ** 4)

    print("y actual value = ", y_actual)
    print("y predicted value = ", y_pred)



model = gen_sequential_model()
# 모델 구성

X, y = gen_nonlinear_regression_dataset(numofsamples=1000)
# 데이터 샘플 생성

history = model.fit(X, y, epochs=100, verbose=2, validation_split=0.3)
# 모델 학습
# 전체 데이터를 1000번 스캔, 테스트 데이터 30%

plot_loss_curve(history)
# 학습 결과 출력, 분석

print("train loss=", history.history['loss'][-1])
print("test loss=", history.history['val_loss'][-1])

predict_new_sample(model, np.array([0.6, 0.2, 0.4, 0.3]))