cmake_minimum_required(VERSION 3.16)

project(CppVisionPipeline)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenCV REQUIRED)

add_executable(
    vision_app
    src/main.cpp
    src/FrameProcessor.cpp
)

target_include_directories(
    vision_app
    PRIVATE
    include
    ${OpenCV_INCLUDE_DIRS}
)

target_link_libraries(
    vision_app
    ${OpenCV_LIBS}
)
