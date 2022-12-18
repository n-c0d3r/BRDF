cmake_minimum_required(VERSION 3.10)



project(BRDF)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 17)



set(BRDF_CMAKE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/CMake)
set(BRDF_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR}/BRDF/$<CONFIG>)



add_definitions(-DUNICODE)



if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/UL/CMakeLists.txt")
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/UL)
endif()
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/WAL/CMakeLists.txt")
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/WAL)
endif()



add_subdirectory(BRDF)
add_subdirectory(Samples)