# FindSDL2_ttf.cmake
# ------------------
#
# Find SDL2_ttf library, this modules defines:
#
# SDL2_TTF_INCLUDE_DIRS, where to find SDL_ttf.h
# SDL2_TTF_LIBRARIES, where to find library
# SDL2_TTF_FOUND, if it is found

find_path(
	SDL2_TTF_INCLUDE_DIR
	NAMES SDL_ttf.h
	PATH_SUFFIXES SDL2
)

find_library(
	SDL2_TTF_LIBRARY
	NAMES libSDL2_ttf SDL2_ttf
)

include(FindPackageHandleStandardArgs)

find_package_handle_standard_args(
	SDL2_ttf
	FOUND_VAR SDL2_TTF_FOUND
	REQUIRED_VARS SDL2_TTF_LIBRARY SDL2_TTF_INCLUDE_DIR
)

set(SDL2_TTF_LIBRARIES ${SDL2_TTF_LIBRARY})
set(SDL2_TTF_INCLUDE_DIRS ${SDL2_TTF_INCLUDE_DIR})

mark_as_advanced(SDL2_TTF_INCLUDE_DIR SDL2_TTF_LIBRARY)
