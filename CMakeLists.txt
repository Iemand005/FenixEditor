cmake_minimum_required(VERSION 3.19)
project(Editor LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets OpenGL OpenGLWidgets LinguistTools Network)

qt_standard_project_setup()

qt_add_executable(Editor
    # WIN32 MACOSX_BUNDLE
    main.cpp
    editorwindow.cpp
    editorwindow.h
    editorwindow.ui
    enginewidget.h enginewidget.cpp
    mjpegserver.h mjpegserver.cpp
    fevulkanwindow.h fevulkanwindow.cpp
)

qt_add_translations(
    TARGETS Editor
    TS_FILES Editor_en_US.ts
)

set(JOLT_BUILD_SHADERS OFF CACHE BOOL "" FORCE)
set(JPH_USE_DXC OFF CACHE BOOL "" FORCE)
set(JPH_USE_DX12 OFF CACHE BOOL "" FORCE)
set(JPH_USE_MTL OFF CACHE BOOL "" FORCE)
set(JPH_USE_VK OFFsste CACHE BOOL "" FORCE)

# add_subdirectory(../Engine build/bin)

set(ENGINE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../FenixEngine")

if(NOT TARGET Engine)
    message(STATUS "Engine target not found. Looking for engine source...")
    
    if(EXISTS "${ENGINE_DIR}/CMakeLists.txt")
        add_subdirectory("${ENGINE_DIR}" FenixEngine)
    # elif(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/FenixEngine/CMakeLists.txt")
    #     add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/FenixEngine" FenixEngine)
    else()
        message(FATAL_ERROR "FenixEngine not found!")
    endif()
endif()

target_include_directories(Editor PRIVATE
    ../../include
    ../Engine
)

target_include_directories(Editor PRIVATE
        include
        ${ENGINE_DIR}
        ${ENGINE_DIR}/include
        ${ENGINE_DIR}/external
        ${ENGINE_DIR}/external/imgui
        ${ENGINE_DIR}/external/kissfft
        ${ENGINE_DIR}/external/SDL/include
        ${ENGINE_DIR}/src/Engine
)

target_link_libraries(Editor
    PRIVATE
        Qt::Core
        Qt::Widgets
        Qt6::OpenGL
        Qt6::OpenGLWidgets
        Qt6::Network

        Engine
)

include(GNUInstallDirs)

install(TARGETS Editor
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET Editor
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})

set(RES_SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/resources")
set(RES_DEST "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/resources")

# add_custom_command(
#     TARGET Editor POST_BUILD
#     COMMAND ${CMAKE_COMMAND} -E copy_directory
#         "${RES_SOURCE}"
#         "${RES_DEST}"
#     COMMENT "Resources kopiëren naar build directory..."
# )
