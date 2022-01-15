#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* C magic */
typedef int (*Comp)(const void *, const void *);

/* structure holding name of a products and number of them*/
typedef struct {
    char m_Name[100];
    int m_Amount; 
} TProduct;

/*Function comparing amounts of given products*/
int cmpProducts(const  TProduct * aPtr, const TProduct * bPtr){
    int a = aPtr -> m_Amount, b = bPtr -> m_Amount;
    return a == b ? 0 : (a < b ? 1 : -1); 
}
/*Function printing top N products and corresponding number of them 
Prints sum of amounts of those products at the end. */
void topProducts(TProduct * products_list, int watched, int uniq_count){
    
    qsort(products_list, uniq_count, sizeof(* products_list), (Comp) cmpProducts);
    int listed_products = 0;
    int order = 0; //Index of actual product
    int sum = 0;
    while(listed_products < watched){
        int range = 1; 
        while(order + 1 < uniq_count &&(products_list[order].m_Amount == products_list[order+1].m_Amount) ){
            range++;
            order++;
        }
        order += -range +1;
        if(range == 1){
            printf("%d. %s, %dx\n", listed_products+1, products_list[order].m_Name, products_list[order].m_Amount );
            listed_products += 1;
            sum += products_list[order].m_Amount;
            order += 1;
        } else {
            for(int i = 0; i < range;i++ ){
                printf("%d.-%d. %s, %dx\n", listed_products+1, listed_products+range, products_list[order].m_Name, products_list[order].m_Amount);
                sum += products_list[order].m_Amount;
                order += 1;
            }
            listed_products += range;
        }
        
        if(listed_products == uniq_count){
            break;
        }
    }
    printf("Nejprodavanejsi zbozi: prodano %d kusu\n", sum);
}
// The same thing as topProducts function without printing.
void printSum(TProduct * products_list, int watched, int uniq_count){
    qsort(products_list, uniq_count, sizeof(* products_list), (Comp) cmpProducts);
    int listed_products = 0;
    int order = 0;
    int sum = 0;
    while(listed_products < watched){
        int range = 1;
        while(order + 1 < uniq_count && (products_list[order].m_Amount == products_list[order+1].m_Amount) ){
            range++;
            order++;
        }
        order += -range +1;
        if(range == 1){
            listed_products += 1;
            sum += products_list[order].m_Amount;
            order += 1;
        } else {
            for(int i = 0; i < range;i++ ){
                sum += products_list[order].m_Amount;
                order += 1;
            }
            listed_products += range;
        }
        if(listed_products == uniq_count){
            break;
        }
    }
    printf("Nejprodavanejsi zbozi: prodano %d kusu\n", sum);
}
// Function which loads products into array of products
int loadProduct(TProduct ** products, int *prod_count, int  *capacity, int *uniq ){
    //Dynamic memory reallocation
    if(*prod_count >= *capacity) {
    *capacity = *capacity * 2 + 4;
    *products = (TProduct *) realloc(*products, *capacity * sizeof(** products));
    }
    char nazev[101];
    TProduct temp;
    int konverze1 = scanf("%100s", nazev);
    //Incorrect inputs checking
    if(strlen(nazev) > 99 || konverze1 != 1){
        return 0;
    }
    for(int i = 0; i < *prod_count;i++){
    if(strcmp(nazev,(*products)[i].m_Name) == 0){
        (*products)[i].m_Amount++;
        (*prod_count)++;
        return 1;
        }
    }
    strcpy(temp.m_Name, nazev);
    temp.m_Amount = 1; 
    (*products)[*uniq] = temp;
    (*prod_count)++;
    (*uniq)++;
    return 1;
}

int main (void){
    int watched;
    /*I/O checking */
    printf("Pocet sledovanych:\n");
    int res = scanf(" %d", &watched);
    if(res != 1 || watched <= 0){
        printf("Nespravny vstup.\n");
        return 1;
    }
    printf("Pozadavky:\n");
    char sign;
    TProduct * products = NULL;
    int prod_count = 0, capacity = 0;
    int uniq = 0;
    while(scanf(" %c", &sign) == 1){
        switch (sign){
            case '+':
                if(!loadProduct(&products, &prod_count, &capacity, &uniq)){
                    printf("Nespravny vstup.\n");
                    free(products);
                    return 1;
                }
                break;
            case '#':
                if(uniq == 0){
                    printf("Nejprodavanejsi zbozi: prodano 0 kusu\n");
                } else {
                    topProducts(products, watched, uniq);
                }
                break;
            case '?':
                if(uniq == 0){
                    printf("Nejprodavanejsi zbozi: prodano 0 kusu\n");
                } else {
                    printSum(products, watched, uniq);
                }
                break;
            default: 
                printf("Nespravny vstup.\n");
                free(products);
                return 1;

        }
    }
    if(!feof(stdin)) {
        printf("Nespravny vstup.\n");
        free(products);
        return 1;
    }
    free(products);
    return 0;
}
