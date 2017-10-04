CreateTarget(TARGET AuraProject)

set(SOURCE_FOLDERS
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/Water
)

foreach(folder ${SOURCE_FOLDERS})
    get_filename_component(FOLDER_NAME ${folder} NAME)

    AddToSources(
        TARGET AuraProject
        SRC_PATH ${folder}
        GLOB_SEARCH ".hpp;.cpp;.c;.h"
        FOLDER_NAME ${FOLDER_NAME}
    )
endforeach()

AddDependency(TARGET AuraProject DEPENDENCY LostEngine)

BuildNow(TARGET AuraProject EXECUTABLE OUTPUT_NAME AuraProject)
add_custom_command(TARGET AuraProject PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy
                       ${PROJECT_SOURCE_DIR}/Dependencies/dlibs/assimp-vc140-mt.dll $<TARGET_FILE_DIR:AuraProject>)

add_custom_command(TARGET AuraProject PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${PROJECT_SOURCE_DIR}/assets $<TARGET_FILE_DIR:AuraProject>)