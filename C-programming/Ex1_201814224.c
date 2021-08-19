#include <stdio.h>

int main()
{
	int num;
	int n;

	printf("두 자리 숫자를 입력하시오(10~95): ");
	scanf("%d",&num);
	printf("계산을 몇 번 실행하시겠습니까? ");
	scanf("%d",&n);

	int i;
	int scope[n+1];
	int cal[n+1];
	int cnt=0;

	for (i=0;i<n+1;i++)
	{
		scope[i]=num+i;
		cal[i]=(scope[i]<=99)&&(scope[i]%2==0)&&((scope[i]/10)>3)&&((scope[i]%10)>(scope[i]/10));
		cnt=(cal[i]==1)?cnt+1:cnt;
	}

	printf("조건을 만족하는 수의 개수는 %d개입니다.\n",cnt);

	return 0;
}



