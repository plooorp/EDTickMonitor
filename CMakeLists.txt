cmake_minimum_required(VERSION 3.16)
project(EDTickMonitor
	DESCRIPTION "Elite Dangerous BGS tick monitor"
	VERSION 1.0.0
	LANGUAGES CXX
)

include(qt.cmake)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(src)
