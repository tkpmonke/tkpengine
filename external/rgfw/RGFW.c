#include "../../src/core/memory/memory.h"
#include "../../src/core/types.h"

#define RGFW_IMPLEMENTATION
#define RGFW_OPENGL
#define RGFW_EXPORT
#define RGFW_INT_DEFINED

#define RGFW_ALLOC TKP_MALLOC
#define RGFW_FREE TKP_FREE

#include "RGFW.h"
