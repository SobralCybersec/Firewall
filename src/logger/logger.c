#include "logger.h"
#include <stdio.h>
#include <time.h>
#include <string.h>

#define LOG_FILE "firewall.log"

void logger_init(void) {
    FILE* file = fopen(LOG_FILE, "a");
    if (file) {
        fprintf(file, "\n=== GinTama Firewall Iniciado ===\n");
        fclose(file);
    }
}

static void get_timestamp(char* buffer, size_t size) {
    time_t now = time(NULL);
    struct tm* t = localtime(&now);
    strftime(buffer, size, "%Y-%m-%d %H:%M:%S", t);
}

void logger_log_packet(const Packet* packet, const FilterResult* result) {
    FILE* file = fopen(LOG_FILE, "a");
    if (!file) {
        return;
    }

    char timestamp[64];
    get_timestamp(timestamp, sizeof(timestamp));

    const char* action_str;
    switch (result->action) {
        case ACTION_ALLOW:
            action_str = "PERMITIR";
            break;
        case ACTION_BLOCK:
            action_str = "BLOQUEAR";
            break;
        case ACTION_REDIRECT:
            action_str = "REDIRECIONAR";
            break;
        default:
            action_str = "DESCONHECIDO";
    }

    fprintf(file, "[%s] %s:%hu -> %s:%hu | %s",
            timestamp,
            packet->src_ip, packet->src_port,
            packet->dst_ip, packet->dst_port,
            action_str);

    if (result->action == ACTION_REDIRECT) {
        fprintf(file, " -> %s", result->redirect_url);
    }

    fprintf(file, "\n");
    fclose(file);
}

void logger_log_message(LogLevel level, const char* message) {
    FILE* file = fopen(LOG_FILE, "a");
    if (!file) {
        return;
    }

    char timestamp[64];
    get_timestamp(timestamp, sizeof(timestamp));

    const char* level_str;
    switch (level) {
        case LOG_INFO:
            level_str = "INFO";
            break;
        case LOG_WARNING:
            level_str = "WARN";
            break;
        case LOG_BLOCK:
            level_str = "BLOCK";
            break;
        case LOG_REDIRECT:
            level_str = "REDIRECT";
            break;
        default:
            level_str = "UNKNOWN";
    }

    fprintf(file, "[%s] [%s] %s\n", timestamp, level_str, message);
    fclose(file);
}

void logger_show_recent(int count) {
    FILE* file = fopen(LOG_FILE, "r");
    if (!file) {
        printf("Nenhum log encontrado\n");
        return;
    }

    char lines[100][512];
    int total = 0;

    while (fgets(lines[total % 100], sizeof(lines[0]), file) && total < 10000) {
        total++;
    }

    fclose(file);

    int start = (total > count) ? (total - count) : 0;
    int display_count = (total > count) ? count : total;

    printf("\n=== Logs Recentes ===\n");
    for (int i = 0; i < display_count; i++) {
        printf("%s", lines[(start + i) % 100]);
    }
}
