#include <stdio.h>
#include <stdlib.h>
#include "BinaryTree.h"

/*
 자료구조및알고리즘 과제5
 
 프로그램 작성일:2021-05-25
 프로그램 설명: (x,y) 좌표로 이루어진 노드들을 이진 트리에 추가하여 전위순회/후위순회의 방법으로 길 찾기
 */

BTreeNode *addNode(BTreeNode *bt, int x, int y, int val) //트리에 노드 추가
{
    if (bt==NULL)
    {
        bt=(BTreeNode*)malloc(sizeof(BTreeNode));
        
        bt->x=x;
        bt->y=y;
        
        bt->val=val;
        
        bt->left = NULL;
        bt->right = NULL;
    }
    
    else if (bt->x > x)
    {
        bt->left = addNode(bt->left, x, y, val);
    }
    
    else if (bt->x < x)
    {
        bt->right = addNode(bt->right, x, y, val);
    }
    
    return bt;
}

void SetData(BTreeNode *bt, int x, int y, int val)
{
    bt->x = x;
    bt->y = y;
    bt->val = val;
}

int getX(BTreeNode *bt)
{
    if (bt==NULL)
        return 0;
    
    return bt->x;
}

int getY(BTreeNode *bt)
{
    if (bt==NULL)
        return 0;
    
    return bt->y;
}

int getVal(BTreeNode *bt)
{
    return bt->val;
}

BTreeNode *GetLeftSubTree(BTreeNode *bt)
{
    return bt->left;
}

BTreeNode *GetRightSubTree(BTreeNode *bt)
{
    return bt->right;
}

BTreeNode *RemoveLeftSubTree(BTreeNode *bt)
{
    BTreeNode * delNode=NULL;

    if(bt != NULL) {
        delNode = bt->left;
        bt->left = NULL;
    }
    return delNode;
}

BTreeNode *RemoveRightSubTree(BTreeNode *bt)
{
    BTreeNode * delNode=NULL;

    if(bt != NULL) {
        delNode = bt->right;
        bt->right = NULL;
    }
    return delNode;
}

void ChangeLeftSubTree(BTreeNode *main, BTreeNode *sub)
{
    main->left = sub;
}
 
void ChangeRightSubTree(BTreeNode *main, BTreeNode *sub)
{
    main->right = sub;
}

BTreeNode *removeNode(BTreeNode **pRoot, int x, int y, int val)
{
    // 삭제 대상이 루트 노드인 경우를 별도로 고려해야 한다.

    BTreeNode * pVRoot = (BTreeNode*)malloc(sizeof(BTreeNode));    // 가상 루트 노드
    
    pVRoot->left = NULL;
    pVRoot->right = NULL;
    
    BTreeNode * pNode = pVRoot;    // parent node
    BTreeNode * cNode = *pRoot;    // current node
    BTreeNode * dNode;    // delete node

    // 루트 노드를 pVRoot가 가리키는 노드의 오른쪽 서브 노드가 되게 한다.
    ChangeRightSubTree(pVRoot, *pRoot);
    
    // 삭제 대상을 저장한 노드 탐색
    while(cNode != NULL && getX(cNode) != x)
    {
        pNode = cNode;
        
        if(x < getX(cNode))
            cNode = GetLeftSubTree(cNode);
        else
            cNode = GetRightSubTree(cNode);
    }

    if(cNode == NULL)    // 삭제 대상이 존재하지 않는다면,
        return NULL;

    dNode = cNode;    // 삭제 대상을 dNode가 가리키게 한다.

    // 첫 번째 경우: 삭제할 노드가 단말 노드인 경우
    if(GetLeftSubTree(dNode) == NULL && GetRightSubTree(dNode) == NULL)
    {
        if(GetLeftSubTree(pNode) == dNode)
            RemoveLeftSubTree(pNode);
        else
            RemoveRightSubTree(pNode);
    }

    // 두 번째 경우: 하나의 자식 노드를 갖는 경우
    else if(GetLeftSubTree(dNode) == NULL || GetRightSubTree(dNode) == NULL)
    {
        BTreeNode * dcNode;    // delete node의 자식 노드

        if(GetLeftSubTree(dNode) != NULL)
            dcNode = GetLeftSubTree(dNode);
        else
            dcNode = GetRightSubTree(dNode);

        if(GetLeftSubTree(pNode) == dNode)
            ChangeLeftSubTree(pNode, dcNode);
        else
            ChangeRightSubTree(pNode, dcNode);
    }

    // 세 번째 경우: 두 개의 자식 노드를 모두 갖는 경우
    else
    {
        BTreeNode * mNode = GetRightSubTree(dNode);    // mininum node
        BTreeNode * mpNode = dNode;    // mininum node의 부모 노드
        int delX;
        int delY;
        int delVal;

        // 삭제할 노드를 대체할 노드를 찾는다.
        while(GetLeftSubTree(mNode) != NULL)
        {
            mpNode = mNode;
            mNode = GetLeftSubTree(mNode);
        }
        
        // 대체할 노드에 저장된 값을 삭제할 노드에 대입한다.
        delX = getX(dNode);    // 대입 전 데이터 백업
        delY = getY(dNode);
        delVal = getVal(dNode);
        
        SetData(dNode, getX(mNode), getY(mNode), getVal(mNode));

        // 대체할 노드의 부모 노드와 자식 노드를 연결한다.
        if(GetLeftSubTree(mpNode) == mNode)
            ChangeLeftSubTree(mpNode, GetRightSubTree(mNode));
        else
            ChangeRightSubTree(mpNode, GetRightSubTree(mNode));

        dNode = mNode;
        SetData(dNode, delX, delY, delVal);    // 백업 데이터 복원
    }

    // 삭제된 노드가 루트 노드인 경우에 대한 처리
    if(GetRightSubTree(pVRoot) != *pRoot)
        *pRoot = GetRightSubTree(pVRoot);

    free(pVRoot);
    return dNode;
}

