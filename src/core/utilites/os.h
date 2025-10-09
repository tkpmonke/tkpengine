#pragma once

#include "../types.h"

string os_get_home();

/* requires result to be freed */
string os_get_log_path();

void os_write(string data, length length, u32 fd);
