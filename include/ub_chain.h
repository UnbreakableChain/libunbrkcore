#pragma once

#include <time.h>
#include "ut/uthash.h"
#include "ub_link.h"
#include "ub_date.h"



typedef struct {
	uint32_t date;
	UbLink link;
	UT_hash_handle hh;
} UbLinkDatePair;


typedef struct UbChain{
	char* name;
	UbLinkDatePair* links;
} UbChain;


UbChain* new_UbChain(const char* name);
UbChain* copy_UbChain(const UbChain* chain);
void free_UbChain();
void add_UbLink(UbChain* chain, UbLink link, UbDate date);
UbLink get_UbLink(const UbChain* chain, UbDate date);
UbChain* merge_UbChain_v(UbChain* chains[], char* name);
#define make_UbChain_list(...) (UbChain*[]){__VA_ARGS__, NULL}
#define merge_UbChain(chain_list, name) merge_UbChain_v(make_UbChain_list chain_list, name)
