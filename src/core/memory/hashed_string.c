#include "hashed_string.h"

#include <string.h>

hashed_string hashed_string_generate(string s) {
	u64 hash = 1469598103934665603ull;
	for (length i = 0; i < strlen(s); ++i) {
		hash = (hash ^ (uchar)s[i]) * 1099511628211ull;
	}
	return hash; 
}
