/*
 * Copyright (c), Recep Aslantas.
 *
 * MIT License (MIT), http://opensource.org/licenses/MIT
 * Full license can be found in the LICENSE file
 */

#include "clipspace/project_no.h"
#include "call/clipspace/project_no.h"

CGLM_EXPORT
void
glmc_unprojecti_no(vec3 pos, mat4 invMat, vec4 vp, vec3 dest) {
  glm_unprojecti_no(pos, invMat, vp, dest);
}

CGLM_EXPORT
void
glmc_project_no(vec3 pos, mat4 m, vec4 vp, vec3 dest) {
  glm_project_no(pos, m, vp, dest);
}

CGLM_EXPORT
float
glmc_project_z_no(vec3 pos, mat4 m) {
  return glm_project_z_no(pos, m);
}
