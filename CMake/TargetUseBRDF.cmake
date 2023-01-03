
function(TargetUseBRDF TargetName)

    set(CurrentTargetBinDir ${CMAKE_CURRENT_BINARY_DIR}/$<CONFIG>)
    set(CurrentTargetSourceDir ${CMAKE_CURRENT_SOURCE_DIR})

    target_link_libraries(${TargetName} 
        PRIVATE 
            BRDF
    )

    target_include_directories(${TargetName} 
        PUBLIC 
            ${BRDF_SOURCE_DIR}
    )

    add_custom_target(
        ${TargetName}_BuildEvents ALL
        DEPENDS custom_output
    )
    
    add_custom_command(
        OUTPUT custom_output
            
        COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${BRDF_SHADERS_DIR}/
            ${CurrentTargetBinDir}/Shaders/
            
        COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CurrentTargetSourceDir}/Shaders/
            ${CurrentTargetBinDir}/Shaders/

        DEPENDS
            always_rebuild
    )

    set_target_properties(${TargetName}_BuildEvents
        PROPERTIES 
            FOLDER "Samples"
    )
    
    add_dependencies(${TargetName}_BuildEvents BRDF)
    add_dependencies(${TargetName} BRDF ${TargetName}_BuildEvents)

    

endfunction(TargetUseBRDF)
