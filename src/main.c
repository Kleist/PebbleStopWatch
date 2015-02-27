#include "main_layout.h"

#include <pebble.h>

#include "timer.h"

void clickUp(ClickRecognizerRef crRef, void* context) {
	view_setDebugLabel("Up");
}

void clickConfigProvider(void* context) {
  window_single_click_subscribe(BUTTON_ID_UP, clickUp);
}

int main() {
  show_main_layout();
  timer_init();
  window_set_click_config_provider(view_getWindow(), clickConfigProvider);
  app_event_loop();
  hide_main_layout();
}
