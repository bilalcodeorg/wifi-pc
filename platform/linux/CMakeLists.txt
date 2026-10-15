# CMakeList.txt : CMake project for wlan-pc-bcode, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.10)


project (WifiPcLinux VERSION 1.0 LANGUAGES CXX)

# Add library
add_library(
	WifiPcLinux STATIC
	src/wifi_scan.cpp
	src/wifi_scan_helper.cpp
)
add_library(WifiPc::Linux ALIAS WifiPcLinux)
target_include_directories(WifiPcLinux
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)
target_include_directories(WifiPcLinux SYSTEM 
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src/include
)

if(LINUX)
    target_link_libraries(WifiPcLinux PRIVATE nl-3)
    target_link_libraries(WifiPcLinux PRIVATE nl-genl-3)
endif()

set_target_properties(WifiPcLinux PROPERTIES
    OUTPUT_NAME "wifipc_linux_static"
    PREFIX ""
    POSITION_INDEPENDENT_CODE ON
)

# CXX version
function(target_cxx_strict_version target cxx_std_version)
    target_compile_features(${target} PUBLIC cxx_std_${cxx_std_version})

    set_target_properties(
        ${target}
        PROPERTIES
            CXX_STANDARD ${cxx_std_version}
            CXX_STANDARD_REQUIRED ON
            CXX_EXTENSIONS OFF
    )
    if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
        target_compile_options(${target} PRIVATE -Wall -Wextra -pedantic-errors)
        target_compile_options(${target} PRIVATE -Wall -Wextra -pedantic-errors)
    elseif(MSVC)
        target_compile_options(${target} PRIVATE /W4 /permissive-)
        target_compile_options(${target} PRIVATE /W4 /permissive-)
    endif()
endfunction()
# Setting strict CXX version
target_cxx_strict_version(WifiPcLinux 11)