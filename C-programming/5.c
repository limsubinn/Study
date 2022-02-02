/*
 프로그램 작성일: 2020-04-16
 프로그램 설명: 10~95까지의 숫자를 입력 받고
               사용자가 입력한 두 자리수부터 입력한 수에 4를 더한 수까지의 범위에서
	       짝수, 십의 자리 숫자>3, 일의 자리 숫자>십의 자리 숫자를 모두 만족하는 수의 개수 출력
*/

#include <stdio.h>

int main()
{
	int num=0, num1=0, num2=0, num3=0, num4=0; 
	int cal=0, cal1=0, cal2=0, cal3=0, cal4=0;
	int cnt=0;
	//문제를 계산하기 위한 변수 선언

	printf("두 자리 숫자를 입력하시오(10~95). ");
	scanf("%d",&num);
	//두 자리 숫자 입력 받음

	num1 = num+1;
	num2 = num+2;
	num3 = num+3;
	num4 = num+4;
	//조건1의 범위를 만족하는 숫자

	cal= (num%2==0)&&((num/10)>3)&&((num%10)>(num/10));
	cal1 = (num1%2==0)&&((num1/10)>3)&&((num1%10)>(num1/10));
	cal2 = (num2%2==0)&&((num2/10)>3)&&((num2%10)>(num2/10));
	cal3 = (num3%2==0)&&((num3/10)>3)&&((num3%10)>(num3/10));
	cal4 = (num4%2==0)&&((num4/10)>3)&&((num4%10)>(num4/10));
	//조건2~4를 만족하는 계산과정
	
	cnt = (cal==1)? cnt+1 : cnt;
	cnt = (cal1==1)? cnt+1 : cnt;
	cnt = (cal2==1)? cnt+1 : cnt;
	cnt = (cal3==1)? cnt+1 : cnt;
	cnt = (cal4==1)? cnt+1 : cnt;
	//조건을 만족하는 수의 개수 계산

	printf("조건을 만족하는 수의 개수는 %d개입니다.\n",cnt);
	//조건을 만족하는 수의 개수 출력
	
	return 0;
}
