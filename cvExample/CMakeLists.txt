cmake_minimum_required(VERSION 3.29)
set(targetName learnOpencvExample)
project(${targetName})

set(CMAKE_CXX_STANDARD 17)
file(GLOB_RECURSE SOURCE_FILES "*.cpp")

add_executable(${targetName} ${SOURCE_FILES})

target_link_libraries(${targetName} PUBLIC  ${OpenCV_LIBS})
