This project is a very simple example that shows how to use **librmn**
in a client application with [CMake](https://cmake.org).

It contains examples for [C](example.c) and [Fortran](example.F90).

[CMakeLists.txt](CMakeLists.txt) shows how to link the library with your
application. This file is loaded with comments to explain what each
CMake command does.


## Requirements

- This only works with the development branch of librmn (20.0.0)
- The library must be accessible through one of the following means:
    - **LD_LIBRARY_PATH**, **LIBRARY_PATH** and **CPATH** must contain
      the paths to the library and headers
    - **EC_LD_LIBRARY_PATH** and **EC_INCLUDE_PATH** must contain the paths
      to the library and headers respectively (done when loading with
      `r.load.dot`/`ssm`)
    - **rmn_ROOT** can be specified in the CMake command line (`-Drmn_ROOT=...`)
      or as an environment variable.  In both cases, it must contain the path
      to the installation root of the library under which **lib** and
      **include** can be found.
- If not building on ECCC's systems, git submodules must be retrieved:
  `git submodule init` followed with `git submodule update --recursive`


## Building

1. Create a folder where to build the project
   `mkdir /tmp/${USER}/librmn-client-example`
2. Go inside the newly created folder
   `cd /tmp/${USER}/librmn-client-example`
3. Launch CMake on the path where this repository was cloned
   `cmake <librmn-client-example clone path>`
4. Launch make
   `make`
