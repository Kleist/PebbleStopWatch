#include "main_layout.h"
#include <pebble.h>

// BEGIN AUTO-GENERATED UI CODE; DO NOT MODIFY
static Window *s_window;
static GFont s_res_bitham_34_medium_numbers;
static TextLayer *lbl_time;
static TextLayer *lbl_debug;

static void initialise_ui(void) {
  s_window = window_create();
  window_set_fullscreen(s_window, 0);
  
  s_res_bitham_34_medium_numbers = fonts_get_system_font(FONT_KEY_BITHAM_34_MEDIUM_NUMBERS);
  // lbl_time
  lbl_time = text_layer_create(GRect(3, 2, 133, 41));
  text_layer_set_text(lbl_time, "00:00.0");
  text_layer_set_font(lbl_time, s_res_bitham_34_medium_numbers);
  layer_add_child(window_get_root_layer(s_window), (Layer *)lbl_time);
  
  // lbl_debug
  lbl_debug = text_layer_create(GRect(3, 39, 139, 125));
  layer_add_child(window_get_root_layer(s_window), (Layer *)lbl_debug);
}

static void destroy_ui(void) {
  window_destroy(s_window);
  text_layer_destroy(lbl_time);
  text_layer_destroy(lbl_debug);
}
// END AUTO-GENERATED UI CODE

static void handle_window_unload(Window* window) {
  destroy_ui();
}

void show_main_layout(void) {
  initialise_ui();
  window_set_window_handlers(s_window, (WindowHandlers) {
    .unload = handle_window_unload,
  });
  window_stack_push(s_window, true);
}

void hide_main_layout(void) {
  window_stack_remove(s_window, true);
}

void view_setTimeLabel(char* text) {
    text_layer_set_text(lbl_time, text);	
}

void view_setDebugLabel(char* text) {
    text_layer_set_text(lbl_debug, text);	
}

Window* view_getWindow() {
	return s_window;
}
