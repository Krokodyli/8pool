cmake_minimum_required(VERSION 3.11)

##### Fetch needed libraries ##################################################

include(FetchContent)

FetchContent_Declare(
      glfw
      GIT_REPOSITORY https://github.com/glfw/glfw
)

FetchContent_GetProperties(glfw)
if(NOT glfw_POPULATED)
  MESSAGE(STATUS "Downloading glfw library")
  FetchContent_Populate(glfw)

  set(GLFW_BUILD_EXAMPLES OFF CACHE INTERNAL "Build the GLFW example programs")
  set(GLFW_BUILD_TESTS OFF CACHE INTERNAL "Build the GLFW test programs")
  set(GLFW_BUILD_DOCS ON CACHE INTERNAL "Build the GLFW documentation")
  set(GLFW_INSTALL OFF CACHE INTERNAL "Generate installation target")

  add_subdirectory(${glfw_SOURCE_DIR} ${glfw_BINARY_DIR})
endif()

FetchContent_Declare(
  glm
  GIT_REPOSITORY https://github.com/g-truc/glm.git
)

FetchContent_GetProperties(glm)
if(NOT glm_POPULATED)
  MESSAGE(STATUS "Downloading glm library")
  FetchContent_Populate(glm)
  add_subdirectory(${glm_SOURCE_DIR} ${glm_BINARY_DIR})
endif()


FetchContent_Declare(
  glad
  GIT_REPOSITORY https://github.com/Dav1dde/glad.git
)

FetchContent_GetProperties(glad)
if(NOT glad_POPULATED)
  MESSAGE(STATUS "Downloading glad library")
  FetchContent_Populate(glad)
  set(GLAD_PROFILE "core" CACHE STRING "OpenGL profile")
  set(GLAD_API "gl=" CACHE STRING "API type/version pairs, like \"gl=3.3,gles=\", no version means latest")
  set(GLAD_GENERATOR "c" CACHE STRING "Language to generate the binding for")
  add_subdirectory(${glad_SOURCE_DIR} ${glad_BINARY_DIR})
endif()

set(STB_DIRECTORY ${CMAKE_BINARY_DIR}/_deps/stb)
set(STB_LIB_PATH ${STB_DIRECTORY}/stb_image.h)
if(NOT EXISTS ${STB_LIB_PATH})
  file(MAKE_DIRECTORY ${STB_DIRECTORY})
  file(
    DOWNLOAD
    https://raw.githubusercontent.com/nothings/stb/master/stb_image.h
    ${STB_LIB_PATH}
    SHOW_PROGRESS
  )
endif()

###############################################################################

project(TrainSceneOpenGL)

# set binary file output and create symlink to resources
get_filename_component(ROOT_DIR ${CMAKE_BINARY_DIR} DIRECTORY)
file(MAKE_DIRECTORY ${ROOT_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${ROOT_DIR}/bin)
add_custom_target(shadersLink ALL COMMAND ${CMAKE_COMMAND} -E create_symlink ${ROOT_DIR}/src/shaders ${ROOT_DIR}/bin/shaders)
add_custom_target(texturesLink ALL COMMAND ${CMAKE_COMMAND} -E create_symlink ${ROOT_DIR}/resources/textures ${ROOT_DIR}/bin/textures)

set(CMAKE_BUILD_TYPE Debug)
add_executable(
  game
  src/main.cpp
  src/window.cpp
  src/shader.cpp
  src/camera.cpp
  src/model.cpp
  src/renderer.cpp
  src/glfwInstance.cpp
  src/filesystemHelper.cpp
  src/logger/logger.cpp
  src/inputManager.cpp
  src/meshes/cuboidMesh.cpp
  src/meshes/sphereMesh.cpp
  src/texture.cpp
  src/textureLoader.cpp
  src/resourceManager/textureManager.cpp
  src/resourceManager/shaderManager.cpp
  src/resourceManager/resourceManager.cpp
)

target_link_libraries(game glfw glm glad)
target_include_directories(game INTERFACE ${glm_SOURCE_DIR})
