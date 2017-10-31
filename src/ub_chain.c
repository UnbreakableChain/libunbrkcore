#include <string.h>
#include "ub_chain.h"



UbChain* new_UbChain(const char* name){
	UbChain* c = malloc(sizeof(UbChain));
	if (c == NULL) return NULL;
	c->name = malloc(sizeof(char) * (strlen(name) + 1));
	if (c->name == NULL) return NULL;
	strcpy(c->name, name);
	c->links = NULL;
	return c;
}


UbChain* copy_UbChain(const UbChain* chain){
	UbChain* c = new_UbChain(chain->name);
	if (c == NULL) return NULL;

	UbLinkDatePair *link_date_pair, *tmp;
	HASH_ITER(hh, chain->links, link_date_pair, tmp){
		UbLinkDatePair* copy = malloc(sizeof(UbLinkDatePair));
		*copy = *link_date_pair;
		HASH_ADD_INT(c->links, date, copy);
	}

	return c;
}


void free_UbChain(UbChain* chain){
	free(chain->name);
	
	UbLinkDatePair *link_date_pair, *tmp;
	HASH_ITER(hh, chain->links, link_date_pair, tmp){
		HASH_DEL(chain->links, link_date_pair);
		free(link_date_pair);
	}

	free(chain);
}


void add_UbLink_unsorted(UbChain* chain, UbLink link, UbDate date){
	UbLinkDatePair *link_date_pair, *replaced;	
	
	link_date_pair = malloc(sizeof(UbLinkDatePair));
	link_date_pair->date = UbDate_to_int(date);
	link_date_pair->link = link;
	HASH_REPLACE(hh, chain->links, date, sizeof(link_date_pair->date),
		     link_date_pair, replaced);
	if (replaced != NULL) free(replaced);
}


UbLink get_UbLink(const UbChain* chain, UbDate date){
	uint32_t int_date = UbDate_to_int(date);
	UbLinkDatePair* link_date_pair;
	HASH_FIND_INT(chain->links, &int_date, link_date_pair);

	if (link_date_pair == NULL){
		return (UbLink){.hardness = 0, .flags = UB_UNINIT_LINK};
	}

	return link_date_pair->link;
}


int sort_by_date(UbLinkDatePair* ldp1, UbLinkDatePair* ldp2){
	if (ldp1->date == ldp2->date) return 0;
	return ldp1->date > ldp2->date ? -1 : 1;
}


void sort_UbChain(UbChain* chain){
	HASH_SORT(chain->links, sort_by_date);
}


void add_UbLink(UbChain* chain, UbLink link, UbDate date){
	UbLinkDatePair *link_date_pair, *replaced;	
	
	link_date_pair = malloc(sizeof(UbLinkDatePair));
	link_date_pair->date = UbDate_to_int(date);
	link_date_pair->link = link;
	HASH_REPLACE_INORDER(hh, chain->links, date, sizeof(link_date_pair->date),
		     link_date_pair, replaced, sort_by_date);
	if (replaced != NULL) free(replaced);

}



UbChain* merge_UbChain_v(UbChain* chains[], char* name){
	UbChain* c = new_UbChain(name);

	UbLinkDatePair *link_date_pair, *iter, *tmp;
	for(int i=0; chains[i] != NULL; i++){
		HASH_ITER(hh, chains[i]->links, iter, tmp){
			if ((iter->link.flags & UB_UNINIT_LINK) == 0){
				HASH_FIND_INT(c->links, &(iter->date), link_date_pair);
				if (link_date_pair == NULL){
					link_date_pair = malloc(sizeof(UbLinkDatePair));
					link_date_pair->link.hardness = iter->link.hardness * ((iter->link.flags & UB_GHOST_LINK) == 0);
					link_date_pair->link.flags = iter->link.flags & UB_GHOST_LINK;
					link_date_pair->date = iter->date;
					HASH_ADD_INT(c->links, date, link_date_pair);
				} else {
					link_date_pair->link.hardness += iter->link.hardness * ((iter->link.flags & UB_GHOST_LINK) == 0);
					link_date_pair->link.flags &= iter->link.flags & UB_GHOST_LINK;
				}
			}
		}
	}

	return c;
}


void UbChain_iter_first(UbChain* chain, UbChainIterator** iter){
	*iter = chain->links;
}


void UbChain_iter_next(UbChainIterator** iter){
	*iter = (*iter)->hh.next; 
}


void UbChain_iter_prev(UbChainIterator** iter){
	*iter = (*iter)->hh.prev; 
}
