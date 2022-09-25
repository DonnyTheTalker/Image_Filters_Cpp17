cmake_minimum_required(VERSION 3.17)
project(image_processor)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

add_executable(image_processor
    image_processor.cpp
        args_parser.cpp
        color.cpp
        image.cpp
        filters/blur_filter.cpp
        filters/complex_filter.cpp
        filters/crop_filter.cpp
        filters/edge_detection_filter.cpp
        filters/grayscale_filter.cpp
        filters/matrix_filter.cpp
        filters/negative_filter.cpp
        filters/sharpening_filter.cpp
)
