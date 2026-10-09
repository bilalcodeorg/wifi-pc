# CMakeList.txt : CMake project for wlan-pc-bcode, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.10)


project (WifiPc VERSION 1.0 LANGUAGES CXX)

# Add library
add_library(
	WifiPc STATIC
	src/scan.cpp
	src/error.cpp
	src/wifi_network.cpp
	platform/src/windows/wifi_scan.cpp
)
add_library(WifiPc::Cpp ALIAS WifiPc)
target_include_directories(WifiPc
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
	PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/platform/include
)
if(WIN32)
    target_link_libraries(WifiPc PRIVATE wlanapi)
endif()
set_target_properties(WifiPc PROPERTIES
    OUTPUT_NAME "wifipc_static"
    PREFIX ""
)

# Standard shared library
project (WifiPcCAbi)
add_library (
	WifiPcCAbi SHARED
    c_api/src/list.cpp
	c_api/src/scan.cpp
	c_api/src/wifi_network.cpp
	c_api/src/error.cpp
)
add_library(WifiPc::CAbi ALIAS WifiPcCAbi)
target_include_directories(WifiPcCAbi
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/c_api/include
)
target_link_libraries(WifiPcCAbi PRIVATE WifiPc)
target_compile_definitions(WifiPcCAbi PUBLIC WPC_COMPILING)
set_target_properties(WifiPcCAbi PROPERTIES
    OUTPUT_NAME "wifi_pc"
    PREFIX ""
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

target_cxx_strict_version(WifiPc 11)
target_cxx_strict_version(WifiPcCAbi 11)