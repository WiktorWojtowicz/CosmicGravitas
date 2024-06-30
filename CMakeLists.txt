cmake_minimum_required(VERSION 3.10)
project(CosmicGravitas)

add_executable(CosmicGravitas
    src/main.cpp
    src/Clock.cpp
)

if(NOT PNG)
    set(PNG_LIBRARY "C:/Program Files(x86)/libpng")
    set(PNG_PNG_INCLUDE_DIR "C:/Program Files(x86)/libpng/include")
    set(PNG_LIBRARY "C:/Program Files(x86)/libpng")
endif()


find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

target_include_directories(CosmicGravitas
    PUBLIC include/
    PUBLIC ${SDL2_INCLUDE_DIRS}
    PUBLIC ${SDL2IMAGE_INCLUDE_DIRS}
)

if(WIN32 AND NOT MSVC)
    target_link_libraries(CosmicGravitas PUBLIC ${SDL2_LIBRARIES} SDL2_image::SDL2_image mingw32)
else()
    target_link_libraries(CosmicGravitas PUBLIC ${SDL2_LIBRARIES} SDL2_image::SDL2_image)
endif()

add_custom_target(copy_resources ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/res ${CMAKE_BINARY_DIR}/res
    COMMENT "Copying resources to build directory"
)
