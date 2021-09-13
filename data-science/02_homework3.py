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