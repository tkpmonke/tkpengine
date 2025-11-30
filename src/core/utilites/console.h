#pragma once

#include <stdio.h>
#include <stdarg.h>

#include "../types.h"
#include "visibility.h"

#define TKP_DEFAULT_CONSOLE_BUFFER_ALLOCATION 128

TKP_EXPORT void console_init(boolean print_header, boolean print_help);

/* passing NULL will use a default log path */
TKP_EXPORT void console_init_log_file(string path);

/* defaults to stdout, so no need to call unless you know what you're doing */
TKP_EXPORT void console_set_console_file(FILE* console);

TKP_EXPORT void console_write(string message);
TKP_EXPORT void console_write_len(string message, length len);
TKP_EXPORT void console_write_warning(string warning);
TKP_EXPORT void console_write_error(string error);

TKP_EXPORT void console_va(string message, va_list list);
TKP_EXPORT void console_write_va(string message, ...);
TKP_EXPORT void console_write_warning_va(string warning, ...);
TKP_EXPORT void console_write_error_va(string error, ...);

TKP_EXPORT void console_free(void);
