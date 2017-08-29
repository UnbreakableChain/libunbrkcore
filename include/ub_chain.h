/**
 * @file ub_chain.h
 * @brief Header file for the UbChain struct and related functions 
 */

#pragma once

#include <time.h>
#include "ut/uthash.h"
#include "ub_link.h"
#include "ub_date.h"



/**
 * @brief Auxiliar struct for uthash
 */
typedef struct {
	uint32_t date; ///< key of the hash table
	UbLink link; ///< value stored in the hash table
	UT_hash_handle hh;
} UbLinkDatePair;


/*
 * @brief Structure to provide iteration support
 */
typedef UbLinkDatePair UbChainIterator;


/**
 * @brief A struct representing a chain of UbLinks
 */
typedef struct UbChain{
	char* name; ///< Chain name
	UbLinkDatePair* links; ///< Hash table where the links are stored
} UbChain;



/**
 * @brief Creates a new UbChain. The chain must be freed with free_UbChain()
 * @param name The name of the new UbChain
 * @return A pointer to the new UbChain
 * @see free_UbChain()
 */
UbChain* new_UbChain(const char* name);

/**
 * @brief Creates a new UbChain with the same name and links. The chain must be freed with free_UbChain()
 * @param chain The UbChain from which the new chain is copied
 * @return A pointer to the new UbChain
 * @see free_UbChain()
 */
UbChain* copy_UbChain(const UbChain* chain);

/**
 * @brief Frees a UbChain Struct
 * @param chain A pointer to the chain to free
 */
void free_UbChain(UbChain* chain);

/**
 * @brief Adds or replaces an UbLink in an UbChain  
 * @param chain UbChain in which the UbLink will be added
 * @param link UbLink to add
 * @param date Date of the link
 */
void add_UbLink(UbChain* chain, UbLink link, UbDate date);

/**
 * @brief Returns the UbLink bound to a date in a UbChain
 * @param chain Chain from which get the link
 * @param date Date of the link in the chain
 * @return The UbLink bounded to the date 
 */
UbLink get_UbLink(const UbChain* chain, UbDate date);

/**
 * @brief Merges several UbChains in a new one. The merging process consists in
 * sum the hardness value of all the links in a same date except these that have the flags
 * UB_GHOST_LINK or UB_UNINIT_LINK. If in a date ALL the links have the flag UB_GHOST_LINK
 * the merged link will have that flag too. 
 * @param chains A vector of pointers to the chains to merge. The vector must end with a NULL pointer
 * @param name The name of the new UbChain
 * @return The merged UbChain which must be freed using free_UbChain()
 * @see free_UbChain()
 * @see merge_UbChain()
 */
UbChain* merge_UbChain_v(UbChain* chains[], char* name);

#define make_UbChain_list(...) (UbChain*[]){__VA_ARGS__, NULL}

/**
 *@brief An easy way to call merge_UbChain_v using variadic arguments 
 */
#define merge_UbChain(chain_list, name) merge_UbChain_v(make_UbChain_list chain_list, name)

/**
 * @brief Initialice the iterator with the first element of the chain.
 * If the chain is empty iter will be NULL
 */
void UbChain_iter_first(UbChain* chain, UbChainIterator** iter);

/**
 * @brief Fills iter with the next iterator
 * If there are not more elements in the chain iter will be NULL
 */
void UbChain_iter_next(UbChainIterator** iter);
