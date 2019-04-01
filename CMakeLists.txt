cmake_minimum_required(VERSION 3.0)
project(OpenGLPrj)

option(GLFW_BUILD_DOCS OFF)
option(GLFW_BUILD_EXAMPLES OFF)
option(GLFW_BUILD_TESTS OFF)

add_subdirectory(vendor/glfw)

if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -std=c++11")
    if(NOT WIN32)
        set(GLAD_LIBRARIES dl)
    endif()
endif()

set(SHADERS_RELATIVE_SRC_PATH "res/shaders")
set(TEXTURES_RELATIVE_SRC_PATH "res/textures")

include_directories(include/
                    vendor/glad/include/
                    vendor/glfw/include/
                    vendor/glm/
                    vendor/stb/)

file(GLOB VENDORS_SOURCES vendor/glad/src/glad.c)
file(GLOB PROJECT_HEADERS include/*.hpp)
file(GLOB PROJECT_SOURCES src/*.cpp)
file(GLOB PROJECT_SHADERS ${SHADERS_RELATIVE_SRC_PATH}/*.comp
                          ${SHADERS_RELATIVE_SRC_PATH}/*.frag
                          ${SHADERS_RELATIVE_SRC_PATH}/*.geom
                          ${SHADERS_RELATIVE_SRC_PATH}/*.vert
                          ${SHADERS_RELATIVE_SRC_PATH}/*.vs
                          ${SHADERS_RELATIVE_SRC_PATH}/*.fs
                          ${SHADERS_RELATIVE_SRC_PATH}/*.glsl
                          )

file(GLOB PROJECT_TEXTURES ${TEXTURES_RELATIVE_SRC_PATH}/*.png
                           ${TEXTURES_RELATIVE_SRC_PATH}/*.jpg
                          )

file(GLOB PROJECT_CONFIGS CMakeLists.txt
                          Readme.md
                         .gitattributes
                         .gitignore
                         .gitmodules)

source_group("include" FILES ${PROJECT_HEADERS})
source_group("shaders" FILES ${PROJECT_SHADERS})
source_group("textures" FILES ${PROJECT_TEXTURES})
source_group("src" FILES ${PROJECT_SOURCES})
source_group("vendors" FILES ${VENDORS_SOURCES})

add_definitions(-DGLFW_INCLUDE_NONE
                -DPROJECT_SOURCE_DIR=\"${PROJECT_SOURCE_DIR}\")

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES} ${PROJECT_HEADERS}
                               ${PROJECT_SHADERS} ${PROJECT_TEXTURES} ${PROJECT_CONFIGS}
                               ${VENDORS_SOURCES})
target_link_libraries(${PROJECT_NAME}
		      glfw
                      ${GLFW_LIBRARIES} ${GLAD_LIBRARIES}
		      )


#set (source "${CMAKE_SOURCE_DIR}/res")
#set (destination "${CMAKE_CURRENT_BINARY_DIR}/res")

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/res
        $<TARGET_FILE_DIR:${PROJECT_NAME}>/../res)


set_target_properties(${PROJECT_NAME}
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${PROJECT_NAME}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${PROJECT_NAME}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${PROJECT_NAME}/bin"
)
