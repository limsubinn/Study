#include <stdio.h>

void matrix(int m, int n, int p, int A[][n], int B[][p], int C[][p]);

int main()
{
	int m;
	int n;
	int p;
	
	printf("m,n,p를 입력하시오: ");
	scanf("%d %d %d",&m,&n,&p);

	int A[m][n];
	int B[n][p];
	int i=0, j=0;

	printf("첫 번째 %d * %d 행렬(A)를 입력하시오:\n",m,n);
	for (i=0;i<m;i++)
	{
		for (j=0;j<n;j++)
			scanf("%d",&A[i][j]);
	}


	printf("두 번째 %d * %d 행렬(B)를 입력하시오:\n",n,p);

	for (i=0;i<n;i++)
	{
		for (j=0;j<p;j++)
			scanf("%d",&B[i][j]);
	}

	int C[m][p];
	matrix(m,n,p,A,B,C);

	printf("결과:\n");
	for (i=0;i<m;i++)
	{
		for (j=0;j<p;j++)
			printf("%d ",C[i][j]);
		printf("\n");
	}
	
	return 0;
}

void matrix(int m, int n, int p, int A[][n], int B[][p], int C[][p])
{
	int i=0, j=0, k=0, l=0;
	int cal=0;

	for (i=0;i<m;i++)
	{
		for (j=0;i<p;j++)
		{
			for (k=0;k<p;k++)
			{
				for (l=0;l<n;l++)
					cal+=A[l][k]*B[k][l];
			}
			C[i][j]=cal;
		}
	}
}
