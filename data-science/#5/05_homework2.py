import numpy as np
import pymysql
import time

def load_dbscore_data():
    conn = pymysql.connect(host='localhost', user='datascience', password='datascience', db='university')
    curs = conn.cursor(pymysql.cursors.DictCursor)

    sql = "select * from score"
    curs.execute(sql)

    data = curs.fetchall()

    curs.close()
    conn.close()

    X = [ (t['attendance'], t['homework'], t['final'] ) for t in data ]
    X = np.array(X)

    y = [(t['score']) for t in data]
    y = np.array(y)

    return X, y


X, y = load_dbscore_data()
X_T = np.transpose(X)

import statsmodels.api as sm

X_const = sm.add_constant(X)

model = sm.OLS(y, X_const)
ls = model.fit()

print(ls.summary())

ls_c = ls.params[0]
ls_m1 = ls.params[1]
ls_m2 = ls.params[2]
ls_m3 = ls.params[3]

# y_pred = ls_m1 * X_T[0] + ls_m2 * X_T[1] + ls_m3 * X_T[2] + ls_c


def gradient_descent_naive(X, y):
    epochs = 100000
    min_grad = 0.0001
    learning_rate = 0.001

    m1 = 0.0
    m2 = 0.0
    m3 = 0.0
    c = 0.0

    n = len(y)

    c_grad = 0.0
    m1_grad = 0.0
    m2_grad = 0.0
    m3_grad = 0.0


    for epoch in range(epochs):

        for i in range(n):
            y_pred = m1 * X[i][0] + m2 * X[i][1] + m3 * X[i][2] + c
            m1_grad += 2 * (y_pred - y[i]) * X[i][0]
            m2_grad += 2 * (y_pred - y[i]) * X[i][1]
            m3_grad += 2 * (y_pred - y[i]) * X[i][2]
            c_grad += 2 * (y_pred - y[i])

        c_grad /= n
        m1_grad /= n
        m2_grad /= n
        m3_grad /= n

        m1 = m1 - learning_rate * m1_grad
        m2 = m2 - learning_rate * m2_grad
        m3 = m3 - learning_rate * m3_grad
        c = c - learning_rate * c_grad

        if (epoch % 1000 == 0):
            print("epoch %d: m1_grad=%f, m2_grad=%f, m3_grad=%f, c_grad=%f, m1=%f, m2=%f, m3=%f, c=%f"
                  % (epoch, m1_grad, m2_grad, m3_grad, c_grad, m1, m2, m3, c))


        if (abs(m1_grad) < min_grad and abs(m2_grad) < min_grad
                and abs(m3_grad) < min_grad and abs(c_grad) < min_grad):
            break

    return m1, m2, m3, c


start_time = time.time()
m1, m2, m3, c = gradient_descent_naive(X, y)
end_time = time.time()
non_vec_time = end_time - start_time

def gradient_descent_vectorized(X, y):
    epochs = 100000
    min_grad = 0.0001
    learning_rate = 0.001

    m1 = 0.0
    m2 = 0.0
    m3 = 0.0
    c = 0.0

    n = len(y)

    c_grad = 0.0
    m1_grad = 0.0
    m2_grad = 0.0
    m3_grad = 0.0

    for epoch in range(epochs):

        y_pred = m1 * X_T[0] + m2 * X_T[1] + m3 * X_T[2] + c
        m1_grad = (2 * (y_pred - y) * X_T[0]).sum() / n
        m2_grad = (2 * (y_pred - y) * X_T[1]).sum() / n
        m3_grad = (2 * (y_pred - y) * X_T[2]).sum() / n
        c_grad = (2 * (y_pred - y)).sum() / n

        m1 = m1 - learning_rate * m1_grad
        m2 = m2 - learning_rate * m2_grad
        m3 = m3 - learning_rate * m3_grad
        c = c - learning_rate * c_grad

        if (epoch % 1000 == 0):
            print("epoch %d: m1_grad=%f, m2_grad=%f, m3_grad=%f, c_grad=%f, m1=%f, m2=%f, m3=%f, c=%f"
                  % (epoch, m1_grad, m2_grad, m3_grad, c_grad, m1, m2, m3, c))

        if (abs(m1_grad) < min_grad and abs(m2_grad) < min_grad
                and abs(m3_grad) < min_grad and abs(c_grad) < min_grad):
            break

    return m1, m2, m3, c

start_time = time.time()
vec_m1, vec_m2, vec_m3, c = gradient_descent_vectorized(X, y)
end_time = time.time()
vec_time = end_time - start_time


print("\n\n<<<<Final>>>>")

print("\nnon-vec: ")
print("gdn_m1=%f, gdn_m2=%f, gdn_m3=%f, gdn_c=%f" % (m1, m2, m3, c))
print("%f seconds" %(non_vec_time))

print("\nvec: ")
print("gdn_m1=%f, gdn_m2=%f, gdn_m3=%f, gdn_c=%f" % (vec_m1, vec_m2, vec_m3, c))
print("%f seconds" %(vec_time))

print("\nLS: ")
print("ls_m1=%f, ls_m2=%f, ls_m3=%f ls_c=%f" % (ls_m1, ls_m2, ls_m3, ls_c))