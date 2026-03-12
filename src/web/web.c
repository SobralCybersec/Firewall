#include "web.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")
typedef int socklen_t;
#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#define closesocket close
#define SOCKET int
#define INVALID_SOCKET -1
#define SOCKET_ERROR -1
#endif

static void send_response(SOCKET client, const char* content) {
    char response[8192];
    snprintf(response, sizeof(response),
             "HTTP/1.1 200 OK\r\n"
             "Content-Type: text/html; charset=utf-8\r\n"
             "Content-Length: %zu\r\n"
             "Connection: close\r\n"
             "\r\n%s", strlen(content), content);
    
    send(client, response, (int)strlen(response), 0);
}

static void generate_html(const Config* config, char* buffer, size_t size) {
    snprintf(buffer, size,
        "<!DOCTYPE html>"
        "<html><head><meta charset='utf-8'><title>GinTama Firewall</title>"
        "<style>"
        "body{font-family:Arial;margin:40px;background:#f5f5f5}"
        "h1{color:#333}"
        "table{width:100%%;border-collapse:collapse;background:white;box-shadow:0 2px 4px rgba(0,0,0,0.1)}"
        "th,td{padding:12px;text-align:left;border-bottom:1px solid #ddd}"
        "th{background:#4CAF50;color:white}"
        ".allow{color:green}.block{color:red}.redirect{color:blue}"
        "</style></head><body>"
        "<h1>GinTama Firewall - Regras</h1>"
        "<table><tr><th>IP</th><th>Porta</th><th>Acao</th><th>URL de Redirecionamento</th></tr>");

    for (int i = 0; i < config->rule_count; i++) {
        const Rule* rule = &config->rules[i];
        const char* action_str;
        const char* action_class;

        switch (rule->action) {
            case ACTION_ALLOW:
                action_str = "PERMITIR";
                action_class = "allow";
                break;
            case ACTION_BLOCK:
                action_str = "BLOQUEAR";
                action_class = "block";
                break;
            case ACTION_REDIRECT:
                action_str = "REDIRECIONAR";
                action_class = "redirect";
                break;
            default:
                action_str = "DESCONHECIDO";
                action_class = "";
        }

        char row[512];
        snprintf(row, sizeof(row),
                "<tr><td>%s</td><td>%hu</td><td class='%s'>%s</td><td>%s</td></tr>",
                rule->ip, rule->port, action_class, action_str,
                rule->action == ACTION_REDIRECT ? rule->redirect_url : "-");
        
        strncat(buffer, row, size - strlen(buffer) - 1);
    }

    strncat(buffer, "</table></body></html>", size - strlen(buffer) - 1);
}

void web_start_server(Config* config, unsigned short port) {
#ifdef _WIN32
    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        printf("Falha ao inicializar Winsock\n");
        return;
    }
#endif

    SOCKET server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == INVALID_SOCKET) {
        printf("Falha ao criar socket\n");
        return;
    }

    int opt = 1;
    setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, (char*)&opt, sizeof(opt));

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(port);

    if (bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) == SOCKET_ERROR) {
        printf("Falha no bind\n");
        closesocket(server_socket);
        return;
    }

    if (listen(server_socket, 5) == SOCKET_ERROR) {
        printf("Falha no listen\n");
        closesocket(server_socket);
        return;
    }

    printf("Interface web iniciada em http://localhost:%hu\n", port);
    printf("Pressione Ctrl+C para parar\n\n");

    while (1) {
        struct sockaddr_in client_addr;
        socklen_t client_len = sizeof(client_addr);
        SOCKET client_socket = accept(server_socket, (struct sockaddr*)&client_addr, &client_len);

        if (client_socket == INVALID_SOCKET) {
            continue;
        }

        char buffer[8192];
        recv(client_socket, buffer, sizeof(buffer) - 1, 0);

        char html[8192];
        generate_html(config, html, sizeof(html));
        send_response(client_socket, html);

        closesocket(client_socket);
    }

    closesocket(server_socket);
#ifdef _WIN32
    WSACleanup();
#endif
}
