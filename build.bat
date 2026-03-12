@echo off
echo Compilando GinTama Firewall...
echo.

REM Verificar se existe o arquivo de icone
if exist gintama.ico (
    echo Compilando com icone...
    windres resources.rc -O coff -o resources.res
    if %ERRORLEVEL% NEQ 0 (
        echo Aviso: Falha ao compilar recursos, continuando sem icone...
        goto :compile_without_icon
    )
    
    gcc -o GinTamaFirewall.exe ^
        main.c ^
        src/core/config.c ^
        src/filter/filter.c ^
        src/redirect/redirect.c ^
        src/logger/logger.c ^
        src/capture/capture.c ^
        src/web/web.c ^
        src/blocklist/blocklist.c ^
        resources.res ^
        -lws2_32 ^
        -lwininet ^
        -std=c99
    goto :check_result
)

:compile_without_icon
echo Compilando sem icone...
gcc -o GinTamaFirewall.exe ^
    main.c ^
    src/core/config.c ^
    src/filter/filter.c ^
    src/redirect/redirect.c ^
    src/logger/logger.c ^
    src/capture/capture.c ^
    src/web/web.c ^
    src/blocklist/blocklist.c ^
    -lws2_32 ^
    -lwininet ^
    -std=c99

:check_result
if %ERRORLEVEL% EQU 0 (
    echo.
    echo Compilacao concluida com sucesso!
    echo Execute: GinTamaFirewall.exe
) else (
    echo.
    echo Erro na compilacao!
)

pause
