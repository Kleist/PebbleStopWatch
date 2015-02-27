#include "main_layout.h"

#include <pebble.h>


enum TimerState {
  Running,
  Paused
};

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
  view_setTimeLabel(timeLabel);
}

void timer_callback(void* _) {
  time_t time;
  uint16_t mstime = time_ms(&time, 0);
  //setTime(time/60, time%60, mstime/100);
  char buffer[129];
  snprintf(buffer, 128, "Timer");
  APP_LOG(APP_LOG_LEVEL_DEBUG, "Timer callback called");
  view_setDebugLabel("Timer callback called");
  g_timer = app_timer_register(TIMER_TIMEOUT, timer_callback, 0);
}

void clickUp(ClickRecognizerRef crRef, void* context) {
	view_setDebugLabel("Up");
}

void clickConfigProvider(void* context) {
  window_single_click_subscribe(BUTTON_ID_UP, clickUp);
}

int main() {
  show_main_layout();
  g_timer = app_timer_register(TIMER_TIMEOUT, timer_callback, 0);
  window_set_click_config_provider(view_getWindow(), clickConfigProvider);
  app_event_loop();
  hide_main_layout();
}
