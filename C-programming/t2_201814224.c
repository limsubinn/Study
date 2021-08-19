/*
 이름: 임수빈
 학번: 201814224
 프로그램 작성일: 2020-07-02
 프로그램 설명: 재고 상품에 대한 정보를 구조체에 저장하여 출력
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct inventory {
	char *name;
	int quantity;
	double price;
	struct inventory *next_inventory;
} invent; //구조체 선언

int main()
{
	invent *one;
	invent *two;
	invent *three;
	//구조체 변수 선언

	one=(invent *)malloc(sizeof(invent));
	if (one==NULL)
	{
		printf("malloc 오류\n");
		return 0;
	}
	one->name=(char *)malloc(sizeof(char)*100);
	if (one->name==NULL)
	{
		printf("malloc 오류\n");
		return 0;
	}
	//구조체 one과 one->name 동적 메모리 할당

	two=(invent *)malloc(sizeof(invent));
	if (two==NULL)
	{
		printf("malloc 오류\n");
		return 0;
	}
	two->name=(char *)malloc(sizeof(char)*100);
	if (two->name==NULL)
	{
		printf("malloc 오류\n");
		return 0;
	}
	//구조체 two와 two->name 동적 메모리 할당

	three=(invent *)malloc(sizeof(invent));
	if (three==NULL)
	{
		printf("malloc 오류\n");
		return 0;
	}
	three->name=(char *)malloc(sizeof(char)*100);
	if (three->name==NULL)
	{
		printf("malloc 오류\n");
		return 0;
	}
	//구조체 three와 three->name 동적 메모리 할당

	one->next_inventory=two;
	two->next_inventory=three;
	three->next_inventory=NULL;
	//구조체 연결

	printf("첫 번째 재고의 정보를 입력하시오.\n");
	printf("이름: ");
	scanf("%s",one->name);
	printf("수량: ");
	scanf("%d",&one->quantity);
	printf("가격: ");
	scanf("%lf",&one->price);
	printf("-----------------------------------------------\n");

	printf("두 번째 재고의 정보를 입력하시오.\n");
	printf("이름: ");
	scanf("%s",two->name);
	printf("수량: ");
	scanf("%d",&two->quantity);
	printf("가격: ");
	scanf("%lf",&two->price);
	printf("-----------------------------------------------\n");

	printf("세 번째 재고의 정보를 입력하시오.\n");
	printf("이름: ");
	scanf("%s",three->name);
	printf("수량: ");
	scanf("%d",&three->quantity);
	printf("가격: ");
	scanf("%lf",&three->price);
	printf("\n");

	//one, two, three 구조체의 각 멤버에 재고의 정보 입력 받음

	printf("현재 재고는 다음과 같습니다.\n");
	printf("%s %d %.0lf\n", one->name, one->quantity, one->price);
	printf("%s %d %.0lf\n", one->next_inventory->name, one->next_inventory->quantity, one->next_inventory->price);
	printf("%s %d %.0lf\n", one->next_inventory->next_inventory->name,one->next_inventory->next_inventory->quantity, one->next_inventory->next_inventory->price);
	//구조체에 저장한 정보 출력

	free(one->name);
	free(one);

	free(two->name);
	free(two);

	free(three->name);
	free(three);

	//동적 메모리 해제

	return 0;
}



