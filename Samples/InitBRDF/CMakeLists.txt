cmake_minimum_required(VERSION 3.10)



file(GLOB InitBRDFSourceFiles
    "Source/*.cpp"
    "Source/*.h"
)
source_group("Source" FILES ${InitBRDFSourceFiles})



add_executable(Samples.InitBRDF
    ${InitBRDFSourceFiles}
)



set_target_properties(Samples.InitBRDF
    PROPERTIES 
        FOLDER "Samples"
)



include(${BRDF_CMAKE_DIR}/TargetUseBRDF.cmake)
TargetUseBRDF(Samples.InitBRDF)