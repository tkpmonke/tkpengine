#pragma once

#include "../types.h"

typedef struct {
	void* arena;
	u32 capacity;
	u32 used;
} arena_allocator_t;

/* try to keep the start_capacity as low as it needs to be */
arena_allocator_t* arena_allocator_initilize(u32 start_capacity);
void* arena_allocator_allocate(arena_allocator_t* arena, u32 bytes);

/* if new_size is 0 or equal to existing capacity, then it won't reallocate */
void arena_allocator_reset(arena_allocator_t* arena, u32 new_size);
void arena_allocator_free(arena_allocator_t* arena);
