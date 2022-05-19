#include "application.h"
#include "game_types.h"

#include "logger.h"

#include "platform/platform.h"

typedef struct application_state
{
    game* game_inst;
    b8 is_running;
    b8 is_suspended;
    platform_state platform;
    i16 window_width;
    i16 window_height;
    f64 last_time;
}application_state;

static b8 intialized = FALSE;
static application_state app_state;

b8 application_create(game* game_inst){
    if(intialized){
        BERROR("application_create: Called more than once!");
        return FALSE;
    }
    app_state.game_inst = game_inst;

    // initialize the subsystems
    initialize_logging();

    // TODO: Remove this
    BFATAL("This is a fatal error: %f", 3.14f);
    BERROR("This is an error: %f", 3.14f);
    BWARNING("This is a warning: %f", 3.14f);
    BINFO("This is an info: %f", 3.14f);
    BDEBUG("This is a debug: %f", 3.14f);
    BTRACE("This is a trace: %f", 3.14f);

    app_state.is_running = TRUE;
    app_state.is_suspended = FALSE;

    if(!platform_startup(
        &app_state.platform,
        game_inst->app_config.title,
        game_inst->app_config.start_pos_x,                     
        game_inst->app_config.start_pos_y,
        game_inst->app_config.start_width,
        game_inst->app_config.start_height)){
        return FALSE;
    }

    // Initialize the game.
    if (!app_state.game_inst->initialize(app_state.game_inst)){
        BFATAL("Failed to initialize the game!");
        return FALSE;
    }

    app_state.game_inst->on_resize(app_state.game_inst, app_state.window_width, app_state.window_height);

    intialized = TRUE;

    return TRUE;
}

b8 application_run(){
    while(app_state.is_running){
        if(!platform_pump_messages(&app_state.platform)){
            app_state.is_running = FALSE;
        }

        if(!app_state.is_suspended){
            if(!app_state.game_inst->update(app_state.game_inst, (f32)0)){
                BFATAL("Game update failed, shutting down!");
                app_state.is_running = FALSE;
                break;
            }

            // Call the game's render routine.
            if(!app_state.game_inst->render(app_state.game_inst, (f32)0)) {
                BFATAL("Game render failed, shutting down!");
                app_state.is_running = FALSE;
                break;
            }
        }
    }

    app_state.is_running = FALSE;

    platform_shutdown(&app_state.platform);

    return TRUE;
}