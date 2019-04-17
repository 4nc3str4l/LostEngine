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

# Require ASSIMP
RequireExternal(
    TARGET LostEngine
    ENSURE_ORDER
    LINK_SUBDIR "code/Debug/"
    LINK_NAME "assimp-vc140-mt"
    MODULE "assimp/assimp:v4.1.0"
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


# Libraries
find_package(OpenGL)
AddDependency(TARGET LostEngine DEPENDENCY ${OPENGL_gl_LIBRARY})

#######################################################################
##########################################################################
# Includes 
if(WIN32)
AddToIncludes(
    TARGET LostEngine
    INC_PATH ${PROJECT_SOURCE_DIR}/Dependencies/SFML-2.5.1/include/win
)
endif(WIN32)

if(UNIX)
AddToIncludes(
    TARGET LostEngine
    INC_PATH ${PROJECT_SOURCE_DIR}/Dependencies/SFML-2.5.1/include/lin
)
endif(UNIX)


# Windows
if(WIN32)
    AddDependency(TARGET LostEngine DEPENDENCY ${PROJECT_SOURCE_DIR}/Dependencies/SFML-2.5.1/lib/windows/flac.lib)  
    AddDependency(TARGET LostEngine DEPENDENCY ${PROJECT_SOURCE_DIR}/Dependencies/SFML-2.5.1/lib/windows/freetype.lib)
    AddDependency(TARGET LostEngine DEPENDENCY ${PROJECT_SOURCE_DIR}/Dependencies/SFML-2.5.1/lib/windows/ogg.lib)
    AddDependency(TARGET LostEngine DEPENDENCY ${PROJECT_SOURCE_DIR}/Dependencies/SFML-2.5.1/lib/windows/openal32.lib)
    AddDependency(TARGET LostEngine DEPENDENCY ${PROJECT_SOURCE_DIR}/Dependencies/SFML-2.5.1/lib/windows/vorbis.lib)
    AddDependency(TARGET LostEngine DEPENDENCY ${PROJECT_SOURCE_DIR}/Dependencies/SFML-2.5.1/lib/windows/vorbisenc.lib)
    AddDependency(TARGET LostEngine DEPENDENCY ${PROJECT_SOURCE_DIR}/Dependencies/SFML-2.5.1/lib/windows/vorbisfile.lib)

    AddDependency(TARGET LostEngine DEPENDENCY ${PROJECT_SOURCE_DIR}/Dependencies/SFML-2.5.1/lib/windows/sfml-main-d.lib)
    AddDependency(TARGET LostEngine DEPENDENCY ${PROJECT_SOURCE_DIR}/Dependencies/SFML-2.5.1/lib/windows/sfml-window-d.lib)
    AddDependency(TARGET LostEngine DEPENDENCY ${PROJECT_SOURCE_DIR}/Dependencies/SFML-2.5.1/lib/windows/sfml-system-d.lib)
    AddDependency(TARGET LostEngine DEPENDENCY ${PROJECT_SOURCE_DIR}/Dependencies/SFML-2.5.1/lib/windows/sfml-graphics-d.lib)
    AddDependency(TARGET LostEngine DEPENDENCY ${PROJECT_SOURCE_DIR}/Dependencies/SFML-2.5.1/lib/windows/sfml-network-d.lib)
    AddDependency(TARGET LostEngine DEPENDENCY ${PROJECT_SOURCE_DIR}/Dependencies/SFML-2.5.1/lib/windows/sfml-audio-d.lib)
endif(WIN32)


###################################################################################
ResolveExternal(TARGET LostEngine)   
if (LostEngine_IS_RESOLVED)
    BuildNow(TARGET LostEngine STATIC_LIB OUTPUT_NAME LostEngine DEFINES "ASIO_STANDALONE")
    
    
    if(UNIX)
        find_package(OpenGL REQUIRED)
        if(NOT OPENGL_FOUND)
            message("ERROR: OpenGL not found")
        endif(NOT OPENGL_FOUND)
        set(GL_LIBRARY GL GLU X11)
        target_link_libraries(LostEngine -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio ${GL_LIBRARY} m -lpthread -lm -ldl ${CMAKE_SOURCE_DIR}/build/third_party/src/assimp_assimp_v4.1.0-build/code/libassimp.so)

    endif(UNIX)
endif()