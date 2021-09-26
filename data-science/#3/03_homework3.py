'''
데이터사이언스 과제3-3
midterm, final, score의 variance, standard deviation 구하기
'''

import pandas as pd
xl_file = './db_score.xlsx'
df = pd.read_excel(xl_file,         # 엑셀 파일 경로
                   usecols='A:H')   # A~H열 사용

print('midterm variance:', df['midterm'].var(), '\nmidterm standard deviation:', df['midterm'].var()**0.5)
print('\nfinal variance:', df['final'].var(), '\nfinal standard deviation:', df['final'].var()**0.5)
print('\nscore variance:', df['score'].var(), '\nscore standard deviation:', df['score'].var()**0.5)
# 분산: 파이썬 내장 함수 이용
# 표준편차: 분산의 제곱근