project(CG2019ICMC)

cmake_minimum_required(VERSION 3.10)

include(ExternalProject)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/ExternalResources/")
include( glfw )

add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/ExternalResources/GLAD" "ExternalResources/GLAD")
set(GLAD_INCLUDES "${CMAKE_CURRENT_SOURCE_DIR}/ExternalResources/GLAD/include")

set(CG2019ICMC_CPP_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/ExternalResources/include)
add_subdirectory(ExternalResources)

##################################################################
# EXECUTAVEIS

# Versao orientado a objetos
add_executable( projeto1CPP projeto_1.cpp )
target_link_libraries( projeto1CPP glad ${GLFW_LIBRARIES} cg2019cpp )
target_include_directories( projeto1CPP PUBLIC 
                            ${CG2019ICMC_CPP_INCLUDE_DIR}
                            ${GLFW_INCLUDE_DIR} ${GLAD_INCLUDES} )
