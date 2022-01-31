#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"

/*
 자료구조및알고리즘
 프로그램 작성일: 2021-06-03
 
 결과를 출력하기 위해 사용할 리스트의 adt
 리스트의 초기화/삽입/조회 기능만을 구현
 */

void ListInit(List * plist) //리스트 초기화
{
    plist->head = NULL;
    plist->tail = NULL;
}

void LInsert(List * plist, LData data) //리스트 삽입 (꼬리에)
{
    Node * newNode = (Node*)malloc(sizeof(Node)); 
    newNode->data = data;
    newNode->next = NULL;
    
    if (plist->head==NULL) //리스트가 비어있을 때 (삽입 1회차)
        plist->head = newNode;
    else //리스트가 비어있지 않을 때 (삽입 2회차)
        plist->tail->next = newNode;
    
    plist->tail = newNode;
}

int LFirst(List * plist, LData * pdata) //리스트의 첫번째 데이터 조회
{
    if(plist->head == NULL)
        return FALSE;

    plist->cur = plist->head;

    *pdata = plist->head->data;
    return TRUE;
}

int LNext(List * plist, LData * pdata) //리스트의 두번째 데이터 조회
{
    if(plist->cur->next == NULL)
        return FALSE;

    plist->before = plist->cur;
    plist->cur = plist->cur->next;

    *pdata = plist->cur->data;
    return TRUE;
}
