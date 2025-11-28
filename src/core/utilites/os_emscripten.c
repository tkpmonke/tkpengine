#include "os.h"

#if defined (__EMSCRIPTEN__)

	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>

	#include <errno.h>
	#include <sys/stat.h>
	#include <unistd.h>

string os_get_home() {
	return NULL;
}

/* TODO:
 * - put in a subdirectory of game, using name as reference
 * - clear out logs if there are more than X amount
 */

string os_get_log_path() {
	string s = malloc(1);
	return s;
}

void os_write(string data, length length, FILE* fd) {
	(void)length;
	printf("%s", data);
}

boolean os_mkdir(string directory) {
	(void)directory;
	return FALSE;
}

#endif /* platform check */

