cmake_minimum_required(VERSION 3.9)
project(SmallSharedEngine VERSION 0.1.0 DESCRIPTION "A simple vulkan game engine" LANGUAGES C CXX)

include(GenerateExportHeader)
set(ARCH64 False)
if(${CMAKE_SIZEOF_VOID_P} EQUAL 8)
	set(ARCH64 True)
endif()

find_package(Vulkan REQUIRED)
find_package(GLM REQUIRED)

set(SSE_SRCS 
	src/veritum.cpp
	src/Window.cpp
	src/Win32Window.cpp)

configure_file("${CMAKE_CURRENT_SOURCE_DIR}/config.h.in" "${CMAKE_CURRENT_BINARY_DIR}/config.h")

add_library(engine SHARED ${SSE_SRCS})
target_include_directories(engine PUBLIC ${CMAKE_CURRENT_BINARY_DIR})
target_include_directories(engine PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src")
target_include_directories(engine PUBLIC ${Vulkan_INCLUDE_DIRS})
target_include_directories(engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
GENERATE_EXPORT_HEADER(engine
	BASE_NAME sse_engine
	EXPORT_MACRO_NAME SSEAPI
	DEPRECATED_MACRO_NAME SSE_DEPRICATED)

add_executable(example example/main.cpp)
target_include_directories(example PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(example engine)
