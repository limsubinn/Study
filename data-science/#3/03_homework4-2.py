'''
데이터사이언스 과제3-4
(2) final의 percentile plot 그리기
'''

import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

xl_file = './db_score.xlsx'
df = pd.read_excel(xl_file,         # 엑셀 파일 경로
                   usecols='A:H')   # A~H열 사용

x = [0, 10, 20, 30, 40, 50, 60, 70, 80, 90, 100]              # 백분위수 범위
y = np.percentile(df['final'], x, interpolation='nearest')    # 백분위수 구하기

plt.xlim(x[0]-2, x[10]+2)                        # x축 길이
plt.ylim(y[0]-2, y[10]+2)                        # y축 길이
plt.xticks(x)                                    # x축 범위
plt.yticks(np.arange(y[0], y[10]+1, y[10]/10))   # y축 범위
plt.plot(x, y, marker='o')                       # 그래프 그리기
plt.show()
