#include "ub_date.h"



uint32_t UbDate_to_int(UbDate date){
	return date.day + date.mon*100 + date.year*10000; 
}


UbDate int_to_UbDate(uint32_t date){
	return (UbDate){
		.day = date % 100,
		.mon = (date/100) % 100,
		.year = date / 10000
	};	
}


struct tm* UbDate_to_tm(UbDate date){
	struct tm* tm = malloc(sizeof(struct tm));
	tm->tm_mday = date.day;
	tm->tm_mon = date.mon - 1;
	tm->tm_year = date.year - 1900;
	tm->tm_sec = 0;
	tm->tm_min = 0;
	tm->tm_hour = 0;
	return tm;
}


int cmp_UbDate(UbDate date1, UbDate date2){
	uint32_t d1 = UbDate_to_int(date1);
	uint32_t d2 = UbDate_to_int(date2);
	return (d1 > d2) - (d1 < d2);
}
