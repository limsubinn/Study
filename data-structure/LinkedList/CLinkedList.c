#include <stdio.h>
#include <stdlib.h>
#include "CLinkedList.h"

/*
 자료구조및알고리즘
 프로그램 작성일: 2021-04-11
*/

void ListInit(List * plist)
{
    plist->tail = NULL;
    plist->cur = NULL;
    plist->before = NULL;
    plist->numOfData = 0;
}

void LInsertFront(List * plist, Data data)
{
    Node * newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;

    if(plist->tail == NULL)
    {
        plist->tail = newNode;
        newNode->next = newNode;
    }
    else
    {
        newNode->next = plist->tail->next;
        plist->tail->next = newNode;
    }

    (plist->numOfData)++;
}

void LInsert(List * plist, Data data)
{
    Node * newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;

    if(plist->tail == NULL)
    {
        plist->tail = newNode;
        newNode->next = newNode;
    }
    else
    {
        newNode->next = plist->tail->next;
        plist->tail->next = newNode;
        plist->tail = newNode;
    }

    (plist->numOfData)++;
}

int LFirst(List * plist, Data * pdata)
{
    if(plist->tail == NULL)
        return FALSE;

    plist->before = plist->tail;
    plist->cur = plist->tail->next;

    *pdata = plist->cur->data;
    return TRUE;
}

int LNext(List * plist, Data * pdata)
{
    if(plist->tail == NULL)
        return FALSE;

    plist->before = plist->cur;
    plist->cur = plist->cur->next;

    *pdata = plist->cur->data;
    return TRUE;
}

void LRemove(List * plist) //삭제된 데이터를 리턴하지 않음
{
    Node * rpos = plist->cur;
//    Data rdata = rpos->data;

    if(rpos == plist->tail)
    {
        if(plist->tail == plist->tail->next)
            plist->tail = NULL;
        else
            plist->tail = plist->before;
    }

    plist->before->next = plist->cur->next;
    plist->cur = plist->before;

    free(rpos);
    (plist->numOfData)--;
//    return rdata;
}

int LCount(List * plist)
{
    return plist->numOfData;
}


//추가한 부분
void LChange(List * plist, Data data) //리스트의 노드를 수정
{
    Node * rpos = plist->cur; //없앨 데이터의 노드
    
    Node * changeNode = (Node*)malloc(sizeof(Node));
    changeNode->data = data;
    //새로운 노드를 할당하여 사용자로부터 입력받은 data의 값을 넣어줌
    
    changeNode->next = plist->cur->next;
    plist->before->next = changeNode;
    plist->cur = changeNode;
    //changeNode를 기존 리스트에 연결
    
    if (rpos == plist->tail) //없앨 데이터의 노드가 리스트의 tail을 가리킨다면
    {
        plist->tail = changeNode; //변경된 노드를 tail로 만들어줌
    }
    
    free(rpos);
}
    
