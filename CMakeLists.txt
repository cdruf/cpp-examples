cmake_minimum_required(VERSION 3.24)
project(cpp-examples)

set(CMAKE_CXX_STANDARD 20)

# Boost
set(BOOST_DIR /usr/local/boost_1_82_0)
include_directories(${BOOST_DIR})
link_directories(${BOOST_DIR}/stage/lib)



add_executable(boost_example boost_example.cpp)
add_executable(my_bellman_ford my_bellman_ford.cpp MyWeightedDiGraph.h)
