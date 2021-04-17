#include "product.h"
#include "manager.h"
#include <stdlib.h>
#include <stdio.h>

int main(void)
{
        product *p[20];
        int menu, num, srchOption;
        int count = loadDataList(p);
        int index = count;
        //CREATE, READ, UPDATE, DELETE, SEARCH, SAVE, EXIT
        while(1)
        {
            #ifdef DEBUG
            printf("\n[DEBUG MODE]\n");
            printf("count = %d\n", count);
            printf("index = %d\n", index);
            #endif
                menu = selectMenu();
                switch(menu)
                {
                case 0:
                return 0;
                //CREATE
                case 1:
                if(count < 20)
                {
                    p[index] = (product*)malloc(sizeof(product));
                    count += createProduct(p[index++]);
                    printf("추가됨!\n");
                }
                else
                        printf("추가할 수 없습니다!\n");
                break;
                //READ
                case 2:
                if(count == 0)
                {
                    printf("데이터가 없습니다!\n");
                }
                else
                {
                    listProductList(p, index);
                }
                break;
                //UPDATE
                case 3:
                if(count == 0)
                        printf("데이터가 없습니다!\n");
                else
                {
                    num = selectDataNo(p, index);

                    if(num == 0)
                        printf("=> 취소됨!\n");
                    else
                        updateProduct(p[num-1]);
                }
                break;
                //DELETE
                case 4:
                        if(count == 0)
                                printf("데이터가 없습니다.\n");
                        else
                        {
                            num = selectDataNo(p, index);
                            if(deleteData(&p[num-1]))
                            {
                                     count--;
                                     printf("삭제됨!\n");

                                     if(count == 0)
                                        index = 0;
                             }
                            else
                                printf("취소됨!\n");
                        }
                break;
               //SEARCH
                case 5:
                if(count == 0)
                        printf("검색할 데이터가 없습니다!\n");
                else
                {
                        printf("\n***검색종류***\n");
                        printf("0.취소\n");
                        printf("1.이름 검색\n");
                        printf("2.설정 가격보다 낮은 가격만 검색\n");
                        printf("3.설정 별점만 검색\n");
                        printf("4.설정 리뷰수보다 높은 리뷰수만 검색\n");
                        printf("번호 선택: ");
                        scanf("%d", &srchOption);

                        switch(srchOption)
                        {
                            case 0:
                                    printf("취소됨!\n");
                                    break;
                            case 1:
                                    searchProductNameList(p, index);
                                    break;

                            case 2:
                                    searchProductPriceList(p, index);
                                    break;

                            case 3:
                                    searchProductStarsList(p, index);
                                    break;

                            case 4:
                                    searchProductReviewsList(p, index);
                                    break;

                            default:
                                    printf("다시 입력하세요!\n");
                                    break;
                        }
                }
                break;
                //SAVE
                case 6:
                {
                        if(count == 0)
                        {
                        // 데이터가 없는 상태에서 저장하는 경우 파일 삭제
                                printf("=> 저장됨!(데이터 없음)\n");
                                remove("product.txt");
                        }
                        else
                        {
                                FILE *ffrt=fopen("product.txt", "w");
                                if(ffrt == NULL)
                                        printf("ERROR!\n");
                                else
                                {
                                        saveDataList(ffrt, p, count, index);
                                        printf("저장됨!\n");
                                        fclose(ffrt);
                                }
                        }
                        break;
                }
                default:
                printf("다시 입력하세요!\n");
                break;
                }
        }
        for(int i=0; i< index; i++)
            free(p[i]);
        printf("종료됨!\n");
        return 0;
}
