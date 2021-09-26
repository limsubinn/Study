'''
데이터사이언스 과제3-1
midterm, final, score의 mean, median 구하기
'''

import pandas as pd
xl_file = './db_score.xlsx'
df = pd.read_excel(xl_file,         # 엑셀 파일 경로
                   usecols='A:H')   # A~H열 사용

print('midterm mean:', df['midterm'].mean(), '\nmidterm median:', df['midterm'].median())
print('\nfinal mean:', df['final'].mean(), '\nfinal median:', df['final'].median())
print('\nscore mean:', df['score'].mean(), '\nscore median:', df['score'].median())