cmake_minimum_required(VERSION 2.8)
project(sge)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_CXX_STANDARD_REQUIRED On)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${sge_SOURCE_DIR}/cmake)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)

set(
    HEADERS
    ${sge_SOURCE_DIR}/include/sge/assets/asset.hpp
    ${sge_SOURCE_DIR}/include/sge/assets/cache.hpp
    ${sge_SOURCE_DIR}/include/sge/assets/loader.hpp
    ${sge_SOURCE_DIR}/include/sge/assets/locator.hpp
    ${sge_SOURCE_DIR}/include/sge/assets/manager.hpp
    ${sge_SOURCE_DIR}/include/sge/assets/loaders/font.hpp
    ${sge_SOURCE_DIR}/include/sge/assets/loaders/image.hpp
    ${sge_SOURCE_DIR}/include/sge/assets/locators/file.hpp
    ${sge_SOURCE_DIR}/include/sge/initializers/sdl-fonts.hpp
    ${sge_SOURCE_DIR}/include/sge/initializers/sdl.hpp
    ${sge_SOURCE_DIR}/include/sge/initializers/sdl-image.hpp
    ${sge_SOURCE_DIR}/include/sge/initializers/sdl-window.hpp
    ${sge_SOURCE_DIR}/include/sge/actionmgr.hpp
    ${sge_SOURCE_DIR}/include/sge/engine-forward.hpp
    ${sge_SOURCE_DIR}/include/sge/engine.hpp
    ${sge_SOURCE_DIR}/include/sge/error.hpp
    ${sge_SOURCE_DIR}/include/sge/init.hpp
    ${sge_SOURCE_DIR}/include/sge/mainloop.hpp
    ${sge_SOURCE_DIR}/include/sge/node.hpp
    ${sge_SOURCE_DIR}/include/sge/scenemgr.hpp
    ${sge_SOURCE_DIR}/include/sge/sge.hpp
    ${sge_SOURCE_DIR}/include/sge/timer.hpp
    ${sge_SOURCE_DIR}/include/sge/nodes/position.hpp
    ${sge_SOURCE_DIR}/include/sge/nodes/sprite.hpp
)

set(
    SOURCES
    ${sge_SOURCE_DIR}/src/assets/asset.cpp
    ${sge_SOURCE_DIR}/src/assets/manager.cpp
    ${sge_SOURCE_DIR}/src/assets/loaders/font.cpp
    ${sge_SOURCE_DIR}/src/assets/loaders/image.cpp
    ${sge_SOURCE_DIR}/src/assets/locators/file.cpp
    ${sge_SOURCE_DIR}/src/initializers/sdl.cpp
    ${sge_SOURCE_DIR}/src/initializers/sdl-fonts.cpp
    ${sge_SOURCE_DIR}/src/initializers/sdl-image.cpp
    ${sge_SOURCE_DIR}/src/initializers/sdl-window.cpp
    ${sge_SOURCE_DIR}/src/actionmgr.cpp
    ${sge_SOURCE_DIR}/src/engine.cpp
    ${sge_SOURCE_DIR}/src/init.cpp
    ${sge_SOURCE_DIR}/src/initializers
    ${sge_SOURCE_DIR}/src/mainloop.cpp
    ${sge_SOURCE_DIR}/src/node.cpp
    ${sge_SOURCE_DIR}/src/scenemgr.cpp
    ${sge_SOURCE_DIR}/src/nodes/position.cpp
    ${sge_SOURCE_DIR}/src/nodes/sprite.cpp
)

add_library(sge SHARED ${HEADERS} ${SOURCES})
target_include_directories(
    sge
    PUBLIC
        ${SDL2_INCLUDE_DIRS}
        ${SDL2_IMAGE_INCLUDE_DIRS}
        ${SDL2_TTF_INCLUDE_DIRS}
        $<BUILD_INTERFACE:${sge_SOURCE_DIR}/include>
)
target_link_libraries(
    sge
    ${SDL2_LIBRARIES}
    ${SDL2_IMAGE_LIBRARIES}
    ${SDL2_TTF_LIBRARIES}
)

add_executable(testsge ${sge_SOURCE_DIR}/test.cpp)
target_include_directories(
    testsge
    PUBLIC
        ${SDL2_INCLUDE_DIRS}
        ${SDL2_IMAGE_INCLUDE_DIRS}
        ${SDL2_TTF_INCLUDE_DIRS}
        $<BUILD_INTERFACE:${sge_SOURCE_DIR}/include>
)
target_link_libraries(
    testsge
    sge
)