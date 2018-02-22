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


UbDate tm_to_UbDate(const struct tm* tm){
	return (UbDate){
		.day = tm->tm_mday,
		.mon = tm->tm_mon + 1,
		.year = tm->tm_year + 1900
	};
}


int cmp_UbDate(UbDate date1, UbDate date2){
	struct tm* tm1 = UbDate_to_tm(date1);
	struct tm* tm2 = UbDate_to_tm(date2);
	time_t t1 = mktime(tm1);
	time_t t2 = mktime(tm2);
	free(tm1);
	free(tm2);
	return (t1 - t2) / (60 * 60 * 24); 
}
