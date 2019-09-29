#pragma once

// Copyright (c) 2017 rxi
// This library is free software; you can redistribute it and/or modify it
// under the terms of the MIT license. See `log.c` for details.

#include <stdio.h>
#include <stdarg.h>

#define LOG_VERSION "0.1.0"
#define LOG_USE_COLOR

typedef void (*log_LockFn)(void *udata, int lock);

enum
{
    LOGGER_TRACE,
    LOGGER_DEBUG,
    LOGGER_INFO,
    LOGGER_WARN,
    LOGGER_ERROR,
    LOGGER_FATAL
};

#define log_trace(...) log_log(LOGGER_TRACE, __FILE__, __LINE__, __VA_ARGS__)
#define log_debug(...) log_log(LOGGER_DEBUG, __FILE__, __LINE__, __VA_ARGS__)
#define log_info(...) log_log(LOGGER_INFO, __FILE__, __LINE__, __VA_ARGS__)
#define log_warn(...) log_log(LOGGER_WARN, __FILE__, __LINE__, __VA_ARGS__)
#define log_error(...) log_log(LOGGER_ERROR, __FILE__, __LINE__, __VA_ARGS__)
#define log_fatal(...) log_log(LOGGER_FATAL, __FILE__, __LINE__, __VA_ARGS__)

void log_set_udata(void *udata);
void log_set_lock(log_LockFn fn);
void log_set_fp(FILE *fp);
void log_set_level(int level);
void log_set_quiet(int enable);

void log_log(int level, const char *file, int line, const char *fmt, ...);
