CreateTarget(TARGET LostEngine)

# Source directories
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
    ${CMAKE_CURRENT_SOURCE_DIR}/Gfx/PostProcessing      
    ${CMAKE_CURRENT_SOURCE_DIR}/Gfx/Water
    ${CMAKE_CURRENT_SOURCE_DIR}/Gfx/Terrain    
    ${CMAKE_CURRENT_SOURCE_DIR}/Net 
    ${CMAKE_CURRENT_SOURCE_DIR}/Audio   
)

# Require GLM
RequireExternal(
    TARGET LostEngine
    EXCLUDE
    SKIP_BUILD
    MODULE "g-truc/glm:0.9.8"
    INC_PATH "."
)

# Require GLFW
RequireExternal(
    TARGET LostEngine
    ENSURE_ORDER
    LINK_SUBDIR "src/Debug/"
    LINK_NAME "glfw3.lib"
    MODULE "glfw/glfw:3.2.1"
    INC_PATH "./include"
)


# Require ASSIMP
RequireExternal(
    TARGET LostEngine
    ENSURE_ORDER
    LINK_SUBDIR "code/Debug/"
    LINK_NAME "assimp-vc140-mt"
    MODULE "assimp/assimp:v4.1.0"
    INC_PATH "./include"
)

# Require OpenAL
RequireExternal(
    TARGET LostEngine
    ENSURE_ORDER
    LINK_SUBDIR "./Debug/"
    LINK_NAME "OpenAL32.lib"
    MODULE "kcat/openal-soft:openal-soft-1.19.1"
    INC_PATH "./include"
)

# Get all the files inside my source directiories
foreach(folder ${SOURCE_FOLDERS})
    get_filename_component(FOLDER_NAME ${folder} NAME)

    AddToSources(
        TARGET LostEngine
        SRC_PATH ${folder}
        GLOB_SEARCH ".hpp;.cpp;.c;.h"
        FOLDER_NAME ${FOLDER_NAME}
    )
endforeach()

# Includes 
AddToIncludes(
    TARGET LostEngine
    INC_PATH ${PROJECT_SOURCE_DIR}/Dependencies/includes
)

# Includes 
AddToIncludes(
    TARGET LostEngine
    INC_PATH ${PROJECT_SOURCE_DIR}/Dependencies/includes/asio
)


# Libraries
find_package(OpenGL)
AddDependency(TARGET LostEngine DEPENDENCY ${OPENGL_gl_LIBRARY})

ResolveExternal(TARGET LostEngine)
if (LostEngine_IS_RESOLVED)
    BuildNow(TARGET LostEngine STATIC_LIB OUTPUT_NAME LostEngine DEFINES "ASIO_STANDALONE")
endif()