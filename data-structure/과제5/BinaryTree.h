#ifndef __BINARY_TREE_H__
#define __BINARY_TREE_H__

/*
 자료구조및알고리즘 과제5 (adt)
 
 이름: 임수빈
 학번: 201814224
 프로그램 작성일:2021-05-25
 프로그램 설명: (x,y) 좌표로 이루어진 노드들을 이진 트리에 추가하여 전위순회/후위순회의 방법으로 길 찾기
 */

typedef struct _bTreeNode //x, y와 val(노드번호)를 가짐
{
    int x;
    int y;
    
    int val;
    
    struct _bTreeNode * left;
    struct _bTreeNode * right;
} BTreeNode;

BTreeNode *addNode(BTreeNode *bt, int x, int y, int val);

void SetData(BTreeNode *bt, int x, int y, int val);

int getX(BTreeNode *bt);
int getY(BTreeNode *bt);
int getVal(BTreeNode *bt);

BTreeNode *GetLeftSubTree(BTreeNode *bt);
BTreeNode *GetRightSubTree(BTreeNode *bt);

BTreeNode *RemoveLeftSubTree(BTreeNode *bt);
BTreeNode *RemoveRightSubTree(BTreeNode *bt);

void ChangeLeftSubTree(BTreeNode *main, BTreeNode *sub);
void ChangeRightSubTree(BTreeNode *main, BTreeNode *sub);

BTreeNode *removeNode(BTreeNode **pRoot, int x, int y, int val);


#endif
