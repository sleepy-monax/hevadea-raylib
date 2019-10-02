#pragma once

#include <stdbool.h>

bool gui_label(const char *text);

bool gui_button(const char *text);

bool gui_checkbox(const char *text, bool *value);

bool gui_section(const char *text, bool *stat);