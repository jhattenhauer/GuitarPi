cmake_minimum_required(VERSION 3.10)
project(GuitarPi CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(PkgConfig REQUIRED)
pkg_check_modules(ALSA REQUIRED alsa)
pkg_check_modules(FFTW3 REQUIRED fftw3)
pkg_check_modules(SDL2 REQUIRED sdl2)

add_executable(audio_fft alsa_utils.cpp)
add_executable(game game_loop.cpp)

# Include directories
target_include_directories(audio_fft PRIVATE
    ${ALSA_INCLUDE_DIRS}
    ${FFTW3_INCLUDE_DIRS}
    ${SDL2_INCLUDE_DIRS}
)
target_include_directories(game PRIVATE
    ${SDL2_INCLUDE_DIRS}
)

# Link libraries
target_link_libraries(audio_fft PRIVATE
    ${ALSA_LIBRARIES}
    ${FFTW3_LIBRARIES}
    ${SDL2_LIBRARIES}
    m pthread
)
target_link_libraries(game PRIVATE
    ${SDL2_LIBRARIES}
    pthread
)
