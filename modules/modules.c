/* auto generated initilzation for modules */

#include "camera/register_module.h"
#include "collider/register_module.h"

void modules_register() {
	register_module_camera();
	register_module_collider();
}

void modules_deregister() {
	deregister_module_camera();
	deregister_module_collider();
}