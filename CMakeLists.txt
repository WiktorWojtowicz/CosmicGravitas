cmake_minimum_required(VERSION 3.20)
project(CosmicGravitas)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(CosmicGravitas
    src/Main.cpp
    src/Clock.cpp
)

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
