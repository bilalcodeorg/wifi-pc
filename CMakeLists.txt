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
	WifiPc
	src/scan.cpp
	src/throw_err.cpp
	src/wifi_network.cpp
	platform/windows/src/windows_wifi_scan.cpp
)
target_include_directories(WifiPc
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
	PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/platform/windows/include
)

# TODO: Add tests and install targets if needed.

if(WIN32)
    target_link_libraries(WifiPc PRIVATE wlanapi)
endif()

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



# Cmake version
if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET WifiPc PROPERTY CXX_STANDARD 20)
  set_property(TARGET Test PROPERTY CXX_STANDARD 20)
endif()