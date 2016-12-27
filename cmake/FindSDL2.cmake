# FindSDL2
# --------
#
# Find SDL2 library, this modules defines:
#
# SDL2_INCLUDE_DIRS, where to find SDL.h
# SDL2_LIBRARIES, where to find library
# SDL2_FOUND, if it is found

find_path(SDL2_INCLUDE_DIR NAMES SDL.h PATH_SUFFIXES SDL2)
find_library(SDL2_LIBRARY NAMES libSDL2 SDL2)

include(FindPackageHandleStandardArgs)

find_package_handle_standard_args(
    SDL2
    FOUND_VAR SDL2_FOUND
    REQUIRED_VARS SDL2_LIBRARY SDL2_INCLUDE_DIR
)

set(SDL2_LIBRARIES ${SDL2_LIBRARY})
set(SDL2_INCLUDE_DIRS ${SDL2_INCLUDE_DIR})

mark_as_advanced(SDL2_INCLUDE_DIR SDL2_LIBRARY)
