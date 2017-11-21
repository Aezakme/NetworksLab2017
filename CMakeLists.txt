cmake_minimum_required(VERSION 3.8)
project(NetworksLab2017)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "$CMAKE_CXX_FLAGS} -pthread -g2 -O0")

#ADD_SUBDIRECTORY(tcp_template/client_linux)
#ADD_SUBDIRECTORY(tcp_template/server_linux)
#
#ADD_SUBDIRECTORY(udp_template/client_linux)
#ADD_SUBDIRECTORY(udp_template/server_linux)

ADD_SUBDIRECTORY(LDAP/tcp_template/client_linux)
ADD_SUBDIRECTORY(LDAP/tcp_template/server_linux)

