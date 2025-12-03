#pragma once

#include "../types.h"

#include <stdio.h>

double os_get_time_since_startup(void);

string os_get_home(void);

/* requires result to be freed */
string os_get_log_path(void);

void os_write(string data, length length, FILE* fd);

/* returns FALSE on error */
boolean os_mkdir(string directory);
void os_recursive_mkdir(string path);
