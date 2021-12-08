cmake_minimum_required(VERSION 3.16)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake_rpn)
include(ec_init)
ec_git_version()

project(librmn-client-example DESCRIPTION "An extremely simple example that shows how to use librmn in a client application")
set(PROJECT_VERSION ${GIT_VERSION})

enable_language(C Fortran)

set(CMAKE_VERBOSE_MAKEFILE TRUE)

# The link type for librmn can be explicitly specified using RMN_LINK_TYPE
# It can be STATIC or SHARED.  For example:
#   set(RMN_LINK_TYPE STATIC)
# If BUILD_SHARED_LIBS has been explicitly defined, it will be used to figure out RMN_LINK_TYPE.
# As a last resort, the link type will be set to STATIC

set(RMN_LINK_TYPE SHARED)
find_package(rmn 20.0.0 REQUIRED)

add_executable(fexample example.F90)
target_link_libraries(fexample rmn)

add_executable(cexample example.c)
target_link_libraries(cexample rmn)
