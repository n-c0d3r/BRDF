cmake_minimum_required(VERSION 3.10)



include(${BRDF_CMAKE_DIR}/APIOptions.cmake)



set(BRDF_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Source PARENT_SCOPE)
set(BRDF_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Source)

set(BRDF_SHADERS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Shaders PARENT_SCOPE)
set(BRDF_SHADERS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Shaders)



configure_file(ConfigurationFiles/BRDF/.BuildInfo ${CMAKE_CURRENT_BINARY_DIR}/ConfigurationFiles/BRDF/.BuildInfo)



file(GLOB BRDFSourceFiles
    "Source/BRDF/*.cpp"
    "Source/BRDF/*.h"
)
source_group("Source\\BRDF" FILES ${BRDFSourceFiles})

file(GLOB BRDFMicrofacetBasedSourceFiles
    "Source/BRDF/MicrofacetBased/*.cpp"
    "Source/BRDF/MicrofacetBased/*.h"
)
source_group("Source\\BRDF\\MicrofacetBased" FILES ${BRDFMicrofacetBasedSourceFiles})



add_library(BRDF STATIC
    ${BRDFSourceFiles}
    ${BRDFMicrofacetBasedSourceFiles}
)

target_link_libraries(BRDF
    PUBLIC 
        UL
        WAL
        d3d11.lib 
        d3dcompiler.lib
)

target_include_directories(BRDF
    PUBLIC 
        ${CMAKE_CURRENT_BINARY_DIR}/ConfigurationFiles
        ${CMAKE_CURRENT_SOURCE_DIR}/Source
        ${CMAKE_SOURCE_DIR}/UL/UL/Source
        ${CMAKE_SOURCE_DIR}/WAL/WAL/Source
)

target_compile_definitions(BRDF
    PRIVATE BRDF_EXPORTS=1
)