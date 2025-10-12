#include "string.h"
#include "cglm/cglm.h"

/* https://www.geeksforgeeks.org/c/how-to-convert-an-integer-to-a-string-in-c/ */
i32 u32_to_str(u32 in, string out) {
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

	return i;
}

i32 i32_to_str(i32 in, string out) {
	i32 i = 0;
	i32 sign = in;

	if (in < 0) {
		in = -in;
	}

	if (in == 0) {
		out[0] = '0';
		out[1] = '\0';
		return 1;
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
	
	return i;
}

/* https://www.geeksforgeeks.org/cpp/convert-floating-point-number-string/ */
void f32_to_str(f32 in, string out) {
	i32 post_dec = (int)in;
	float pre_dec = in-(float)post_dec;
	int i = i32_to_str(post_dec, out);
	
	out[i] = '.';
	
	/* pow(10, 5) is 100,000 */
	pre_dec *= 100000;
	if (pre_dec < 0) {
		pre_dec = -pre_dec;
	}
	i32_to_str((int)pre_dec, out+i+1);
}
