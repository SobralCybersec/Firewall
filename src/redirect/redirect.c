#include "redirect.h"

#include <stdio.h>
#include <stdlib.h>

void redirect_to_url(const char* url) {
    char command[1024];

#ifdef _WIN32
    snprintf(command, sizeof(command), "start %s", url);
#elif __APPLE__
    snprintf(command, sizeof(command), "open %s", url);
#else
    snprintf(command, sizeof(command), "xdg-open %s", url);
#endif

    system(command);
}
