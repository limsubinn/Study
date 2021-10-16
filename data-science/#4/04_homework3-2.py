'''
데이터사이언스 과제4-3-2
grade B에 대한 Logistic Regression 알고리즘의 binary classification 성능 결과를 얻을 수 있는 프로그램 작성
train_test_split와 K-fold cross validation을 통한 성능 제시
'''

import pymysql
import numpy as np
from sklearn.linear_model import LogisticRegression
from sklearn.model_selection import train_test_split
from sklearn.model_selection import KFold
import statistics
from sklearn.preprocessing import StandardScaler

def classification_performance_eval(y, y_predict):
    tp, tn, fp, fn = 0, 0, 0, 0

    for y, yp in zip(y, y_predict):
        if y == 1 and yp == 1:
            tp += 1
        elif y == 1 and yp == -1:
            fn += 1
        elif y == -1 and yp == 1:
            fp += 1
        else:
            tn += 1

    accuracy = (tp + tn) / (tp + tn + fp + fn)
    precision = (tp) / (tp + fp)
    recall = (tp) / (tp + fn)
    f1_score = 2 * precision * recall / (precision + recall)

    return accuracy, precision, recall, f1_score

conn = pymysql.connect(host='localhost', user='datascience', password='datascience', db='university')
curs = conn.cursor(pymysql.cursors.DictCursor)

sql = "select * from db_score_3_labels"
curs.execute(sql)

data = curs.fetchall()

curs.close()
conn.close()

X = [(t['sno'], t['homework'], t['discussion'], t['final']) for t in data]
X = np.array(X)

y = [1 if (t['grade']=='B') else -1 for t in data]
y = np.array(y)

X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.33, random_state=42)
sc = StandardScaler()
X_train = sc.fit_transform(X_train)
X_test = sc.transform(X_test)
model = LogisticRegression(class_weight='balanced')
model.fit(X_train, y_train)
y_predict = model.predict(X_test)

acc, prec, rec, f1 = classification_performance_eval(y_test, y_predict)

print("/////train test split/////")
print("accuracy=%f" %acc)
print("precision=%f" %prec)
print("recall=%f" %rec)
print("f1_score=%f" %f1)

accuracy = []
precision = []
recall = []
f1_score = []

kf = KFold(n_splits=5, random_state=42, shuffle=True)

for train_index, test_index in kf.split(X):
    X_train, X_test = X[train_index], X[test_index]
    y_train, y_test = y[train_index], y[test_index]

    X_train = sc.fit_transform(X_train)
    X_test = sc.transform(X_test)

    model = LogisticRegression(class_weight='balanced')
    model.fit(X_train, y_train)
    y_predict = model.predict(X_test)

    acc, prec, rec, f1 = classification_performance_eval(y_test, y_predict)

    accuracy.append(acc)
    precision.append(prec)
    recall.append(rec)
    f1_score.append(f1)

print("\n/////K-fold across validation/////")
print("average_accuracy =", statistics.mean(accuracy))
print("average_precision =", statistics.mean(precision))
print("average_recall =", statistics.mean(recall))
print("average_f1_score =", statistics.mean(f1_score))