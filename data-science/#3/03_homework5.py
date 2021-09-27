'''
데이터사이언스 과제3-5
midterm, final, score box plot 그리기
'''

import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

xl_file = './db_score.xlsx'
df = pd.read_excel(xl_file,         # 엑셀 파일 경로
                   usecols='E:G')   # E~G열 사용 (midterm, final, score만 사용)

y = np.arange(0, 101, 10)                                           # 백분위수 범위
midterm = np.percentile(df['midterm'], y, interpolation='nearest')  # midterm 백분위수 구하기
final = np.percentile(df['final'], y, interpolation='nearest')      # final 백분위수 구하기
score = np.percentile(df['score'], y, interpolation='nearest')      # score 백분위수 구하기

plt.ylim(y[0]-2, y[10]+2)                           # y축 길이
plt.boxplot([midterm, final, score],                # midterm, final, score에 대해 boxplot 그리기
            labels=['midterm', 'final', 'score'],
            sym='+')
plt.show()