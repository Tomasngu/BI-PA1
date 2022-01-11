#include <stdio.h>

/*Vypise pocet cifer cisla po prevodu do dane bazi*/
/*int pocetCifer(int num, int base){
	int digits = 0;
	while(num != 0){
		num /= base;
		digits++;
	}
	return digits;
}
*/
/*Binarni umocnovani*/
long long power(long long base, int exp){
	long long prod = 1;
	for(int i = 1; i <= exp; i <<= 1){
		if ( i & exp) prod *= base;
		base *= base;
	}
	return prod;
}

/*Nezmeni cifry 0-9, prepise na pismena 10-35*/
char num_to_char(int num){
	if(num <= 9){
		return '0' + num;
	}
	else {
		return 'a' + num -10 ;
	}
}
/* Vypise cislo v zadane bazi*/
void convert(long long num, long long base){
	int k = 0;
	while(power(base,k+1) <= num){
		//printf("%d\n", k);
		//printf("%lld\n", power(base,k+1) );
		k++;
	}
	//printf("%d\n", k);
	int div = 0;
	for(int i = k; i >= 0; i--){
		div = num / power(base,i);
		printf("%c", num_to_char(div));
		num = num % power(base,i);
	}
	printf("\n");
	 
}

int main(void){
	long long pos; 
	long long base = 0;
	
	printf("Pozice a soustava:\n");
	while(scanf(" %lld %lld", &pos, &base ) == 2) {
		if(pos < 0) {
			printf("Nespravny vstup.\n");
			return 1;
		}
		if(base < 2 || base > 36){
			printf("Nespravny vstup.\n");
			return 1;
		}
		if(pos == 0){
			printf("0\n");
			printf("^\n");
			continue;
		}
		if(pos == 1) {
			printf("1\n");
			printf("^\n");
			continue;
		}
		if(pos == 2 && base == 10) {
			printf("2\n");
			printf("^\n");
			continue;
		}
		
		long long soucet = 1;
		long long cislo = 1;
		int cifer;
		for(cifer = 1; soucet <= pos ;cifer++){
			//soucet += pocetCifer(i,base);
			long long tmp = (base-1)*power(base,cifer-1);
			soucet += cifer*tmp;
			cislo  += tmp;
		}
		/* Odecteni cisel/cifer po presahu*/
		soucet -= (cifer-1)*(base-1)*power(base,cifer-2);
		cislo -= (base-1)*power(base,cifer-2);
		
		long long posuv = (pos-soucet-1)/(cifer-1);
		cislo  += posuv;
		soucet += posuv*(cifer-1);
		int index = (pos % soucet);
		if(index == cifer-1) {
			cislo++;
			index = 0;
		}
		convert(cislo, base);
		for(int i = 0; i < index; i++) printf(" "); 
		printf("^\n");
		
	}
	if(base == 0){
		printf("Nespravny vstup.\n");
		return 1;
	}
	
	if(!feof(stdin)){
		printf("Nespravny vstup.\n");
		return 1;
	}
	if(feof(stdin)) return 0;
	
	return 0;
}
