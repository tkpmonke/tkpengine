#include "register_module.h"
#include "camera.h"
#include "core/component_registry.h"

component_t* create_camera_component() {
	return malloc(sizeof(component_camera_t));
}

component_variable_t variables[] = {
	{
		.name = "Projection Matrix",
		.offset = offsetof(component_camera_t, matrices.projection),
		.type = component_variable_type_matrix4,
		.flags = component_variable_flags_hidden,
		.enum_values = NULL
	}, {
		.name = "View Matrix",
		.offset = offsetof(component_camera_t, matrices.view),
		.type = component_variable_type_matrix4,
		.flags = component_variable_flags_hidden,
		.enum_values = NULL
	}, {
		.name = "Near Plane",
		.offset = offsetof(component_camera_t, clip_plane.near),
		.type = component_variable_type_f32,
		.flags = 0,
		.enum_values = NULL
	}, {
		.name = "Far Plane",
		.offset = offsetof(component_camera_t, clip_plane.far),
		.type = component_variable_type_f32,
		.flags = 0,
		.enum_values = NULL
	}, {
		.name = "Projection Mode",
		.offset = offsetof(component_camera_t, projection_mode),
		.type = component_variable_type_enum,
		.flags = 0,
		.enum_values =
		(const char* const[3]){ "perspective", "orthographic", NULL }
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
