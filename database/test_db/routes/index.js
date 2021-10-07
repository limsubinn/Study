var express = require('express');
var router = express.Router();

/* GET home page. */
router.get('/', function(req, res, next) {
  res.render('index', { title: 'Express' });
});

module.exports = router;

var a=10;
let b=20;
const c=30;

console.log(a);
console.log(b);
console.log(c);

if (a===10) {
  console.log('a is 10');
}
else {
  console.log('a is not 10');
}
console.log("#####################");

for (var dan=2;dan<4;dan++) {
  console.log("#### "+dan+" table ####");
  for (var i=1;i<10;i++) {
    console.log(dan + "*" + i + "=" + dan * i);
  }
}

console.log("#####################");

function calc(x,y) {
  var sum1=x+y;

  return sum1;
}
console.log(calc(20,30));

console.log("#####################");

var s=calc(10,20);
console.log(s);

console.log("#####################");

var calc2=function(x,y) {
  return x+y;
};
console.log(calc2(50,50));

