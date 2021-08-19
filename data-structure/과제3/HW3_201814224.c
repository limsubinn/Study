#include <stdio.h>
#include <string.h>
#include "CLinkedList.h"

/*
 자료구조및알고리즘 과제3
 main

 이름: 임수빈
 학번: 201814224
 프로그램 작성일: 2021-04-11
 프로그램 설명: 사용자가 입력한 아이디를 리스트로 저장하여 7단계를 거친 후 추천 아이디 리턴
*/

List arr_to_list(char id[1000]) //사용자가 입력한 아이디를 연결리스트의 노드에 저장
{
    List list;
    ListInit(&list); //리스트 초기화
    
    int i;
    
    for (i=0;i<strlen(id);i++)
    {
        LInsert(&list, id[i]); //리스트에 삽입
    }
    
    return list;
}

List solution(List new_id) //7단계를 거친 후 추천 아이디 리턴
{
    int nodeNum;
    char data;
    int len=0; //리스트의 길이 계산
    int i,j;
    
    nodeNum=LCount(&new_id); //노드의 개수를 저장

    if (nodeNum!=0)
    {
        
        //1단계
        LFirst(&new_id,&data);
        if (data>='A' && data<='Z') //데이터가 대문자일 때
        {
            data=data+32; //소문자로 변환
            LChange(&new_id,data); //리스트의 노드 수정
        }
        
        for (i=0;i<nodeNum-1;i++)
        {
            LNext(&new_id,&data);
            if (data>='A' && data<='Z')
            {
                data=data+32;
                LChange(&new_id,data);
            }
        }
        
     
        
        //2단계
        LFirst(&new_id,&data);
        if (!((data>='a' && data<='z') || (data>=48 && data<=57) || (data=='.') || (data=='-') || (data=='_'))) //조건 외의 문자 제거
        {
            LRemove(&new_id);
        }
        
        for (i=0;i<nodeNum-1;i++)
        {
            LNext(&new_id,&data);
            if (!((data>='a' && data<='z') || (data>=48 && data<=57) || (data=='.') || (data=='-') || (data=='_')))
            {
                LRemove(&new_id);
            }
        }
        
        
        
        //3단계
        nodeNum=LCount(&new_id); //노드를 삭제했기 때문에 노드의 개수 변함
        
        LFirst(&new_id,&data);
        if (data=='.')
        {
            for(i=0; i<nodeNum-1; i++)
            {
                LNext(&new_id, &data);
                if (data=='.') //마침표가 2번 이상 연속된 경우
                {
                    LRemove(&new_id);
                }
                else //마침표가 2번 이상 연속되지 않은 경우
                {
                    break;
                }
            }
        }
        
        nodeNum=LCount(&new_id);
        
        LFirst(&new_id,&data);
        for (i=0;i<nodeNum-1;i++)
        {
            LNext(&new_id,&data);
            if (data=='.')
            {
                for(j=0; i<nodeNum-2; i++)
                {
                    LNext(&new_id, &data);
                    if (data=='.')
                    {
                        LRemove(&new_id);
                    }
                    else
                    {
                        break;
                    }
                    
                }
            }
        }
        
   
        
        //4단계
        nodeNum=LCount(&new_id);
        
        LFirst(&new_id,&data);
        if (data=='.') //리스트의 첫번째 노드가 마침표일 때
        {
            LRemove(&new_id);
        }
        
        if (nodeNum>=2)
        {
            
            for (i=0;i<nodeNum-1;i++)
            {
                LNext(&new_id,&data);
            }

            if (data=='.') //리스트의 마지막 노드가 마침표일 때
            {
                LRemove(&new_id);
            }
        }
        
        
        
        //5단계
        if (LFirst(&new_id,&data)==0) //리스트가 비어있을 때
        {
            data='a';
            LInsertFront(&new_id, data);
        }
        
        
        
        //6단계
        nodeNum=LCount(&new_id);
        
        LFirst(&new_id,&data);
        len++;
        
        for (i=0;i<nodeNum-1;i++)
        {
            LNext(&new_id,&data);
            len++;

            if (len>=16) //리스트의 노드의 개수가 16개 이상일 때
            {
                LRemove(&new_id);
            }
        }
        
        nodeNum=LCount(&new_id);
        
        if (len>=16)
        {
            LFirst(&new_id,&data);
 
            for (i=0;i<14;i++)
            {
                LNext(&new_id,&data);
            }
            if (data=='.') //제거 후 마침표가 리스트의 끝에 위치할 때
            {
                LRemove(&new_id);
            }
        }
        
        
        
        //7단계
        nodeNum=LCount(&new_id);
        
        if (nodeNum<3) //리스트의 노드의 개수가 3개 미만일 때
        {
            LFirst(&new_id,&data);
            
            if (nodeNum==1)
            {
                LInsert(&new_id,data);
                LInsert(&new_id,data);
                //맨 마지막 글자 2번 더 붙이기
            }
            else
            {
                LNext(&new_id,&data);
                LInsert(&new_id,data);
                //맨 마지막 글자 1번 더 붙이기
            }
        }
    }
    
    return new_id;
}

int main(void)
{
    char id[1000];
    char data;
    int i=0;
    
    printf("id를 입력하세요: ");
    scanf("%s",id);
    
    List new_id; //아이디를 저장할 리스트
    new_id=arr_to_list(id); //사용자가 입력한 배열을 리스트로 변환
    new_id=solution(new_id); //7단계를 거친 후의 추천 아이디
    
    printf("바뀐 아이디: ");
    if (LFirst(&new_id, &data)) //추천 아이디 출력
    {
        printf("%c", data);
            
        for(i=0; i<LCount(&new_id)-1; i++)
        {
            if(LNext(&new_id, &data))
                printf("%c", data);
        }
    }
    
    printf("\n");
    
    return 0;
}
