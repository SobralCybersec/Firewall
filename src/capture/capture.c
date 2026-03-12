#include "capture.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")
#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#endif

void capture_simulate_traffic(const Config* config, PacketHandler handler) {
    printf("\n=== Simulando Trafego ===\n");
    printf("Gerando pacotes de teste...\n\n");

    const char* test_ips[] = {
        "192.168.1.100",
        "10.0.0.50",
        "172.16.0.1",
        "8.8.8.8",
        "1.1.1.1"
    };

    const unsigned short test_ports[] = {80, 443, 8080, 22, 3306};

    for (int i = 0; i < 10; i++) {
        Packet packet;
        strcpy(packet.src_ip, "192.168.1.50");
        packet.src_port = 50000 + i;
        
        strcpy(packet.dst_ip, test_ips[i % 5]);
        packet.dst_port = test_ports[i % 5];

        FilterResult result = filter_packet(&packet, config);

        printf("Packet %d: %s:%hu -> %s:%hu | ",
               i + 1,
               packet.src_ip, packet.src_port,
               packet.dst_ip, packet.dst_port);

        switch (result.action) {
            case ACTION_ALLOW:
                printf("PERMITIDO\n");
                break;
            case ACTION_BLOCK:
                printf("BLOQUEADO\n");
                break;
            case ACTION_REDIRECT:
                printf("REDIRECIONADO -> %s\n", result.redirect_url);
                break;
        }

        if (handler) {
            handler(&packet, &result);
        }
    }

    printf("\nSimulacao completa\n");
}

void capture_start(const Config* config, PacketHandler handler) {
#ifdef _WIN32
    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        printf("WSAStartup failed\n");
        return;
    }
#endif

    printf("Iniciando captura de pacotes...\n");
    printf("Pressione Ctrl+C para parar\n\n");

    capture_simulate_traffic(config, handler);

#ifdef _WIN32
    WSACleanup();
#endif
}
