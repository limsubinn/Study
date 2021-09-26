'''
데이터사이언스 2주차 과제3

score 테이블에 대하여 midterm과 final이 모두 20점 이상인 학생의
학번, 중간고사, 기말고사를 학번 순으로 출력
'''

import pymysql

conn = pymysql.connect(host='localhost', user='datascience', password='datascience', db='university')
curs = conn.cursor(pymysql.cursors.DictCursor)

sql = '''select sno, midterm, final 
from score 
where midterm>=20 && final>=20'''''
curs.execute(sql)

row = curs.fetchone()
while row:
    print(row)
    row = curs.fetchone()

curs.close()
conn.close()