#include "console.h"
#include "os.h"
#include "../types.h"

#include <stdio.h>
#include <string.h>

/*
 *	what i want to do in the future is wait until the end of the frame, and then
 *	write to the log file, kinda as a batching system.
 *
 *	i could extend this further and do it every 5 or so frames, but that kinda
 *	gets rid of the point of having a log system that can be as up-to-date as possible (i
 *	consider waiting until the end of the frame as up-to-date)
 */

static FILE* log_file;
static FILE* console;

void console_init(void) {
	console = stdout;
}

void console_init_log_file(char* path) {
	if (path == NULL) {
		path = os_get_log_path();
	}

	log_file = fopen(path, "w");
}

void console_set_console_file(FILE* file) {
	console = file;
}

void console_write(char* message) {
	os_write(message, strlen(message), console->_fileno);
}

void console_write_warning(char* warning) {

}

void console_write_error(char* error) {

}

void console_free(void);
