cmake_minimum_required(VERSION 2.8)

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)

project(GameEngine)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
file(GLOB SRC_LIST src/*.cpp)

find_package(Boost 1.65.0 COMPONENTS filesystem thread)
if(Boost_FOUND)
       include_directories(${Boost_INCLUDE_DIRS})
endif()

add_library(${PROJECT_NAME} STATIC ${SRC_LIST})



