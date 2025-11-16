/* auto generated initilzation for modules */

#include "camera/register_module.h"
#include "texture/register_module.h"
#include "render_texture/register_module.h"

void modules_register() {
	register_module_camera();
	register_module_texture(); {
		register_module_render_texture();
	}
}

void modules_deregister() {
	deregister_module_camera();
	deregister_module_texture(); {
		deregister_module_render_texture();
	}
}