#include<stdio.h>
#include<stdlib.h>

typedef int (*Comp)(const void *, const void *);

int cmpNum(const int* a, const int* b){
    if(*a == *b) return 0;
    if(*a > *b) return -1;
    return 1;
}

void cubesSort(int * cubes, int num){
    qsort(cubes, num , sizeof(*cubes), (Comp) cmpNum );
}
int countDup(int *cubes, int towerPos){
    int duplicates = 1;
    while(cubes[towerPos] == cubes[towerPos+1]){
        duplicates++;
        towerPos++;
    }
    return duplicates;
}

void printTower(int * tower, int num){
    int end = -1;
    for(int i = num-1; i>=0;i--){
        if(tower[i] != 0) {
            end = i;
            break;
        }
    }
    for(int i = 0; i <= end;i++){
        if(tower[i]==0) continue;
        if(i==end){
            printf("%d",tower[i]);
        } else {
            printf("%d, ", tower[i]);
        }
    }
    if(end != -1) printf("\n");
}

void recursion(int * cubes, int num, int *tower, int towerPos,int *count){
    if(towerPos == num){
        printTower(tower,num);
        (*count)++;
        return;
    }
    int dup_count = countDup(cubes,towerPos);
    for(int i = dup_count; i >= 0; i--){
        for(int j = towerPos; j < towerPos+i;j++){
            tower[j] = cubes[j];
        }
        for(int j = towerPos+i;j < towerPos+dup_count;j++){
            tower[j] = 0;
        }
        recursion(cubes, num, tower, towerPos+dup_count,count);
    }
    
    
    
}
/*
void printrec(int * cubes, int num){
    for(int i = 0; i < num; i++){
        // printf("%d ",cubes[i]);
        recursion(cubes,num);
    }
}
*/
int main(void){
    int num;
    printf("Pocet kostek:\n");
    int res = scanf(" %d", &num);
    if(res != 1 || num <= 0){
        printf("Nespravny vstup.\n");
        return 1;
    }
    printf("Velikosti:\n");

    int *cubes = (int *) calloc((num+1),sizeof(*cubes));
    for(int i = 0; i < num; i++){
        int con = scanf(" %d",&cubes[i]);
        if(con != 1 || cubes[i] <= 0){
            printf("Nespravny vstup.\n");
            return 1;
        }
    }
    int *tower = (int *)calloc(num+1,sizeof(*tower));
    /*
    for(int i = 0; i < num;i++){
        printf("%d ", cubes[i]);
    }
    */
    int count = 0;
    cubesSort(cubes, num);
    
    recursion(cubes, num, tower, 0, &count);
    printf("Celkem: %d\n",count-1);
    free(tower);
    free(cubes);    
    return 0;
}
