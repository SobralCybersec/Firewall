#ifndef BLOCKLIST_H
#define BLOCKLIST_H

#include "../core/config.h"

int blocklist_download(const char* url, const char* filename);
int blocklist_load_from_file(Config* config, const char* filename, Action action);
int blocklist_load_inbound(Config* config);
int blocklist_load_outbound(Config* config);

#endif
