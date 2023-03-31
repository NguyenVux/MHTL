cmake_minimum_required(VERSION 3.24)
project(MHTL)
set(CMAKE_CXX_STANDARD 17)

set(
	COMMON_SOURCES  
	"src/result.inl" 
	"include/result.h"
)
set(PLATFORM_SOURCES)
if(UNIX)

elseif(WIN32)
list(
	APPEND PLATFORM_SOURCES 
)
endif()

if(${CMAKE_CURRENT_SOURCE_DIR} STREQUAL ${CMAKE_SOURCE_DIR})
add_executable(${PROJECT_NAME} ${COMMON_SOURCES}  ${PLATFORM_SOURCES})
else()
add_library(${PROJECT_NAME} STATIC ${COMMON_SOURCES} ${PLATFORM_SOURCES})
endif()

target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")