#pragma once

#include "../types.h"
#include <stdio.h>

string os_get_home();

/* requires result to be freed */
string os_get_log_path();

void os_write(string data, length length, FILE* fd);

/* returns FALSE on error */
boolean os_mkdir(string directory);
void os_recursive_mkdir(string path);
