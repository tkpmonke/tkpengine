#include "../types.h"
#include "../memory/memory.h"
#include "../version.h"

#include "console.h"
#include "os.h"
#include "str.h"

#include <string.h>
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
	console_write_va("TKPEngine %s\nCompiled on %s at %s\n\n", TKP_GET_VERSION_STRING(), __DATE__, __TIME__);

	printf("Home Path > %s\n", os_get_home());
	if (log_file != NULL) {
		char* log_path = os_get_log_path();
		console_write_va("Log Path > %s\n\n", log_path);
		TKP_FREE(log_path);
	} else {
		console_write("Log Path > Disabled\n\n");
	}

}

void console_init_log_file(string path) {
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

void console_write(string message) {
	if (console != NULL) {
		os_write(message, strlen(message), console->_fileno);
	} if (log_file != NULL) {
		os_write(message, strlen(message), log_file->_fileno);
	}
}

void console_write_len(string message, length len) {
	if (console != NULL) {
		os_write(message, len, console->_fileno);
	} if (log_file != NULL) {
		os_write(message, len, log_file->_fileno);
	}
}

void console_write_warning(string warning) {
	if (console != NULL) {
		os_write("\x1b[1;4;33mWarning:\x1b[0m ", 22, console->_fileno);
		os_write(warning, strlen(warning), console->_fileno);
	} if (log_file != NULL) {
		os_write("Warning: ", 9, log_file->_fileno);
		os_write(warning, strlen(warning), log_file->_fileno);
	}
}

void console_write_error(string error) {
	length len = strlen(error);
	if (console != NULL) {
		os_write("\x1b[1;4;31mError:\x1b[0m ", 20, console->_fileno);
		if (len > 0) {
			os_write(error, len, console->_fileno);
		}
	} if (log_file != NULL) {
		os_write("Error: ", 7, log_file->_fileno);
		if (len > 0) {
			os_write(error, len, log_file->_fileno);
		}
	}
}

/* this is where it's gonna get fun :despairge: */
void console_va(string message, va_list list) {
	char buffer[128];
	length len = strlen(message);
	char last_character = '\0';
	for (length i = 0; i < len; ++i) {
		if (last_character == '%') {
			switch (message[i]) {
				case ('%'): {
					console_write_len("%", 1);
					break;
				} case ('s'): {
					console_write(va_arg(list, string));
					break;
				} case ('d'): case ('i'): {
					i32_to_str(va_arg(list, i32), buffer);
					console_write(buffer);
					break;
				} case ('f'): {
					f32_to_str(va_arg(list, f64), buffer);
					console_write(buffer);
					break;
				}
			}
		} else if (message[i] != '%') {
			console_write_len(&message[i], 1);
		}
		last_character = message[i];
	}
}

void console_write_va(string message, ...) {
	va_list list;
	va_start(list, message);
	console_va(message, list);
	va_end(list);
}

void console_write_warning_va(string warning, ...) {
	va_list list;
	va_start(list, warning);
	console_write_warning("");
	console_va(warning, list);
	va_end(list);
}
void console_write_error_va(string error, ...) {
	va_list list;
	va_start(list, error);
	console_write_error("");
	console_va(error, list);
	va_end(list);
}

void console_free(void) {
	if (log_file != NULL) {
		fclose(log_file);
	}
}
