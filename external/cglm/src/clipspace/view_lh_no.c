/*
 * Copyright (c), Recep Aslantas.
 *
 * MIT License (MIT), http://opensource.org/licenses/MIT
 * Full license can be found in the LICENSE file
 */

#include "clipspace/view_lh_no.h"
#include "call/clipspace/view_lh_no.h"

CGLM_EXPORT
void
glmc_lookat_lh_no(vec3 eye, vec3 center, vec3 up, mat4 dest) {
  glm_lookat_lh_no(eye, center, up, dest);
}

CGLM_EXPORT
void
glmc_look_lh_no(vec3 eye, vec3 dir, vec3 up, mat4 dest) {
  glm_look_lh_no(eye, dir, up, dest);
}

CGLM_EXPORT
void
glmc_look_anyup_lh_no(vec3 eye, vec3 dir, mat4 dest) {
  glm_look_anyup_lh_no(eye, dir, dest);
}
