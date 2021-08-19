#ifndef __LINKED_LIST_H__
#define __LINKED_LIST_H__

#define TRUE    1
#define FALSE    0

/*
 자료구조및알고리즘 과제6
 LinkedList.h

 이름: 임수빈
 학번: 201814224
 프로그램 작성일: 2021-06-03
 
 결과를 출력하기 위해 사용할 리스트의 adt
 리스트의 초기화/삽입/조회 기능만을 구현
 */

typedef int LData;

typedef struct _node
{
    LData data;
    struct _node * next;
} Node;

typedef struct _linkedList
{
    Node * head;
    Node * cur;
    Node * tail;
    Node * before;
} LinkedList;


typedef LinkedList List;

void ListInit(List * plist);
void LInsert(List * plist, LData data);

int LFirst(List * plist, LData * pdata);
int LNext(List * plist, LData * pdata);

#endif
