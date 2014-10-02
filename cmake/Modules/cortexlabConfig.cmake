INCLUDE(FindPkgConfig)
PKG_CHECK_MODULES(PC_CORTEXLAB cortexlab)

FIND_PATH(
    CORTEXLAB_INCLUDE_DIRS
    NAMES cortexlab/api.h
    HINTS $ENV{CORTEXLAB_DIR}/include
        ${PC_CORTEXLAB_INCLUDEDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/include
          /usr/local/include
          /usr/include
)

FIND_LIBRARY(
    CORTEXLAB_LIBRARIES
    NAMES gnuradio-cortexlab
    HINTS $ENV{CORTEXLAB_DIR}/lib
        ${PC_CORTEXLAB_LIBDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/lib
          ${CMAKE_INSTALL_PREFIX}/lib64
          /usr/local/lib
          /usr/local/lib64
          /usr/lib
          /usr/lib64
)

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(CORTEXLAB DEFAULT_MSG CORTEXLAB_LIBRARIES CORTEXLAB_INCLUDE_DIRS)
MARK_AS_ADVANCED(CORTEXLAB_LIBRARIES CORTEXLAB_INCLUDE_DIRS)

