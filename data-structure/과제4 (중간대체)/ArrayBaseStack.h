#ifndef __AB_STACK_H__
#define __AB_STACK_H__

#define TRUE    1
#define FALSE    0
#define STACK_LEN    100

/*
 자료구조및알고리즘 중간대체과제
 이름: 임수빈
 학번: 201814224
 프로그램 작성일: 2021-05-02
 */

typedef int Data;

typedef struct _arrayStack
{
    Data stackArr[STACK_LEN];
    int topIndex;
} ArrayStack;

typedef ArrayStack Stack;

void StackInit(Stack * pstack);
int SIsEmpty(Stack * pstack);

void SPush(Stack * pstack, Data data);
Data SPop(Stack * pstack);
Data SPeek(Stack * pstack);

#endif
