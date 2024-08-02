# Initial CMake config 
cmake_minimum_required(VERSION 3.30)
project(CosmicGravitas VERSION 0.0.2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


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

# SDL2
find_package(SDL2 QUIET)
if(NOT SDL2_FOUND)
    message(STATUS "SDL2 not found. Fetching it automatically")
    FetchContent_Declare(
      SDL2
      GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
      GIT_TAG release-2.26.5
    )
    FetchContent_MakeAvailable(SDL2)
    set(SDL2_INCLUDE_DIRS ${sdl2_SOURCE_DIR}/include)
    set(SDL2_LIBRARIES SDL2::SDL2)
endif()

# SDL2_image
find_package(SDL2_image QUIET)
if(NOT SDL2_IMAGE_FOUND)
    message(STATUS "SDL2_image not found. Fetching it automatically")
    FetchContent_Declare(
      SDL2_image
      GIT_REPOSITORY https://github.com/libsdl-org/SDL_image.git
      GIT_TAG release-2.6.3
    )
    FetchContent_MakeAvailable(SDL2_image)
    set(SDL2_IMAGE_INCLUDE_DIRS ${sdl2_image_SOURCE_DIR})
    set(SDL2_IMAGE_LIBRARIES SDL2_image::SDL2_image)
endif()

# Boost
find_package(Boost QUIET)
if(NOT Boost_FOUND)
    message(STATUS "Boost not found. Fetching it automatically")
    FetchContent_Declare(
      Boost
      GIT_REPOSITORY https://github.com/boostorg/boost.git
      GIT_TAG boost-1.78.0
    )
    set(BOOST_ROOT ${boost_SOURCE_DIR})
    set(Boost_INCLUDE_DIRS ${boost_SOURCE_DIR})
    set(Boost_LIBRARIES Boost::Boost)
endif()

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(Boost REQUIRED CONFIG)

add_executable(CosmicGravitas
    src/Main.cpp
    src/Clock.cpp
)

target_include_directories(CosmicGravitas
    PUBLIC include/
    PUBLIC ${SDL2_INCLUDE_DIRS}
    PUBLIC ${SDL2IMAGE_INCLUDE_DIRS}
    PUBLIC ${Boost_INCLUDE_DIRS}
)

if(WIN32 AND NOT MSVC)
    target_link_libraries(CosmicGravitas 
    PUBLIC ${SDL2_LIBRARIES} 
    PUBLIC SDL2::SDL2main
    PUBLIC SDL2_image::SDL2_image mingw32
    PUBLIC ${Boost_LIBRARIES}
)
else()
    target_link_libraries(CosmicGravitas 
    PUBLIC SDL2::SDL2
    PUBLIC SDL2::SDL2main
    PUBLIC SDL2_image::SDL2_image
    PUBLIC ${Boost_LIBRARIES}
)
endif()

# Post-build commands to copy SDL2 and SDL2_image DLLs (for Windows)
if(WIN32)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "$<TARGET_FILE:SDL2::SDL2>" "$<TARGET_FILE_DIR:${PROJECT_NAME}>"
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "$<TARGET_FILE:SDL2_image::SDL2_image>" "$<TARGET_FILE_DIR:${PROJECT_NAME}>"
    )
endif()

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

if(WIN32)
    install(FILES "$<TARGET_FILE:SDL2::SDL2>"
        DESTINATION bin
        COMPONENT library
    )
    install(FILES "$<TARGET_FILE:SDL2_image::SDL2_image>"
        DESTINATION bin
        COMPONENT library
    )
endif()

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

