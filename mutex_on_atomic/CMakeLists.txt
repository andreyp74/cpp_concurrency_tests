cmake_minimum_required (VERSION 3.8)

set(PROJECT_NAME_STR test_mutex_on_atomic)

project(${PROJECT_NAME_STR} CXX C)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

link_directories(
    ${CMAKE_BINARY_DIR}
)

if(MSVC)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
    add_definitions(-D_SCL_SECURE_NO_WARNINGS)
    add_definitions(-D_WIN32_WINNT=0x0A00) # Target is windows 10
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
endif()

file(GLOB_RECURSE TEST_ATOMIC_SRCS
        RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp)

add_executable(${PROJECT_NAME_STR} ${TEST_ATOMIC_SRCS})