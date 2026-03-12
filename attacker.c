#include <stdio.h>
#include <string.h>

#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")
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

static void print_banner(void) {
    printf("\n");
    printf("  ╔═══════════════════════════════════════╗\n");
    printf("  ║   Simulador de Ataque - GinTama FW   ║\n");
    printf("  ╚═══════════════════════════════════════╝\n");
    printf("\n");
}

static void simulate_connection(const char* target_ip, unsigned short target_port) {
#ifdef _WIN32
    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        printf("[ERRO] Falha ao inicializar Winsock\n");
        return;
    }
#endif

    SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == INVALID_SOCKET) {
        printf("[ERRO] Falha ao criar socket\n");
        return;
    }

    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(target_port);
    server.sin_addr.s_addr = inet_addr(target_ip);

    printf("[ATAQUE] Tentando conectar em %s:%d...\n", target_ip, target_port);

    if (connect(sock, (struct sockaddr*)&server, sizeof(server)) == SOCKET_ERROR) {
        printf("[BLOQUEADO] Conexao recusada!\n");
        printf("[INFO] O firewall pode ter bloqueado esta conexao\n");
    } else {
        printf("[SUCESSO] Conexao estabelecida!\n");
        printf("[INFO] O firewall permitiu esta conexao\n");
        
        const char* request = "GET / HTTP/1.1\r\nHost: test\r\n\r\n";
        send(sock, request, strlen(request), 0);
        
        char buffer[1024];
        int received = recv(sock, buffer, sizeof(buffer) - 1, 0);
        if (received > 0) {
            buffer[received] = '\0';
            printf("[RESPOSTA] %d bytes recebidos\n", received);
        }
    }

    closesocket(sock);

#ifdef _WIN32
    WSACleanup();
#endif
}

static void test_multiple_targets(void) {
    printf("\n=== Teste de Multiplos Alvos ===\n\n");

    const char* targets[][2] = {
        {"192.168.1.100", "80"},
        {"192.168.1.100", "443"},
        {"10.0.0.50", "80"},
        {"172.16.0.1", "8080"},
        {"8.8.8.8", "53"}
    };

    for (int i = 0; i < 5; i++) {
        printf("\n[Teste %d]\n", i + 1);
        simulate_connection(targets[i][0], atoi(targets[i][1]));
        printf("\n");
    }
}

static void port_scan(const char* target_ip) {
    printf("\n=== Port Scan em %s ===\n\n", target_ip);

    unsigned short ports[] = {21, 22, 23, 25, 80, 443, 3306, 8080};

    for (int i = 0; i < 8; i++) {
        printf("[Scan] Porta %d... ", ports[i]);
        
#ifdef _WIN32
        WSADATA wsa;
        WSAStartup(MAKEWORD(2, 2), &wsa);
#endif

        SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
        if (sock != INVALID_SOCKET) {
            struct sockaddr_in server;
            server.sin_family = AF_INET;
            server.sin_port = htons(ports[i]);
            server.sin_addr.s_addr = inet_addr(target_ip);

            if (connect(sock, (struct sockaddr*)&server, sizeof(server)) == 0) {
                printf("ABERTA\n");
            } else {
                printf("FECHADA/BLOQUEADA\n");
            }
            closesocket(sock);
        }

#ifdef _WIN32
        WSACleanup();
#endif
    }
}

int main(void) {
    print_banner();

    int choice;

    while (1) {
        printf("\n=== Menu do Atacante ===\n");
        printf("1. Simular Conexao Unica\n");
        printf("2. Testar Multiplos Alvos\n");
        printf("3. Port Scan\n");
        printf("4. Ataque de Forca Bruta (Simulado)\n");
        printf("0. Sair\n");
        printf("Escolha: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                char ip[32];
                int port;
                printf("\nIP Alvo: ");
                scanf("%31s", ip);
                printf("Porta Alvo: ");
                scanf("%d", &port);
                simulate_connection(ip, (unsigned short)port);
                break;
            }

            case 2:
                test_multiple_targets();
                break;

            case 3: {
                char ip[32];
                printf("\nIP Alvo: ");
                scanf("%31s", ip);
                port_scan(ip);
                break;
            }

            case 4: {
                char ip[32];
                int port;
                printf("\nIP Alvo: ");
                scanf("%31s", ip);
                printf("Porta Alvo: ");
                scanf("%d", &port);
                
                printf("\n[ATAQUE] Iniciando forca bruta...\n");
                for (int i = 0; i < 10; i++) {
                    printf("[Tentativa %d] ", i + 1);
                    simulate_connection(ip, (unsigned short)port);
                }
                printf("\n[INFO] Ataque concluido\n");
                break;
            }

            case 0:
                printf("\nEncerrando simulador...\n");
                return 0;

            default:
                printf("\nOpcao invalida\n");
        }
    }

    return 0;
}
