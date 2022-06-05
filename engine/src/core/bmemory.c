#include "bmemory.h"

#include "core/logger.h"
#include "platform/platform.h"

// TODO: Custom string library.
#include <string.h>
#include <stdio.h>

struct memory_statistics
{
    u64 total_allocated;
    u64 tagged_allocations[MEMORY_TAG_MAX_TAGS];
};

static const char* memory_tag_strings[MEMORY_TAG_MAX_TAGS] = {
    "UNKNOWN    ",
    "ARRAY      ",
    "DARRAY     ",
    "DICT       ",
    "RING_QUEUE ",
    "BST        ",
    "STRING     ",
    "APPLICATION",
    "JOB        ",
    "TEXTURE    ",
    "MAT_INST   ",
    "RENDERER   ",
    "GAME       ",
    "TRANSFORM  ",
    "ENTITY     ",
    "ENTITY_NODE",
    "SCENE      "};

static struct memory_statistics memory_stats;

void initialize_memory_system()
{
    platform_zero_memory(&memory_stats, sizeof(memory_stats));
}

void shutdown_memory_system()
{

}

void* ballocate(u64 size, memory_tag tag)
{
    if(tag == MEMORY_TAG_UNKNOWN)
    {
        BWARNING("MEMORY_TAG_UNKNOWN used in call to ballocate. Re-class the allocation.");
    }

    // TODO: Memory alignment.
    void* block = platform_allocate(size, FALSE);
    platform_zero_memory(block, size);
    if (block)
    {
        memory_stats.total_allocated += size;
        memory_stats.tagged_allocations[tag] += size;
    }

    return block;
}

void bfree(void* block, u64 size, memory_tag tag)
{
    if(tag == MEMORY_TAG_UNKNOWN)
    {
        BWARNING("MEMORY_TAG_UNKNOWN used in call to bfree. Re-class the allocation.");
    }
    
    memory_stats.total_allocated -= size;
    memory_stats.tagged_allocations[tag] -= size;

    // TODO: Memory alignment.
    platform_free(block, FALSE);
}

void* bzero_memory(void* block, u64 size)
{
    return platform_zero_memory(block, size);
}

void* bcopy_memory(void* dest, const void* src, u64 size)
{
    return platform_copy_memory(dest, src, size);
}

void* bset_memory(void* block, i32 value, u64 size)
{
    return platform_set_memory(block, value, size);
}

char* get_memory_usage_string()
{
    const u64 gib = 1024 * 1024 * 1024;
    const u64 mib = 1024 * 1024;
    const u64 kib = 1024;

    char buffer[8000] = "System use (tagged): \n";
    u64 offset = strlen(buffer);

    for(u32 i = 0; i < MEMORY_TAG_MAX_TAGS; i++)
    {
        char unit[4] = "XiB";
        float amount = 1.0f;
        if(memory_stats.tagged_allocations[i] >= gib)
        {
            amount = (float)memory_stats.tagged_allocations[i] / (float)gib;
            unit[0] = 'G';
        } else if(memory_stats.tagged_allocations[i] >= mib){
            amount = (float)memory_stats.tagged_allocations[i] / (float)mib;
            unit[0] = 'M';
        } else if(memory_stats.tagged_allocations[i] >= kib){
            amount = (float)memory_stats.tagged_allocations[i] / (float)kib;
            unit[0] = 'K';
        } else {
            unit[0] = 'B';
            unit[1] = 0;
            amount = (float)memory_stats.tagged_allocations[i];
        }

        i32 length = snprintf(buffer + offset, 8000, "%s: %.2f %s\n", memory_tag_strings[i], amount, unit);
        offset += length;
    }
    char* out_string  = _strdup(buffer);
    return out_string;
}
