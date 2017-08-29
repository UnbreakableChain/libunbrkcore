#include <glib.h>
#include "ub_chain.h"



typedef struct{

} fixture;


void test_new_UbChain(){
	UbChain* c = new_UbChain("chain_name");
	g_assert(c != NULL);
	g_assert_cmpstr(c->name, ==, "chain_name");
	free_UbChain(c);
}


void test_free_UbChain(){
	UbChain* c = new_UbChain("");
	free_UbChain(c);
	g_assert(c != NULL);
}


void test_add_get_UbLink(){
	UbChain* chain = new_UbChain("");
	UbDate date = {.year = 2024, .mon = 3, .day = 23};
	UbLink link = {.hardness = 1, .flags = 0}; 
	add_UbLink(chain, link, date);
	link = get_UbLink(chain, date);
	g_assert(link.hardness == 1);
	link = get_UbLink(chain, (UbDate){.year = 1999, .mon = 1, .day = 1});
	g_assert((link.flags & UB_UNINIT_LINK) != 0);
	free_UbChain(chain);
}


void test_copy_UbChain(){
	UbChain* chain = new_UbChain("chain_name");
	add_UbLink(chain, (UbLink){.hardness = 1, .flags = 0}, (UbDate){.year = 2024, .mon = 3, .day = 23});
	UbChain* copy = copy_UbChain(chain);
	g_assert_cmpstr(copy->name, ==, "chain_name");
	g_assert(get_UbLink(copy, (UbDate){.year = 2024, .mon = 3, .day = 23}).hardness == 1);
	free_UbChain(chain);
	free_UbChain(copy);
}


void test_merge_UbChain(){
	UbChain *chain1 = new_UbChain("");
	UbChain	*chain2 = new_UbChain("");
	UbChain	*chain3 = new_UbChain("");
	UbDate d1 = {.year = 2024, .mon = 3, .day = 1};
	UbDate d2 = {.year = 2024, .mon = 3, .day = 2};
	UbDate d3 = {.year = 2024, .mon = 3, .day = 3};
	UbDate d4 = {.year = 2024, .mon = 3, .day = 4};
	add_UbLink(chain1, (UbLink){.hardness = 1, .flags = 0}, d1);
	add_UbLink(chain2, (UbLink){.hardness = 2, .flags = 0}, d1);
	add_UbLink(chain3, (UbLink){.hardness = 0, .flags = 0}, d1);
	add_UbLink(chain1, (UbLink){.hardness = 1, .flags = 0}, d2);
	add_UbLink(chain2, (UbLink){.hardness = 1, .flags = UB_GHOST_LINK}, d2);
	add_UbLink(chain3, (UbLink){.hardness = 1, .flags = UB_GHOST_LINK | UB_UNINIT_LINK}, d2);
	add_UbLink(chain1, (UbLink){.hardness = 1, .flags = 0}, d3);
	add_UbLink(chain2, (UbLink){.hardness = 1, .flags = UB_UNINIT_LINK}, d3);
	add_UbLink(chain3, (UbLink){.hardness = 1, .flags = UB_UNINIT_LINK | UB_GHOST_LINK}, d3);
	add_UbLink(chain1, (UbLink){.hardness = 1, .flags = UB_GHOST_LINK}, d4);
	add_UbLink(chain2, (UbLink){.hardness = 1, .flags = UB_GHOST_LINK}, d4);

	UbChain* chain = merge_UbChain((chain1, chain2, chain3), "merged chain"); 
	g_assert_cmpstr(chain->name, ==, "merged chain");
	g_assert_cmpint(get_UbLink(chain, d1).hardness, ==, 3);
	g_assert_cmpint(get_UbLink(chain, d2).hardness, ==, 1);
	g_assert_cmpint(get_UbLink(chain, d3).hardness, ==, 1);
	g_assert_cmpint(get_UbLink(chain, d4).hardness, ==, 0);
	g_assert_cmpint((get_UbLink(chain, d4).flags & UB_GHOST_LINK), !=, 0);
	g_assert_cmpint((get_UbLink(chain, (UbDate){.year = 1999, .mon = 1, .day = 1}).flags & UB_UNINIT_LINK), !=, 0);

	free_UbChain(chain1);
	free_UbChain(chain2);
	free_UbChain(chain3);
	free_UbChain(chain);
}


void test_UbChain_iter(){
	UbChain* chain = new_UbChain("");
	UbLink l1 = {.hardness = 0, .flags = 0};
	UbLink l2 = {.hardness = 1, .flags = 0};
	UbLink l3 = {.hardness = 2, .flags = 0};
	UbDate d1 = {.day = 1, .mon = 3, .year = 1990};
	UbDate d2 = {.day = 3, .mon = 5, .year = 1991};
	UbDate d3 = {.day = 5, .mon = 7, .year = 1992};
	UbChainIterator* iter;

	UbChain_iter_first(chain, &iter);
	g_assert(iter == NULL);

	add_UbLink(chain, l1, d1);
	add_UbLink(chain, l2, d2);
	add_UbLink(chain, l3, d3);

	UbChain_iter_first(chain, &iter);
	g_assert_cmpint(iter->link.hardness, ==, l1.hardness);
	g_assert(iter->date == UbDate_to_int(d1));
	UbChain_iter_next(&iter);
	g_assert_cmpint(iter->link.hardness, ==, l2.hardness);
	g_assert(iter->date == UbDate_to_int(d2));
	UbChain_iter_next(&iter);
	g_assert_cmpint(iter->link.hardness, ==, l3.hardness);
	g_assert(iter->date == UbDate_to_int(d3));
	UbChain_iter_next(&iter);
	g_assert(iter == NULL);

	free_UbChain(chain);
}


int main(int argc, char** argv){
	g_test_init(&argc, &argv, NULL);
	g_test_add_func("/set1/new UbChain test", test_new_UbChain);
	g_test_add_func("/set1/free UbChain test", test_free_UbChain);
	g_test_add_func("/set1/add get UbLink test", test_add_get_UbLink);
	g_test_add_func("/set1/copy UbChain test", test_copy_UbChain);
	g_test_add_func("/set1/merge UbChain test", test_merge_UbChain);
	g_test_add_func("/set1/iter UbChain test", test_UbChain_iter);
	return g_test_run();
}
