cmake_minimum_required(VERSION 3.22)
project(SDL_Yourmom)

set(CMAKE_CXX_STANDARD 14)

# Must set the path to the main.cpp, for example: scripts/main.cpp if it is inside a folder
add_executable(${PROJECT_NAME} scripts/main.cpp
        scripts/vector.h
        scripts/audio.cpp
        scripts/audio.h
        scripts/entity.cpp
        scripts/entity.h
        scripts/textureLoadeer.cpp
        scripts/textureLoader.h
        scripts/game.h
        scripts/game.cpp
        scripts/gameObject.h
        scripts/gameObject.cpp
        scripts/tile.h
        scripts/tile.cpp
        scripts/physics.cpp
        scripts/physics.h
        scripts/ball.cpp
        scripts/ball.h)

# --- SDL2 SETUP ---
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/modules)
set(SDL2_PATH "SDL2/x86_64-w64-mingw32")
set(SDL2_IMAGE_PATH "SDL2/x86_64-w64-mingw32")
set(SDL2_TTF_PATH "SDL2/x86_64-w64-mingw32")
set(SDL2_MIXER_PATH "SDL2/x86_64-w64-mingw32")

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_mixer REQUIRED)


include_directories(${SDL2_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARIES} ${SDL2_TTF_LIBRARIES} ${SDL2_MIXER_LIBRARIES})