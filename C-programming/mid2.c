#include <stdio.h>

int main()
{
	int h;
	int m;
	char ap;

	printf("몇 시, 몇 분, 오전/오후(A/P) 에 일어나길 원하십니까?: ");
	scanf("%d %d %c",&h, &m,&ap);

	if (m>=45)
		printf("%d %d %c\n",h,m-45,ap);
	else
	{
		if (h==12)
		{
			if (ap=='A')
				printf("%d %d %c\n",h-1,60+m-45,'P');
			else
				printf("%d %d %c\n",h-1,60+m-45,'A');
		}
		else
		{
			if (h==1)
				printf("%d %d %c\n",12+h-1,60+m-45,ap);
			else
				printf("%d %d %c\n",h-1,60+m-45,ap);
		}
	}

	return 0;
}
