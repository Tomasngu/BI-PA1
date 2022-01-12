#ifndef __PROGTEST__
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#endif /* __PROGTEST__ */


// Checks whether year is leap
int isLeap (int year){
    return ((year % 400 == 0 || year % 100 != 0 ) && year % 4000 != 0&& year % 4 == 0);
}

/* Returns index of a given day of a year */
int day_index(int year, int month, int day ){
    int i_day = 0;
    int leap_one = ((isLeap(year)) ? 1 : 0);
    switch(month){
        case 1: i_day = day; break;
        case 2: i_day = 31 + day; break;
        case 3: i_day = 59 + leap_one + day; break;
        case 4: i_day = 90 + leap_one + day; break;
        case 5: i_day = 120 + leap_one + day; break;
        case 6: i_day = 151 + leap_one + day; break;
        case 7: i_day = 181 + leap_one + day; break;
        case 8: i_day = 212 + leap_one + day; break;
        case 9: i_day = 243 + leap_one + day; break;
        case 10: i_day = 273 + leap_one + day; break;
        case 11: i_day = 304 + leap_one + day; break;
        case 12: i_day = 334 + leap_one + day; break;
        default: return 0;
    }
    return i_day;
}
/* Returns consumption until the end of an hour */ 
int till_hour(int minute){
    int consumption = 0;
    int minute_consumption = 200;
    int XORed_minute[60]={ 4,5,2,3,3,1,5,4,1,6,
                    4,5,2,3,3,1,5,4,1,7,
                    4,5,2,3,3,1,5,4,1,4,
                    4,5,2,3,3,1,5,4,1,5,
                    4,5,2,3,3,1,5,4,1,5,
                    4,5,2,3,3,1,5,4,1,5 };
    for(int i = minute; i < 60; i++){
        consumption += XORed_minute[i];
        consumption += minute_consumption;
    }
    return consumption;
}
/* Returns consumption until the end of a day */ 
int till_day(int hour, int minute){
    int consumption = 0;
    int hour_consumption = 12200;
    int XORed_hour[24]={ 4,5,2,3,3,1,5,4,1,6,
                    4,5,2,3,3,1,5,4,1,7,
                    4,5,2,6};
    consumption += till_hour(minute);
    for(int i = hour ; i < 24; i++){
        consumption += XORed_hour[i];
        consumption += hour_consumption;
    }
    consumption -= hour_consumption;
    return consumption;


}
/* Returns consumption from beginning of day to given time*/ 
int till_time(int hour, int minute){
    int day_consumption = 292886; 
    return day_consumption - till_day(hour, minute);
}


// Check whether date is valid
int checkDate(int year, int month, int day, int hour, int minute){
	int flag = 1;
	if(year < 1600 || month < 1 || month > 12 || day < 1) flag = 0;
    	if ((month == 1 ||
        month == 3 ||
        month == 5 ||
        month == 7 ||
        month == 8 ||
        month == 10 ||
        month == 12 ) && (day > 31)) flag = 0;
    if ((month == 4 ||
        month == 6 ||
        month == 9 ||
        month == 11 ) && day > 30) flag = 0;
    if (month == 2 && day > ((isLeap(year)) ? 29 : 28)) flag = 0;
    if (hour < 0 || hour > 23 || minute < 0 || minute > 59) flag = 0;
    if (flag == 0) {
    	// printf("Rozbil jsem se zde na %d %d %d %d %d\n", year, month, day, hour, minute);
    	return 0;
    }
	return 1;
}    

long long countDaysbetween(int year1, int year2){
    long long days = 0;
    if (year2-year1 < 10000){
        for(int y = year1 + 1; y <= year2 -1; y++){
            days += ((isLeap(y)) ? 366 : 365);
        }
    } else {
        int after_4K = year1 + (4000 - (year1 % 4000));
        for(int y = year1 +1 ;y <= after_4K -1; y++){
            days += ((isLeap(y)) ? 366 : 365);
        }
        int before_4K = year2 - (year2 % 4000);
        for (int y = before_4K; y <= year2 -1; y++){
            days += ((isLeap(y)) ? 366 : 365);
        }
        int whole_4k = (before_4K - after_4K)/4000;
        long long leaps = 969*whole_4k;
        long long non_leaps = 3031*whole_4k;
        days += 366*leaps + 365*non_leaps;

    }
    return days;
}


// Calculates energy consupmtion between two dates
int energyConsumption ( int y1, int m1, int d1, int h1, int i1,
                        int y2, int m2, int d2, int h2, int i2, long long int * consumption ){
	/*input checks*/
    if(checkDate(y1,m1,d1,h1,i1) == 0 
		||checkDate(y2,m2,d2,h2,i2) == 0 
		|| y1 > y2 
		|| (y1 == y2 && m1 > m2) 
		|| 	(y1 == y2 && m1 == m2 && d1 > d2) 
		||  (y1 == y2 && m1 == m2 && d1 == d2 && h1 > h2) 
		|| (y1 == y2 && m1 == m2 && d1 == d2 && h1 == h2 && i1 > i2)) return 0;
    /*____________________________*/
    long long energy = 0;
    int day_consumption = 292886; 
    if(y1 < y2){
        int days_till_endyear = ((isLeap(y1)) ? 366 : 365) - day_index(y1, m1, d1);
        int days_till_date = day_index(y2,m2, d2) -1;
        long long days_whole_years = countDaysbetween(y1,y2);
        long long days_between = days_till_endyear + days_whole_years + days_till_date;
        energy = till_day(h1,i1) + days_between*day_consumption + till_time(h2,i2);
    } else {
        int difftime_comp = till_day(h1,i1) + till_time(h2,i2);
        long long wholedays_diff = day_index(y2, m2, d2) - day_index(y1, m1, d1) -1 ;
        long long wholedays_comp = wholedays_diff * day_consumption;
        energy = wholedays_comp + difftime_comp;
    }
    *consumption = energy;
    return 1;
    
}



#ifndef __PROGTEST__
int main ( int argc, char * argv [] )
{
    long long int consumption;
    /*
    printf("%lld\n", countDaysbetween(2016,2020));
    
            
    printf("%lld", consumption);
    */
    assert ( energyConsumption ( 2021, 10,  1, 13, 15,
                                2021, 10,  1, 18, 45, &consumption ) == 1
            && consumption == 67116LL );
    
    assert ( energyConsumption ( 2021, 10,  1, 13, 15,
                                2021, 10,  2, 11, 20, &consumption ) == 1
            && consumption == 269497LL );
    assert ( energyConsumption ( 2021,  1,  1, 13, 15,
                                2021, 10,  5, 11, 20, &consumption ) == 1
            && consumption == 81106033LL );
    assert ( energyConsumption ( 2024,  1,  1, 13, 15,
                                2024, 10,  5, 11, 20, &consumption ) == 1
            && consumption == 81398919LL );
    assert ( energyConsumption ( 1900,  1,  1, 13, 15,
                                1900, 10,  5, 11, 20, &consumption ) == 1
            && consumption == 81106033LL );
    assert ( energyConsumption ( 2021, 10,  1,  0,  0,
                                2021, 10,  1, 12,  0, &consumption ) == 1
            && consumption == 146443LL );
    assert ( energyConsumption ( 2021, 10,  1,  0, 15,
                                2021, 10,  1,  0, 25, &consumption ) == 1
            && consumption == 2035LL );
    assert ( energyConsumption ( 2021, 10,  1, 12,  0,
                                2021, 10,  1, 12,  0, &consumption ) == 1
            && consumption == 0LL );
    assert ( energyConsumption ( 2021, 10,  1, 12,  0,
                                2021, 10,  1, 12,  1, &consumption ) == 1
            && consumption == 204LL ); 
     assert ( energyConsumption ( 2021, 11,  1, 12,  0,
                                2014, 10,  1, 12,  0, &consumption ) == 0 );
    assert ( energyConsumption ( 2021, 10, 31, 12,  0,
                                2021, 9, 10, 12,  0, &consumption ) == 0 );
    assert ( energyConsumption ( 2400,  2, 29, 12,  0,
                                2400,  2, 29, 12,  0, &consumption ) == 1
            && consumption == 0LL ); 
    return 0;
    
}
#endif /* __PROGTEST__ */
