#pragma once

#include "defines.h"

typedef enum memory_tag {
    // For temporary use. Should be assigned one of the below or have a new tag created.
    MEMORY_TAG_UNKNOWN,
    MEMORY_TAG_ARRAY,
    MEMORY_TAG_DARRAY,
    MEMORY_TAG_DICT,
    MEMORY_TAG_RING_QUEUE,
    MEMORY_TAG_BST,
    MEMORY_TAG_STRING,
    MEMORY_TAG_APPLICATION,
    MEMORY_TAG_JOB,
    MEMORY_TAG_TEXTURE,
    MEMORY_TAG_MATERIAL_INSTANCE,
    MEMORY_TAG_RENDERER,
    MEMORY_TAG_GAME,
    MEMORY_TAG_TRANSFORM,
    MEMORY_TAG_ENTITY,
    MEMORY_TAG_ENTITY_NODE,
    MEMORY_TAG_SCENE,

    MEMORY_TAG_MAX_TAGS
} memory_tag;

BAPI void initialize_memory_system();
BAPI void shutdown_memory_system();

BAPI void* ballocate(u64 size, memory_tag tag);

BAPI void bfree(void* block, u64 size, memory_tag tag);

BAPI void* bzero_memory(void* block, u64 size);

BAPI void* bcopy_memory(void* dest, const void* src, u64 size);

BAPI void* bset_memory(void* block, i32 value, u64 size);

BAPI char* get_memory_usage_string();