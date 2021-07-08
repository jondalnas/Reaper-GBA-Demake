#pragma once

#include <gba_types.h>

enum EntityTypes {
	player,
	brawler
};

typedef struct {
	u32 x; //Fixed point 16-16
	u32 y; //Fixed point 16-16
	EntityTypes type;
} EntityData_t;