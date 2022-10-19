cmake_minimum_required(VERSION 3.8)

project(Bronya_tinySTL)

set(CMAKE_CXX_STANDARD 11)

message(STATUS "Project: Bronya_tinySTL")

set(SOURCE_FILES 
${PROJECT_SOURCE_DIR}/tiny/main.cpp
${PROJECT_SOURCE_DIR}/tiny/stl_algobase.h
${PROJECT_SOURCE_DIR}/tiny/stl_allocator.h
${PROJECT_SOURCE_DIR}/tiny/stl_config.h
${PROJECT_SOURCE_DIR}/tiny/stl_construct.h
${PROJECT_SOURCE_DIR}/tiny/stl_iterator_base.h
${PROJECT_SOURCE_DIR}/tiny/stl_iterator.h
${PROJECT_SOURCE_DIR}/tiny/stl_uninitialized.h
${PROJECT_SOURCE_DIR}/tiny/stl_vector.h
${PROJECT_SOURCE_DIR}/tiny/type_traits.h
)

add_executable(Bronya_tinySTL ${SOURCE_FILES})