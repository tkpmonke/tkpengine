#pragma once

#ifndef TKP_NO_STDLIB
	#include <stdlib.h>
	#define TKP_MALLOC malloc
	#define TKP_REALLOC realloc
	#define TKP_FREE free
#endif
