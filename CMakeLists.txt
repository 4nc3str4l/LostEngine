cmake_minimum_required(VERSION 2.8)
project(LostEngine)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake-utils)

# -[ Macros and functions
include(Configure)
include(Macros)
include(External)

# Avoids problems by cleaning suff
ResetAllTargets()

# -[ C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED on)

# -[ Sources
add_subdirectory(src)