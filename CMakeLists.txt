# // ------------------------------------------------------------------------------ \\
# 
# This is root CMake-File for "mecs_lib" project.
# 
# ABOUT:
# "mecs_lib" - Mobile 'Entity Component System'.
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
set ( ROOT_PROJECT_NAME "mecs_lib" )

# Project Version
set ( ROOT_PROJECT_VERSION 0.0.1 )

# Configure Project
project ( ${ROOT_PROJECT_NAME} VERSION ${ROOT_PROJECT_VERSION} LANGUAGES C CXX )

# =================================================================================
# CONFIGS
# =================================================================================

# Enable Example-Executable
if ( NOT DEFINED MECS_LIB_HEADERS AND NOT DEFINED MECS_LIB_SOURCES )
	# Enable Example Sub-Project
	set( MECS_LIB_BUILD_EXAMPLE ON )
	
	# INFO
	message ( STATUS "${ROOT_PROJECT_NAME} - example project enabled. To export code without example-build, set <MECS_LIB_HEADERS> & <MECS_LIB_SOURCES> & add them to your project." )
else ( NOT DEFINED MECS_LIB_HEADERS AND NOT DEFINED MECS_LIB_SOURCES )
	# INFO
	message ( STATUS "${ROOT_PROJECT_NAME} - headers & sources are exported to <MECS_LIB_HEADERS> & <MECS_LIB_SOURCES> relatively." )
endif ( NOT DEFINED MECS_LIB_HEADERS AND NOT DEFINED MECS_LIB_SOURCES )

# Multi-threading
if ( NOT DEFINED MECS_LIB_MT_ENABLED )
	# INFO
	message ( STATUS "${ROOT_PROJECT_NAME} - set <MECS_LIB_MT_ENABLED> <ON> or <OFF>, and add definition <MECS_LIB_MT_ENABLED=1> to source-code, to enable/disable multi-threading/thread-safety support." )
	
	# Enable by default.
	set ( MECS_LIB_MT_ENABLED ON )
	
	# Add Definition.
	add_definitions ( -DMECS_LIB_MT_ENABLED )
else ( NOT DEFINED MECS_LIB_MT_ENABLED )
	# MT
	if ( MECS_LIB_MT_ENABLED )
		# INFO
		message ( STATUS "${ROOT_PROJECT_NAME} - multi-threading (thread-safety) support enabled." )
	else ( MECS_LIB_MT_ENABLED )
		# INFO
		message ( STATUS "${ROOT_PROJECT_NAME} - multi-threading (thread-safety) support disabled." )
	endif ( MECS_LIB_MT_ENABLED )
endif ( NOT DEFINED MECS_LIB_MT_ENABLED )

# =================================================================================
# CONSTANTS
# =================================================================================

# Source-Dir
set ( MECS_LIB_SRC_DIR "${CMAKE_SOURCE_DIR}/src/cpp" )

# =================================================================================
# HEADERS
# =================================================================================

# Local-Project Headers
set ( MECS_LIB_HEADERS ${MECS_LIB_HEADERS}
	# CORE
	"${MECS_LIB_SRC_DIR}/ecs.hpp"
	"${MECS_LIB_SRC_DIR}/cfg/ecs_types.hpp"
	"${MECS_LIB_SRC_DIR}/utils/IDStorage.hpp"
	"${MECS_LIB_SRC_DIR}/utils/IDMap.hpp"
	# COMPONENTS
	"${MECS_LIB_SRC_DIR}/components/Component.hpp"
	"${MECS_LIB_SRC_DIR}/components/ComponentsManager.hpp"
	# ENTITIES
	"${MECS_LIB_SRC_DIR}/entities/Entity.hpp"
	"${MECS_LIB_SRC_DIR}/entities/EntitiesManager.hpp"
	# SYSTEMS
	"${MECS_LIB_SRC_DIR}/systems/System.hpp"
	"${MECS_LIB_SRC_DIR}/systems/SystemsManager.hpp"
	# EVENTS
	"${MECS_LIB_SRC_DIR}/events/IEventListener.hxx"
	"${MECS_LIB_SRC_DIR}/events/Event.hpp"
	"${MECS_LIB_SRC_DIR}/events/EventsManager.hpp" )

# =================================================================================
# SOURCES
# =================================================================================

# Local-Project Sources
set ( MECS_LIB_SOURCES ${MECS_LIB_SOURCES}
	# CORE
	"${MECS_LIB_SRC_DIR}/ecs.cpp"
	# COMPONENTS
	"${MECS_LIB_SRC_DIR}/components/Component.cpp"
	"${MECS_LIB_SRC_DIR}/components/ComponentsManager.cpp"
	# ENTITIES
	"${MECS_LIB_SRC_DIR}/entities/Entity.cpp"
	"${MECS_LIB_SRC_DIR}/entities/EntitiesManager.cpp"
	# SYSTEMS
	"${MECS_LIB_SRC_DIR}/systems/System.cpp"
	"${MECS_LIB_SRC_DIR}/systems/SystemsManager.cpp"
	# EVENTS
	"${MECS_LIB_SRC_DIR}/events/Event.cpp"
	"${MECS_LIB_SRC_DIR}/events/EventsManager.cpp" )

# =================================================================================
# EXPORT
# =================================================================================

# Export Headers & Sources
if ( NOT MECS_LIB_BUILD_EXAMPLE )
	# Export Headers
	set ( MECS_LIB_HEADERS ${MECS_LIB_HEADERS} PARENT_SCOPE )
	
	# Export Sources
	set ( MECS_LIB_SOURCES ${MECS_LIB_SOURCES} PARENT_SCOPE )
endif ( NOT MECS_LIB_BUILD_EXAMPLE )

# =================================================================================
# EXAMPLE-PROJECT
# =================================================================================

# Example-Proejct
if ( MECS_LIB_BUILD_EXAMPLE )
	# Include/Add Example-Project
	add_subdirectory ( "${MECS_LIB_SRC_DIR}/test" )
endif ( MECS_LIB_BUILD_EXAMPLE )

# =================================================================================
# BINARY
# =================================================================================

# Example Executable
if ( MECS_LIB_BUILD_EXAMPLE )

	# Create Executable Object
	add_executable ( mecs_test ${MECS_LIB_SOURCES} ${MECS_LIB_HEADERS} )

	# Configure Executable Object
	set_target_properties ( mecs_test PROPERTIES
	OUTPUT_NAME "mecs_lib_test"
	RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin" )

endif ( MECS_LIB_BUILD_EXAMPLE )