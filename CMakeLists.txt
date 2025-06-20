# Initial CMake config 
cmake_minimum_required(VERSION 3.30)
project(CosmicGravitas VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

message(STATUS ${CMAKE_INSTALL_PREFIX})

# Build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build." FORCE)
endif()

# Multithreading
include(ProcessorCount)
ProcessorCount(N)

if (N EQUAL 0)
    set(N 1) # Default to 1 if ProcessorCount fails
endif()

message(STATUS "Building with ${N} threads")
set(CMAKE_BUILD_PARALLEL_LEVEL ${N})


# Fetching missing libraries
include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.1
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

add_executable(CosmicGravitas
    src/Main.cpp
)

target_compile_features(CosmicGravitas PRIVATE cxx_std_17)
target_link_libraries(CosmicGravitas PRIVATE SFML::Graphics)

# Enable ccache if available
find_program(CCACHE_PROGRAM ccache)
if(CCACHE_PROGRAM)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ${CCACHE_PROGRAM})
    set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK ${CCACHE_PROGRAM})
endif()

# Pack with CPack

install(TARGETS ${PROJECT_NAME}
    DESTINATION bin
    COMPONENT application
)

# if(WIN32)
#     install(FILES "$<TARGET_FILE:SDL2::SDL2>"
#         DESTINATION bin
#         COMPONENT library
#     )
#     install(FILES "$<TARGET_FILE:SDL2_image::SDL2_image>"
#         DESTINATION bin
#         COMPONENT library
#     )
# endif()

include(InstallRequiredSystemLibraries)

set(CPACK_RESOURCE_FILE_LICENSE ${CMAKE_CURRENT_SOURCE_DIR}/LICENSE)
# Set version
set(CMAKE_PROJECT_VERSION ${PROJECT_VERSION})

set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
set(CPACK_RESOURCE_FILE_README "${CMAKE_CURRENT_SOURCE_DIR}/README.md")
set(CPACK_PACKAGE_NAME "Cosmic Gravitas Alpha ${PROJECT_VERSION}")
set(CPACK_PACKAGE_VENDOR "Wiktor Wójtowicz")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "CosmicGravitas - 2D C++ program that uses Newton's law of gravity to simulate the movement of planets")
set(CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}-${CMAKE_SYSTEM_NAME}")
set(CPACK_PACKAGE_INSTALL_DIRECTORY "CosmicGravitas")
set(CPACK_PACKAGE_EXECUTABLES "CosmicGravitas" "CosmicGravitas")

set(CPACK_ARCHIVE_COMPONENT_INSTALL ON)
include(CPack)

