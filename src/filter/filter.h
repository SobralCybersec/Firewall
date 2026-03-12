#ifndef FILTER_H
#define FILTER_H

#include "../core/config.h"

typedef struct {
    char src_ip[MAX_IP_LENGTH];
    char dst_ip[MAX_IP_LENGTH];
    unsigned short src_port;
    unsigned short dst_port;
} Packet;

typedef struct {
    Action action;
    char redirect_url[MAX_URL_LENGTH];
} FilterResult;

FilterResult filter_packet(const Packet* packet, const Config* config);

#endif
