#include <stdio.h>
#define MAX 100

/*
 자료구조및알고리즘 과제2

 이름: 임수빈
 학번: 201814224
 프로그램 작성일: 2021-03-29
 프로그램 설명: n*n 행렬을 (n/2)*(n/2) 행렬 4개로 분할하여 재귀함수를 이용해 계산
*/

void cal(int n, int Arow, int Acol, int Brow, int Bcol, int A[MAX][MAX], int B[MAX][MAX], int C[MAX][MAX])
{
    if (n==1) //더이상 나눌 수 없을 때
    {
        C[Arow][Bcol]+=A[Arow][Acol]*B[Brow][Bcol];
        return;
    }
    
    
    //**************행렬을 4개로 분할**************//
    
    cal(n/2, Arow, Acol, Brow, Bcol, A, B, C);
    cal(n/2, Arow, Acol+n/2, Brow+n/2, Bcol, A, B, C);
    //c11=a11*b11+a12*b21 일반화

    cal(n/2, Arow, Acol, Brow, Bcol+n/2, A, B, C);
    cal(n/2, Arow, Acol+n/2, Brow+n/2, Bcol+n/2, A, B, C);
    //c12=a11*b12+a12*b22 일반화

    cal(n/2, Arow+n/2, Acol, Brow, Bcol, A, B, C);
    cal(n/2, Arow+n/2, Acol+n/2, Brow+n/2, Bcol, A, B, C);
    //c21=a21*b11+a22*b21 일반화

    cal(n/2, Arow+n/2, Acol, Brow, Bcol+n/2, A, B, C);
    cal(n/2, Arow+n/2, Acol+n/2, Brow+n/2, Bcol+n/2, A, B, C);
    //c22=a21*b12+a22*b22 일반화
}

int main()
{
    int n;
    printf("차수를 입력하세요: ");
    scanf("%d",&n); //행렬의 크기 입력받음
    
    int A[MAX][MAX];
    int B[MAX][MAX];
    int C[MAX][MAX];
    
    int i=0;
    int j=0;
    
    printf("\n행렬A를 입력하세요:\n");
    for (i=0;i<n;i++)
    {
        for (j=0;j<n;j++)
        {
            scanf("%d",&A[i][j]); //행렬 A 입력받음
        }
    }
    
    printf("\n행렬B를 입력하세요:\n");
    for (i=0;i<n;i++)
    {
        for (j=0;j<n;j++)
        {
            scanf("%d",&B[i][j]); //행렬 B 입력받음
        }
    }
    
    cal(n,0,0,0,0,A,B,C); //행렬의 곱셈 계산

    printf("\n결과:\n");
    for (i=0;i<n;i++)
    {
        for (j=0;j<n;j++)
        {
            printf("%d ",C[i][j]); //결과 출력
        }
        printf("\n");
    }

    return 0;
 }
