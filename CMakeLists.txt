cmake_minimum_required(VERSION 3.5)
project(zen_virtual_machine C)

set(CMAKE_C_STANDARD 11)
#SET(CMAKE_BUILD_TYPE "Debug")
#SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g2 -ggdb")
#SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")
SET(PLATFORM_SPECIFIC_LIBS "-lpthread")

add_executable(
    zen
    main.c
    instructions/transfer.c
    instructions/arithmetic.c
    instructions/logic.c
    instructions/control.c
    instructions/gui.c
    instructions/prog.c
    instructions/sys.c
    instructions/cons.c
    instructions/file.c
    instructions/net.c
)

find_package(PkgConfig)
if (PKG_CONFIG_FOUND)
  pkg_check_modules(GTK "gtk+-3.0")
  if (GTK_FOUND)    
    target_link_libraries(zen ${GTK_LIBRARIES})
    add_definitions(${GTK_CFLAGS} ${GTK_CFLAGS_OTHER})
  endif()
endif()

find_package (Threads)
target_link_libraries (zen ${CMAKE_THREAD_LIBS_INIT})