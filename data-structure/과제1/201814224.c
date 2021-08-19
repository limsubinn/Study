#include <stdio.h>
#include <stdlib.h>
/*
 자료구조및알고리즘 과제1

 이름: 임수빈
 학번: 201814224
 프로그램 작성일: 2021-03-19
 프로그램 설명: 피보나치를 재귀함수를 이용하여 시간 복잡도가 O(n)을 가지도록 구현
 */
int fibo(int n)
{
	int *arr;
	arr=(int *)malloc(n*sizeof(int)); //동적메모리 할당

	if (arr==NULL) 
	{
		printf("malloc 오류\n");
		exit(1);
	}

	arr[0]=0; //n=1일 경우
	arr[1]=1; //n=2일 경우

	int i;
	if (n>=3) //배열 초기화
	{
		for (i=2;i<n;i++)
		{
			arr[i]=0;
		}
	}

	if (arr[n-1]==0 && n!=1) //배열에 저장된 값이 없을 경우(피보나치가 한번도 호출되지 않았을 경우) 피보나치 호출
		arr[n-1]=fibo(n-1)+fibo(n-2);
	
	int result;
	result=arr[n-1];

	free(arr); //동적메모리 해제
	return result;

}

int main()
{
	int n;
	printf("숫자를 입력하세요: ");
	scanf("%d",&n);

	int i;
	for (i=1;i<=n;i++)
		printf("%d ",fibo(i));
	printf("\n");

	return 0;
}
