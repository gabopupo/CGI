file(GLOB HEADERS 
        ${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp
        )
file(GLOB SOURCES 
        ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
        )

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
add_library(cg2019cpp STATIC ${SOURCES} ${HEADERS})
add_dependencies(cg2019cpp glfw)
target_link_libraries(cg2019cpp PUBLIC ${GLFW_LIBRARIES} glad)
set_target_properties(cg2019cpp PROPERTIES
        OUTPUT_NAME "cg2019cpp"
        FOLDER "CG2019cpp")
target_include_directories(cg2019cpp PUBLIC ${CG2019ICMC_SOURCE_DIR}/include ${GLFW_INCLUDE_DIR})

set(CG2019ICMC_CPP_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")
# add_library(glad STATIC "${GLAD_DIR}/glad.c")
# SET_TARGET_PROPERTIES(glad PROPERTIES LINKER_LANGUAGE CXX)
# target_include_directories(glad PRIVATE "${GLAD_DIR}/include/glad.h")