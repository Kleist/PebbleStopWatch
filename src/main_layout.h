#pragma once
#include <pebble.h>

void show_main_layout(void);
void hide_main_layout(void);

void view_setTimeLabel(char* text);
void view_setDebugLabel(char* text);

Window* view_getWindow();