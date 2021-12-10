cmake_minimum_required(VERSION 3.21)
project(CovidTracker C)

set(CMAKE_C_STANDARD 99)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -rdynamic")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pthread")

add_executable(CovidTracker
        main/main.c
        window/admin/admin_window.c window/admin/admin_window.h
        window/admin/admin_socket.c window/admin/admin_socket.h
        window/onboarding/onboarding_window.c window/onboarding/onboarding_window.h
        window/client/client_window.c window/client/client_window.h
        window/client/client_socket.c window/client/client_socket.h
        common/common.h common/record.h data/data.c data/data.h common/record_display.h)


find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)
include_directories(${GTK3_INCLUDE_DIRS})
link_directories(${GTK3_LIBRARY_DIRS})
add_definitions(${GTK3_CFLAGS_OTHER})
target_link_libraries(CovidTracker ${GTK3_LIBRARIES})