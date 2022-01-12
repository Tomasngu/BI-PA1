#include<stdio.h>
#define ID_LIMIT 100000
/**
 * Reads numbers from inputs into array 'accesses'. 
 * 
 * Reading is not successful if :  
 *      number is not an integer in given boundaries 
 *      'access_count' reaches 1 million.
 * Prints which access it is for given ID
 * Frequency of given numbers increments by 1 in array 'freq'
 * @param[out] freq array of frequencies of given ID
 * @param[out] accesses array of IDs
 * @param[in,out] access_count number of loaded IDs
 * @return 1 if reading successful, 0 otherwise
 */
int loadInput(int freq[], int accesses[], int *access_count){
    int id;
    int konverze1 = scanf(" %d", &id);
    if (konverze1 != 1 || id < 0 || id > 99999 || *access_count >= 1000000 ){
        return 0;
    }
    if(freq[id] == 0){
        printf("> prvni navsteva\n");
        freq[id]++;
    } else {
        printf("> navsteva #%d\n", freq[id]+1);
        freq[id]++;
    }
    accesses[*access_count] = id;
    (*access_count)++;
    return 1;
}
/**
 * Counts number of unique elements in a given range of array 'accesses'.
 * For each ID in given ranges writes into array 'isThere' 1 on a index ID.
 * Number of unique IDs is numbers of '1's in array 'isThere'.
 * @param[in] accesses array of IDs
 * @param[in] left starting index of a given range
 * @param[in] right ending index of a given range
 * @return number of unique numbers in array
 */
int countUniq(int accesses[], int left, int right){
	int uniq_count = 0;
    int isThere[ID_LIMIT] = {};
    for(int i = left; i <= right; i++){
        int id = accesses[i];
        isThere[id] = 1;
    }
    for(int i = 0; i < 100000; i++){
        if(isThere[i]) uniq_count++;
    }
	return uniq_count;	
}

/**
 * Reads two numbers defining a range and passes them to function 'countUniq'.
 * Reading is unsuccessful if numbers are not integers from a given range or if the second numbers is smaller.
 * Prints No. unique numbers in range with respect to length of the range.
 * @param[out] accesses array of IDs
 * @param[in,out] access_count number of loaded IDs
 * @return 1 if successful, 0 otherwise
 */
int loadQuery(int accesses[], int *access_count){
    int from, to;
    int konverze = scanf(" %d %d", &from, &to );
    if(konverze != 2 || from < 0 || to >= *access_count || from > to ){
        return 0;
    }
    int pocet = to - from +1;
    int uniq = countUniq(accesses, from, to);
    printf("> %d / %d\n", uniq, pocet);
    return 1;
}

int main(void){
    static int freq[ID_LIMIT];
    static int accesses[1000000];
    char sign;
    int access_count = 0;   
    printf("Pozadavky:\n");
    //Loads sign and procceds into switch corresponding to the sign. 
    // Program ends if unsuccessful 
    while(scanf(" %c", &sign) == 1){
        switch (sign){
            case '+':
                if(!loadInput(freq, accesses, &access_count )){
                    printf("Nespravny vstup.\n");
                    return 1;
                }
                break;
            case '?':
                if(!loadQuery(accesses, &access_count )){
                    printf("Nespravny vstup.\n");
                    return 1;
                }
                break;

            default:
                printf("Nespravny vstup.\n");
                return 1;
        }
    }
	if(!feof(stdin)){
        printf("Nespravny vstup.\n");
        return 1;
    } 
    return 0;
}
