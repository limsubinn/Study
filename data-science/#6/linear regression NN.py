import os
os.environ['TF_CPP_MIN_LOG_LEVEL'] = '2'

import numpy as np

from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import Input, Dense
from tensorflow.keras import initializers

# y = 3*x1 + 5*x2 + 10
# 두 개의 입력값을 주면 y값을 추정하는 regression

def gen_sequential_model():
    model = Sequential([ # input, output을 하나의 레이어로만 구성
        Input(2, name='input_layer'), # 2개의 x값
        Dense(16, activation='sigmoid', name='hidden_layer1', # 16개의 뉴런
        kernel_initializer = initializers.RandomNormal(mean=0.0, stddev=0.05, seed=42)),
        Dense(1, activation='relu', name='output_layer', # 1개의 y값
        kernel_initializer = initializers.RandomNormal(mean=0.0, stddev=0.05, seed=42))
    ])

    model.summary()
    # input 2개, 각 뉴런에 bias 값 -> 32+16 = 48개의 파라미터 (hidden)
    # 16개의 weight + 1개의 bias -> 17개의 파라미터 (output)

    model.compile(optimizer='sgd', loss='mse') # 뭐라는건지 모르겠음..

    return model

# y = w1*x1 + w2*x2 + b
def gen_linear_regression_dataset(numofsamples=500, w1=3, w2=5, b=10):
    np.random.seed(42)
    X = np.random.rand(numofsamples, 2) # 샘플의 개수만큼 2차원 array로 리턴
    print(X)
    print(X.shape)

    coef = np.array([w1, w2])
    bias = b

    print(coef)
    print(coef.shape)

    y = np.matmul(X, coef.transpose()) + bias

    # X=(numofsamples, 2), coef.transpose() = (2,1)

    print(y)
    print(y.shape)

    return X, y


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


def predict_new_sample(model, x, w1=3, w2=5, b=10):
    x = x.reshape(1, 2)
    y_pred = model.predict(x)[0][0]

    y_actual = w1 * x[0][0] + w2 * x[0][1] + b

    print("y actual value = ", y_actual)
    print("y predicted value = ", y_pred)


model = gen_sequential_model()
X, y = gen_linear_regression_dataset(numofsamples=1000)
history = model.fit(X, y, epochs=200, verbose=2, validation_split=0.3)
plot_loss_curve(history)
print("train loss=", history.history['loss'][-1])
print("test loss=", history.history['val_loss'][-1])

predict_new_sample(model, np.array([0.6, 0.3]))