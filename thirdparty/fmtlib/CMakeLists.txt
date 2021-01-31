include(DownloadProject)

download_project(
  PROJ fmtlib 
  GIT_REPOSITORY https://github.com/fmtlib/fmt.git
  GIT_TAG master
  GIT_SHALLOW TRUE
  PREFIX ${CMAKE_CURRENT_BINARY_DIR}
  UPDATE_DISCONNECTED 1
)

add_subdirectory(${fmtlib_SOURCE_DIR} ${fmtlib_BINARY_DIR})
