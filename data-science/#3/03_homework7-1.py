'''
데이터사이언스 과제3-7
(1) midterm-final scatter plot 그리기
'''

import pandas as pd
import matplotlib.pyplot as plt

xl_file = './db_score.xlsx'
df = pd.read_excel(xl_file,           # 엑셀 파일 경로
                   usecols='E:G')     # E~G열 사용 (midterm, final, score)

midterm = df['midterm']
final = df['final']

plt.scatter(midterm, final)     # x축 midterm, y축 final -> scatter
plt.xlabel('midterm')           # x축 이름 붙이기 (midterm)
plt.ylabel('final')             # y축 이름 붙이기 (final)

plt.show()