/*
��ǻ�ͱ��� ����2
���־�Ʃ����� �ۼ��߽��ϴ�.
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
	//�������� �־������ �迭�� ũ�⸦ �����ϸ� ������ ���� �� ���� ���ڸ� ���Ƿ� �����߽��ϴ�.

	printf("ĳ�� ũ�⸦ �Է��ϼ���(0~30): ");
	scanf("%d", &cacheSize);

	char** cache = malloc(21 * sizeof(sizeof(char*)));
	int i = 0;
	for (i = 0;i < 21;i++)
	{
		cache[i] = malloc(cacheSize * sizeof(char));
	}
	if (cache == NULL)
	{
		printf("malloc ����\n");
		return 0;
	}
	for (i = 0;i < cacheSize;i++)
	{
		cache[i] = NULL;
	}

	printf("���� �̸��� �Է��ϼ���: ");
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
	//�Է¹��� ���ڿ��� ��ǥ�� �����Ͽ� cities�� ����

	while (1)
	{
		printf("�޸� ��ü �˰����� �����ϼ���(LRU/FIFO): ");
		scanf("%s", algorithm);
		if ((strcmp(algorithm, "LRU") == 0) || (strcmp(algorithm, "FIFO") == 0)) break;
		else printf("LRU�� FIFO �� �ϳ��� �Է��ؾ� �մϴ�.\n");
	}
	
	int j = 0, k = 0;
	int time = 0;

	int* use; //LRU �˰����� ���� ��� �󵵼� ���
	use = (int*)malloc(cacheSize * sizeof(int));
	if (use == NULL)
	{
		printf("malloc ����\n");
		return 0;
	}
	for (i = 0;i < cacheSize;i++)
	{
		use[i] = 0;
	}

	int* recent; //FIFO �˰����� ���� ��� ���� ���
	recent = (int*)malloc(cacheSize * sizeof(int));
	if (recent == NULL)
	{
		printf("malloc ����\n");
		return 0;
	}
	for (i = 0;i < cacheSize;i++)
	{
		recent[i] = 0;
	}

	for (i = 0;i < citySize;i++)
	{
		printf("\n\n�ܰ�: %d\n", i);
		printf("ã���� �ϴ� ����: %s\n", cities[i]);
		
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

				if (j == cacheSize - 1) //ĳ�ð� �� �� �ְ�, cities�� ���� ���ڿ��� ĳ�ÿ� �������� ���� ��
				{
					if (strcmp(algorithm, "LRU") == 0) //LRU �˰���
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
					else if (strcmp(algorithm, "FIFO") == 0) //FIFO �˰���
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

		printf("���� ĳ���� ����: ");
		for (j = 0;j < cacheSize;j++)
		{
			if (cache[j] == NULL)
				printf("������� ");
			else
				printf("%s ", cache[j]);
		}
	}

	printf("\n\n\n�� ����ð�: %d\n", time);

	free(cache);
	free(use);
	free(recent);
	return 0;
}


