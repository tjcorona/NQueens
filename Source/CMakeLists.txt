get_filename_component(BUILD_PARENT_DIR ${CMAKE_BINARY_DIR} PATH)
set(CMAKE_INSTALL_PREFIX "${BUILD_PARENT_DIR}" CACHE PATH "Install path prefix, prepended onto install directories." FORCE)

add_library (NQTypeDefs NQTypeDefs.cc)
add_library (NQDisplay NQDisplay.cc)
add_library (NQSymmetryFilter NQSymmetryFilter.cc)
add_library (NQBackTrackingSolver NQBackTrackingSolver.cc)
add_library (NQDLXSolver NQDLXSolver.cc)

add_executable (NQueens NQueens.cc)

target_link_libraries (NQueens LINK_PUBLIC
  NQTypeDefs
  NQDisplay
  NQSymmetryFilter
  NQBackTrackingSolver
  NQDLXSolver)

install (TARGETS NQueens DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)