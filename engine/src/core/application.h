#pragma once

#include "defines.h"

struct game;


typedef struct application_config
{
    // Window starting position x axis, if applicable.
    i16 start_pos_x;

    // Window starting position y axis, if applicable.
    i16 start_pos_y;

    // Window starting width, if applicable.
    i16 start_width;

    // Window starting height, if applicable.
    i16 start_height;

    // Window title, if applicable.
    char* title;
} application_config;


BAPI b8 application_create(struct game* game_inst);

BAPI b8 application_run();
