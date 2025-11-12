#include "register_module.h"
#include "camera.h"
#include "core/object_registry.h"
#include "core/memory/memory.h"
#include "core/memory/hashed_string.h"

static object_variable_t* variables = NULL;

object_t* create_camera_component() {
	component_t* c = TKP_MALLOC(sizeof(component_camera_t));
	c->start = component_camera_start;
	c->fixed_update = NULL;
	c->update = component_camera_update;
	c->render = NULL;
	c->post_render = NULL;
	c->shutdown = component_camera_shutdown;
	return (object_t*)c;
}

void register_module_camera() {
	object_variable_t vars[] = {
		{
			.name = hashed_string_generate("projection_matrix"),
			.offset = offsetof(component_camera_t, matrices.projection),
			.type = variant_type_matrix4,
		}, {
			.name = hashed_string_generate("view_matrix"),
			.offset = offsetof(component_camera_t, matrices.view),
			.type = variant_type_matrix4,
		}, {
			.name = hashed_string_generate("near_plane"),
			.offset = offsetof(component_camera_t, clip_plane.near),
			.type = variant_type_f32,
		}, {
			.name = hashed_string_generate("far_plane"),
			.offset = offsetof(component_camera_t, clip_plane.far),
			.type = variant_type_f32,
		}, {
			.name = hashed_string_generate("projection_mode"),
			.offset = offsetof(component_camera_t, projection_mode),
			.type = variant_type_enum,
		}, {
			.name = hashed_string_generate("clear_mode"),
			.offset = offsetof(component_camera_t, clear_mode),
			.type = variant_type_enum,
		},
		{ 0, 0, 0 }
	};

	variables = TKP_MALLOC(sizeof(vars));
	memcpy(variables, vars, sizeof(vars));

	object_definition_t definition = {
		.name = hashed_string_generate("camera"),
		.unhashed_name = "camera",
		.create_func = create_camera_component,
		.variables = variables
	};

	object_registry_add(&definition);
}

void deregister_module_camera() {
	TKP_FREE(variables);
}
