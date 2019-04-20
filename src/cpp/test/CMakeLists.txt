# // ------------------------------------------------------------------------------ \\
# 
# This is CMake-File for "mecs_lib" example project executable.
# 
# LICENSE: see "LICENSE" file
# TOOLS: Visual Studio Code (VSCode), Ninja, CMake, MSBuild (MSVC)
# LANGUAGE: C++
# PLATFORMS: Any with C++ 11 support
# 
# // ------------------------------------------------------------------------------ \\

# =================================================================================
# CMake Meta-Data
# =================================================================================

# CMake-Version
cmake_minimum_required ( VERSION 3.8 FATAL_ERROR )

# =================================================================================
# PROJECT
# =================================================================================

# Project Name
set ( ROOT_PROJECT_NAME "mecs_lib_test" )

# Project Version
set ( ROOT_PROJECT_VERSION 0.0.1 )

# Configure Project
project ( ${ROOT_PROJECT_NAME} VERSION ${ROOT_PROJECT_VERSION} LANGUAGES C CXX )

# =================================================================================
# HEADERS
# =================================================================================

# Local-Project Headers
set ( MECS_LIB_HEADERS ${MECS_LIB_HEADERS} "${MECS_LIB_SRC_DIR}/test/main.hpp" )

# =================================================================================
# SOURCES
# =================================================================================

# Local-Project Sources
set ( MECS_LIB_SOURCES ${MECS_LIB_SOURCES} "${MECS_LIB_SRC_DIR}/test/main.cpp" )
	
# =================================================================================
# EXPORT
# =================================================================================

# Export Headers
set ( MECS_LIB_HEADERS ${MECS_LIB_HEADERS} PARENT_SCOPE )
	
# Export Sources
set ( MECS_LIB_SOURCES ${MECS_LIB_SOURCES} PARENT_SCOPE )