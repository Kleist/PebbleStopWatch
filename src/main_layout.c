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

enum TimerState {
  Running,
  Paused
};

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

static const uint32_t TIMER_TIMEOUT = 1000;
AppTimer* g_timer;
int g_timerState = Paused;

void setTime(int m, int s, int ds) {
  char timeLabel[8] = "00:00.0";
  timeLabel[0] = m/10+'0';
  timeLabel[1] = m%10+'0';
  timeLabel[3] = s/10+'0';
  timeLabel[4] = s%10+'0';
  timeLabel[6] = ds+'0';
  text_layer_set_text(lbl_time, timeLabel);
}

void timer_callback(void* _) {
  time_t time;
  uint16_t mstime = time_ms(&time, 0);
  //setTime(time/60, time%60, mstime/100);
  char buffer[129];
  snprintf(buffer, 128, "Timer");
  APP_LOG(APP_LOG_LEVEL_DEBUG, "Timer callback called");
  text_layer_set_text(lbl_debug, "Timer callback called");
  g_timer = app_timer_register(TIMER_TIMEOUT, timer_callback, 0);
}

void clickUp(ClickRecognizerRef crRef, void* context) {
  text_layer_set_text(lbl_debug, "Up");
}

void clickConfigProvider(void* context) {
  window_single_click_subscribe(BUTTON_ID_UP, clickUp);
}

int main() {
  show_main_layout();
  g_timer = app_timer_register(TIMER_TIMEOUT, timer_callback, 0);
  window_set_click_config_provider(s_window, clickConfigProvider);
  app_event_loop();
  hide_main_layout();
}
