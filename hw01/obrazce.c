#include <stdio.h>
#include <math.h>
#define EPS 1e-6

int isTriangle(double a, double b, double c){ // Triangle inequality check
	if(a+b-c <= EPS*(a+b+c) || a+c -b <= EPS*(a+b+c)  || b+c-a <= EPS*(a+b+c)){
		return 0;
	}
	return 1;
}
double obvodT(double a, double b, double c){ //Triangle perimeter
	return a+b+c;
}
double obvodR(double a, double b){ //Rectangle perimeter
	return 2*(a+b);
}
double obvodS(double a){ //Square perimeter
	return 4*a;
}
double obsahT(double a, double b, double c){ //Triangle area
	double s = (a+b+c)/2 ;
	return sqrt(s*(s-a)*(s-b)*(s-c));
}
double obsahR(double a, double b){ //Rectangle area
	return a*b;
}
double obsahS(double a){ //Square area
	return a*a;
}

int main(void){
	// Prvni obrazec
	char obrazec_1;
	int vstup_t1, vstup_r1, vstup_s1;
	double obvod_1, obsah_1 = 0.0;
	printf("Obrazec #1\n");
	int vstup_obrazec_1 = scanf(" %c",&obrazec_1);
	if(vstup_obrazec_1 != 1){
		printf("Nespravny vstup.\n");
		return 1;
	}
	
	switch(obrazec_1){
		case 'T':
			double t1_1,t2_1,t3_1;
			vstup_t1 = scanf(" %lf %lf %lf", &t1_1, &t2_1, &t3_1);
			if(vstup_t1 != 3 || t1_1 <= 0 || t2_1 <= 0 || t3_1 <= 0 || isTriangle(t1_1,t2_1,t3_1) == 0){
				printf("Nespravny vstup.\n");
				return 1;
			}
			// printf("%c %f %f %f\n",obrazec_1,t1_1,t2_1,t3_1);
			obvod_1 = obvodT(t1_1,t2_1,t3_1);
			obsah_1 = obsahT(t1_1,t2_1,t3_1);
	
			break;
		case 'R':
			double r1_1,r2_1;
			vstup_r1 = scanf(" %lf %lf", &r1_1, &r2_1);
			if(vstup_r1 != 2 || r1_1 <= 0 || r2_1 <= 0 || r1_1 == r2_1){
				printf("Nespravny vstup.\n");
				return 1;
			}
			// printf("%c %f %f\n",obrazec_1,r1_1,r2_1);
			obvod_1 = obvodR(r1_1,r2_1);
			obsah_1 = obsahR(r1_1,r2_1);
			break;
		case 'S':
			double s1_1;
			vstup_s1 = scanf(" %lf", &s1_1);
			if(vstup_s1 != 1 || s1_1 <= 0){
				printf("Nespravny vstup.\n");
				return 1;
			}
			// printf("%c %f\n", obrazec_1, s1_1);
			obvod_1 = obvodS(s1_1);
			obsah_1 = obsahS(s1_1);
			break;
		default:
			printf("Nespravny vstup.\n");
			return 1;
			
	
	}
	//printf("%f\n",obvod_1);
	//printf("%f\n",obsah_1);
	
	//druhy obrazec
	char obrazec_2;
	int vstup_t2, vstup_r2, vstup_s2;
	double obvod_2, obsah_2 = 0.0;
	printf("Obrazec #2\n");
	int vstup_obrazec_2 = scanf(" %c",&obrazec_2);
	if(vstup_obrazec_2 != 1){
		printf("Nespravny vstup.\n");
		return 1;
	}
	
	switch(obrazec_2){
		case 'T':
			double t1_2,t2_2,t3_2;
			vstup_t2 = scanf(" %lf %lf %lf", &t1_2, &t2_2, &t3_2);
			if(vstup_t2 != 3 || t1_2 <= 0 || t2_2 <= 0 || t3_2 <= 0 || isTriangle(t1_2,t2_2,t3_2) == 0){
				printf("Nespravny vstup.\n");
				return 1;
			}
			//printf("%c %f %f %f\n",obrazec_2,t1_2,t2_2,t3_2);
			obvod_2 = obvodT(t1_2,t2_2,t3_2);
			obsah_2 = obsahT(t1_2,t2_2,t3_2);
	
			break;
		case 'R':
			double r1_2,r2_2;
			vstup_r2 = scanf(" %lf %lf", &r1_2, &r2_2);
			if(vstup_r2 != 2 || r1_2 <= 0 || r2_2 <= 0 || r1_2 == r2_2){
				printf("Nespravny vstup.\n");
				return 1;
			}
			//printf("%c %f %f\n",obrazec_2,r1_2,r2_2);
			obvod_2 = obvodR(r1_2,r2_2);
			obsah_2 = obsahR(r1_2,r2_2);
			break;
		case 'S':
			double s1_2;
			vstup_s2 = scanf(" %lf", &s1_2);
			if(vstup_s2 != 1 || s1_2 <= 0){
				printf("Nespravny vstup.\n");
				return 1;
			}
			//printf("%c %f\n", obrazec_2, s1_2);
			obvod_2 = obvodS(s1_2);
			obsah_2 = obsahS(s1_2);
			break;
		default:
			printf("Nespravny vstup.\n");
			return 1;
			
	
	}
	//printf("%f\n",obvod_2);
	//printf("%f\n",obsah_2);
	
	//Pripad Trojuhelnik Trojuhelnik
	if (obrazec_1 == 'T' && obrazec_2 =='T'){
		if(fabs(obvod_1 - obvod_2) <= EPS*(obvod_1+obvod_2)){
			printf("Obvod: trojuhelnik #1 = trojuhelnik #2\n");
		}
		else if(obvod_1 - obvod_2 > EPS*(obvod_1+obvod_2)){
			printf("Obvod: trojuhelnik #1 > trojuhelnik #2\n");
		}
		else {
			printf("Obvod: trojuhelnik #1 < trojuhelnik #2\n");
		}
		
		if(fabs(obsah_1 - obsah_2) <= EPS*(obsah_1+obsah_2)){
			printf("Obsah: trojuhelnik #1 = trojuhelnik #2\n");
		}
		else if(obsah_1 - obsah_2 > EPS*(obsah_1+obsah_2)){
			printf("Obsah: trojuhelnik #1 > trojuhelnik #2\n");
		}
		else {
			printf("Obsah: trojuhelnik #1 < trojuhelnik #2\n");
		}
		return 0;
	}
	//Pripad Trojuhelnik Obdelnik
	if (obrazec_1 == 'T' && obrazec_2 =='R'){
		if(fabs(obvod_1 - obvod_2) <= EPS*(obvod_1+obvod_2)){
			printf("Obvod: trojuhelnik #1 = obdelnik #2\n");
		}
		else if(obvod_1 - obvod_2 > EPS*(obvod_1+obvod_2)){
			printf("Obvod: trojuhelnik #1 > obdelnik #2\n");
		}
		else {
			printf("Obvod: trojuhelnik #1 < obdelnik #2\n");
		}
		
		if(fabs(obsah_1 - obsah_2) <= EPS*(obsah_1+obsah_2)){
			printf("Obsah: trojuhelnik #1 = obdelnik #2\n");
		}
		else if(obsah_1 - obsah_2 > EPS*(obsah_1+obsah_2)){
			printf("Obsah: trojuhelnik #1 > obdelnik #2\n");
		}
		else {
			printf("Obsah: trojuhelnik #1 < obdelnik #2\n");
		}
		return 0;
	}
	//Pripad Trojuhelnik Ctverec
	if (obrazec_1 == 'T' && obrazec_2 =='S'){
		if(fabs(obvod_1 - obvod_2) <= EPS*(obvod_1+obvod_2)){
			printf("Obvod: trojuhelnik #1 = ctverec #2\n");
		}
		else if(obvod_1 - obvod_2 > EPS*(obvod_1+obvod_2)){
			printf("Obvod: trojuhelnik #1 > ctverec #2\n");
		}
		else {
			printf("Obvod: trojuhelnik #1 < ctverec #2\n");
		}
		
		if(fabs(obsah_1 - obsah_2) <= EPS*(obsah_1+obsah_2)){
			printf("Obsah: trojuhelnik #1 = ctverec #2\n");
		}
		else if(obsah_1 - obsah_2 > EPS*(obsah_1+obsah_2)){
			printf("Obsah: trojuhelnik #1 > ctverec #2\n");
		}
		else {
			printf("Obsah: trojuhelnik #1 < ctverec #2\n");
		}
		return 0;
	}
	//Pripad Obdelnik Obdelnik
	if (obrazec_1 == 'R' && obrazec_2 =='R'){
		if(fabs(obvod_1 - obvod_2) <= EPS*(obvod_1+obvod_2)){
			printf("Obvod: obdelnik #1 = obdelnik #2\n");
		}
		else if(obvod_1 - obvod_2 > EPS*(obvod_1+obvod_2)){
			printf("Obvod: obdelnik #1 > obdelnik #2\n");
		}
		else {
			printf("Obvod: obdelnik #1 < obdelnik #2\n");
		}
		
		if(fabs(obsah_1 - obsah_2) <= EPS*(obsah_1+obsah_2)){
			printf("Obsah: obdelnik #1 = obdelnik #2\n");
		}
		else if(obsah_1 - obsah_2 > EPS*(obsah_1+obsah_2)){
			printf("Obsah: obdelnik #1 > obdelnik #2\n");
		}
		else {
			printf("Obsah: obdelnik #1 < obdelnik #2\n");
		}
		return 0;
	}
	//Pripad Obdelnik Trojuhelnik
	if (obrazec_1 == 'R' && obrazec_2 =='T'){
		if(fabs(obvod_1 - obvod_2) <= EPS*(obvod_1+obvod_2)){
			printf("Obvod: obdelnik #1 = trojuhelnik #2\n");
		}
		else if(obvod_1 - obvod_2 > EPS*(obvod_1+obvod_2)){
			printf("Obvod: obdelnik #1 > trojuhelnik #2\n");
		}
		else {
			printf("Obvod: obdelnik #1 < trojuhelnik #2\n");
		}
		
		if(fabs(obsah_1 - obsah_2) <= EPS*(obsah_1+obsah_2)){
			printf("Obsah: obdelnik #1 = trojuhelnik #2\n");
		}
		else if(obsah_1 - obsah_2 > EPS*(obsah_1+obsah_2)){
			printf("Obsah: obdelnik #1 > trojuhelnik #2\n");
		}
		else {
			printf("Obsah: obdelnik #1 < trojuhelnik #2\n");
		}
		return 0;
	}
	//Pripad Obdelnik Ctverec
	if (obrazec_1 == 'R' && obrazec_2 =='S'){
		if(fabs(obvod_1 - obvod_2) <= EPS*(obvod_1+obvod_2)){
			printf("Obvod: obdelnik #1 = ctverec #2\n");
		}
		else if(obvod_1 - obvod_2 > EPS*(obvod_1+obvod_2)){
			printf("Obvod: obdelnik #1 > ctverec #2\n");
		}
		else {
			printf("Obvod: obdelnik #1 < ctverec #2\n");
		}
		
		if(fabs(obsah_1 - obsah_2) <= EPS*(obsah_1+obsah_2)){
			printf("Obsah: obdelnik #1 = ctverec #2\n");
		}
		else if(obsah_1 - obsah_2 > EPS*(obsah_1+obsah_2)){
			printf("Obsah: obdelnik #1 > ctverec #2\n");
		}
		else {
			printf("Obsah: obdelnik #1 < ctverec #2\n");
		}
		return 0;
	}
	//Pripad Ctverec Ctverec
	if (obrazec_1 == 'S' && obrazec_2 =='S'){
		if(fabs(obvod_1 - obvod_2) <= EPS*(obvod_1+obvod_2)){
			printf("Obvod: ctverec #1 = ctverec #2\n");
		}
		else if(obvod_1 - obvod_2 > EPS*(obvod_1+obvod_2)){
			printf("Obvod: ctverec #1 > ctverec #2\n");
		}
		else {
			printf("Obvod: ctverec #1 < ctverec #2\n");
		}
		
		if(fabs(obsah_1 - obsah_2) <= EPS*(obsah_1+obsah_2)){
			printf("Obsah: ctverec #1 = ctverec #2\n");
		}
		else if(obsah_1 - obsah_2 > EPS*(obsah_1+obsah_2)){
			printf("Obsah: ctverec #1 > ctverec #2\n");
		}
		else {
			printf("Obsah: ctverec #1 < ctverec #2\n");
		}
		return 0;
	}
	//Pripad Ctverec Trojuhelnik
	if (obrazec_1 == 'S' && obrazec_2 =='T'){
		if(fabs(obvod_1 - obvod_2) <= EPS*(obvod_1+obvod_2)){
			printf("Obvod: ctverec #1 = trojuhelnik #2\n");
		}
		else if(obvod_1 - obvod_2 > EPS*(obvod_1+obvod_2)){
			printf("Obvod: ctverec #1 > trojuhelnik #2\n");
		}
		else {
			printf("Obvod: ctverec #1 < trojuhelnik #2\n");
		}
		
		if(fabs(obsah_1 - obsah_2) <= EPS*(obsah_1+obsah_2)){
			printf("Obsah: ctverec #1 = trojuhelnik #2\n");
		}
		else if(obsah_1 - obsah_2 > EPS*(obsah_1+obsah_2)){
			printf("Obsah: ctverec #1 > trojuhelnik #2\n");
		}
		else {
			printf("Obsah: ctverec #1 < trojuhelnik #2\n");
		}
		return 0;
	}
	//Pripad Ctverec Obdelnik
	if (obrazec_1 == 'S' && obrazec_2 =='R'){
		if(fabs(obvod_1 - obvod_2) <= EPS*(obvod_1+obvod_2)){
			printf("Obvod: ctverec #1 = obdelnik #2\n");
		}
		else if(obvod_1 - obvod_2 > EPS*(obvod_1+obvod_2)){
			printf("Obvod: ctverec #1 > obdelnik #2\n");
		}
		else {
			printf("Obvod: ctverec #1 < obdelnik #2\n");
		}
		
		if(fabs(obsah_1 - obsah_2) <= EPS*(obsah_1+obsah_2)){
			printf("Obsah: ctverec #1 = obdelnik #2\n");
		}
		else if(obsah_1 - obsah_2 > EPS*(obsah_1+obsah_2)){
			printf("Obsah: ctverec #1 > obdelnik #2\n");
		}
		else {
			printf("Obsah: ctverec #1 < obdelnik #2\n");
		}
		return 0;
	}
	return 0;
	
}
