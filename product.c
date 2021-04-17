#include <stdio.h>
#include <stdlib.h>
#include "product.h"

int createProduct(product *p)
{
    while(getchar() != '\n');
    printf("\n************상품 추가************\n");
    printf("(1/5) 이름은?\n");
    scanf("%[^\n]s", p->name);

    do
    {
        printf("(2/5) 무게는?(단위:kg)\n");
        scanf("%lf", &p->weight);
    }while(p->weight <= 0.0);

    do
    {
        printf("(3/5) 가격은?\n");
        scanf("%d", &p->price);
    }while(p->price < 0);

    do
    {
        printf("(4/5) 별점은?(1~5)\n");
        scanf("%d", &p->rating);
    }while(p->rating < 1 || p->rating > 5);

    do
    {
        printf("(5/5) 리뷰수는?\n");
        scanf("%d", &p->review);
    }while(p->review < 0);

    return 1;
}

// 하나의 상품 출력 함수
// 무게는 소수점 1자리까지만 출력한다.
void readProduct(product *p)
{
    printf("%-7s     %-.1lf(kg)        %-7d       %-7d  %-7d\n", p->name, p->weight, p->price, p->rating, p->review);
}

// 전체 등록된 상품 리스트를 출력하는 함수
void listProduct(void)
{
    printf("\n*****************상품 목록*********************************\n");
    printf("No   name      weight(kg)    price(won)   ratings   reviews\n");
    printf("***********************************************************\n");

}

// 이미 추가된 상품의 정보를 수정하는 함수
// 필요한 부분만 선택해서 수정할 수 있으며 유효하지 않은 값에 대한 예외 처리는 DO-WHILE문으로 다시 입력받도록 했다.
void updateProduct(product *p)
{
    while(1)
    {
        int num = 0;
        printf("\n************상품 수정************\n");
        printf("0. 취소\n");
        printf("1. 이름\n");
        printf("2. 무게\n");
        printf("3. 가격\n");
        printf("4. 별점\n");
        printf("5. 리뷰수\n");
        printf("수정할 정보: ");
        scanf("%d", &num);

        switch(num)
        {
            case 0:
                printf("=> 취소됨!\n");
                return ;

            case 1:
		while(getchar() != '\n');
                printf("수정할 이름은?\n");
		printf("%s => ", p->name);
		scanf("%[^\n]s", p->name);
                printf("=> 수정 성공!\n");
                break;

            case 2:
                do
                {
                    printf("수정할 무게는?(단위:kg)\n");
		    printf("%.1lf(kg) => ", p->weight);
                    scanf("%lf", &p->weight);
                } while(p->weight <= 0.0);
                printf("=> 수정 성공!\n");
                break;

            case 3:
                do
                {
                    printf("수정할 가격은?(0원 이상)\n");
		    printf("%d원 => ", p->price);
                    scanf("%d", &p->price);
                } while(p->price < 0);
                printf("=> 수정 성공!\n");
                break;

            case 4:
                do
                {
                    printf("수정할 별점은?(1점~5점)\n");
		    printf("%d점 => ", p->rating);
                    scanf("%d", &p->rating);
                } while(p->rating < 1 || p->rating > 5);
                printf("=> 수정 성공!\n");
                break;

            case 5:
                do
                {
                    printf("수정할 리뷰수는?\n");
		    printf("%d개 => ", p->review);
                    scanf("%d", &p->review);
                } while(p->review < 0);
                printf("=> 수정 성공!\n");
                break;

            default:
                printf("다시 입력하세요.\n");
                break;
        }
    }
}

// 상품을 삭제할지 묻고 그 선택값을 반환하는 함수
// 1을 반환할 경우 메인 함수에서 구조체 멤버인 이름 배열에 '\0' 삽입하고 count = 0 할당 
// 0을 반환할 경우 삭제 취소 메시지 출력
int deleteData(product **p)
{
    int num = 0;

    while(1)
    {
        printf("정말로 삭제하시겠습니까?(삭제:1,취소:0) ");
        scanf("%d", &num);

        switch(num)
        {
            // main() 함수에서 삭제 메시지 출력
            case 1:
             *p = NULL;
	     free(*p);
             return 1;
            
            // main() 함수에서 취소 메시지 출력
            case 0:
                return 0;   
            
            default:
                printf("유효하지 않은 값입니다. 다시 입력하세요.\n");
                break;
        }
    }
}
/*
// 외부의 텍스트 파일을 불러와서 상품 리스트에 추가하는 함수
// 파일을 성공적으로 불러온 경우 불러온 데이터 개수를 반환하여 인덱스(No)가 해당 값부터 시작하도록 한다.
int loadData(product *p) 
{
    FILE* ffrt = fopen("product.txt", "r");
    if(ffrt == NULL)
    {
        printf("=> 파일 없음!\n");
        return 0;
    }
    else
    {
    	        fscanf(ffrt, "%s %lf %d %d %d", p->name, &p->weight, &p->price, &p->rating, &p->review);
		fclose(ffrt);
    		printf("=> 로딩 성공!\n");
    		return (p->name[0] == '\0' ? 0 : 1);
    }
}

// 상품 리스트를 외부의 파일에 저장하는 함수
void saveData(FILE* ffrt, product *p)
{
	if(p->name[0] != '\0')
        	fprintf(ffrt, "%s %.1f %d %d %d", p->name, p->weight, p->price, p->rating, p->review);
}

// 상품 이름을 검색하여 관련있는 상품을 출력하는 함수
void searchProductName(product *p)
{
    char search[20];
    int noResult = 1;   // 사용자가 입력한 조건에 맞는 상품이 없는 경우 데이터 없음 메시지 출력
	
	while(getchar()!='\n');
    printf("검색할 이름 : ");
    scanf("%[^\n]s", search);
	
	listProduct();

        if(strstr(p->name, search))
        {
            readProduct(p);
            noResult = 0;
        }
    if(noResult)
        printf("=> 검색된 데이터가 없습니다!\n");
}

// 가격 기준으로 검색
// 사용자가 입력한 가격을 기준으로 낮은 가격의 상품은 모두 출력
void searchProductPrice(product *p)
{
    int max;
    int noResult = 1; // 사용자가 입력한 조건에 맞는 상품이 없는 경우 데이터 없음 메시지 출력

    do
    {
        printf("검색할 상품의 최대 가격: ");
        scanf("%d", &max);
    }while(max < 1);

	listProduct();

        if(p->price <= max)
        {
            readProduct(p);
            noResult = 0;
        }
    if(noResult)
        printf("검색된 데이터가 없습니다!\n");
}

// 별점 기준으로 검색
// 사용자가 입력한 별점을 기준으로 해당 별점이상의 상품은 모두 출력
void searchProductStars(product *p)
{
    int stars;
    int noResult = 1; // 사용자가 입력한 조건에 맞는 상품이 없는 경우 데이터 없음 메시지 출력

    do
    {
        printf("검색할 상품의 별점: ");
        scanf("%d", &stars);
    }while(stars < 1 || stars > 5);

	listProduct();

        if(p->rating >= stars)
        {
            readProduct(p);
            noResult = 0;
        }
    if(noResult)
        printf("검색된 데이터가 없습니다!\n");
}

// 리뷰수 기준으로 검색
// 사용자가 입력한 리뷰수를 기준으로 해당 리뷰수보다 많은 리뷰수를 가진 상품 출력
void searchProductReviews(product *p)
{
    int min;
    int noResult = 1;

    do
    {
        printf("검색할 상품의 최소 리뷰수: ");
        scanf("%d", &min);
    }while(min < 1);

	listProduct();

        if(p->review >= min)
        {
            readProduct(p);
            noResult = 0;
        }
    if(noResult)
        printf("검색된 데이터가 없습니다!\n");
}
*/
int selectMenu(void)
{
    int menu;
    printf("\n*** Fruit Shop ***\n");
    printf("1. 메뉴추가\n");
    printf("2. 메뉴조회\n");
    printf("3. 메뉴수정\n");
    printf("4. 메뉴삭제\n");
    printf("5. 메뉴검색\n");
    printf("6. 파일저장\n");
    printf("0. 종료\n\n");
    printf("=> 원하는 메뉴는? ");
    scanf("%d", &menu);
    return menu;
}
