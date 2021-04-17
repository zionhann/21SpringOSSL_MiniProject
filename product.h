// 21800779 한시온
// OSSL Mini Project

#ifndef __PRODUCT_H__
#define __PRODUCT_H__

#include <stdio.h>
#include <string.h>

typedef struct
{
    char name[100];     // 상품 이름
    double weight;      // 상품 무게
    int price;          // 상품 가격
    int rating;         // 상품 별점
    int review;         // 상품 리뷰수(별점 개수)
}product;

// 상품을 추가하는 함수
// 음수 등 유효하지 않은 값이 입력되면 DO-WHILE문을 통해 다시 입력받도록 한다.
int createProduct(product *p);

// 하나의 상품 출력 함수
// 무게는 소수점 1자리까지만 출력한다.
void readProduct(product *p);

// 목록 리스트를 출력하는 함수
// 상품 리스트 출력은 listProduct 함수이다.
void printList(void);

// 사용자로부터 상품의 번호를 입력받아 번호를 반환하는 함수
// 상품 수정, 삭제 함수에서 쓰이며 입력받은 번호가 현재 인덱스를 넘어가거나 음수이거나 이미 삭제된 번호인 경우 다시 입력받도록 한다.
//int selectDataNo(product *p[], int index);

// 이미 추가된 상품의 정보를 수정하는 함수
// 필요한 부분만 선택해서 수정할 수 있으며 유효하지 않은 값에 대한 예외 처리는 DO-WHILE문으로 다시 입력받도록 했다.
void updateProduct(product *p);

// 상품을 삭제하는 함수
// 삭제: 해당 포인터 변수에 NULL을 할당하고 동적할당 해제, 1반환(count--;)
// 취소: 0반환(main함수에서 삭제 취소 메시지 출력)
int deleteData(product **p);

// 메뉴를 출력하는 함수
// CREATE, READ, UPDATE, DELETE, SEARCH, SAVE, EXIT
int selectMenu(void);
#endif
