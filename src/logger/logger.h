#ifndef LOGGER_H
#define LOGGER_H

#include "../filter/filter.h"

typedef enum {
    LOG_INFO,
    LOG_WARNING,
    LOG_BLOCK,
    LOG_REDIRECT
} LogLevel;

void logger_init(void);
void logger_log_packet(const Packet* packet, const FilterResult* result);
void logger_log_message(LogLevel level, const char* message);
void logger_show_recent(int count);

#endif
