cmake_minimum_required(VERSION 2.8)

project(GameEngine)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
file(GLOB SRC_LIST src/*.cpp)


include_directories(${CMAKE_CURRENT_SOURCE_DIR}/ext/boost/include)

add_library(${PROJECT_NAME} STATIC ${SRC_LIST})



