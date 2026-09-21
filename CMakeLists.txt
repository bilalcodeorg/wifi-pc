# CMakeList.txt : CMake project for wlan-pc-bcode, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.10)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project (WifiPc)

# Add library
add_library(
	WifiPc STATIC
	src/scan.cpp
	src/wifi_network.cpp
	platform/src/windows/wifi_scan.cpp
	src/error.cpp
)
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
project (WifiPcShared)
add_library (
	WifiPcShared SHARED
    c_api/src/list.cpp
	c_api/src/scan.cpp
	c_api/src/wifi_network.cpp
	c_api/src/error.cpp
)
add_library(WifiPc::Shared ALIAS WifiPcShared)
target_include_directories(WifiPcShared
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/c_api/include
)
target_link_libraries(WifiPcShared PRIVATE WifiPc)
target_compile_definitions(WifiPcShared PRIVATE WPC_COMPILING)

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
project (TestSharedLib)
add_executable (
	TestSharedLib
	test/shared_lib_consume.cpp
)
target_include_directories(TestSharedLib
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)
target_link_libraries(TestSharedLib PRIVATE WifiPc::Shared)

# Cmake version
if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET WifiPc PROPERTY CXX_STANDARD 20)
  set_property(TARGET Test PROPERTY CXX_STANDARD 20)
endif()