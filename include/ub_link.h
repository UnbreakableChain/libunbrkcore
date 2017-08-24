/**
 * @file ub_link.h
 * @brief Header file for the UbLink struct
 */

#pragma once


static const uint8_t UB_GHOST_LINK = 1; ///< Flag representing a ghost link i.e. a link without hardness
static const uint8_t UB_UNINIT_LINK = 2; ///< Flag representing an uninitialized link


/**
 * Struct that represents a link
 */
typedef struct UbLink{
	uint8_t flags;
	uint8_t hardness;
} UbLink;
