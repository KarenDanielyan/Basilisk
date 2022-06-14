#pragma once

#include "defines.h"

typedef struct event_context 
{
    // 128 bytes
    union 
    {
        i64 i64[2];
        u64 u64[2];
        f64 f64[2];

        i32 i32[4];
        u32 u32[4];
        f32 f32[4];

        i16 i16[8];
        u16 u16[8];
        
        i8 i8[16];
        u8 u8[16];

        char c[16];
    } data;
    
} event_context;

// Should return true if handled
typedef b8 (*pfon_event)(u16 code, void* sender, void* subscriber_inst, event_context data);

b8 event_init();
void event_shutdown();

/**
 * Register to listen for when events are sent with the provided code. Events with duplicate
 * subsriber/callback combos will not be registered again and will cause this to return FALSE.
 * @param code The code of the event to listen for.
 * @param subscriber Pointer to the instance of the subscriber. Can be 0/NULL.
 * @param on_event The callbak function pointer to be invoked when the event is fired.
 * @returns TRUE if the event was registered, FALSE if it was not.
 */
BAPI b8 event_register(u16 code, void* subscriber, pfon_event on_event);

/**
 * Unregister from listening for when events are fired with the provided code. If no matching
 * registration is found, this function will return FALSE.
 * @param code The code of the event to listen for.
 * @param subscriber Pointer to the instance of the subscriber. Can be 0/NULL.
 * @param on_event The callbak function pointer to be invoked when the event is fired.
 * @returns TRUE if the event was unregistered, FALSE if it was not.
 */
BAPI b8 event_unregister(u16 code, void* subscriber, pfon_event on_event);

/**
 * Fires an event to listeners of the given code. If an event handler returns
 * TRUE the event is considered handled and will not be fired to other listeners.
 * @param code The code of the event to fire.
 * @param sender The pointer to the sender. Can be 0/NULL.
 * @param data The data to pass to the event handler.
 * @returns TRUE if the event was handled, FALSE if it was not.
 */
BAPI b8 event_fire(u16 code, void* sender, event_context context);

// System internal event codes. Application should use codes beyond 255.
typedef enum system_event_code {
    // Shuts the application down on the next frame.
    EVENT_CODE_APPLICATION_QUIT = 0x01,

    // Keyboard key pressed.
    /* Context usage:
     * u16 key_code = data.data.u16[0];
     */
    EVENT_CODE_KEY_PRESSED = 0x02,

    // Keyboard key released.
    /* Context usage:
     * u16 key_code = data.data.u16[0];
     */
    EVENT_CODE_KEY_RELEASED = 0x03,

    // Mouse button pressed.
    /* Context usage:
     * u16 button = data.data.u16[0];
     */
    EVENT_CODE_BUTTON_PRESSED = 0x04,

    // Mouse button released.
    /* Context usage:
     * u16 button = data.data.u16[0];
     */
    EVENT_CODE_BUTTON_RELEASED = 0x05,

    // Mouse moved.
    /* Context usage:
     * u16 x = data.data.u16[0];
     * u16 y = data.data.u16[1];
     */
    EVENT_CODE_MOUSE_MOVED = 0x06,

    // Mouse moved.
    /* Context usage:
     * u8 z_delta = data.data.u8[0];
     */
    EVENT_CODE_MOUSE_WHEEL = 0x07,

    // Resized/resolution changed from the OS.
    /* Context usage:
     * u16 width = data.data.u16[0];
     * u16 height = data.data.u16[1];
     */
    EVENT_CODE_RESIZED = 0x08,

    MAX_EVENT_CODE = 0xFF
} system_event_code;