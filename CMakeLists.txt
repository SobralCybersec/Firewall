cmake_minimum_required(VERSION 3.20)
project(GinTamaFirewall C)

set(CMAKE_C_STANDARD 99)

if(WIN32)
    set(PLATFORM_LIBS ws2_32 wininet)
    enable_language(RC)
    set(RESOURCE_FILE resources.rc)
endif()

add_executable(GinTamaFirewall 
    main.c
    src/core/config.c
    src/filter/filter.c
    src/redirect/redirect.c
    src/logger/logger.c
    src/capture/capture.c
    src/web/web.c
    src/blocklist/blocklist.c
    ${RESOURCE_FILE}
)

if(WIN32)
    target_link_libraries(GinTamaFirewall ${PLATFORM_LIBS})
endif()
