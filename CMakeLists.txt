cmake_minimum_required(VERSION 3.16)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake_rpn/modules)
include(ec_init)
ec_git_version()

project(librmn-client-example DESCRIPTION "An extremely simple example that shows how to use librmn in a client application")
set(PROJECT_VERSION ${GIT_VERSION})

enable_language(C Fortran)

set(CMAKE_VERBOSE_MAKEFILE TRUE)

if (NOT rmn_FOUND)
    # The "COMPONENTS shared" part is optional, but can be added to link to
    # the shared library instead of linking statically
    find_package(rmn 20.0.0 REQUIRED COMPONENTS shared)
endif()

add_executable(fexample example.F90)
target_link_libraries(fexample rmn)

add_executable(cexample example.c)
target_link_libraries(cexample rmn)
