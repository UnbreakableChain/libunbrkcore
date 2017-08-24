#pragma once
#include <stdlib.h>
#include <stdint.h>
#include <time.h>



typedef struct {
	uint16_t year;
	uint8_t mon;
	uint8_t day;
} UbDate;


uint32_t UbDate_to_int(UbDate date);
struct tm* UbDate_to_tm(UbDate date);
time_t UbDate_to_time_t(UbDate date);
int cmp_UbDate(UbDate date1, UbDate date2);
