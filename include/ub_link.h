#pragma once


static const uint8_t UB_GHOST_LINK = 1;
static const uint8_t UB_UNINIT_LINK = 2;


typedef struct UbLink{
	uint8_t flags;
	uint8_t hardness;
} UbLink;
