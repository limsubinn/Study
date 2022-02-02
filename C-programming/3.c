#include <stdio.h> //헤더파일 포함

/*
프로그램 작성일: 2020-03-31
프로그램 설명: 변수를 사용하여 이름, 학번, 성별을 화면에 출력
*/

int main() //메인 함수 시작
{
	char l = 'L';
	char i = 'i';
	char m = 'm';
	char s = 'S';
	char u = 'u';
	char b = 'b';
	char n = 'n';
       	//변수에 이름 저장
	char sex = 'F'; //변수에 성별 저장
	int num = 0; //변수에 학번 저장

	printf("--------\n");
	printf("이름: %c%c%c %c%c%c%c%c\n학번: %d\n성별: %c\n", l, i, m, s, u, b, i, n, num, sex);
	printf("--------\n");
	//화면에 이름, 학번, 성별 출력

	return 0; //외부로 0값을 반환
} //메인 함수 종료
