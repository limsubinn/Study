'''
데이터사이언스 2주차 과제1

첨부된 엑셀 파일 score.xlsx를 입력파일로 받아서, dataframe으로 읽어들인 다음
midterm과 final이 모두 20점 이상인 학생의 학번, 중간고사, 기말고사를 학번 순으로 출력
'''

import pandas as pd
xl_file = './score.xlsx'
df = pd.read_excel(xl_file, index_col=None, header=None)

midterm_cells = df[4][1:93]
final_cells = df[5][1:93]

for i in range(1,93):
    if int(midterm_cells[i]) >= 20 and int(final_cells[i]) >= 20:
        print('sno: %2d  midterm: %.2f  final: %.2f' %(i, midterm_cells[i], final_cells[i]))
        # 엑셀 파일에 학번순으로 저장되어 있기 때문에 따로 정렬 안 함