#pragma once

#include <stdio.h>
#include <stdarg.h>

#include "../types.h"
#include "arguments.h"

#define TKP_DEFAULT_CONSOLE_BUFFER_ALLOCATION 128

void console_init(arguments_t* args);

/* passing NULL will use a default log path */
void console_init_log_file(string path);

/* defaults to stdout, so no need to call unless you know what you're doing */
void console_set_console_file(FILE* console);

void console_write(string message);
void console_write_len(string message, length len);
void console_write_warning(string warning);
void console_write_error(string error);

void console_va(string message, va_list list);
void console_write_va(string message, ...);
void console_write_warning_va(string warning, ...);
void console_write_error_va(string error, ...);

void console_free(void);
