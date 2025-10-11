#include "os.h"
#include "console.h"
#include "../memory/memory.h"

/* ik i don't need to check for *all* of these, but why not */
#if defined(__unix__) || defined(__linux__) || defined(__gnu_linux__)

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <errno.h>
#include <unistd.h>
#include <sys/stat.h>

string os_get_home() {
	const string home_is_not_set_error = "$HOME is not set\n";
	u8 home_is_not_set_error_len = 17;
	string home = getenv("HOME");
	
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
	const string logs_dir = "/tkpengine/logs/";
	const string logs_file_name = "log.txt";

	string cache = getenv("XDG_CACHE_HOME");
	boolean b = cache == NULL;
	
	if (b) {
		char* home = os_get_home();
		length home_len = strlen(home);

		cache = malloc(home_len);
		memcpy(cache, home, home_len);
		memcpy(cache+home_len, "/.cache", 7);
	}
	
	int cache_len = strlen(cache);
	length log_len = strlen(logs_dir);
	length logs_file_name_len = strlen(logs_dir);
	string path = (string)malloc(cache_len+log_len+logs_file_name_len);
	memcpy(path, cache, cache_len);
	memcpy(path+cache_len, logs_dir, log_len);
		
	struct stat st;
	if (stat(path, &st) != 0) {
		os_recursive_mkdir(path);
	}

	memcpy(path+cache_len+log_len, logs_file_name, logs_file_name_len);

	if (b) {
		free(cache); 
	}

	return path;
}

void os_write(string data, length length, u32 fd) {
	write(fd, data, length);
}

boolean os_mkdir(string directory) {
	errno = 0;
	if (mkdir(directory, 0777) == 0) {
		return TRUE;
	}

	if (errno != EEXIST) {
		console_write_error("Error detected when creating path");
		return FALSE;
	}

	struct stat st;
	if (stat(directory, &st) != 0) {
		console_write_error("Error detected when creating path, path doesn't exist");
		return FALSE;
	}

	if (!S_ISDIR(st.st_mode)) {
		errno = ENOTDIR;
		console_write_error("Error detected when creating path, path is a file");
		return FALSE;
	}

	return TRUE;
}

/* 
 * "inspired" by 
 * https://gist.github.com/JonathonReinhart/8c0d90191c38af2dcadb102c4e202950 
 *
 * "inspired" as in copyed and converted into my formatting :var:
 */
void os_recursive_mkdir(string path) {
	length path_len = strlen(path);
	string path_dup = TKP_MALLOC(path_len);
	if (path_dup == NULL) {
		return;
	}

	memcpy(path_dup, path, path_len);

	for (char* p = path_dup+1; *p; p++) {
		if (*p == '/') {
			*p = '\0';
			if (os_mkdir(path_dup) == FALSE) {
				goto finished;
			}
			*p = '/';
		}
	}

finished:
	TKP_FREE(path_dup);
}

#endif /* platform check */
