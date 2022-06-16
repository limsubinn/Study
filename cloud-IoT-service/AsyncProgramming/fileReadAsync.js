/* fileReadAsync.js */

// 최댓값, 최솟값 찾기
function findMax (prev, cur) {
    return prev > cur? prev: cur;
}
function findMin (prev, cur) {
    return prev > cur? cur: prev;
}

// 파일 읽기
function f_readFile (name) { 
    return new Promise (function (resolve, reject) {
        var fileData = fs.readFileSync(name, "utf-8");
        data = JSON.parse(fileData);

        resolve(data);
    }) 
};

// 최댓값, 최솟값 얻기
async function getMinMax (name) {
    await f_readFile(name);
    max = findMax(max, data.reduce(findMax));
    min = findMin(min, data.reduce(findMin));
    console.log(max, min);
};

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
async function cal () {
    await getMinMax(file[0]);
    await getMinMax(file[1]);
    await getMinMax(file[2]);
    console.log('최댓값 :', max);
    console.log('최솟값 :', min);
}

cal();