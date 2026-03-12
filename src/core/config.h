#ifndef CONFIG_H
#define CONFIG_H

#define MAX_URL_LENGTH 512
#define MAX_IP_LENGTH 16
#define MAX_RULES 1024
#define CONFIG_FILE "firewall.conf"
#define MAX_IP_PATTERN 32

typedef enum {
    ACTION_ALLOW,
    ACTION_BLOCK,
    ACTION_REDIRECT
} Action;

typedef struct {
    char ip[MAX_IP_PATTERN];
    unsigned short port;
    Action action;
    char redirect_url[MAX_URL_LENGTH];
    int use_wildcard;
} Rule;

typedef struct {
    Rule rules[MAX_RULES];
    int rule_count;
    char default_redirect_url[MAX_URL_LENGTH];
} Config;

int config_load(Config* config);
int config_save(const Config* config);
void config_init(Config* config);

#endif
