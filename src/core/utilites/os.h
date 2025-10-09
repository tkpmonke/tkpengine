#pragma once

#include "../types.h"

char* os_get_home();
char* os_get_log_path();

void os_write(char* data, length length, u32 fd);
