include(DownloadProject)

download_project(
  PROJ cxxopts 
  GIT_REPOSITORY https://github.com/jarro2783/cxxopts.git
  GIT_TAG master
  GIT_SHALLOW TRUE
  PREFIX ${CMAKE_CURRENT_BINARY_DIR}
  UPDATE_DISCONNECTED 1
)

add_subdirectory(${cxxopts_SOURCE_DIR} ${cxxopts_BINARY_DIR})
