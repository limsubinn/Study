#include <stdio.h>

int main()
{
	int num1;
	int num2;

	printf("4자리 숫자를 입력하시오: ");
	scanf("%d",&num1);

	if ((num1>=1)&&(num1<=9999))
	{
		printf("화면에 나타내고자 하는 숫자를 입력하시오: ");
		scanf("%d",&num2);

		printf("결과: ");

		if (num2==(num1/1000))
			printf("0 ");
		else
			printf("- ");

		if (num2==(num1%1000/100))
			printf("1 ");
		else
			printf("- ");

		if (num2==(num1%100/10))
			printf("2 ");
		else
			printf("- ");

		if (num2==(num1%10))
			printf("3\n");
		else
			printf("-\n");
	}
	else
	{
		printf("잘못 입력하셨습니다.\n");
	}

	return 0;
}
