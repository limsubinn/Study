'''
데이터사이언스 과제3-6
(2) final histogram 그리기
'''

import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

xl_file = './db_score.xlsx'
df = pd.read_excel(xl_file,         # 엑셀 파일 경로
                   usecols='F')     # F열 사용 (final)

per_range = np.arange(0, 101, 10)                               # 백분위수 범위
final = np.percentile(df, per_range, interpolation='nearest')   # final 백분위수 구하기

plt.hist(final)   # 히스토그램 그리기
plt.show()