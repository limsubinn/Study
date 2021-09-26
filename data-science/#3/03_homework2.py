'''
데이터사이언스 과제3-2
grade의 mode 구하기
'''

import pandas as pd
xl_file = './db_score.xlsx'
df = pd.read_excel(xl_file,         # 엑셀 파일 경로
                   usecols='A:H')   # A~H열 사용

print(df['grade'].mode())