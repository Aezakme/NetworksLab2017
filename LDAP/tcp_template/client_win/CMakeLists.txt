cmake_minimum_required(VERSION 2.8)
project(client_linux)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra")

set(SOURCE_FILES main.c)
add_executable(LDAP_client_win ${SOURCE_FILES})

if (MINGW)
    target_link_libraries(LDAP_client ws2_32)
endif ()