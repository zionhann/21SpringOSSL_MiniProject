#include <stdio.h>
#include <stdlib.h>
#include "product.h"

void listProduct(product *p[], int index)
{
	
	listProduct();

    for(int i=0; i<index; i++)
    {
        if(p[i] == NULL)
            continue;
        printf("(%d) ", i+1);
        readProduct(p[i]);
    }  
    putchar('\n');
}

int selectDataNo(product *p[], int index)
{
    int num = 0;
    do
    {
        listProduct(p, index);

        printf("번호는 (취소 :0)? ");
        scanf("%d", &num);

    }while(num > index || num < 0 || p[num-1] == NULL);

    return num;
}

int loadData(product *p[]) 
{
    int c = 0;
    FILE* ffrt = fopen("product.txt", "r");
    if(ffrt == NULL)
    {
        printf("=> 파일 없음!\n");
        return 0;
    }
    else
    {
        for(int i=0; i<20; i++)
        {
            if(feof(ffrt) != 0)   //파일의 끝에 도달한 경우 불러온 데이터 개수를 할당후 반복문 종료
            {
                c = i;
		break;
            }
            p[i] = (product*)malloc(sizeof(product));
            fscanf(ffrt, "%s %lf %d %d %d", p[i]->name, &p[i]->weight, &p[i]->price, &p[i]->rating, &p[i]->review);
        }
        fclose(ffrt);
        printf("=> 로딩 성공!\n");
        return c;
    }
}

void saveData(FILE* ffrt, product *p[], int count, int index)
{
    count = count -1;
    for(int i=0; i<index; i++)
    {
        if(p[i]->name == NULL) 
            continue;
        fprintf(ffrt, "%s %.1f %d %d %d", p[i]->name, p[i]->weight, p[i]->price, p[i]->rating, p[i]->review);
        if(count) // 공백 출력
        {
            fputs("\n\n", ffrt);
            count--;
        }
    }
}

void searchProductName(product *p[], int index)
{
    char search[20];
    int noResult = 1;   // 사용자가 입력한 조건에 맞는 상품이 없는 경우 데이터 없음 메시지 출력

    printf("검색할 이름 : ");
    scanf("%s", search);

	listProduct();

    for(int i=0;i<index;i++)
    {
        if(p[i] == NULL) 
            continue;
        if(strstr(p[i]->name, search))
        {
            printf("(%d) ", i+1);
            readProduct(p[i]);
            noResult = 0;
        }
    }
    if(noResult)
        printf("=> 검색된 데이터 없음!\n");
}

void searchProductPrice(product *p[], int index)
{
    int max;
    int noResult = 1; // 사용자가 입력한 조건에 맞는 상품이 없는 경우 데이터 없음 메시지 출력

    do
    {
        printf("검색할 상품의 최대 가격: ");
        scanf("%d", &max);
    }while(max < 1);

	listProduct();

    for(int i=0; i< index; i++)
    {
        if(p[i] == NULL)
            continue;
        if(p[i]->price <= max)
        {
            printf("(%d) ", i+1);
            readProduct(p[i]);
            noResult = 0;
        }
    }
    if(noResult)
        printf("검색된 데이터가 없습니다!\n");
}

void searchProductStars(product *p[], int index)
{
    int stars;
    int noResult = 1; // 사용자가 입력한 조건에 맞는 상품이 없는 경우 데이터 없음 메시지 출력

    do
    {
        printf("검색할 상품의 별점: ");
        scanf("%d", &stars);
    }while(stars < 1 || stars > 5);

	listProduct();

    for(int i=0; i< index; i++)
    {
        if(p[i] == NULL)
            continue;
        if(p[i]->rating == stars)
        {
            printf("(%d) ", i+1);
            readProduct(p[i]);
            noResult = 0;
        }
    }
    if(noResult)
        printf("검색된 데이터가 없습니다!\n");
}

void searchProductReviews(product *p[], int index)
{
    int min;
    int noResult = 1;

    do
    {
        printf("검색할 상품의 최소 리뷰수: ");
        scanf("%d", &min);
    }while(min < 1);

	listProduct();

    for(int i=0; i< index; i++)
    {
        if(p[i] == NULL)
            continue;
        if(p[i]->review >= min)
        {
            printf("(%d) ", i+1);
            readProduct(p[i]);
            noResult = 0;
        }
    }
    if(noResult)
        printf("검색된 데이터가 없습니다!\n");
}
