include(DownloadProject)

download_project(
  PROJ pugixml 
  GIT_REPOSITORY https://github.com/zeux/pugixml
  GIT_TAG master
  GIT_SHALLOW TRUE
  PREFIX ${CMAKE_CURRENT_BINARY_DIR}
  UPDATE_DISCONNECTED 1
)

add_subdirectory(${pugixml_SOURCE_DIR} ${pugixml_BINARY_DIR})
