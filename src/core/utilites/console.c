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

static FILE* _log_file = NULL;
static FILE* _console = NULL;

static const string _help_message =
"-h/--help\t-\tprints this help message\n"
"--width\t\t-\tspecify custom window width\n"
"--height\t-\tspecify custom window height\n"
"--log-path\t-\tspecify custom log path (default is ~/.cache/tkpengine/logs/log.txt)\n"
"--no-header\t-\tdon't print the starting header\n\n";

void console_init(arguments_t* args) {
#if defined(__linux__)
	const string os = "linux";
#elif defined(__unix__)
	const string os = "unix";
#elif defined(_WIN32)
	const string os = "windows";
#else
	const string os = "undefined";
#endif

	_console = stdout;

	if (args->print_header == TRUE) {
		console_write_va("TKPEngine %s-%s\nCompiled on %s at %s\n\n", TKP_GET_VERSION_STRING(), os, __DATE__, __TIME__);
		console_write_va("Home Path > %s\n", os_get_home());

		if (_log_file != NULL) {
			if (args->log_path == NULL) {
			char* log_path = os_get_log_path();
			console_write_va("Log Path > %s\n\n", log_path);
			TKP_FREE(log_path);
			} else {
				console_write_va("Log Path > %s\n\n", args->log_path);
			}
		} else {
			console_write("Log Path > Disabled\n\n");
		}
	}

	if (args->print_help_message == TRUE) {
		console_write(_help_message);
		console_free();
		TKP_FREE(args);
		exit(0);
	}
}

void console_init_log_file(string path) {
	boolean b = FALSE;
	if (path == NULL) {
		path = os_get_log_path();
		b = TRUE;
	}

	_log_file = fopen(path, "w");
	if (_log_file == NULL) {
		console_write_error("Log file could not be found nor created\n");
	}
	
	if (b) {
		TKP_FREE(path);
	}
}

void console_set_console_file(FILE* file) {
	_console = file;
}

void console_write(string message) {
	if (_console != NULL) {
		os_write(message, strlen(message), _console->_fileno);
	} if (_log_file != NULL) {
		os_write(message, strlen(message), _log_file->_fileno);
	}
}

void console_write_len(string message, length len) {
	if (_console != NULL) {
		os_write(message, len, _console->_fileno);
	} if (_log_file != NULL) {
		os_write(message, len, _log_file->_fileno);
	}
}

void console_write_warning(string warning) {
	if (_console != NULL) {
		os_write("\x1b[1;4;33mWarning:\x1b[0m ", 22, _console->_fileno);
		os_write(warning, strlen(warning), _console->_fileno);
	} if (_log_file != NULL) {
		os_write("Warning: ", 9, _log_file->_fileno);
		os_write(warning, strlen(warning), _log_file->_fileno);
	}
}

void console_write_error(string error) {
	length len = strlen(error);
	if (_console != NULL) {
		os_write("\x1b[1;4;31mError:\x1b[0m ", 20, _console->_fileno);
		if (len > 0) {
			os_write(error, len, _console->_fileno);
		}
	} if (_log_file != NULL) {
		os_write("Error: ", 7, _log_file->_fileno);
		if (len > 0) {
			os_write(error, len, _log_file->_fileno);
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
	if (_log_file != NULL) {
		fclose(_log_file);
	}
}
