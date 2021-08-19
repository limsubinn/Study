#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "BinaryTree.h"
#define MAX 10000

/*
 자료구조및알고리즘 과제5 (main)
 
 이름: 임수빈
 학번: 201814224
 프로그램 작성일:2021-05-25
 프로그램 설명: (x,y) 좌표로 이루어진 노드들을 이진 트리에 추가하여 전위순회/후위순회의 방법으로 길 찾기
 */

void res(BTreeNode * bt) //전위순회
{
    if (bt)
    {
        printf("%d ",getVal(bt));
        res(bt->left);
        res(bt->right);
    }
}

void pos(BTreeNode * bt) //후위순회
{
    if(bt)
    {
        pos(bt->left);
        pos(bt->right);
        printf("%d ",getVal(bt));
    }
}

BTreeNode *makeTree(char nodeinfo[MAX]) //문자열 파싱하여 트리에 노드 삽입
{
    BTreeNode *bt=NULL;
    
    int x, y;
    int val=1;
    
    char *token;
    token=strtok(nodeinfo,"[,\n");
    
    while (1)
    {
        x=atoi(token);
        
        token=strtok(NULL,"],\n");
        
        if (token==NULL)
            break;
        
        y=atoi(token);
        
        bt=addNode(bt, x, y, val);
        val++;
        
        token=strtok(NULL,"[,\n");
    }
    
    return bt;
}

int findMax(BTreeNode *bt) //트리에서 y의 최대값 찾기
{
    int root, left, right;
    int max=0;
    
    if (bt!=NULL)
    {
        root=bt->y;
        left=findMax(bt->left);
        right=findMax(bt->right);
        
        if (left>right)
        {
            max=left;
        }
        else
        {
            max=right;
        }
        
        if (root>max)
        {
            max=root;
        }
    }
    
    return max;
}

BTreeNode *findNext(BTreeNode *bt, int max) //트리에 추가할 다음 노드 찾기
{
    BTreeNode *cn, *ln, *rn;
    BTreeNode *mn=NULL;
    
    if (bt!=NULL)
    {
        cn=bt;
        ln=findNext(bt->left, max);
        rn=findNext(bt->right, max);
        
        mn=NULL;
        
        if (getY(cn)==max)
        {
            mn=addNode(mn,cn->x,cn->y,cn->val);
        }
        
        else if (getY(ln)==max)
        {
            mn=addNode(mn,ln->x,ln->y,ln->val);
        }
        else if (getY(rn)==max)
        {
            mn=addNode(mn,rn->x,rn->y,rn->val);
        }
    }
    
    return mn;
}

BTreeNode *solution(BTreeNode *bt)
{
    int max;
    
    BTreeNode *nextNode=NULL;
    BTreeNode *root=NULL; //새로운 트리(정렬된 트리)
    
    while (bt!=NULL)
    {
        max=findMax(bt); //bt에서 y의 최대값 찾기
        
        nextNode=addNode(nextNode,findNext(bt,max)->x,findNext(bt,max)->y,findNext(bt,max)->val); //최대값(y)을 갖는 노드 찾기
        
        root=addNode(root,nextNode->x,nextNode->y,nextNode->val); //최대값(y)을 갖는 노드 트리에 추가
        
        BTreeNode *rm=NULL;
        rm=removeNode(&bt, nextNode->x, nextNode->y, nextNode->val); //bt에서 최대값(y)을 갖는 노드 삭제
        free(rm);
        
        removeNode(&nextNode, nextNode->x, nextNode->y, nextNode->val);
    }
    
    return root;
}

int main()
{
    char nodeinfo[MAX];
    
    printf("입력: ");
    scanf("%s",nodeinfo);
    
    BTreeNode *bt=makeTree(nodeinfo);
    bt=solution(bt);
   
    printf("출력: [");
    res(bt);
    printf(", ");
    pos(bt);
    printf("]\n");
    
    return 0;
}
