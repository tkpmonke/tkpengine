/* copying godot goes brrrrrrrr */
#pragma once

#include "types.h"

typedef enum {
	variant_type_null,
	variant_type_u8,
	variant_type_u16,
	variant_type_u32,
	variant_type_u64,
	variant_type_i8,
	variant_type_i16,
	variant_type_i32,
	variant_type_i64,
	variant_type_f32,
	variant_type_f64,
	variant_type_boolean,
	variant_type_string,
	variant_type_vector2,
	variant_type_vector3,
	variant_type_vector4,
	variant_type_matrix2,
	variant_type_matrix2x3,
	variant_type_matrix2x4,
	variant_type_matrix3,
	variant_type_matrix3x2,
	variant_type_matrix3x4,
	variant_type_matrix4,
	variant_type_matrix4x2,
	variant_type_matrix4x3,
	variant_type_enum,
	/* reference to an object */
	variant_type_object,

	/* bitflag */
	variant_type_array = 128,
} variant_type_t;

typedef struct {
	variant_type_t type;
	void* data;
} variant_t;

inline static boolean variant_is_number(variant_t* variant) {
	return 
		variant->type == variant_type_u8 ||
		variant->type == variant_type_u16 ||
		variant->type == variant_type_u32 ||
		variant->type == variant_type_u64 ||
		variant->type == variant_type_i8 ||
		variant->type == variant_type_i16 ||
		variant->type == variant_type_i32 ||
		variant->type == variant_type_i64 ||
		variant->type == variant_type_f32 ||
		variant->type == variant_type_f64;
}

inline static boolean variant_is_vector(variant_t* variant) {
	return 
		variant->type == variant_type_vector2 ||
		variant->type == variant_type_vector3 ||
		variant->type == variant_type_vector4;
}

inline static boolean variant_is_matrix(variant_t* variant) {
	return
		variant->type == variant_type_matrix4 ||
		variant->type == variant_type_matrix2 ||
		variant->type == variant_type_matrix2x3 ||
		variant->type == variant_type_matrix2x4 ||
		variant->type == variant_type_matrix3 ||
		variant->type == variant_type_matrix3x2 ||
		variant->type == variant_type_matrix3x4 ||
		variant->type == variant_type_matrix4x2 ||
		variant->type == variant_type_matrix4x3;
}
