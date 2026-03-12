#!/bin/bash

echo "Compilando GinTama Firewall..."

gcc -o GinTamaFirewall \
    main.c \
    src/core/config.c \
    src/filter/filter.c \
    src/redirect/redirect.c \
    src/logger/logger.c \
    src/capture/capture.c \
    src/web/web.c \
    -std=c99

if [ $? -eq 0 ]; then
    echo ""
    echo "Compilacao concluida com sucesso!"
    echo "Execute: ./GinTamaFirewall"
else
    echo ""
    echo "Erro na compilacao!"
fi
