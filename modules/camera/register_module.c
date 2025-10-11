#include "register_module.h"
#include "camera.h"
#include "core/component_registry.h"
#include "core/memory/memory.h"

component_t* create_camera_component() {
	component_t* c = TKP_MALLOC(sizeof(component_camera_t));
	c->start = component_camera_start;
	c->update = component_camera_update;
	c->shutdown = component_camera_shutdown;
	c->type = component_registry_get_component("camera")->id;
	return c;
}

static component_variable_t variables[] = {
	{
		.name = "projection_matrix",
		.offset = offsetof(component_camera_t, matrices.projection),
		.type = component_variable_type_matrix4,
		.flags = component_variable_flags_hidden,
		.enum_values = NULL
	}, {
		.name = "view_matrix",
		.offset = offsetof(component_camera_t, matrices.view),
		.type = component_variable_type_matrix4,
		.flags = component_variable_flags_hidden,
		.enum_values = NULL
	}, {
		.name = "near_plane",
		.offset = offsetof(component_camera_t, clip_plane.near),
		.type = component_variable_type_f32,
		.flags = 0,
		.enum_values = NULL
	}, {
		.name = "far_plane",
		.offset = offsetof(component_camera_t, clip_plane.far),
		.type = component_variable_type_f32,
		.flags = 0,
		.enum_values = NULL
	}, {
		.name = "projection_mode",
		.offset = offsetof(component_camera_t, projection_mode),
		.type = component_variable_type_enum,
		.flags = 0,
		.enum_values =
		(const string[3]){ "perspective", "orthographic", NULL }
	}, {
		.name = "clear_mode",
		.offset = offsetof(component_camera_t, clear_mode),
		.type = component_variable_type_enum,
		.flags = 0,
		.enum_values =
		(const string[4]){ "skybox", "clear_color", "nothing", NULL }
	},
	COMPONENT_VARIABLE_NULL_INITILIZER
};

void register_module_camera() {
	component_definition_t definition = {
		.name = "camera",
		.create = create_camera_component,
		.variables = variables
	};

	component_registry_add(&definition);
}
