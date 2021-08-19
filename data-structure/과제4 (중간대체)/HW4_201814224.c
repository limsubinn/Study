#include <stdio.h>
#include <string.h>
#include "ArrayBaseStack.h"
#define MAX 1000

/*
 자료구조및알고리즘 중간대체과제

 이름: 임수빈
 학번: 201814224
 프로그램 작성일: 2021-05-02
 프로그램 설명: 텍스트 T에서 A라는 단어를 다음과 같은 알고리즘을 이용해서 제거
            1. T에 A가 없으면 알고리즘 종료
            2. T에서 처음 등장하는 A 삭제
            3. T에 A가 없으면 알고리즘 종료
            4. T에서 마지막으로 등장하는 A 삭제
            5. 1번으로 돌아감
*/

Stack arr_to_stack(char arr[MAX]) //배열을 스택으로 바꾸는 함수
{
    Stack stack;
    StackInit(&stack);
    
    long i;
    
    for (i=strlen(arr)-1;i>=0;i--) //사용자가 입력한 배열을 스택에 거꾸로 넣음
    {
        SPush(&stack, arr[i]);
    }
    
    return stack;
}

Stack censorship(Stack A1, Stack T1) //텍스트 T에서 단어 A를 삭제하는 알고리즘
{
    char data;
    
    int i;
    int flag=0; //처음 등장하는 A를 제거할지, 마지막으로 등장하는 A를 제거할지를 구분해주는 변수
    
    int num;
    num=A1.topIndex;
    
    char A_top;
    A_top=SPeek(&A1);
    
    Stack A2, T2;
    StackInit(&A2);
    StackInit(&T2);
    
    while (1)
    {
        if (flag==0) //T에서 처음 등장하는 A를 삭제하는 알고리즘 (없으면 종료)
        {
            if (SIsEmpty(&T1)) //T에 A가 없기 때문에 알고리즘 종료
            {
                while (!SIsEmpty(&T2))
                {
                    data=SPop(&T2);
                    SPush(&T1,data);
                }
                
                break;
            }
            
            else if (SPeek(&A1)==SPeek(&T1))
            {
                data=SPop(&A1);
                SPush(&A2,data);
        
                data=SPop(&T1);
                SPush(&T2,data);
            
                if (SIsEmpty(&A1)) //A의 모든 단어가 T에서 일치할 때
                {
                    flag=1;
                    A_top=SPeek(&A2);
                    
                    for (i=0;i<=num;i++) //T에서 A 제거
                    {
                        SPop(&T2);
                    }
                
                    while(!SIsEmpty(&T1)) //T1의 모든 단어를 T2로 옮김 (다음 알고리즘으로 넘어가기 위해)
                    {
                        data=SPop(&T1);
                        SPush(&T2,data);
                    }
                }
            }
            
            else if ((SPeek(&T1)==A_top) && (SPeek(&A1)!=A_top))
            {
                data=SPop(&T1);
                SPush(&T2,data);
            }

            else //if (SPeek(&A1)!=SPeek(&T1))
            {
                data=SPop(&T1);
                SPush(&T2,data);
            
                while (!SIsEmpty(&A2))
                {
                    data=SPop(&A2);
                    SPush(&A1,data);
                }
            
                if (SIsEmpty(&T1)) //T에 A가 없기 때문에 알고리즘 종료
                {
                    while (!SIsEmpty(&T2))
                    {
                        data=SPop(&T2);
                        SPush(&T1,data);
                    }
                
                    break;
                }
            }
        }
    
    
        if (flag==1) //T에서 마지막으로 등장하는 A를 삭제하는 알고리즘 (없으면 종료)
        {
            if (SIsEmpty(&T2)) //T에 A가 없기 때문에 알고리즘 종료
            {
                break;
            }
            
            else if (SPeek(&A2)==SPeek(&T2))
            {
                data=SPop(&A2);
                SPush(&A1,data);
        
                data=SPop(&T2);
                SPush(&T1,data);
            
                if (SIsEmpty(&A2)) //A의 모든 단어가 T에서 일치할 때
                {
                    flag=0;
                    A_top=SPeek(&A1);
                    
                    for (i=0;i<=num;i++) //T에서 A 제거
                    {
                        SPop(&T1);
                    }
                
                    while(!SIsEmpty(&T2)) //T2의 모든 단어를 T1으로 옮김
                    {
                        data=SPop(&T2);
                        SPush(&T1,data);
                    }
                }
            }
            
            else if ((SPeek(&T2)==A_top) && (SPeek(&A2)!=A_top))
            {
                data=SPop(&T2);
                SPush(&T1,data);
            }
            
            else //if (SPeek(&A2)!=SPeek(&T2))
            {
                data=SPop(&T2);
                SPush(&T1,data);
            
                while (!SIsEmpty(&A1))
                {
                    data=SPop(&A1);
                    SPush(&A2,data);
                }
            
                if (SIsEmpty(&T2)) //T에 A가 없기 때문에 알고리즘 종료
                {
                    break;
                }
            }
        }
    }
    
    
    return T1;
}

int main()
{
    char arr_A[25];
    char arr_T[MAX];
    
    printf("제거할 단어 A를 입력하세요: ");
    scanf("%s",arr_A);
    
    printf("텍스트 T를 입력하세요: ");
    scanf("%s",arr_T);
    
    Stack A1;
    Stack T1;
    Stack result;
    
    A1=arr_to_stack(arr_A); //사용자가 입력한 단어를 스택으로 저장
    T1=arr_to_stack(arr_T); //사용자가 입력한 텍스트를 스택으로 저장
    result=censorship(A1,T1); //텍스트에서 단어를 제거하는 함수 호출
    
    
    printf("결과: ");
    while (!SIsEmpty(&result))
    {
        printf("%c",SPop(&result));
    }
    printf("\n");
    
    return 0;
}



