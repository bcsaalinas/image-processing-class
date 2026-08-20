cmake_minimum_required(VERSION 3.20)
project(image_processing_class LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(OpenCV REQUIRED)

file(GLOB EXERCISES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/[0-9][0-9]-*.cpp")
foreach(exercise IN LISTS EXERCISES)
    get_filename_component(name "${exercise}" NAME_WE)
    add_executable(${name} "${exercise}")
    target_link_libraries(${name} PRIVATE ${OpenCV_LIBS})
endforeach()
