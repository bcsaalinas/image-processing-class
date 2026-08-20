cmake_minimum_required(VERSION 3.23)

project(
    image_processing_class
    VERSION 1.0.0
    DESCRIPTION "Small, independent OpenCV exercises for image-processing class"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Do not bake a Homebrew path into the project. OpenCV's package configuration
# is discovered from the active environment, which also keeps this portable.
find_package(OpenCV 5 REQUIRED COMPONENTS core imgproc imgcodecs highgui)

message(STATUS "Using OpenCV ${OpenCV_VERSION} from ${OpenCV_DIR}")

file(
    GLOB_RECURSE CLASS_EXERCISE_SOURCES
    CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/sessions/*.cpp"
)

if(NOT CLASS_EXERCISE_SOURCES)
    message(FATAL_ERROR "No exercises found under sessions/<YYYY-MM-DD>/*.cpp")
endif()

foreach(source_file IN LISTS CLASS_EXERCISE_SOURCES)
    file(RELATIVE_PATH relative_source "${CMAKE_CURRENT_SOURCE_DIR}/sessions" "${source_file}")
    get_filename_component(session_date "${relative_source}" DIRECTORY)
    get_filename_component(exercise_name "${source_file}" NAME_WE)

    set(target_name "exercise_${session_date}_${exercise_name}")
    string(MAKE_C_IDENTIFIER "${target_name}" target_name)

    set(output_name "${session_date}_${exercise_name}")
    string(REPLACE "/" "_" output_name "${output_name}")
    string(REPLACE "\\" "_" output_name "${output_name}")

    add_executable("${target_name}" "${source_file}")
    target_include_directories("${target_name}" PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include")
    target_link_libraries("${target_name}" PRIVATE ${OpenCV_LIBS})
    target_compile_definitions(
        "${target_name}"
        PRIVATE
            CLASS_PROJECT_DIR="${CMAKE_CURRENT_SOURCE_DIR}"
            CLASS_OUTPUT_DIR="${CMAKE_CURRENT_SOURCE_DIR}/outputs/${session_date}/${exercise_name}"
    )

    if(CMAKE_CXX_COMPILER_ID MATCHES "AppleClang|Clang|GNU")
        target_compile_options("${target_name}" PRIVATE -Wall -Wextra -Wpedantic)
    elseif(MSVC)
        target_compile_options("${target_name}" PRIVATE /W4 /permissive-)
    endif()

    set_target_properties(
        "${target_name}"
        PROPERTIES
            OUTPUT_NAME "${output_name}"
            RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    )
endforeach()
