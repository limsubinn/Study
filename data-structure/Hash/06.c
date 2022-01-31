#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "LinkedList.h"

#define MAX 10000
#define SNUM 500 //배열의 크기 임의로 설정

/*
 자료구조및알고리즘
 
 프로그램 작성일: 2021-06-03
 프로그램 설명: 장르 별로 가장 많이 재생된 노래를 두 개씩 모아 베스트 앨범 출시
            1. 속한 노래가 많이 재생된 장르 먼저 수록
            2. 장르 내 많이 재생된 노래 먼저 수록
            3. 장르 내 재생 횟수가 같으면 고유 번호가 낮은 노래 먼저 수록
 */

typedef struct _priority
{
    int plays;
    int index;
} Priority; //노래의 재생 횟수와 각 인덱스를 저장

typedef struct _song
{
    char *genres;
    int sum;
    Priority first;
    Priority second;
} Song; //노래의 장르, 총합, 우선순위에 따라 두 곡 저장

int makeArray(char *in_genres, char *in_plays, char **genres, int *plays)
//in_genres, in_plays에서 토큰을 분리하여 각각 genres, plays에 저장하고 노래의 총 개수를 리턴
{
    int i;
    int cnt=0; //입력 받은 모든 곡의 개수를 저장하기 위한 변수

    char *token;
    token = strtok(in_genres,"[]\",\n");

    for (i=0; token!=NULL; i++)
    {
        genres[i]=token;
        cnt++;
        token=strtok(NULL, "[]\",\n");
    }

    token = strtok(in_plays, "[]\",\n");
    
    for (i=0; token!=NULL; i++)
    {
        plays[i]=atoi(token);
        token=strtok(NULL, "[]\",\n");
    }
    
    return cnt;
}


List solution(char **genres, int *plays, int cnt)
{
    Song song[cnt]; //노래의 장르별로 재생횟수의 총합과 우선순위에 따른 두 곡 저장
    
    song[0].genres = genres[0];
    song[0].sum = plays[0];
    song[0].first.plays = plays[0];
    song[0].first.index = 0;
    song[0].second.plays = 0;
    song[0].second.index = 0;
    
    int i, j;
    int num = 0;
    int arrayNum = num;
    
    for (i=1; i<cnt; i++)
    {
        for (j=0; j<=arrayNum; j++)
        {
            
            if ((j==arrayNum) && (strcmp(genres[i],song[j].genres))!=0)
            {
                num++;
                song[num].genres = genres[i];
                song[num].sum = plays[i];
                song[num].first.plays = plays[i];
                song[num].first.index = i;
                song[num].second.plays = 0;
                song[num].second.index = 0;
            }
            
            if (strcmp(genres[i],song[j].genres)==0)
            {
                song[j].sum += plays[i];
                
                if (plays[i] > song[j].first.plays)
                {
                    song[j].second.plays = song[j].first.plays;
                    song[j].second.index = song[j].first.index;
                    song[j].first.plays = plays[i];
                    song[j].first.index = i;
                }
                else if (plays[i] == song[j].first.plays)
                {
                    if (plays[i] > song[j].second.plays)
                    {
                        song[j].second.plays = plays[i];
                        song[j].second.index = i;
                    }
                }
                else
                {
                    if (plays[i] > song[j].second.plays)
                    {
                        song[j].second.plays = plays[i];
                        song[j].second.index = i;
                    }
                }
                
                arrayNum=j;
            }
        }
        arrayNum=num;
    }
    
    int sumArr[num+1];
    int data;
    
    for (i=0; i<=num; i++) //각 장르의 총합만을 차례대로 저장
    {
        sumArr[i]=song[i].sum;
    }
 
    
    for (i=1; i<=num; i++) //삽입정렬 -> 내림차순으로 저장
    {
        data = sumArr[i];
        
        for (j=i-1; j>=0; j--)
        {
            if (data > sumArr[j])
                sumArr[j+1] = sumArr[j];
            else
                break;
        }
        
        sumArr[j+1] = data;
    }
    
    
    List list; //베스트 앨범에 수록할 노래의 인덱스를 순서대로 저장
    ListInit(&list);
    
    for (i=0; i<=num; i++)
    {
        for (j=0; j<=num; j++)
        {
            if (sumArr[i] == song[j].sum)
            {
                LInsert(&list, song[j].first.index);
                if (song[j].second.plays > 0) LInsert(&list, song[j].second.index);
                break;
            }
        }
    }
    
    return list;
}

int main(void) {
    
    char in_genres[MAX];
    char in_plays[MAX];
    
    printf("genres: ");
    scanf("%s", in_genres);
    
    printf("plays: ");
    scanf("%s", in_plays);
    
    char *genres[SNUM];
    int plays[SNUM];
    
    int cnt;
    cnt = makeArray(in_genres, in_plays, genres, plays);
    
    List answer;
    int index;
    
    answer = solution(genres, plays, cnt);
    
    printf("best album: [");
    if (LFirst(&answer, &index))
    {
        printf("%d",index);
        
        while (LNext(&answer, &index))
        {
            printf(",%d",index);
        }
    }
    printf("]\n");
    
    return 0;
}
