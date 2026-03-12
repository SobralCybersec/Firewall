#include "filter.h"
#include <string.h>

static int match_wildcard(const char* pattern, const char* ip) {
    char pattern_copy[MAX_IP_PATTERN];
    char ip_copy[MAX_IP_LENGTH];
    strcpy(pattern_copy, pattern);
    strcpy(ip_copy, ip);

    char* p_token = strtok(pattern_copy, ".");
    char* i_token = strtok(ip_copy, ".");

    while (p_token && i_token) {
        if (strcmp(p_token, "*") != 0 && strcmp(p_token, i_token) != 0) {
            return 0;
        }
        p_token = strtok(NULL, ".");
        i_token = strtok(NULL, ".");
    }

    return (p_token == NULL && i_token == NULL);
}

FilterResult filter_packet(const Packet* packet, const Config* config) {
    FilterResult result = {ACTION_ALLOW, ""};

    for (int i = 0; i < config->rule_count; i++) {
        const Rule* rule = &config->rules[i];
        
        int ip_match = rule->use_wildcard ? 
                       match_wildcard(rule->ip, packet->dst_ip) :
                       (strcmp(packet->dst_ip, rule->ip) == 0);
        
        if (ip_match && (rule->port == 0 || packet->dst_port == rule->port)) {
            
            result.action = rule->action;
            
            if (rule->action == ACTION_REDIRECT) {
                strcpy(result.redirect_url, rule->redirect_url);
            }
            
            return result;
        }
    }

    return result;
}
