cmake_minimum_required(VERSION 3.20)

project(OrderBook LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS_RELEASE "-O3")
add_executable(obExec
    main.cpp
    src/OrderBook.cpp
    src/Utility.cpp
)

target_include_directories(obExec PUBLIC
    ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(obExec)