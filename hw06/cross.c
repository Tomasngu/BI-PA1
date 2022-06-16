#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef int (*Comp)(const void *, const void *);

typedef struct{
    char *m_Line;
    size_t m_Cap;
    int m_Length;
} TLine;

typedef struct{
    TLine *m_Matrix;
    int m_Cap;
    int m_LineCount;
} TMatrix;

typedef struct{
    char *m_Word;
    int m_Len;
} TWord;

typedef struct{
    TWord *m_Words;
    int m_Cap;
    int m_WordCount;
} TWordsArr;

void arrPush(TWordsArr *words_array, char *str, int len){
    if(words_array->m_WordCount >= (words_array)->m_Cap){
        (words_array)->m_Cap = (words_array)->m_Cap*2 + 4;
        (words_array)->m_Words = (TWord *) realloc( (words_array)->m_Words, (words_array)->m_Cap * sizeof(*(words_array)->m_Words));
    }
    (words_array)->m_Words[((words_array)->m_WordCount)].m_Word = (char *) malloc((len + 1)*sizeof(char));
    // str[len] = '\0'; 
    //printf("Vkladam %s\n", str);
    strncpy((words_array)->m_Words[((words_array)->m_WordCount)].m_Word, str, len);
    (words_array)->m_Words[words_array->m_WordCount].m_Word[len] = '\0';
    (words_array)->m_Words[(words_array->m_WordCount)++].m_Len = len;
    //printf("word size %d\n", words_array->m_Words[words_array->m_WordCount -1].m_Len);
    //printf("Vlozeno %s\n", words_array->m_Words[words_array->m_WordCount - 1].m_Word);
}
int alreadyIn(TWordsArr *words_array, char *str, int len){
    for(int i = 0; i < words_array->m_WordCount; i++){
        if( (words_array->m_Words)[i].m_Len == len  && str[0] == (words_array->m_Words)[i].m_Word[0] && strcmp(str,words_array->m_Words[i].m_Word) == 0){
            return 1;
        }
    }
    return 0;
}

void printMatrix(TMatrix *matrix){
    for(int i = 0; i < matrix->m_LineCount; i++){
        printf("%s\n", (matrix->m_Matrix)[i].m_Line);
        // printf("Delka tohoto stringu je %d\n", (matrix->m_Matrix)[i].m_Length);
    }
    printf("pocet radku je %d\n", matrix->m_LineCount);
}

void printArray(TWordsArr *words_array){
    for(int i = 0; i < words_array->m_WordCount; i++){
        printf("prvek %s\n", words_array->m_Words[i].m_Word);
    }
    printf("pocet slov je %d\n", words_array->m_WordCount);
}

void LeftRight(TMatrix *matrix, TWordsArr *words_array, TWordsArr *repeated_words ){
    int length = matrix->m_LineCount;
    char *str = (char *) malloc((length + 1)*sizeof(*str));
    
    int len = 0;
    for(int row = 0; row < length; row++){
        for(int left = 0; left < length; left++ ){
            for(int right = left; right < length; right++ ){
                str[len] = matrix->m_Matrix[row].m_Line[right];
                len++;
                str[len] = '\0';
                // printf("%s\n", str);
                arrPush(words_array,str,len);
            }
            // printf("Delka je %zu\n", strlen(str));
            memset(str, 0, length +1);
            len = 0;
        }
    }    
    free(str);
}
void RightLeft(TMatrix *matrix, TWordsArr *words_array, TWordsArr *repeated_words){
    int length = matrix->m_LineCount;
    char *str = (char *) malloc((length + 1)*sizeof(*str));
    
    int len = 0;
    for(int row = 0; row < length; row++){
        for(int right = length -1 ; right >= 0 ; right-- ){
            for(int left = right; left >= 0; left-- ){
                str[len] = matrix->m_Matrix[row].m_Line[left];
                len++;
                // printf("%s\n", str);
                if(len>=2) arrPush(words_array, str, len);
                
            }
            memset(str, 0, length +1);
            len = 0;
        }
    }    
    free(str);
}

void UpDown(TMatrix *matrix, TWordsArr *words_array, TWordsArr *repeated_words){
    int length = matrix->m_LineCount;
    char *str = (char *) malloc((length + 1)*sizeof(*str));
    
    int len = 0;
    for(int col = 0; col < length; col++){
        for(int high = 0 ; high < length ; high++ ){
            for(int low = high; low < length; low++ ){
                str[len] = matrix->m_Matrix[low].m_Line[col];
                len++;
                str[len] = '\0';
                // printf("%s\n", str);
                if(len>=2) arrPush(words_array, str, len);
            }
            // printf("Delka je %zu\n", strlen(str));
            memset(str, 0, length +1);
            len = 0;
        }
    }    
    free(str);
}

void DownUp(TMatrix *matrix, TWordsArr *words_array, TWordsArr *repeated_words){
    int length = matrix->m_LineCount;
    char *str = (char *) malloc((length + 1)*sizeof(*str));
    
    int len = 0;
    for(int col = 0; col < length; col++){
        for(int low = length -1 ; low >= 0 ; low-- ){
            for(int high = low; high >= 0 ; high-- ){
                str[len] = matrix->m_Matrix[high].m_Line[col];
                len++;
                str[len] = '\0';
                // printf("%s\n", str);
                if(len>=2) arrPush(words_array, str, len);
            }
            // printf("Delka je %zu\n", strlen(str));
            memset(str, 0, length +1);
            len = 0;
        }
    }    
    free(str);
}

int inMatrix(int length, int row, int col){
    if (row >= 0 && row < length && col >= 0 && col < length) return 1;
    return 0;
}

void RightDown(TMatrix *matrix, TWordsArr *words_array, TWordsArr *repeated_words){
    int length = matrix->m_LineCount;
    char *str = (char *) malloc((length + 1)*sizeof(*str));
    
    int len = 0;
    for(int diff = -length + 1; diff < length; diff++){
        for(int high = 0; high < length; high++){
            if(!inMatrix(length, high, high - diff)) continue;
            for(int low = high; low < length; low++){
                if(!inMatrix(length, low, low - diff)){
                    //printf("Neprosel row:%d col:%d", row, row - diff);
                    //printf("\n");
                    continue;
                } 
                str[len] = matrix->m_Matrix[low].m_Line[low - diff];
                len++;
                str[len] = '\0';
                if(len>=2) arrPush(words_array, str, len);
            }
            memset(str, 0, length +1);
            len = 0;
        }
    }
    free(str);
}
void LeftUp(TMatrix *matrix, TWordsArr *words_array, TWordsArr *repeated_words){
    int length = matrix->m_LineCount;
    char *str = (char *) malloc((length + 1)*sizeof(*str));
    int len = 0;
    for(int diff = -length + 1; diff < length; diff++){
        for(int low = length -1; low >= 0; low--){
            if(!inMatrix(length, low, low - diff)) continue;
            for(int high = low; high >= 0; high--){
                if(!inMatrix(length, high, high - diff)){
                    //printf("Neprosel row:%d col:%d", row, row - diff);
                    //printf("\n");
                    continue;
                } 
                str[len] = matrix->m_Matrix[high].m_Line[high - diff];
                len++;
                str[len] = '\0';
                if(len>=2) arrPush(words_array, str, len);
            }
            memset(str, 0, length +1);
            len = 0;
        }
    }
    free(str);
}

void LeftDown(TMatrix *matrix, TWordsArr *words_array, TWordsArr *repeated_words){
    int length = matrix->m_LineCount;
    char *str = (char *) malloc((length + 1)*sizeof(*str));
    
    int len = 0;
    for(int sum = 0; sum < 2*(length-1) + 1; sum++){
        for(int high = 0; high < length; high++){
            if(!inMatrix(length, high, sum - high)) continue;
            for(int low = high; low < length; low++){
                if(!inMatrix(length, low, sum - low)){
                    //printf("Neprosel row:%d col:%d", row, row - diff);
                    //printf("\n");
                    continue;
                } 
                str[len] = matrix->m_Matrix[low].m_Line[sum - low];
                len++;
                str[len] = '\0';
                if(len>=2) arrPush(words_array, str, len);
            }
            memset(str, 0, length +1);
            len = 0;
        }
    }
    free(str);
}
void RightUp(TMatrix *matrix, TWordsArr *words_array, TWordsArr *repeated_words){
    int length = matrix->m_LineCount;
    char *str = (char *) malloc((length + 1)*sizeof(*str));
    int len = 0;
    for(int sum = 0; sum < 2*(length-1) + 1; sum++){
        for(int low = length -1; low >= 0; low--){
            if(!inMatrix(length, low, sum - low)) continue;
            for(int high = low; high >= 0; high--){
                if(!inMatrix(length, high, sum - high)){
                    //printf("Neprosel row:%d col:%d", row, row - diff);
                    //printf("\n");
                    continue;
                } 
                str[len] = matrix->m_Matrix[high].m_Line[sum - high];
                len++;
                str[len] = '\0';
                if(len>=2) arrPush(words_array, str, len);
            }
            memset(str, 0, length +1);
            len = 0;
        }
    }
    free(str);
}

int lexCmp(const TWord * aPtr, const TWord * bPtr){
    char *a = aPtr->m_Word; char *b = bPtr->m_Word;
    int val = strcmp(a,b);
    if(val == 0) return 0;
    if(val < 0) return -1;
    return 1;
}
void lexSort(TWordsArr *words_array){
    qsort(words_array->m_Words, words_array->m_WordCount, sizeof(* (words_array->m_Words)), (Comp) lexCmp);
}
int cmpbyLen(const TWord * aPtr, const TWord * bPtr){
    int a = aPtr->m_Len, b = bPtr->m_Len;
    return a == b ? 0 : (a < b ? 1 : -1); 
}
void findRepeats(TWordsArr * words_array, TWordsArr * repeated_words){
    int found = 0;
    for(int i = 0; i < words_array->m_WordCount - 1;i++){
        if((words_array->m_Words)[i].m_Word[0] == (words_array->m_Words)[i+1].m_Word[0] && strcmp(words_array->m_Words[i].m_Word,words_array->m_Words[i+1].m_Word) == 0){
            if(found) continue;
            found = 1;
            arrPush(repeated_words, words_array->m_Words[i].m_Word, words_array->m_Words[i].m_Len);
        } else {
            found = 0;
        }
    }

    return;
}
void SortByLen(TWordsArr *repeated_words){
    qsort(repeated_words->m_Words, repeated_words->m_WordCount, sizeof(* (repeated_words->m_Words)), (Comp) cmpbyLen);
}
void printBest(TWordsArr * repeated_words){
    if(repeated_words->m_WordCount == 0){
        printf("Zadne opakujici se slovo.\n");
        return;
    }
    int length = repeated_words->m_Words[0].m_Len; 
    int index = 0;
    printf("Nejdelsi opakujici se slova:\n");
    while(repeated_words->m_Words[index].m_Len == length){
        printf("%s\n", repeated_words->m_Words[index].m_Word);
        index++;
    }
    return;
}

int loadMatrix(TMatrix * matrix){
    TLine line = {};
    int length_flag = 1;
    int length = 0;
    while(getline(&line.m_Line, &line.m_Cap, stdin) > 0 ){
        //Reallocation if needed 
        if(matrix->m_LineCount >= matrix->m_Cap){
            matrix->m_Cap = matrix->m_Cap*2 + 4;
            matrix->m_Matrix = (TLine *) realloc(matrix->m_Matrix, matrix->m_Cap*sizeof(*matrix->m_Matrix)); 
        }
        // newline substitution.
        if((line.m_Line)[strlen(line.m_Line) - 1] == '\n'){
            (line.m_Line)[strlen(line.m_Line) - 1] = '\0';
        }
        line.m_Length = strlen(line.m_Line);
        // I/O Checks
        if(length_flag){
            length = line.m_Length;
            length_flag = 0;
        }
        // Lines have different lengths
        if(length != line.m_Length){
            free(line.m_Line);
            return 0;
        }
        //inserting line into matrix
        (matrix->m_Matrix)[matrix->m_LineCount] = line;
        (matrix->m_LineCount)++;
        
        //line nulling
        line.m_Line = NULL;
        line.m_Length = 0;
        line.m_Cap = 0;
    }
    // Checking if matrix is a square
    if(length != matrix->m_LineCount || length == 0){
        free(line.m_Line);
        return 0;
    }
    free(line.m_Line);
    return 1;
}

void freeArray(TWordsArr * array){
    for(int i = 0; i < array->m_WordCount; i++){
        free(array->m_Words[i].m_Word);
    }
    free(array->m_Words);
}

void freeMatrix(TMatrix * matrix){
    for(int i = 0; i < matrix->m_LineCount;i++){
        free(matrix->m_Matrix[i].m_Line);   
    }
    free(matrix->m_Matrix);
}

int main(void){
    TMatrix matrix = {};
    TWordsArr words_array = {};
    TWordsArr repeated_words = {};
    printf("Hlavolam:\n");
    if(!loadMatrix(&matrix)){
        printf("Nespravny vstup.\n");
        freeMatrix(&matrix);
        return 1;
    }
    //printMatrix(&matrix);
    
    LeftRight(&matrix, &words_array, &repeated_words);
    
    RightLeft(&matrix, &words_array, &repeated_words);
    
    UpDown(&matrix, &words_array, &repeated_words);
    DownUp(&matrix, &words_array, &repeated_words);
    
    RightDown(&matrix, &words_array, &repeated_words);
    LeftUp(&matrix, &words_array, &repeated_words);
    
    
    LeftDown(&matrix, &words_array, &repeated_words);
    RightUp(&matrix, &words_array, &repeated_words);
    
    
    // printf("arr size %d\n", words_array.m_WordCount);
    //printArray(&words_array);
    lexSort(&words_array);
    //printArray(&words_array);
    findRepeats(&words_array,&repeated_words);
    SortByLen(&repeated_words);
    //printArray(&repeated_words);
    printBest(&repeated_words);
    freeMatrix(&matrix);
    freeArray(&words_array);
    freeArray(&repeated_words);
    return 0;
}
