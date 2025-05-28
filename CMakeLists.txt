cmake_minimum_required(VERSION 3.25)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin) 
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "-std=c++17 -O0 -g -Wno-nontrivial-memaccess -Wimplicit-function-declaration")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(arc CXX C)

add_library(arc
    ${CMAKE_SOURCE_DIR}/src/arc_collision_detection.cpp
    ${CMAKE_SOURCE_DIR}/src/arc_physics_world.cpp
    ${CMAKE_SOURCE_DIR}/src/arc_rigid_body.cpp
)

target_include_directories(arc PUBLIC
    ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(arc PRIVATE 
	stdc++
)

option(BUILD_EXAMPLES "Build examples" ON)
if(BUILD_EXAMPLES)
    add_subdirectory(examples/helloworld)
    add_subdirectory(examples/opengl_2d)
endif()


set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -sEXPORTED_RUNTIME_METHODS=['cwrap','ccall']")
set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE "${CMAKE_COMMAND} -E time")
set_property(TARGET arc PROPERTY RULE_LAUNCH_COMPILE "${CMAKE_COMMAND} -E time")
set(CMAKE_EXPORT_COMPILE_COMMANDS, 1)