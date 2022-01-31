var createError = require('http-errors');
var express = require('express');
var path = require('path');
var cookieParser = require('cookie-parser');
var logger = require('morgan');

//설치한 모듈 불러옴
var bodyParser = require('body-parser'); //add code

//mysql_db.js파일 요청 및 DB연결코드
var mysqlDB = require('./mysql_db');    //add code
mysqlDB.connect();                      //add code

var indexRouter = require('./routes/index');
var usersRouter = require('./routes/users');
var show_all_data_router = require('./routes/show_all_data'); //add code
var login_router = require('./routes/login');                       //add code
var join_router = require('./routes/join');                        //add code
var delete_account_router = require('./routes/delete_account');     //add code
var password_change_router = require('./routes/password_change');   //add code

var app = express();

// view engine setup
app.set('views', path.join(__dirname, 'views'));
app.set('view engine', 'ejs');

app.use(logger('dev'));
app.use(express.json());
app.use(express.urlencoded({ extended: false }));
app.use(cookieParser());
app.use(express.static(path.join(__dirname, 'public')));

//app.use로 등록
app.use(bodyParser.json());                                 //add code
app.use(bodyParser.urlencoded({extended : false}));         //add code

app.use('/', indexRouter);
app.use('/users', usersRouter);

app.use('/show_all_data', show_all_data_router);  //add code
app.use('/login', login_router);                        //add code
app.use('/join', join_router);                        //add code
app.use('/delete_account', delete_account_router);    //add code
app.use('/password_change', password_change_router);  //add code

// catch 404 and forward to error handler
app.use(function(req, res, next) {
  next(createError(404));
});

// error handler
app.use(function(err, req, res, next) {
  // set locals, only providing error in development
  res.locals.message = err.message;
  res.locals.error = req.app.get('env') === 'development' ? err : {};

  // render the error page
  res.status(err.status || 500);
  res.render('error');
});

module.exports = app;
