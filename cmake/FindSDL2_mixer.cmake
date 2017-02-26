# FindSDL2_mixer.cmake
# --------------------
#
# Find SDL2_mixer library, this modules defines:
#
# SDL2_MIXER_INCLUDE_DIRS, where to find SDL_mixer.h
# SDL2_MIXER_LIBRARIES, where to find library
# SDL2_MIXER_FOUND, if it is found

find_path(
    SDL2_MIXER_INCLUDE_DIR
    NAMES SDL_mixer.h
    PATH_SUFFIXES SDL2
)

find_library(
    SDL2_MIXER_LIBRARY
    NAMES libSDL2_mixer SDL2_mixer
)

include(FindPackageHandleStandardArgs)

find_package_handle_standard_args(
    SDL2_mixer
    FOUND_VAR SDL2_MIXER_FOUND
    REQUIRED_VARS SDL2_MIXER_LIBRARY SDL2_MIXER_INCLUDE_DIR
)

set(SDL2_MIXER_LIBRARIES ${SDL2_MIXER_LIBRARY})
set(SDL2_MIXER_INCLUDE_DIRS ${SDL2_MIXER_INCLUDE_DIR})

mark_as_advanced(SDL2_MIXER_INCLUDE_DIR SDL2_MIXER_LIBRARY)
