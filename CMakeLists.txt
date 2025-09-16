cmake_minimum_required(VERSION 3.16)

# Tell CMake where to look for additional modules.
# This allows loading cmake_rpn modules.
# 2 search paths are added:
#   - The EC_CMAKE_MODULE_PATH environment variable.
#       This will only work on ECCC's systems.
#   - ${CMAKE_SOURCE_DIR}/cmake_rpn/modules
#       This uses git submodules to fetch cmape_rpn and can work for public projects.
list(APPEND CMAKE_MODULE_PATH $ENV{EC_CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake_rpn/modules)

# Initialize cmake_rpn.  This gets the version from git and configures
# compilers using appropriate presets corresponding to ${EC_ARCH}
# Graceful fallbacks are builtin to also work on non ECCC systems.
include(ec_init)

# Set project properties
project(librmn-client-example DESCRIPTION "An extremely simple example that shows how to use librmn in a client application")

# Set the project's version from what was retrieved from git
# This is optional, but ensures you know exactly what version of the
# code was compiled.
#
# Please note that git does not produce a new version unless commits are
# made. This means that it's not possible to distinguish between
# multiple "dirty" builds.
# Making frequent small commits that target a specific change is a
# best practice.
set(PROJECT_VERSION ${GIT_VERSION})

enable_language(C Fortran)

# Display the actual commands when `make` is executed
set(CMAKE_VERBOSE_MAKEFILE TRUE)

# Check if rmn CMake module was already loaded. Technically, this isn't
# required for such a simple project, but complex projects may be made
# up of multiple components which may have already loaded rmn.
#
# Please note that the library must already be loaded in the
# environement (ssmuse-sh or r.load.dot or setting LD_LIBRARY_PATH and
# CPATH) before executing CMake.
if (NOT rmn_FOUND)
    # The "COMPONENTS shared" part is optional, but can be added to link to
    # the shared library instead of linking statically
    find_package(rmn 20.1.0 REQUIRED)
endif()

# Tell CMake to produce an executable from Fortran source code.
# Multiple source files can be specified after the executable name.
add_executable(fexample example.F90)
# This informs CMake that the executable must be linked with librmn.
# CMake will automatically add all the needed compile flags and link options.
target_link_libraries(fexample rmn::rmn)

# Same thing as the Fortran example, but for a C program.
add_executable(cexample example.c)
target_link_libraries(cexample rmn::rmn)

# Here is an example with MPI
add_executable(is_same_host is_same_host.F90)
# It isn't necessary to add to linked to MPI since rmn already has
# the dependency documented at the CMake level
target_link_libraries(is_same_host PRIVATE rmn::rmn-ompi)
