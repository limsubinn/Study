/*
 프로그램 작성일: 2020-06-10
 프로그램 설명: readInput, cal 함수를 이용하여 369게임
		(1~99의 정수를 입력받고 이에 따른 박수의 개수 출력)
*/

#include <stdio.h>

int readInput();
int cal(int nm);

int main()
{
	int cnt=0; //박수의 개수를 저장할 변수
	char *s[4] = {
		"박수없음\n",
		"박수짝\n",
		"박수짝짝\n",
		"\n"
	}; //박수의 출력을 저장한 배열

	while (cnt!=3) //사용자가 0을 입력하기 전까지 반복
	{
		printf("1~99 정수를 입력하시오>> ");
		cnt=readInput(); //함수 호출

		printf("%s",s[cnt]); //박수 출력

	}

	return 0;
}

int readInput()
{
	int num; //사용자에게 입력받을 정수
	scanf("%d",&num);

	int n; //사용자에게 입력받은 정수의 일의 자리에 따른 카운트 값을 계산하기 위한 변수
	int m; //십의 자리에 따른 카운트 값을 계산하기 위한 변수
	int nm; //카운트 값을 계산하기 위한 변수

	if ((num%10==3)||(num%10==6)||(num%10==9)) //일의 자리가 3,6,9일 때
		n=0;
	else
		n=1;

	if ((num/10==3)||(num/10==6)||(num/10==9)) //십의 자리가 3,6,9일 때
		m=0;
	else
		m=1;

	if (num==0) //사용자가 0을 입력했을 때
		nm=-1;
	else
		nm=m+n;

	int cnt; //박수의 개수를 저장할 변수
	cnt=cal(nm); //박수의 개수를 계산하기 위한 함수 호출

	return cnt; //박수의 개수 반환
}

int cal(int nm)
{
	int cnt;
	cnt=2-nm; //박수의 개수 계산 (예외. 프로그램을 종료할 때 cnt=3)

	return cnt; //박수의 개수 반환
}
