#include "os.h"

/* ik i don't need to check for *all* of these, but why not */
#if defined(__unix__) || defined(__linux__) || defined(__gnu_linux__)

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

string os_get_home() {
	const string home_is_not_set_error = "$HOME is not set\n";
	u8 home_is_not_set_error_len = 17;
	char* home = getenv("HOME");
	
	if (home == NULL) {
		os_write((char*)home_is_not_set_error, home_is_not_set_error_len, stdout->_fileno);
		return NULL;
	}

	return home;
}

/* TODO:
 * - put in a subdirectory of game, using name as reference
 * - clear out logs if there are more than X amount
 */

string os_get_log_path() {
	const string log_path = "/tkpengine/logs/log.txt";
	char* cache = getenv("XDG_CACHE_HOME");
	boolean b = cache == NULL;
	
	if (b) {
		char* home = os_get_home();
		int home_len = strlen(home);

		cache = malloc(home_len);
		memcpy(cache, home, home_len);
		memcpy(cache+home_len, "/.cache", 7);
	}
	
	int cache_len = strlen(cache);
	int log_len = strlen(log_path);
	string path = (string)malloc(cache_len+log_len);
	memcpy(path, cache, cache_len);
	memcpy(path+cache_len, log_path, log_len);

	if (b) {
		free(cache); 
	}

	return path;
}

void os_write(string data, length length, u32 fd) {
	write(fd, data, length);
}

#endif /* platform check */
