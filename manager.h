// 다중 데이터 관리 함수

#ifndef __MANAGER_H__
#define __MANAGER_H__
#include "product.h"

void listProductList(product *p[], int index);

// 사용자로부터 상품의 번호를 입력받아 번호를 반환하는 함수
// 상품 수정, 삭제 함수에서 쓰이며 입력받은 번호가 현재 인덱스를 넘어가거나 음수이거나 이미 삭제된 번호인 경우 다시 입력받도록 한다.
int selectDataNo(product *p[], int index);

// 외부의 텍스트 파일을 불러와서 상품 리스트에 추가하는 함수
// 파일을 성공적으로 불러온 경우 불러온 데이터 개수를 반환하여 인덱스(No)가 해당 값부터 시작하도록 한다.
int loadData(product *p[]);

// 상품 리스트를 외부의 파일에 저장하는 함수
void saveData(FILE* ffrt, product *p[], int count, int index);

// 검색
void searchProductName(product *p[], int index);

void searchProductPrice(product *p[], int index);

void searchProductStars(product *p[], int index);

void searchProductReviews(product *p[], int index);
#endif
