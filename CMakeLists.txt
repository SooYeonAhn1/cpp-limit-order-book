cmake_minimum_required(VERSION 3.20)

project(OrderBook LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(obExec
    main.cpp
    src/OrderBook.cpp
)

target_include_directories(obExec PUBLIC
    ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(obExec)