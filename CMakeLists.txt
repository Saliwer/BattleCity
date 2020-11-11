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
                src/Renderer/VertexBuffer.h
                src/Renderer/VertexBuffer.cpp
                src/Renderer/IndexBuffer.h
                src/Renderer/IndexBuffer.cpp
                src/Renderer/VertexArray.h
                src/Renderer/VertexArray.cpp
                src/Renderer/Renderer.h
                src/Renderer/Renderer.cpp

                src/Game/Game.h
                src/Game/Game.cpp
                src/Game/Level.h
                src/Game/Level.cpp

                src/Game/GameObjects/Tank.h
                src/Game/GameObjects/Tank.cpp
                src/Game/GameObjects/IGameObject.h
                src/Game/GameObjects/IGameObject.cpp
                src/Game/GameObjects/BrickWall.h
                src/Game/GameObjects/BrickWall.cpp
                src/Game/GameObjects/BetonWall.h
                src/Game/GameObjects/BetonWall.cpp
                src/Game/GameObjects/Tree.h
                src/Game/GameObjects/Tree.cpp
                src/Game/GameObjects/Ice.h
                src/Game/GameObjects/Ice.cpp
                src/Game/GameObjects/Water.h
                src/Game/GameObjects/Water.cpp
                src/Game/GameObjects/Eagle.h
                src/Game/GameObjects/Eagle.cpp
                src/Game/GameObjects/Border.h
                src/Game/GameObjects/Border.cpp

                src/Manager/ResourceManager.h
                src/Manager/ResourceManager.cpp
                src/Manager/stb_image.h)

target_include_directories(${PROJECT_NAME} PRIVATE external/glm)
target_include_directories(${PROJECT_NAME} PRIVATE external/rapidjson)

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

