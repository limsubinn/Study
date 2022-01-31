#include <stdio.h>
#include <string.h>

int password(void) 
{
	int x=0;
	char a[8];

	int i=1;

	while (i<4)
	{
		printf("Enter password(length 8): ");
		scanf("%8s",a);

		if (strcmp(a,"abcdefgh")==0)
			x=1;

		if (x)
		{
			printf("Password is correct!\n");
			break;
		}
		else
		{
			printf("Password is not correct!\n");
			printf("error time: %d/3\n",i);
			i++;
		}
   	}

	return i;
}
