cmake_minimum_required(VERSION 2.8)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

project( PartD_12 )
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )
add_executable( ${PROJECT_NAME} PartD_12.cpp )
target_link_libraries( ${PROJECT_NAME} ${OpenCV_LIBS} )



