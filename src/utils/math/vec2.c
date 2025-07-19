#include "vectors.h"

#include <math.h>
#include <string.h>

void vec2_copy(vec2 src, vec2 dest) {
	memcpy(dest, src, sizeof(vec2));
}

void vec2_zero(vec2 v) {
	v[0] = 0;
	v[1] = 0;
}

void vec2_one(vec2 v) {
	v[0] = 1;
	v[1] = 1;
}

float vec2_dot(vec2 a, vec2 b) {
	return a[0]*b[0]+a[1]*b[1];
}

float vec2_cross(vec2 a, vec2 b) {
	return a[0]*b[1]-a[1]*b[0];
}

float vec2_norm2(vec2 v) {
	return v[0]*v[0]+v[1]*v[1];
}

float vec2_norm(vec2 v) {
	return sqrt(v[0]*v[0]+v[1]*v[1]);
}

void vec2_add(vec2 a, vec2 b, vec2 dest) {
	dest[0] = a[0] + b[0];
	dest[1] = a[1] + b[1];
}

void vec2_addf(vec2 v, float s, vec2 dest) {
	dest[0] = v[0] + s;
	dest[1] = v[1] + s;
}

void vec2_sub(vec2 a, vec2 b, vec2 dest) {
	dest[0] = a[0] - b[0];
	dest[1] = a[1] - b[1];
}

void vec2_subf(vec2 v, float s, vec2 dest) {
	dest[0] = v[0] - s;
	dest[1] = v[1] - s;
}

void vec2_mul(vec2 a, vec2 b, vec2 dest) {
	dest[0] = a[0] * b[0];
	dest[1] = a[1] * b[1];
}

void vec2_mulf(vec2 v, float s, vec2 dest) {
	dest[0] = v[0] * s;
	dest[1] = v[1] * s;
}

void vec2_div(vec2 a, vec2 b, vec2 dest) {
	dest[0] = a[0] / b[0];
	dest[1] = a[1] / b[1];
}

void vec2_divf(vec2 v, float s, vec2 dest) {
	dest[0] = v[0] / s;
	dest[1] = v[1] / s;
}

void vec2_negate(vec2 v) {
	v[0] = -v[0];
	v[1] = -v[1];
}

void vec2_negate_to(vec2 v, vec2 dest) {
	dest[0] = -v[0];
	dest[1] = -v[1];
}

void vec2_normalize(vec2 v) {
	/* get norm */
	float m = sqrtf(v[0]*v[0]+v[1]*v[1]);
	v[0] /= m;
	v[1] /= m;
}

void vec2_normalize_to(vec2 v, vec2 dest) {
	float m = sqrtf(v[0]*v[0]+v[1]*v[1]);

	dest[0] = v[0]/m;
	dest[1] = v[1]/m;
}

void vec2_rotate(vec2 v, float angle, vec2 dest) {
	float ca = cosf(angle);
	float sa = sinf(angle);
	dest[0] = v[0]*ca-sa*v[1];
	dest[1] = v[0]*sa+ca*v[1];
}

void vec2_center(vec2 a, vec2 b, vec2 dest) {
	dest[0] = (a[0]+b[0])*0.5f;
	dest[1] = (a[1]+b[1])*0.5f;
}

float vec2_distance2(vec2 a, vec2 b) {
	float x = b[0] - a[0];
	float y = b[1] - a[1];
	return x*x+y*y;
}

float vec2_distance(vec2 a, vec2 b) {
	float x = b[0] - a[0];
	float y = b[1] - a[1];
	return sqrtf(x*x+y*y);
}

void vec2_max(vec2 v1, vec2 v2, vec2 dest) {
	dest[0] = v1[0] > v2[0] ? v1[0] : v2[0];
	dest[1] = v1[1] > v2[1] ? v1[1] : v2[1];
}

void vec2_min(vec2 v1, vec2 v2, vec2 dest) {
	dest[0] = v1[0] < v2[0] ? v1[0] : v2[0];
	dest[1] = v1[1] < v2[1] ? v1[1] : v2[1];
}

void vec2_maxf(vec2 v1, float s, vec2 dest) {
	dest[0] = v1[0] > s ? v1[0] : s;
	dest[1] = v1[1] > s ? v1[1] : s;
}

void vec2_minf(vec2 v1, float s, vec2 dest) {
	dest[0] = v1[0] < s ? v1[0] : s;
	dest[1] = v1[1] < s ? v1[1] : s;
}

void vec2_clamp(vec2 v, float min_val, float max_val) {
	v[0] = v[0] < min_val ? min_val : v[0] > max_val ? max_val : v[0];
}

void vec2_swizzle(vec2 v, int mask, vec2 dest) {
	/* 
	 * bit shift fuckery
	 * (copied from cglm, i have no idea whats going on here
	 */
	dest[0] = v[mask & (3 << 0)];
	dest[1] = v[(mask & (3 << 2)) >> 2];
}

void vec2_lerp(vec2 from, vec2 to, float t, vec2 dest) {
	dest[0] = from[0]*(1-t)+to[0]*t;
	dest[1] = from[1]*(1-t)+to[1]*t;
}

void vec2_step(vec2 edge, vec2 x, vec2 dest) {
	dest[0] = x[0] < edge[0] ? 0 : 1;
	dest[1] = x[1] < edge[1] ? 0 : 1;
}

void vec2_make(float* src, vec2 dest) {
	memcpy(dest, src, sizeof(float)*2);
}

void vec2_reflect(vec2 v, vec2 n, vec2 dest) {
	vec2 temp;

	float dot = (v[0]*n[0]+v[1]*n[1]);
	temp[0] = n[0] * 2*dot;
	temp[1] = n[1] * 2*dot;
	
	dest[0] = v[0]-temp[0];
	dest[1] = v[1]-temp[1];
}
