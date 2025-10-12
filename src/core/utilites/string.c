#include "string.h"

/* https://www.geeksforgeeks.org/c/how-to-convert-an-integer-to-a-string-in-c/ */
void u32_to_str(u32 in, string out) {
	u32 i = 0;

	while (in > 0) {
		out[i++] = (char)(in % 10) + '0';
		in /= 10;
	}

	out[i] = '\0';

	for (int j = 0, k = i - 1; j < k; j++, k--) {
		char temp = out[j];
		out[j] = out[k];
		out[k] = temp;
	}
}

void i32_to_str(i32 in, string out) {
	i32 i = 0;
	i32 sign = in;

	if (in == 0) {
		out[0] = '0';
		out[1] = '\0';
		return;
	}

	while (in > 0) {
		out[i++] = (char)(in % 10) + '0';
		in /= 10;
	}

	if (sign < 0) {
		out[i++] = '-';
	}
	out[i] = '\0';

	for (int j = 0, k = i - 1; j < k; j++, k--) {
		char temp = out[j];
		out[j] = out[k];
		out[k] = temp;
	}
}

void f32_to_str(f32 in, string out);
void f64_to_str(f64 in, string out);

void str_to_u32(string in, u32 out);
void str_to_i32(string in, i32 out);
void str_to_f32(string in, f32 out);
void str_to_f64(string in, f64 out);
