cmake_minimum_required(VERSION 2.8)

project( codeLearning )

find_package(OpenCV REQUIRED)

set(EXECUTABLE_OUTPUT_PATH ../bin)

include_directories( src )
include_directories( ${OpenCV_INCLUDE_DIRS} )
include_directories("C:/Boost/include/boost-1_59")

file(GLOB_RECURSE codeLearning_SRC "*.cpp" "*.h")
add_executable( codeLearning ${codeLearning_SRC})
target_link_libraries( codeLearning ${OpenCV_LIBS} )
