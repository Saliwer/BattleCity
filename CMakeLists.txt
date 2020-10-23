cmake_minimum_required(VERSION 3.16)

set(PROJECT_NAME BattleCity)
project(${PROJECT_NAME})

set(CMAKE_BUILD_TYPE Debug)

add_executable(${PROJECT_NAME} src/main.cpp
                src/Renderer/ShaderProgram.cpp
                src/Renderer/ShaderProgram.h
                src/Renderer/Texture2D.h
                src/Renderer/Texture2D.cpp
		src/Renderer/Sprite.h
		src/Renderer/Sprite.cpp
         	src/Renderer/AnimatedSprite.h
		src/Renderer/AnimatedSprite.cpp
		src/Manager/ResourceManager.h
                src/Manager/ResourceManager.cpp
                src/Manager/stb_image.h)

target_include_directories(${PROJECT_NAME} PRIVATE external/glm)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

add_subdirectory(external/glfw)
target_link_libraries(${PROJECT_NAME} glfw)

add_subdirectory(external/glad)
target_link_libraries(${PROJECT_NAME} glad)

set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                   ${CMAKE_SOURCE_DIR}/resource $<TARGET_FILE_DIR:${PROJECT_NAME}>/resource)

