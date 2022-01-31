/*
 이름: 임수빈
 학번: 201814224
 프로그램 작성일: 2020-07-02
 프로그램 설명: 사용자에게 행을 입력받고 파스칼의 삼각형 출력
*/

#include <stdio.h>
#include <stdlib.h>

int pascalTriangle(int num1, int num2);
void trianglePrint(int num, int array[][num]);

int main()
{
	int n;
	printf("파스칼의 삼각형을 몇 번째 행까지 계산하시겠습니까? ");
	scanf("%d",&n); 
	//사용자에게 몇 행을 계산할 건지 입력받음

	int (*pascal)[n]; //파스칼을 저장할 배열 선언
	pascal=(int(*)[n])malloc(sizeof(int)*n*n); //동적 메모리 할당
	if (pascal==NULL)
	{
		printf("malloc 실패\n");
		return 0;
	}
	
	int i=0;
	int j=0;

	for (i=0;i<n;i++)
	{
		for (j=0;j<=i;j++)
		{
			pascal[i][j]=pascalTriangle(i,j); //파스칼의 삼각형 계산
		}
	}

	trianglePrint(n,pascal); //파스칼의 삼각형 출력

	free(pascal); //동적 메모리 해제
	return 0;
}

int pascalTriangle(int num1, int num2) //파스칼의 삼각형을 계산하는 함수
{
	if (num1==num2)
		return 1;
	else if (num2==0)
		return 1;
	else
		return pascalTriangle(num1-1,num2-1)+pascalTriangle(num1-1,num2);
}

void trianglePrint(int num, int array[][num]) //파스칼의 삼각형을 출력하는 함수
{
	int i=0;
	int j=0;

	for (i=0;i<num;i++)
	{
		for (j=0;j<=i;j++)
		{
			printf("%d ",array[i][j]);
		}
		printf("\n");
	}
}
