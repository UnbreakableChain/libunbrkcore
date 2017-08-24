#include <glib.h>
#include "ub_date.h"



void test_UbDate_to_int(){
	UbDate date1 = {.day=1, .mon=3, .year=1990};
	UbDate date2 = {.day=10, .mon=12, .year=1990};
	UbDate date3 = {.day=1, .mon=1, .year=0};
	UbDate date4 = {.day=0, .mon=0, .year=0};

	g_assert_cmpint(UbDate_to_int(date1), ==, 19900301);
	g_assert_cmpint(UbDate_to_int(date2), ==, 19901210);
	g_assert_cmpint(UbDate_to_int(date3), ==, 101);
	g_assert_cmpint(UbDate_to_int(date4), ==, 0);
}


void test_UbDate_to_tm(){
	UbDate ubdate1 = {.day=1, .mon=3, .year=1900};
	struct tm* tm1 = UbDate_to_tm(ubdate1);
	UbDate ubdate2 = {.day=1, .mon=1, .year=0};
	struct tm* tm2 = UbDate_to_tm(ubdate2);
	UbDate ubdate3 = {.day=0, .mon=0, .year=0};
	struct tm* tm3 = UbDate_to_tm(ubdate3);

	g_assert_cmpint(tm1->tm_mday, ==, 1);
	g_assert_cmpint(tm1->tm_mon, ==, 2);
	g_assert_cmpint(tm1->tm_year, ==, 0);
	
	g_assert_cmpint(tm2->tm_mday, ==, 1);
	g_assert_cmpint(tm2->tm_mon, ==, 0);
	g_assert_cmpint(tm2->tm_year, ==, -1900);

	g_assert_cmpint(tm3->tm_mday, ==, 0);
	g_assert_cmpint(tm3->tm_mon, ==, -1);
	g_assert_cmpint(tm3->tm_year, ==, -1900);

	free(tm1);
	free(tm2);
	free(tm3);
}


void test_cmp_UbDate(){
	UbDate date1 = {.day=1, .mon=1, .year=1900};
	UbDate date2 = {.day=2, .mon=1, .year=1900};
	UbDate date3 = {.day=1, .mon=2, .year=1900};
	UbDate date4 = {.day=1, .mon=1, .year=1901};

	g_assert_cmpint(cmp_UbDate(date1, date2), <, 0);
	g_assert_cmpint(cmp_UbDate(date2, date3), <, 0);
	g_assert_cmpint(cmp_UbDate(date3, date4), <, 0);

	g_assert_cmpint(cmp_UbDate(date2, date1), >, 0);
	g_assert_cmpint(cmp_UbDate(date3, date2), >, 0);
	g_assert_cmpint(cmp_UbDate(date4, date3), >, 0);

	g_assert_cmpint(cmp_UbDate(date1, date1), ==, 0);
}


int main(int argc, char** argv){
	g_test_init(&argc, &argv, NULL);
	g_test_add_func("/set1/UbDate to int test", test_UbDate_to_int);
	g_test_add_func("/set1/UbDate to tm test", test_UbDate_to_tm);
	g_test_add_func("/set1/cmp UbDate test", test_cmp_UbDate);
	return g_test_run();

}
