#include "console.h"
#include "os.h"
#include "../types.h"
#include "../memory/memory.h"

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

static FILE* log_file = NULL;
static FILE* console = NULL;

void console_init(void) {
	console = stdout;
}

void console_init_log_file(char* path) {
	boolean b = FALSE;
	if (path == NULL) {
		path = os_get_log_path();
		b = TRUE;
	}

	log_file = fopen(path, "w");
	if (log_file == NULL) {
		console_write_error("Log file could not be found nor created\n");
	}
	
	if (b) {
		TKP_FREE(path);
	}
}

void console_set_console_file(FILE* file) {
	console = file;
}

void console_write(char* message) {
	if (console != NULL) {
		os_write(message, strlen(message), console->_fileno);
	} if (log_file != NULL) {
		os_write(message, strlen(message), log_file->_fileno);
	}
}

void console_write_warning(char* warning) {
	if (console != NULL) {
		os_write("\x1b[1;4;33mWarning:\x1b[0m ", 22, console->_fileno);
		os_write(warning, strlen(warning), console->_fileno);
	} if (log_file != NULL) {
		os_write("Warning: ", 9, log_file->_fileno);
		os_write(warning, strlen(warning), log_file->_fileno);
	}
}

void console_write_error(char* error) {
	if (console != NULL) {
		os_write("\x1b[1;4;31mError:\x1b[0m ", 20, console->_fileno);
		os_write(error, strlen(error), console->_fileno);
	} if (log_file != NULL) {
		os_write("Error: ", 7, log_file->_fileno);
		os_write(error, strlen(error), log_file->_fileno);
	}
}

/* this is where it's gonna get fun :despairge: */
void console_write_va(string message, ...) {
	va_list list;
	va_start(list, message);

	va_end(list);
}

void console_write_warning_va(string warning, ...) {}
void console_write_error_va(string error, ...) {}

void console_free(void) {
	fclose(log_file);
}
