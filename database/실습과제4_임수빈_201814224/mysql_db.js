//mysql 모듈 불러오기(import 해서 객체 할당한 것과 같음)
var mysql = require('mysql');

//연결 정보
var connection = mysql.createConnection({
    host: 'mm.konkuk.ac.kr',
    post: 3306,
    user: 'user_201814224',
    password: '201814224',
    database: 'user_201814224'
});

//모듈 내보내기
module.exports = connection;