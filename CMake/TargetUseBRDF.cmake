
function(TargetUseBRDF TargetName)
    
    add_dependencies(${TargetName} BRDF)

    target_link_libraries(${TargetName} 
        PRIVATE 
            BRDF
    )

    target_include_directories(${TargetName} 
        PUBLIC 
            ${BRDF_SOURCE_DIR}
    )

endfunction(TargetUseBRDF)
