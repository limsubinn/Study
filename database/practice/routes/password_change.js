//password-change.js
//express 모듈을 불러오고 라우팅 로직을 설정
var express = require('express');
var router = express.Router();

//mysql_db.js파일의 연결 정보를 mysqlDB 객체에 할당
var mysqlDB = require('../mysql_db');

/*
* 클라이언트로 부터 get 호출이 되었을때 아래의 코드를 수행
* req: 클라이언트 요청정보를 담은 객체
* res: 요청한 클라이어트로 응답을 위한 객체
* next: 다음 로직 수행을 위한 함수명
*/
router.get('/', function (req, res, next) {
    res.render('password_change');
});

/*
* 클라이언트로 부터 post 호출이 되었을때 아래의 코드를 수행
* req: 클라이언트 요청정보를 담은 객체
* res: 요청한 클라이어트로 응답을 위한 객체
* next: 다음 로직 수행을 위한 함수명
*/
router.post('/', function (req, res, next) {
    //html body로 부터 request 받은 변수
    var userId = req.body['userId'];
    var userPw = req.body['userPw'];
    var userPwNew = req.body['userPwNew'];

    /*
   * mysql 쿼리 요청
   * sql: sql 쿼리문
   * values: sql 쿼리 요청 후 리턴 받은 값
   * err: mysql 쿼리 요청 중 오류가 있을 경우 저장되는 파라미터
   * rows: 쿼리 결과
   * fields: 테이블의 필드 정보
   */
    mysqlDB.query('select * from account where id=? and pw=?', [userId, userPw], function (err, rows, fields) {
        if (!err) {                         //오류가 없을 때 아래의 코드 실행
            if (rows[0] != undefined) {     //row가 존재하면 비밀번호 변경
                mysqlDB.query('update account set pw=SHA1(?) where id=?', [userPwNew, userId], function (err, rows, fields) {
                    if (!err) {             //오류가 없을 때 아래의 코드 실행
                        res.send('password change success');
                    } else {                //오류가 있으면 오류코드 출력
                        res.send('error : ' + err);
                    }
                });
            } else {                        //삭제할 데이터 없으면 아래의 코드 출력
                res.send('no data');
            }

        } else {                             //오류가 있으면 오류코드 출력
            res.send('error : ' + err);
        }
    });

});

module.exports = router;
