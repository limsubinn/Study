/* fileReadCallback.js */

// 최댓값 찾기
function findMax (prev, cur) {
    return prev > cur? prev: cur;
}

// 최솟값 찾기
function findMin (prev, cur) {
    return prev > cur? cur: prev;
}

// 파일 시스템
var fs = require('fs');

// 파일 리스트가 적힌 파일을 열어서 텍스트 추출
var fileList = "list.txt";
var fileData = fs.readFileSync(fileList, "utf-8");
var file = JSON.parse(fileData);

// max, min 값 초기화 (최댓값은 임의로 10000000으로 설정함.)
var max = 0;
var min = 10000000;

// 각각 파일 읽어서 최댓값, 최솟값 계산
var data = null;
function cb (err, fileData) {
    if (err) console.log(err);
    else data = JSON.parse(fileData);
}
for (let i=0; i<file.length; i++) {
    setTimeout(function() {
        fs.readFile(file[i], 'utf-8', cb);
    }, 50 * (i + 1));
    setTimeout(function() {
        max = findMax(max, data.reduce(findMax));
        min = findMin(min, data.reduce(findMin));
    }, 70 * (i + 1));
}

// 출력
setTimeout(function() {
    console.log('최댓값 :', max);
    console.log('최솟값 :', min);
}, 500);