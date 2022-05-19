#pragma once

#include "core/application.h"
#include "core/logger.h"
#include "game_types.h"

// Externally-defined function to create a game.
extern b8 create_game(game* out_game);

/**
 * The main entry point of the application.
 */
int main(void) {

    // Request game instance from the application.
    game game_inst;
    if(!create_game(&game_inst)) {
        BFATAL("Failed to create game instance.");
        return -1;
    }

    // Ensure the funtion pointers exist.
    if(!game_inst.initialize || !game_inst.update || !game_inst.render || !game_inst.on_resize) {
        BFATAL("Game instance is missing required function pointers.");
        return -2;
    }


    if(!application_create(&game_inst)){
        BINFO("Failed to create application.");
        return 1;
    }

    if(!application_run()){
        BINFO("Application did not shutdown correctly.");
        return 2;
    }

    return 0;
}