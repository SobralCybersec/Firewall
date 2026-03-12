#ifndef CAPTURE_H
#define CAPTURE_H

#include "../core/config.h"
#include "../filter/filter.h"

typedef void (*PacketHandler)(const Packet* packet, const FilterResult* result);

void capture_start(const Config* config, PacketHandler handler);
void capture_simulate_traffic(const Config* config, PacketHandler handler);

#endif
