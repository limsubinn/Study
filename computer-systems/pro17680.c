/*
컴퓨터구조 과제2
비주얼스튜디오로 작성했습니다.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define CACHE_HIT 1
#define CACHE_MISS 5

int main()
{
	int cacheSize;
	char arr[2000];
	char* cities[100] = { "" };
	char algorithm[10];
	//문제에서 주어진대로 배열의 크기를 설정하면 오류가 나서 더 작은 숫자를 임의로 설정했습니다.

	printf("캐시 크기를 입력하세요(0~30): ");
	scanf("%d", &cacheSize);

	char** cache = malloc(21 * sizeof(sizeof(char*)));
	int i = 0;
	for (i = 0;i < 21;i++)
	{
		cache[i] = malloc(cacheSize * sizeof(char));
	}
	if (cache == NULL)
	{
		printf("malloc 실패\n");
		return 0;
	}
	for (i = 0;i < cacheSize;i++)
	{
		cache[i] = NULL;
	}

	printf("도시 이름을 입력하세요: ");
	scanf("%s", arr);
	
	char delimiter[] = ",";
	char* token;
	token = strtok(arr, delimiter);

	int citySize = 0;
	for (i = 0;token != NULL;i++)
	{
		cities[i] = token;
		citySize++;
		token = strtok(NULL, delimiter);
	}
	//입력받은 문자열을 쉼표로 구분하여 cities에 저장

	while (1)
	{
		printf("메모리 교체 알고리즘을 선택하세요(LRU/FIFO): ");
		scanf("%s", algorithm);
		if ((strcmp(algorithm, "LRU") == 0) || (strcmp(algorithm, "FIFO") == 0)) break;
		else printf("LRU와 FIFO 중 하나를 입력해야 합니다.\n");
	}
	
	int j = 0, k = 0;
	int time = 0;

	int* use; //LRU 알고리즘을 위한 사용 빈도수 계산
	use = (int*)malloc(cacheSize * sizeof(int));
	if (use == NULL)
	{
		printf("malloc 실패\n");
		return 0;
	}
	for (i = 0;i < cacheSize;i++)
	{
		use[i] = 0;
	}

	int* recent; //FIFO 알고리즘을 위한 사용 순서 계산
	recent = (int*)malloc(cacheSize * sizeof(int));
	if (recent == NULL)
	{
		printf("malloc 실패\n");
		return 0;
	}
	for (i = 0;i < cacheSize;i++)
	{
		recent[i] = 0;
	}

	for (i = 0;i < citySize;i++)
	{
		printf("\n\n단계: %d\n", i);
		printf("찾고자 하는 도시: %s\n", cities[i]);
		
		if (cacheSize == 0)
		{
			printf("cache miss!\n");
			time += CACHE_MISS;
		}
		else
		{ 
			for (j = 0;j < cacheSize;j++)
			{
				if (cache[j] == NULL)
				{
					cache[j] = cities[i];
					use[j] += 1;
					recent[j] += 1;
					printf("cache miss!\n");
					time += CACHE_MISS;
					break;
				}
				else
				{
					if (_strcmpi(cities[i], cache[j]) == 0)
					{
						use[j] += 1;
						time += CACHE_HIT;
						printf("cache hit!\n");
						break;
					}
				}

				if (j == cacheSize - 1) //캐시가 꽉 차 있고, cities와 같은 문자열이 캐시에 존재하지 않을 때
				{
					if (strcmp(algorithm, "LRU") == 0) //LRU 알고리즘
					{
						int min = use[0];
						int index = 0;
						for (k = 0;k < cacheSize;k++)
						{
							if (min > use[k])
							{
								min = use[k];
								index = k;
							}
						}
						cache[index] = cities[i];
						use[index] = min + 1;
					}
					else if (strcmp(algorithm, "FIFO") == 0) //FIFO 알고리즘
					{
						int min = recent[0];
						int index = 0;
						for (k = 0;k < cacheSize;k++)
						{
							if (min > recent[k])
							{
								min = use[k];
								index = k;
							}
						}
						cache[index] = cities[i];
						recent[index] = min + 1;
					}
					time += CACHE_MISS;
					printf("cache miss!\n");
					break;
				}
			}
		}

		printf("현재 캐시의 상태: ");
		for (j = 0;j < cacheSize;j++)
		{
			if (cache[j] == NULL)
				printf("비어있음 ");
			else
				printf("%s ", cache[j]);
		}
	}

	printf("\n\n\n총 실행시간: %d\n", time);

	free(cache);
	free(use);
	free(recent);
	return 0;
}


