#include "config.h"
#include <stdio.h>
#include <string.h>

void config_init(Config* config) {
    config->rule_count = 0;
    strcpy(config->default_redirect_url, "https://www.youtube.com/watch?v=dQw4w9WgXcQ");
}

int config_load(Config* config) {
    FILE* file = fopen(CONFIG_FILE, "r");
    
    if (!file) {
        return -1;
    }

    config->rule_count = 0;
    
    while (fscanf(file, "%31s %hu %d %511s %d", 
                  config->rules[config->rule_count].ip,
                  &config->rules[config->rule_count].port,
                  (int*)&config->rules[config->rule_count].action,
                  config->rules[config->rule_count].redirect_url,
                  &config->rules[config->rule_count].use_wildcard) >= 4) {
        
        if (config->rules[config->rule_count].use_wildcard != 0 && 
            config->rules[config->rule_count].use_wildcard != 1) {
            config->rules[config->rule_count].use_wildcard = 0;
        }
        
        config->rule_count++;
        
        if (config->rule_count >= MAX_RULES) {
            break;
        }
    }

    fclose(file);
    return 0;
}

int config_save(const Config* config) {
    FILE* file = fopen(CONFIG_FILE, "w");
    
    if (!file) {
        return -1;
    }

    for (int i = 0; i < config->rule_count; i++) {
        fprintf(file, "%s %hu %d %s %d\n",
                config->rules[i].ip,
                config->rules[i].port,
                config->rules[i].action,
                config->rules[i].redirect_url,
                config->rules[i].use_wildcard);
    }

    fclose(file);
    return 0;
}
