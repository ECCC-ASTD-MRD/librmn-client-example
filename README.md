This project is a very simple example that shows how to use **librmn**
in a client application with [CMake](https://cmake.org).

It contains examples for [C](hello.c) and [Fortran](hello.F90).

[CMakeLists.txt](CMakeLists.txt) shows how to link the library with your
application.


## Requirements

- This only works with the devlopment branch of librmn (20.0.0)
- The library must be accessible through one of the following means:
    - **LD_LIBRARY_PATH** and **CPATH** must contain the paths to the library
      and headers respectively
    - **EC_LD_LIBRARY_PATH** and **EC_INCLUDE_PATH** must contain the paths
      to the library and headers respectively
    - **RMN_ROOT** can be specified in the CMake commande line (-DRMN_ROOT=...)
      or as an environment variable.  In both cases, it must contain the path
      to the installation root of the library under which **lib** and
      **include** must be found.


## Building

1. Create a folder where to build the project
   `mkdir /tmp/librmn-client-example`
2. Go inside the newly created folder
   `cd /tmp/librmn-client-example`
3. Launch CMake on the path where this repository was cloned
   `cmake <librmn-client-example clone path>`
4. Launch make
   `make`