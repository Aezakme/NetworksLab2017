cmake_minimum_required(VERSION 2.8)
project(server_linux)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra")

set(SOURCE_FILES main.c server.h server.c connectinohandler.c)
add_executable(LDAP_server_win ${SOURCE_FILES})

if (MINGW)
    target_link_libraries(LDAP_server ws2_32)
endif ()