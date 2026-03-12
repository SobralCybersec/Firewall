#include "blocklist.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifdef _WIN32
#include <windows.h>
#include <wininet.h>
#pragma comment(lib, "wininet.lib")
#else
#include <curl/curl.h>
#endif

#define INBOUND_URL "https://raw.githubusercontent.com/bitwire-it/ipblocklist/refs/heads/main/inbound.txt"
#define OUTBOUND_URL "https://raw.githubusercontent.com/bitwire-it/ipblocklist/refs/heads/main/outbound.txt"

#ifdef _WIN32
int blocklist_download(const char* url, const char* filename) {
    HINTERNET inet = InternetOpenA("GinTama Firewall", INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
    if (!inet) return -1;

    HINTERNET hurl = InternetOpenUrlA(inet, url, NULL, 0, INTERNET_FLAG_RELOAD, 0);
    if (!hurl) {
        InternetCloseHandle(inet);
        return -1;
    }

    FILE* f = fopen(filename, "w");
    if (!f) {
        InternetCloseHandle(hurl);
        InternetCloseHandle(inet);
        return -1;
    }

    char buf[4096];
    DWORD read;

    while (InternetReadFile(hurl, buf, sizeof(buf) - 1, &read) && read > 0) {
        buf[read] = '\0';
        fputs(buf, f);
    }

    fclose(f);
    InternetCloseHandle(hurl);
    InternetCloseHandle(inet);
    return 0;
}
#else
static size_t write_data(void* ptr, size_t size, size_t nmemb, void* stream) {
    return fwrite(ptr, size, nmemb, (FILE*)stream);
}

int blocklist_download(const char* url, const char* filename) {
    CURL* curl = curl_easy_init();
    if (!curl) return -1;

    FILE* f = fopen(filename, "w");
    if (!f) {
        curl_easy_cleanup(curl);
        return -1;
    }

    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, f);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

    CURLcode res = curl_easy_perform(curl);
    fclose(f);
    curl_easy_cleanup(curl);

    return (res == CURLE_OK) ? 0 : -1;
}
#endif

int blocklist_load_from_file(Config* cfg, const char* filename, Action act) {
    FILE* f = fopen(filename, "r");
    if (!f) return -1;

    char line[256];
    int count = 0;

    while (fgets(line, sizeof(line), f) && cfg->rule_count < MAX_RULES) {
        line[strcspn(line, "\r\n")] = '\0';
        
        if (strlen(line) == 0 || line[0] == '#') continue;

        Rule* r = &cfg->rules[cfg->rule_count];
        strncpy(r->ip, line, MAX_IP_PATTERN - 1);
        r->ip[MAX_IP_PATTERN - 1] = '\0';
        r->port = 0;
        r->action = act;
        r->redirect_url[0] = '\0';
        r->use_wildcard = 0;

        cfg->rule_count++;
        count++;
    }

    fclose(f);
    return count;
}

int blocklist_load_inbound(Config* cfg) {
    printf("\n  [INFO] Baixando lista inbound...\n");
    
    if (blocklist_download(INBOUND_URL, "inbound.txt") != 0) {
        printf("  [ERRO] Falha ao baixar inbound.txt\n");
        return -1;
    }

    printf("  [OK] Download concluido\n");
    printf("  [INFO] Carregando regras...\n");

    int n = blocklist_load_from_file(cfg, "inbound.txt", ACTION_BLOCK);
    
    if (n > 0) {
        printf("  [OK] %d IPs bloqueados (inbound)\n", n);
        return n;
    }

    printf("  [ERRO] Falha ao carregar regras\n");
    return -1;
}

int blocklist_load_outbound(Config* cfg) {
    printf("\n  [INFO] Baixando lista outbound...\n");
    
    if (blocklist_download(OUTBOUND_URL, "outbound.txt") != 0) {
        printf("  [ERRO] Falha ao baixar outbound.txt\n");
        return -1;
    }

    printf("  [OK] Download concluido\n");
    printf("  [INFO] Carregando regras...\n");

    int n = blocklist_load_from_file(cfg, "outbound.txt", ACTION_BLOCK);
    
    if (n > 0) {
        printf("  [OK] %d IPs bloqueados (outbound)\n", n);
        return n;
    }

    printf("  [ERRO] Falha ao carregar regras\n");
    return -1;
}
