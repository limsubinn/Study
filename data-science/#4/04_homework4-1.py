'''
데이터사이언스 과제4-4-1
grade A, B, C에 대한 SVM 알고리즘의 multi-class classification 성능 결과를 얻을 수 있는 프로그램 작성
train_test_split와 K-fold cross validation을 통한 성능 제시
'''

import pymysql
import numpy as np
from sklearn import svm
from sklearn.model_selection import train_test_split
from sklearn.model_selection import KFold
from sklearn import metrics
import statistics

conn = pymysql.connect(host='localhost', user='datascience', password='datascience', db='university')
curs = conn.cursor(pymysql.cursors.DictCursor)

sql = "select * from db_score_3_labels"
curs.execute(sql)
data = curs.fetchall()

curs.close()
conn.close()

X = [(t['sno'], t['homework'], t['discussion'], t['final']) for t in data]
X = np.array(X)

y = [ 0 if (t['grade'] == 'A') else 1 if (t['grade'] == 'B') else 2 for t in data ]
y = np.array(y)

X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.33, random_state=42)
clf = svm.SVC()
clf.fit(X_train, y_train)
y_predict = clf.predict(X_test)

acc = metrics.accuracy_score(y_test, y_predict)
prec = metrics.precision_score(y_test, y_predict, average=None)
rec = metrics.recall_score(y_test, y_predict, average=None)
f1 = metrics.f1_score(y_test, y_predict, average=None)
# average = None : A, B, C 각각에 대해 성능 측정

grade = ['A', 'B', 'C']
print("/////train test split/////")
print('accuracy=',acc)
for i in range(3):
    print('grade', grade[i], ':', 'precision=', prec[i], ' recall=', rec[i], ' f1=', f1[i])

accuracy = []
precision = []
recall = []
f1_score = []

kf = KFold(n_splits=4, random_state=42, shuffle=True)

for train_index, test_index in kf.split(X):
    X_train, X_test = X[train_index], X[test_index]
    y_train, y_test = y[train_index], y[test_index]

    clf = svm.SVC()
    clf.fit(X_train, y_train)
    y_predict = clf.predict(X_test)

    acc = metrics.accuracy_score(y_test, y_predict)
    prec = metrics.precision_score(y_test, y_predict, average=None)
    rec = metrics.recall_score(y_test, y_predict, average=None)
    f1 = metrics.f1_score(y_test, y_predict, average=None)
    # average = None : A, B, C 각각에 대해 성능 측정

    accuracy.append(acc)
    precision.append(prec.tolist())
    recall.append(rec.tolist())
    f1_score.append(f1.tolist())


precision = [list(x) for x in zip(*precision)]
recall = [list(x) for x in zip(*recall)]
f1_score = [list(x) for x in zip(*f1_score)]
# 값은 편하게 계산하기 위해 전치

print("\n/////K-fold across validation/////")
print("average_accuracy =", statistics.mean(accuracy))
for i in range(3):
    prec_mean = statistics.mean(precision[i])
    rec_mean = statistics.mean(recall[i])
    f1_mean = statistics.mean(f1_score[i])
    print('grade', grade[i], ':', 'precision=', prec_mean, ' recall=', rec_mean, ' f1=', f1_mean)