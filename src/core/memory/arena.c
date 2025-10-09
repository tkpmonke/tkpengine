#include "arena.h"
#include "memory.h"

arena_allocator_t* arena_allocator_initilize(u32 start_capacity) {
	arena_allocator_t* arena = TKP_MALLOC(sizeof(arena_allocator_t));
	arena->arena = TKP_MALLOC(start_capacity);
	arena->capacity = start_capacity;
	arena->used = 0;

	return arena;
}

void* arena_allocator_allocate(arena_allocator_t* arena, u32 bytes) {
#ifdef DEBUG
	if (arena->used+bytes > arena->capacity) {
		
	}
#endif
}

void arena_allocator_reset(arena_allocator_t* arena, u32 new_size);
void arena_allocator_free(arena_allocator_t* arena);
