#pragma once

#include <stdio.h>

#define TKP_DEFAULT_CONSOLE_BUFFER_ALLOCATION 128

void console_init(void);

/* passing NULL will use a default log path */
void console_init_log_file(char* path);

/* defaults to stdout, so no need to call unless you know what you're doing */
void console_set_console_file(FILE* console);

void console_write(char* message);
void console_write_warning(char* warning);
void console_write_error(char* error);
void console_free(void);
