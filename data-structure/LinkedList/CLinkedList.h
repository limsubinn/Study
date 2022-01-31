#ifndef __C_LINKED_LIST_H__
#define __C_LINKED_LIST_H__

#define TRUE    1
#define FALSE    0

/*
 자료구조및알고리즘
 프로그램 작성일: 2021-04-11
*/

typedef char Data; //문자를 삽입할 것이기 때문에 char 타입

typedef struct _node
{
    Data data;
    struct _node * next;
} Node;

typedef struct _CLL
{
    Node * tail;
    Node * cur;
    Node * before;
    int numOfData;
} CList;


typedef CList List;

void ListInit(List * plist);
void LInsert(List * plist, Data data);
void LInsertFront(List * plist, Data data);

int LFirst(List * plist, Data * pdata);
int LNext(List * plist, Data * pdata);
void LRemove(List * plist); //반환값을 가지지 않을 것이기 때문에 void 타입
int LCount(List * plist);

//추가한 부분
void LChange(List * plist, Data data); //노드의 데이터를 변경할 함수

#endif
