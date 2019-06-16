project(CG2019ICMC)

cmake_minimum_required(VERSION 3.10)
set (CMAKE_CXX_STANDARD 11)

message("Using CXX " ${CMAKE_CXX_COMPILER})

include(ExternalProject)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/ExternalResources")
# include( glfw )

find_package(OpenGL REQUIRED)
set(OPENGL_INCLUDE_DIR ${OPENGL_INCLUDE_DIR} CACHE STRING "")
set(OPENGL_LIBRARIES ${OPENGL_LIBRARIES} CACHE STRING "")

add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/ExternalResources/glfw" "ExternalResources/glfw")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/ExternalResources/GLAD" "ExternalResources/GLAD")
set(GLAD_INCLUDES "${CMAKE_CURRENT_SOURCE_DIR}/ExternalResources/GLAD/include")

set(CG2019ICMC_CPP_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/ExternalResources/include)
add_subdirectory(ExternalResources)

##################################################################
# EXECUTAVEIS

# Versao orientado a objetos
add_executable( projeto2CPP projeto_2.cpp )
target_link_libraries( projeto2CPP glad ${GLFW_LIBRARIES} cg2019cpp )
target_include_directories( projeto2CPP PUBLIC 
                            ${CG2019ICMC_CPP_INCLUDE_DIR}
                            ${GLFW_INCLUDE_DIR} ${GLAD_INCLUDES} )