#include "entity.h"
#include "memory/memory.h"

#include <stddef.h>
#include <stdio.h>

#define STRCAT(a, b) a ## b
#define X(func) \
	for (length i = 0; i < entity->components.size; ++i) { \
		component_t* c = *(component_t**)(list_get(&entity->components, i)); \
		if (c->func != NULL) { \
			c->func(c); \
		} \
	} \
	for (length i = 0; i < entity->children.size; ++i) { \
		STRCAT(entity_, func)(list_get(&entity->children, i)); \
	}

#define Y(func) \
	for (length i = 0; i < entity->components.size; ++i) { \
		component_t* c = *(component_t**)(list_get(&entity->components, i)); \
		if (c->func != NULL) { \
			c->func(c, delta); \
		} \
	} \
	for (length i = 0; i < entity->children.size; ++i) { \
		STRCAT(entity_, func)(list_get(&entity->children, i), delta); \
	}

void entity_init(entity_t* entity, string name) {
	entity->name = name;
	entity->initilized = FALSE;
	list_init(&entity->children, 2, sizeof(entity_t));
	list_init(&entity->components, 2, sizeof(component_t*));
}

entity_t* entity_create_child(entity_t* entity) {
	entity_t* e = list_increment(&entity->children);
	e->base.type = entity->base.type;
	return e;
}

void entity_add_component(entity_t* entity, component_t* component) {
	component->parent = entity;

	if (entity->initilized && component->start != NULL) {
		component->start(component);
	}
	list_push(&entity->components, &component);
}

void entity_start(entity_t* entity) {
	X(start);
	entity->initilized = TRUE;
}

void entity_fixed_update(entity_t* entity) {
	X(fixed_update);
}

void entity_update(entity_t* entity, double delta) {
	Y(update);
}

void entity_render(entity_t* entity) {
	X(render);
}

void entity_post_render(entity_t* entity) {
	X(post_render);
}

void entity_shutdown(entity_t* entity) {
	X(shutdown);

	for (length i = 0; i < entity->components.size; ++i) {
		TKP_FREE(*(component_t**)list_get(&entity->components, i));
	}

	list_free(&entity->components);
	list_free(&entity->children);
}

#undef X
#undef Y
