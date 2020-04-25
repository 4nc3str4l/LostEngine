import os

LOST_ENGINE_URL = "https://github.com/4nc3str4l/LostEngine.git"
GIT_CLONE_COMMAND = f"git clone {LOST_ENGINE_URL}"

def write_root_cmake():
    with open("CMakeLists.txt", "w+") as f:
        f.write("cmake_minimum_required(VERSION 2.8)\n")
        f.write("project(LostEngine)\n")
        f.write("include(CMakeToolsHelpers OPTIONAL)\n")
        f.write("list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/LostEngine/cmake-utils)\n")

        f.write("\n")

        f.write("# -[ Macros and functions\n")
        f.write("include(Configure)\n")
        f.write("include(Macros)\n")
        f.write("include(External)\n")

        f.write("\n")

        f.write("# Avoids problems by cleaning suff\n")
        f.write("ResetAllTargets()\n")

        f.write("\n")

        f.write("# -[ C++ standard\n")
        f.write("set(CMAKE_CXX_STANDARD 14)\n")
        f.write("set(CMAKE_CXX_STANDARD_REQUIRED on)\n")

        f.write("\n")

        f.write("# -[ Sources\n")
        f.write("add_subdirectory(LostEngine)\n")
        f.write("add_subdirectory(src)\n")


def write_main_cmake(project_name):
    with open("CMakeLists.txt", "w+") as f:
        f.write(f"CreateTarget(TARGET {project_name})\n")
        f.write("\n")
        f.write("set(SOURCE_FOLDERS\n")
        f.write("    ${CMAKE_CURRENT_SOURCE_DIR}\n")
        f.write(")\n")
        f.write("\n")
        f.write("foreach(folder ${SOURCE_FOLDERS})\n")
        f.write("    get_filename_component(FOLDER_NAME ${folder} NAME)\n")
        f.write("\n")
        f.write("    AddToSources(\n")
        f.write(f"        TARGET {project_name}\n")
        f.write("        SRC_PATH ${folder}\n")
        f.write('        GLOB_SEARCH ".hpp;.cpp;.c;.h"\n')
        f.write("        FOLDER_NAME ${FOLDER_NAME}\n")
        f.write("    )\n")
        f.write("endforeach()\n")
        f.write("\n")
        f.write(f"AddDependency(TARGET {project_name} DEPENDENCY LostEngine)\n")
        f.write("\n")
        f.write("AddToIncludes(\n")
        f.write(f"    TARGET {project_name}\n")
        f.write("    INC_PATH ${PROJECT_SOURCE_DIR}/LostEngine/src\n")
        f.write(")\n")
        f.write("\n")
        f.write(f"ResolveExternal(TARGET {project_name})\n")
        f.write(f"if ({project_name}_IS_RESOLVED)\n")
        f.write(f'    BuildNow(TARGET {project_name} EXECUTABLE OUTPUT_NAME {project_name} DEFINES "ASIO_STANDALONE")\n')
        f.write("\n")
        f.write("    if(WIN)\n")
        f.write(f"    add_custom_command(TARGET {project_name} PRE_BUILD\n")
        f.write("                       COMMAND ${CMAKE_COMMAND} -E copy\n")
        f.write("                           ${PROJECT_SOURCE_DIR}/build/third_party/src/assimp_assimp_v4.1.0-build/code/Debug/assimp-vc140-mt.dll $<TARGET_FILE_DIR:"+project_name+">)\n")
        f.write("    endif(WIN)\n")
        f.write("\n")
        f.write("    # Copy assets folder\n")
        f.write(f"    add_custom_command(TARGET {project_name} PRE_BUILD\n")
        f.write("                       COMMAND ${CMAKE_COMMAND} -E copy_directory\n")
        f.write("                           ${PROJECT_SOURCE_DIR}/assets $<TARGET_FILE_DIR:"+project_name+">)\n")
        f.write("\n")
        f.write("    # SFML\n")
        f.write("    # Windows includes\n")
        f.write("    if(WIN)\n")
        f.write(f"        add_custom_command(TARGET {project_name} PRE_BUILD\n")
        f.write("                        COMMAND ${CMAKE_COMMAND} -E copy_directory\n")
        f.write("                            ${PROJECT_SOURCE_DIR}/LostEngine/Dependencies/SFML-2.5.1/bin $<TARGET_FILE_DIR:"+project_name+">)\n") 
        f.write("    endif(WIN)\n")
        f.write("\n")    
        f.write("    # Linux includes\n")
        f.write("    if(UNIX)\n")
        f.write(f"        add_custom_command(TARGET {project_name} PRE_BUILD\n")
        f.write("                        COMMAND ${CMAKE_COMMAND} -E copy_directory\n")
        f.write("                            ${PROJECT_SOURCE_DIR}/LostEngine/Dependencies/SFML-2.5.1/lib/linux $<TARGET_FILE_DIR:"+project_name+">)\n")
        f.write("    endif(UNIX)\n")
        f.write("   endif()\n")


def write_header_file(project_name):
    with open(f"{project_name}.h", "w+") as f:
        f.write("#pragma once\n")
        
        f.write("\n")
        
        f.write('#include "Engine/Logic/GameLogic.h"\n')
        f.write("#include <string>\n")
          
        f.write("\n")

        f.write("using namespace std;\n")
        f.write("using namespace logic;\n")
        
        f.write("\n")
        
        f.write(f"class {project_name} : public GameLogic\n")
        f.write("{\n")
        f.write("public:\n")
        f.write(f"    {project_name}();\n")
        f.write(f"    ~{project_name}();\n")

        f.write("\n")

        f.write("    void Init(Window* _window, Loader* _loader);\n")
        f.write("    void Update(float _delta, Window* _window);\n")
        f.write("    void Render(Window* _window);\n")
        f.write("};\n")
        f.write("\n")

def write_cpp_file(project_name):
    with open(f"{project_name}.cpp", "w+") as f:
        f.write(f'#include "{project_name}.h"\n')
        
        f.write("\n")

        f.write(f"{project_name}::{project_name}()\n")
        f.write("{\n")
        f.write("    // Init some variables\n")
        f.write("}\n")

        f.write("\n")

        f.write(f"void {project_name}::Init(Window* _window, Loader* _loader)\n")
        f.write("{\n")
        f.write("    // Load all your stuff here\n")
        f.write("}\n")

        f.write("\n")

        f.write(f"void {project_name}::Update(float _delta, Window* _window)\n")
        f.write("{\n")
        f.write("    // Called every tick 60 fps\n")
        f.write("}\n")

        f.write("\n")

        f.write(f"void {project_name}::Render(Window* _window)\n")
        f.write("{\n")
        f.write("    // Render \n")
        f.write("}\n")

        f.write("\n")

        f.write(f"{project_name}::~{project_name}()\n")
        f.write("{\n")
        f.write("    // Clean the house after the party :)\n")
        f.write("}\n")
        f.write("\n")


def write_main_cpp(project_name):
    with open("main.cpp", "w+") as f: 
        f.write(f'#include "{project_name}.h"\n')
        f.write('#include "Engine/LostEngine.h"\n')

        f.write("\n")

        f.write("using namespace le;\n")

        f.write("\n")

        f.write("int main(int argc, char** argv)\n")
        f.write("{\n")
        f.write("    string path(argv[0]);\n")
        f.write("    string base = path.substr(0, path.find_last_of('\\\\'));\n")
        f.write("    std::replace(base.begin(), base.end(), '\\\\', '/');\n")

        f.write("\n")

        f.write(f'    LEngine engine("{project_name}", false, 1280, 720, base, new {project_name}());\n')
        f.write("    engine.Start();\n")
        f.write("    return 0;\n")
        f.write("}\n")

        f.write("\n")

def main():
    # Get the project name
    name = input("Project Name:")

    # Make sure that it doesn't contain white spaces
    name = name.strip()

    # Make sure that the user provided a valid project name
    if len(name) == 0:
        print("[Error] Project can't be empty")
        return

    # Get path to the executing script
    path = os.getcwd()

    # Create the final path for the project
    project_path = os.path.join(path, name)

    # Make sure that there is no existing folder with that name
    if os.path.exists(project_path):
        print(f"[Error] Existing folder in path {project_path}, please type a different name")
        return

    # Create the project folder
    print("[Info] Creating Project Folder")
    os.mkdir(project_path)
    print("[OK] Creating Project Folder")

    # Change directory to the project path
    os.chdir(project_path)

    # Clone the lost engine:
    print("[Info] Cloning project...")
    os.system(GIT_CLONE_COMMAND)
    print("[OK] Cloning project")

    print("[Info] Creating Source Folder")
    os.mkdir("src")
    print("[OK] Creating Source Folder")

    print("[Info] Creating Assets Folder")
    os.mkdir("assets")
    print("[OK] Creating Assets Folder")

    print("[Info] Creating Root CMAKE")
    write_root_cmake()
    print("[OK] Creating Root CMAKE")

    # Move to the source file
    os.chdir("src")

    print("[Info] Creating Main CMAKE")           
    write_main_cmake(name)
    print("[OK] Creating Main CMAKE") 

    print("[Info] Creating Cpp file")           
    write_cpp_file(name)
    print("[OK] Creating Cpp file") 
    
    print("[Info] Creating Header file")           
    write_header_file(name)
    print("[OK] Creating Header file") 
    
    print("[Info] Creating Main cpp file")           
    write_main_cpp(name)
    print("[OK] Creating Main cpp file") 

    print("[Info] Running CMAKE")           
    os.chdir("../")
    os.mkdir("build")
    os.chdir("build")
    os.system("cmake ..")
    print("[OK] Running CMAKE") 

    print("[Info] Building Project")  
    os.system("cmake --build .")
    print("[OK] Building Project") 

main()
