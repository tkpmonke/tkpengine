#pragma once

#include "types.h"
#include "component.h"
#include "memory/list.h"

typedef struct entity_t {
	object_t base;

	string name;
	struct entity_t* parent;
	list_t children;
	list_t components;

	boolean initilized;
} entity_t;

void entity_init(entity_t* entity, string name);

entity_t* entity_create_child(entity_t* entity);
void entity_add_component(entity_t* entity, component_t* component);

void entity_start(entity_t* entity);
void entity_fixed_update(entity_t* entity);
void entity_update(entity_t* entity, double delta);
void entity_render(entity_t* entity);
void entity_post_render(entity_t* entity);
void entity_shutdown(entity_t* entity);
