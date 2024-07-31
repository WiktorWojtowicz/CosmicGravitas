cmake_minimum_required(VERSION 3.20)
project(CosmicGravitas)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(ProcessorCount)

ProcessorCount(N)
if (N EQUAL 0)
    set(N 1) # Default to 1 if ProcessorCount fails
endif()
message(STATUS "Building with ${N} parallel jobs")
set(CMAKE_BUILD_PARALLEL_LEVEL ${N})

set(CMAKE_BUILD_PARALLEL_LEVEL 4)

add_executable(CosmicGravitas
    src/Main.cpp
    src/Clock.cpp
)

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
    FetchContent_MakeAvailable(Boost)
    set(Boost_INCLUDE_DIRS ${boost_SOURCE_DIR})
    set(Boost_LIBRARIES Boost::Boost)
endif()

find_package(PNG REQUIRED)
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(Boost REQUIRED)

target_include_directories(CosmicGravitas
    PUBLIC include/
    PUBLIC ${SDL2_INCLUDE_DIRS}
    PUBLIC ${SDL2IMAGE_INCLUDE_DIRS}
    PUBLIC ${Boost_INCLUDE_DIRS}
)

if(WIN32 AND NOT MSVC)
    target_link_libraries(CosmicGravitas 
    PUBLIC ${SDL2_LIBRARIES} 
    SDL2_image::SDL2_image mingw32     
    PUBLIC ${Boost_LIBRARIES}
)
else()
    target_link_libraries(CosmicGravitas 
    PUBLIC ${SDL2_LIBRARIES}
    SDL2_image::SDL2_image
)
endif()
