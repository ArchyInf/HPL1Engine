# Try to find libGLee
# Based upon FindBZip2 which is included in cmake 2.6


FIND_PATH(GLEE_INCLUDE_DIR GLee.h PATH "GL")
FIND_LIBRARY(GLEE_LIBRARY NAMES glee PATH_SUFFIXES "lib" PATH "GL")
INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(Glee DEFAULT_MSG GLEE_LIBRARY GLEE_INCLUDE_DIR)

MARK_AS_ADVANCED(GLEE_INCLUDE_DIR GLEE_LIBRARY)
