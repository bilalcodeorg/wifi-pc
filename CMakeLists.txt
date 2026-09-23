# CMakeList.txt : CMake project for wlan-pc-bcode, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.10)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project (WifiPc VERSION 1.0 LANGUAGES CXX)

# Add library
add_library(
	WifiPc STATIC
	src/scan.cpp
	src/wifi_network.cpp
	platform/src/windows/wifi_scan.cpp
	src/error.cpp
)
add_library(WifiPc::Cpp ALIAS WifiPc)
target_include_directories(WifiPc
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
	PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/platform/include
)

# TODO: Add tests and install targets if needed.

if(WIN32)
    target_link_libraries(WifiPc PRIVATE wlanapi)
endif()

# Standard shared library
project (WifiPcCAbi)
add_library (
	WifiPcCAbi
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

# Test project
project (Test)
add_executable (
	Test
	test/usage.cpp
)
target_include_directories(Test
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)
target_link_libraries(Test PRIVATE WifiPc)

# Test shared lib
project (TestCAbi)
add_executable (
	TestCAbi
	test/c_abi_consume.cpp
)
target_include_directories(TestCAbi
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/c_api/include
)
target_link_libraries(TestCAbi PRIVATE WifiPc::CAbi)

# Cmake version
set_target_properties(
    WifiPc WifiPcCAbi
    PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED ON
        CXX_EXTENSIONS OFF
)