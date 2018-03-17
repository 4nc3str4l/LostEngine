CreateTarget(TARGET LostEngine)

set(SOURCE_FOLDERS
    ${CMAKE_CURRENT_SOURCE_DIR}    
    ${CMAKE_CURRENT_SOURCE_DIR}/Components
    ${CMAKE_CURRENT_SOURCE_DIR}/Entities
    ${CMAKE_CURRENT_SOURCE_DIR}/Logic
    ${CMAKE_CURRENT_SOURCE_DIR}/Input
    ${CMAKE_CURRENT_SOURCE_DIR}/Tools
    ${CMAKE_CURRENT_SOURCE_DIR}/UI
    ${CMAKE_CURRENT_SOURCE_DIR}/Gfx/Lights
    ${CMAKE_CURRENT_SOURCE_DIR}/Gfx/Models
    ${CMAKE_CURRENT_SOURCE_DIR}/Gfx/Utils
    ${CMAKE_CURRENT_SOURCE_DIR}/Gfx/Skybox  
    ${CMAKE_CURRENT_SOURCE_DIR}/Gfx/Particles 
    ${CMAKE_CURRENT_SOURCE_DIR}/Gfx/Gfx2D   
    ${CMAKE_CURRENT_SOURCE_DIR}/Net   
)

foreach(folder ${SOURCE_FOLDERS})
    get_filename_component(FOLDER_NAME ${folder} NAME)

    AddToSources(
        TARGET LostEngine
        SRC_PATH ${folder}
        GLOB_SEARCH ".hpp;.cpp;.c;.h"
        FOLDER_NAME ${FOLDER_NAME}
    )
endforeach()

AddToIncludes(
    TARGET LostEngine
    INC_PATH ${PROJECT_SOURCE_DIR}/Dependencies/includes
)

find_library(assimp_library assimp-vc140-mt HINTS ${PROJECT_SOURCE_DIR}/Dependencies/libs)
find_library(glfw_library glfw3 HINTS ${PROJECT_SOURCE_DIR}/Dependencies/libs)
find_package(OpenGL)


AddDependency(TARGET LostEngine DEPENDENCY ${assimp_library})
AddDependency(TARGET LostEngine DEPENDENCY ${glfw_library})
AddDependency(TARGET LostEngine DEPENDENCY ${OPENGL_gl_LIBRARY})

BuildNow(TARGET LostEngine STATIC_LIB OUTPUT_NAME LostEngine DEFINES "ASIO_STANDALONE")