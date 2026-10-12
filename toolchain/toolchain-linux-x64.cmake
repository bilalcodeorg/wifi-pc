# Toolchain file: Linux via GCC (native or cross)
#
# Usage:
#   Native x86_64 build (no sysroot, uses system gcc/g++):
#       cmake --preset linux-x64
#   Cross build, e.g. aarch64 (needs: apt install gcc-aarch64-linux-gnu
#                                              g++-aarch64-linux-gnu):
#       cmake --preset linux-x64 -DTARGET_ARCH=aarch64
#
# Optional switches (pass with -D):
#   TARGET_ARCH      x86_64 (default), aarch64, armv7l, riscv64, ...
#   WPC_STATIC_EXE   ON (default) -> fully static executables
#                    OFF          -> dynamic executables

set(CMAKE_SYSTEM_NAME Linux)

# ---------------------------------------------------------------------------
# Target architecture
# ---------------------------------------------------------------------------
if(NOT DEFINED TARGET_ARCH)
    set(TARGET_ARCH x86_64)
endif()
set(CMAKE_SYSTEM_PROCESSOR ${TARGET_ARCH})

if(NOT DEFINED WPC_STATIC_EXE)
    set(WPC_STATIC_EXE ON)
endif()

# Normalise host arch names (some systems report arm64 instead of aarch64)
set(_host_arch ${CMAKE_HOST_SYSTEM_PROCESSOR})
if(_host_arch STREQUAL "amd64")
    set(_host_arch x86_64)
elseif(_host_arch STREQUAL "arm64")
    set(_host_arch aarch64)
endif()

if(TARGET_ARCH STREQUAL _host_arch)
    set(_WPC_CROSS OFF)
else()
    set(_WPC_CROSS ON)
endif()

# ---------------------------------------------------------------------------
# Compilers
# ---------------------------------------------------------------------------
if(_WPC_CROSS)
    # Debian/Ubuntu triplets differ for some arches
    if(TARGET_ARCH STREQUAL "armv7l" OR TARGET_ARCH STREQUAL "arm")
        set(TOOLCHAIN_PREFIX arm-linux-gnueabihf)
    else()
        set(TOOLCHAIN_PREFIX ${TARGET_ARCH}-linux-gnu)
    endif()

    set(CMAKE_C_COMPILER   ${TOOLCHAIN_PREFIX}-gcc)
    set(CMAKE_CXX_COMPILER ${TOOLCHAIN_PREFIX}-g++)
    set(CMAKE_AR           ${TOOLCHAIN_PREFIX}-ar)
    set(CMAKE_RANLIB       ${TOOLCHAIN_PREFIX}-ranlib)
    set(CMAKE_STRIP        ${TOOLCHAIN_PREFIX}-strip)

    # Target sysroot (Debian/Ubuntu cross packages install here).
    # Only valid for REAL cross builds. Never set this for native builds.
    set(CMAKE_SYSROOT        /usr/${TOOLCHAIN_PREFIX})
    set(CMAKE_FIND_ROOT_PATH /usr/${TOOLCHAIN_PREFIX})

    # Search for programs on the host, libraries/headers/packages in the target
    set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
    set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
    set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
    set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)
else()
    # Native build: plain gcc/g++, no sysroot, default search paths
    set(CMAKE_C_COMPILER   gcc)
    set(CMAKE_CXX_COMPILER g++)
endif()
# No RC compiler: windres is Windows-only

# ---------------------------------------------------------------------------
# Linker flags
# ---------------------------------------------------------------------------
# Shared libs and modules: never pass -static (contradicts building a .so).
# Statically linking the GCC/C++ runtime into them is fine.
set(CMAKE_SHARED_LINKER_FLAGS_INIT "-static-libgcc -static-libstdc++")
set(CMAKE_MODULE_LINKER_FLAGS_INIT "-static -static-libgcc -static-libstdc++")
set(CMAKE_EXE_LINKER_FLAGS_INIT "-static -static-libgcc -static-libstdc++")

# Executables
# if(WPC_STATIC_EXE)
#     # Fully static (needs libc.a: apt install libc6-dev)
# else()
#     set(CMAKE_EXE_LINKER_FLAGS_INIT "-static-libgcc -static-libstdc++")
# endif()