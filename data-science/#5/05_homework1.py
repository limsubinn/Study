import numpy as np
import matplotlib.pyplot as plt
import pymysql
from celluloid import Camera


def load_dbscore_data():
    conn = pymysql.connect(host='localhost', user='datascience', password='datascience', db='university')
    curs = conn.cursor(pymysql.cursors.DictCursor)

    sql = "select * from score"
    curs.execute(sql)

    data = curs.fetchall()

    curs.close()
    conn.close()

    X = [(t['final']) for t in data]
    X = np.array(X)

    y = [(t['score']) for t in data]
    y = np.array(y)

    return X, y


X, y = load_dbscore_data()

'''
plt.scatter(X, y) 
plt.show()
'''

# y = mx + c

fig = plt.figure()
ax = fig.subplots()
camera = Camera(fig)


def gradient_descent_vectorized(X, y):
    epochs = 100000
    min_grad = 0.0001
    learning_rate = 0.001

    m = 0.0
    c = 0.0

    n = len(y)

    c_grad = 0.0
    m_grad = 0.0

    for epoch in range(epochs):

        y_pred = m * X + c
        m_grad = (2 * (y_pred - y) * X).sum() / n
        c_grad = (2 * (y_pred - y)).sum() / n

        m = m - learning_rate * m_grad
        c = c - learning_rate * c_grad

        if (epoch % 1000 == 0):
            print("epoch %d: m_grad=%f, c_grad=%f, m=%f, c=%f" % (epoch, m_grad, c_grad, m, c))
            ax.scatter(X, y, color='blue')
            ax.plot([min(X), max(X)], [min(y_pred), max(y_pred)], color='red')
            camera.snap()

        if (abs(m_grad) < min_grad and abs(c_grad) < min_grad):
            break

    return m, c

m, c = gradient_descent_vectorized(X, y)

print("\n\nFinal:")
print("gdv_m=%f, gdv_c=%f" % (m, c))

animation = camera.animate(interval=100, blit=True)
animation.save('homework1.gif')