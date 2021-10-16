import pymysql
import pandas as pd

def load_iris_data():
    csv_file = 'iris.csv'
    iris = pd.read_csv(csv_file)

    conn = pymysql.connect(host='localhost', user='datascience', password='datascience', db='university')
    curs = conn.cursor(pymysql.cursors.DictCursor)
        
    drop_sql = """drop table if exists iris """
    curs.execute(drop_sql)
    conn.commit()
    
    import sqlalchemy
    database_username = 'datascience'
    database_password = 'datascience'
    database_ip       = 'localhost'
    database_name     = 'university'
    database_connection = sqlalchemy.create_engine('mysql+pymysql://{0}:{1}@{2}/{3}'.
                                                   format(database_username, database_password, 
                                                          database_ip, database_name))
    iris.to_sql(con=database_connection, name='iris', if_exists='replace')  
    
def load_dbscore_data():
    xl_file = 'db_score.xlsx'
    db_score = pd.read_excel(xl_file)

    conn = pymysql.connect(host='localhost', user='datascience', password='datascience', db='university')
    curs = conn.cursor(pymysql.cursors.DictCursor)
        
    drop_sql = """drop table if exists db_score """
    curs.execute(drop_sql)
    conn.commit()
    
    import sqlalchemy
    database_username = 'datascience'
    database_password = 'datascience'
    database_ip       = 'localhost'
    database_name     = 'university'
    database_connection = sqlalchemy.create_engine('mysql+pymysql://{0}:{1}@{2}/{3}'.
                                                   format(database_username, database_password, 
                                                          database_ip, database_name))
    db_score.to_sql(con=database_connection, name='db_score', if_exists='replace')      

'''
if __name__ == '__main__':    
    load_iris_data()
    load_dbscore_data()  
'''