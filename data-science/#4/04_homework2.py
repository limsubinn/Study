'''
데이터사이언스 과제 4-2
db_score_3_labels.xlsx 파일을 mysql의 테이블로 구축
'''

import pandas as pd
import pymysql

xl_file = './db_score_3_labels.xlsx'
df = pd.read_excel(xl_file)

conn = pymysql.connect(host='localhost', user='datascience', password='datascience', db='university')
curs = conn.cursor(pymysql.cursors.DictCursor)


sql = '''CREATE TABLE if not exists db_score_3_labels (
sno int primary key, 
homework float,
discussion int,
final float,
grade varchar(20))'''

curs.execute(sql)

sql = '''INSERT IGNORE INTO db_score_3_labels 
(sno, homework, discussion, final, grade)
VALUES (%s, %s, %s, %s, %s)'''

for i in range(len(df)):
    curs.execute(sql, tuple(df.values[i]))

conn.commit()

curs.close()
conn.close()