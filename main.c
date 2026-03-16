#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include <windows.h>
#endif

#include "src/core/config.h"
#include "src/filter/filter.h"
#include "src/redirect/redirect.h"
#include "src/logger/logger.h"
#include "src/capture/capture.h"
#include "src/web/web.h"
#include "src/blocklist/blocklist.h"

#ifdef _WIN32
static void setup_console(void) {
    system("color 0B");
    system("title GinTama Firewall");
    SetConsoleOutputCP(65001);
}
#else
static void setup_console(void) {}
#endif

static void show_banner(void) {
    const char *art =
"⠀⠀⠈⠳⣄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢄⠀⠀⠀⠀⠘⣦⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠠⠤⣄⡙⣿⣿⣿⣿⡿⣿⣿⣿⣿\n"
"⠻⠶⠦⠤⠼⠿⠆⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡀⠀⠉⠳⣄⠀⠀⠈⣦⠘⣆⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢉⣙⡿⠟⠋⣼⣿⣿⣿⣿\n"
"⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠙⢦⣀⠀⠹⡷⡄⠀⠈⣇⠹⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣼⣿⣿⣿⣿⣿\n"
"⠛⢷⣤⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⢷⡀⢻⡙⢦⡀⠸⡆⢧⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠚⣿⣿⣿⣿⣿⣿\n"
"⠀⢙⣻⣿⠟⠁⠀⠀⠀⠀⡀⠀⠀⠀⠀⠀⣿⢰⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠙⢶⡇⠀⠳⡄⢻⢸⡆⠀⠀⠀⠀⠀⣇⣆⠀⠀⠀⠀⠠⣄⠀⠈⠻⣿⣿⣿⣿\n"
"⢀⣾⠟⠁⣀⡴⠂⠀⠀⡞⠁⠀⠀⠀⠀⠀⢹⡈⡇⠀⠀⢀⠀⠀⠀⠀⠀⢀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢳⡄⠈⢿⣎⣏⠁⠀⠀⠀⠀⠀⠹⣞⣧⠀⠀⠀⠀⠈⢷⣶⣦⣽⣿⣿⣿\n"
"⡿⠁⣠⣾⠏⠀⠀⠀⢠⠃⠀⢠⠀⠀⠀⠀⠀⣇⢹⠀⠀⢸⠀⠀⠀⠀⠀⠈⢧⡀⠀⠀⠀⠀⠀⠀⠀⠀⢀⠙⢤⠈⢧⡈⢧⠀⠰⢠⠹⡄⠀⢯⠙⢷⡀⠀⠀⢹⣌⣿⠿⠿⠇⠵⠟\n"
"⢡⣾⢫⡿⠀⢀⠀⠀⢸⠀⢀⡏⠀⠀⠀⠀⠀⠘⣎⣇⠀⢸⠀⢠⡆⢲⡄⠀⠈⢿⣶⣤⠠⣄⠀⠀⠀⠀⢸⡀⠈⠳⢦⡙⢮⣳⡀⠈⢳⡜⢆⠈⢧⠀⠑⢦⠀⠀⣿⣇⠀⠀⢠⠀⠀\n"
"⣾⠋⢹⡇⡰⠃⠀⠀⢸⠀⣸⠀⠀⠀⠀⠀⢰⠀⢘⠹⡄⠸⣦⠈⣧⠀⣏⠳⣄⡰⣝⢷⣄⡈⢻⣦⡘⣆⠸⣇⠀⠀⠀⠉⠳⢿⣿⣦⡀⠙⠦⡳⢌⢷⡀⠀⠑⢤⣹⣿⠀⠀⣿⠃⠀\n"
"⠀⠀⢸⡏⢠⣿⠀⠀⢰⣿⡇⡇⢱⢸⡀⡇⢸⠻⡆⢿⣆⠀⢿⠹⣄⡟⢿⣆⠀⠉⣉⣽⡽⣽⣿⣿⣿⢿⡿⠀⢾⣧⠀⡇⢀⢰⡼⣧⣷⡌⢷⠀⠀⠀⠀⡈⠙⠯⢽⣿⠀⠀⠀⠀⠀\n"
"⠀⠀⣸⣧⣿⣿⠀⢀⣼⠝⠃⣿⢸⡏⣧⢧⣾⣦⣼⣎⢿⣧⡘⢧⠹⣿⡆⠻⠰⠟⢉⣀⣀⠼⠿⠛⠁⠐⠁⠀⠈⢿⣷⣷⡈⣆⣇⣿⣿⠸⡄⢧⡀⠀⠀⠈⢹⡉⢹⡇⠀⠀⠀⠀⠀\n"
"⠀⣤⡼⣿⠟⢿⣆⣼⡇⠀⠀⢸⣇⢷⠘⣟⣿⣁⡀⠬⢿⣇⣽⣾⣧⡹⣿⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⣿⢿⣳⣹⣿⣿⣿⠂⣷⢸⡇⠀⠀⠀⠘⡇⠸⠇⠀⠀⠀⠀⠀\n"
"⣿⣿⣦⣀⣨⣾⢛⣼⠃⠀⠀⠈⡿⣾⣧⢸⣿⣷⡿⠻⣿⡿⠟⡀⠙⠻⣬⣿⣧⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠙⠃⢫⣿⣿⣿⡟⠆⠾⣸⠃⢀⠀⣀⠀⢹⡀⡄⠀⠀⠀⠀⠀\n"
"⣿⣿⣷⡩⣸⣿⠋⢀⣠⠶⣃⠀⡇⠀⣯⠏⣿⠦⠀⠀⠀⠀⢸⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢻⠟⠈⠁⢠⣟⠀⢰⡹⣞⠦⠀⣳⡽⠿⢻⣿⣿⡇⠀\n"
"⣿⣿⣿⣿⣿⣿⣿⠃⠀⠀⠀⠀⣇⣼⣿⣾⣧⠙⠓⠒⠉⠀⢸⡇⠀⠀⠈⠉⠛⠷⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⣿⣯⣧⠇⢠⠇⠀⣮⣧⠈⢳⣤⣿⡇⠀⣀⣾⡆⠀\n"
"⣿⣿⣷⡩⣸⣿⠋⢀⣠⠶⣃⠀⡇⠀⣯⠏⣿⠦⠀⠀⠀⠀⢸⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢻⠟⠈⠁⢠⣟⠀⢰⡹⣞⠦⠀⣳⡽⠿⢻⣿⣿⡇⠀\n"
"⣿⣿⣿⣿⣿⣗⣾⣯⡴⢾⡏⢠⠇⢰⠁⠀⣿⡀⠀⠀⠀⠀⢸⠃⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣶⠦⠴⢿⡈⡇⢸⠻⣼⡷⠛⣡⣴⠾⠛⠛⠛⢷⡀\n"
"⣿⣿⣿⣿⡋⠉⠁⠀⠠⣾⣧⡿⢀⡏⠀⠀⠻⣧⡀⠀⠀⠀⠘⢦⣄⡀⠀⠐⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣾⡏⠀⠀⠈⢳⡇⢸⣦⡙⢷⣟⠋⠀⠀⠀⠀⠀⠈⢷\n"
"⣿⣿⡿⢿⠁⠀⠀⠀⠀⠙⢿⣷⠀⢣⠀⠀⠀⠙⣧⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⣀⡴⠆⠀⠀⠀⠀⠀⠀⠀⠀⠀⣼⣿⠁⠀⣀⡴⢟⣇⣾⠋⠙⠳⠿⠆⠀⠀⠀⢀⣀⣤⣬\n"
"⣿⣿⠇⠈⢀⠀⠀⠀⠈⠀⠀⠙⢧⡀⢷⡀⠀⠀⠈⠷⢄⣀⠀⠀⠀⠀⣀⠤⠴⠚⠋⢁⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣾⡿⣁⡴⠞⣫⡾⠿⠟⠁⠀⠀⠀⠀⠀⣤⣶⣿⣿⣿⣿⢟\n"
"⣿⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠘⣷⠀⢳⡀⠀⠀⠀⠀⠈⠉⠑⠒⠒⠧⢤⣔⠒⠚⠉⠁⠀⠀⠀⠀⠀⠀⠀⢀⣴⣿⣯⠿⢋⣵⠟⠋⠀⠀⠀⠀⠀⠀⢀⣤⣴⣿⣿⣿⣿⣿⣿⡿\n"
"⣿⡇⢠⠀⠀⣼⠀⠀⠀⠀⠀⠀⠀⠘⣧⠐⢧⣀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠉⠲⢤⡀⠀⠀⠀⠀⠀⢀⣴⣿⣿⠟⣡⡶⠟⠁⠀⠀⠀⠀⠀⣠⣴⣾⣿⣿⣿⣿⣿⡿⠛⠉⠀⠀\n"
"⣿⡿⢿⠂⠀⠐⠀⠀⠀⠀⠀⠀⠀⠀⠙⢧⣀⠀⠉⠓⢦⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠙⣆⠀⢀⣠⣖⣿⡿⠋⣠⡾⠟⠁⠀⠀⠀⠀⣀⣴⣿⠿⣿⣿⣿⣿⡿⠛⠁⠀⠀⠀⠀⠀\n"
"⣿⣧⡀⠀⠀⠠⠀⠀⠀⠀⠀⠀⠀⠀⠀⠘⠋⠳⣄⠀⠀⠈⠳⢤⣀⠀⠀⠀⠀⠀⠀⠀⠀⠘⣞⣿⡾⢿⣏⣤⣾⡋⠀⠀⠀⠀⣠⣴⠾⢛⠉⣠⣾⣿⣿⠿⠋⠀⠀⠀⠀⠀⠀⠀⠀\n"
"⣿⠟⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⠳⣄⠀⠀⠀⠈⠛⠦⣄⡀⠀⠀⠀⠀⠀⠘⢹⣿⣦⡙⠻⣭⣷⣤⠀⠰⠞⠋⠁⠀⠀⣴⣿⣿⠟⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
"⣿⠆⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠳⣤⡀⣠⠶⠚⠉⠁⠀⠀⠀⠀⠀⠀⠀⣿⣿⣷⣄⠈⠹⢿⣷⣄⠀⠀⠀⢠⣾⣿⡿⠋⠀⠀⠀⠀⠀⠀⠀⠀⣀⠀⠀⠀\n"
"⣿⡄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣼⡟⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣴⣿⣿⣿⣿⣷⡀⠀⢻⣿⣦⠀⣠⣿⡿⠋⠀⠀⠀⠀⠀⠀⠀⢀⡠⠞⠁⠀⠀⠀\n"
"⡟⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢰⡟⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⠇⢠⡿⠻⣧⣼⣿⣿⣿⣿⢻⢠⣿⣾⣿⡟⠀⠀⠀⠀⠀⠀⢀⡴⠋⠀⠀⢀⣀⠀⠀⠀⠀\n"
"⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣨⡟⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⡞⠀⣸⡟⢶⣌⣿⣿⣿⣿⡏⢠⣿⣿⣿⠏⠀⠀⠀⠀⠀⠀⡴⠋⠀⢀⡠⠖⠋⠀⠀⠀⠀⠀\n"
"⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣴⠟⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡼⠁⢀⣿⠂⠀⠙⢿⣿⣿⣿⣧⣿⣿⣿⠃⠀⠀⠀⠀⠀⣠⠞⠁⣠⠞⠋⠀⠀⠀⠀⠀⠀⠀⠀\n"
"⣿⣿⣿⣿⣿⣿⣷⣶⣶⣶⣶⣾⣿⣿⣿⣿⣿⣿⠏⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣰⠃⠀⣾⣿⠁⠀⠀⢠⣿⣿⣿⣿⣿⡿⠃⠀⠀⠀⠀⢠⠖⢁⣴⠋⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠃⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠁⠀⢰⣿⣿⡆⠀⠀⢸⣿⣿⣿⣿⡿⠁⠀⠀⠀⠀⣰⠃⣠⠞⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⣾⣿⣿⣧⠀⠀⢸⣿⣿⣿⡟⠁⠀⠀⠀⣠⡞⣡⡞⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n";

    printf("\n%s\n", art);
}

static void show_menu(void) {
    printf("\n  ╔═══════════════════════════════════════════════╗\n");
    printf("  ║         === GinTama Firewall ===                ║\n");
    printf("  ╚═══════════════════════════════════════════════╝\n\n");
    printf("  1. Adicionar Regra\n");
    printf("  2. Listar Regras\n");
    printf("  3. Testar Pacote\n");
    printf("  4. Salvar Configuracao\n");
    printf("  5. Carregar Configuracao\n");
    printf("  6. Ver Logs\n");
    printf("  7. Simular Trafego\n");
    printf("  8. Iniciar Interface Web\n");
    printf("  9. Carregar Blocklist Inbound\n");
    printf("  10. Carregar Blocklist Outbound\n");
    printf("  0. Sair\n\n");
    printf("  Escolha: ");
}

static void handle_add_rule(Config* cfg) {
    if (cfg->rule_count >= MAX_RULES) {
        printf("\n  [ERRO] Limite de regras atingido\n");
        return;
    }

    Rule* r = &cfg->rules[cfg->rule_count];
    int act;

    printf("\n  IP (use * para wildcard, ex: 192.168.*.*): ");
    scanf("%31s", r->ip);
    r->use_wildcard = (strchr(r->ip, '*') != NULL);
    
    printf("  Porta (0 para qualquer): ");
    scanf("%hu", &r->port);
    
    printf("  Acao (0=PERMITIR, 1=BLOQUEAR, 2=REDIRECIONAR): ");
    scanf("%d", &act);
    r->action = (Action)act;

    if (r->action == ACTION_REDIRECT) {
        printf("  URL de Redirecionamento: ");
        scanf("%511s", r->redirect_url);
    } else {
        r->redirect_url[0] = '\0';
    }

    cfg->rule_count++;
    printf("\n  [OK] Regra adicionada\n");
    logger_log_message(LOG_INFO, "Nova regra adicionada");
}

static void handle_list_rules(const Config* cfg) {
    printf("\n  === Regras ===\n\n");
    
    if (cfg->rule_count == 0) {
        printf("  Nenhuma regra configurada\n");
        return;
    }
    
    printf("  Total: %d regras\n\n", cfg->rule_count);
    int limit = cfg->rule_count > 20 ? 20 : cfg->rule_count;
    
    for (int i = 0; i < limit; i++) {
        const Rule* r = &cfg->rules[i];
        const char* act = r->action == ACTION_ALLOW ? "PERMITIR" :
                         r->action == ACTION_BLOCK ? "BLOQUEAR" : "REDIRECIONAR";

        printf("  %d. %s:%hu -> %s", i + 1, r->ip, r->port, act);
        
        if (r->use_wildcard) printf(" [WILDCARD]");
        if (r->action == ACTION_REDIRECT) printf(" (%s)", r->redirect_url);
        
        printf("\n");
    }
    
    if (cfg->rule_count > 20) {
        printf("\n  ... e mais %d regras\n", cfg->rule_count - 20);
    }
}

static void handle_test_packet(const Config* cfg) {
    Packet pkt;

    printf("\n  IP de Origem: ");
    scanf("%15s", pkt.src_ip);
    printf("  IP de Destino: ");
    scanf("%15s", pkt.dst_ip);
    printf("  Porta de Origem: ");
    scanf("%hu", &pkt.src_port);
    printf("  Porta de Destino: ");
    scanf("%hu", &pkt.dst_port);

    FilterResult res = filter_packet(&pkt, cfg);
    logger_log_packet(&pkt, &res);

    printf("\n");
    if (res.action == ACTION_ALLOW) {
        printf("  [RESULTADO] PERMITIDO\n");
    } else if (res.action == ACTION_BLOCK) {
        printf("  [RESULTADO] BLOQUEADO\n");
    } else {
        printf("  [RESULTADO] REDIRECIONADO para %s\n", res.redirect_url);
        printf("  [INFO] Abrindo navegador...\n");
        redirect_to_url(res.redirect_url);
    }
}

static void on_packet(const Packet* pkt, const FilterResult* res) {
    logger_log_packet(pkt, res);
    if (res->action == ACTION_REDIRECT) {
        redirect_to_url(res->redirect_url);
    }
}

int main(void) {
    setup_console();
    
    Config cfg;
    config_init(&cfg);
    logger_init();

    show_banner();

    int opt;
    while (1) {
        show_menu();
        scanf("%d", &opt);

        if (opt == 1) {
            handle_add_rule(&cfg);
        } else if (opt == 2) {
            handle_list_rules(&cfg);
        } else if (opt == 3) {
            handle_test_packet(&cfg);
        } else if (opt == 4) {
            printf(config_save(&cfg) == 0 ? "\n  [OK] Configuracao salva\n" : 
                                            "\n  [ERRO] Falha ao salvar configuracao\n");
        } else if (opt == 5) {
            printf(config_load(&cfg) == 0 ? "\n  [OK] Configuracao carregada\n" : 
                                            "\n  [ERRO] Falha ao carregar configuracao\n");
        } else if (opt == 6) {
            logger_show_recent(20);
        } else if (opt == 7) {
            capture_simulate_traffic(&cfg, on_packet);
        } else if (opt == 8) {
            printf("\n  [INFO] Iniciando interface web na porta 8080...\n");
            web_start_server(&cfg, 8080);
        } else if (opt == 9) {
            blocklist_load_inbound(&cfg);
        } else if (opt == 10) {
            blocklist_load_outbound(&cfg);
        } else if (opt == 0) {
            printf("\n  [INFO] Encerrando GinTama Firewall...\n");
            return 0;
        } else {
            printf("\n  [ERRO] Opcao invalida\n");
        }
    }
}
