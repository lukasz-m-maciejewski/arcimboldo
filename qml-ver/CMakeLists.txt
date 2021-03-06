cmake_minimum_required(VERSION 3.1)

project(arcimboldo LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Core Quick Widgets REQUIRED)

list(APPEND ARCIMBOLDO_SOURCES
    src/main.cpp
    src/PhotoDirModel.cpp
    src/AppState.cpp
    src/DirectoryPathValidator.cpp
    src/TargetDirectoryGenerator.cpp)

list(APPEND ARCIMBOLDO_HEADERS
    src/PhotoDirModel.hpp
    src/AppState.hpp
    src/DirectoryPathValidator.hpp
    src/TargetDirectoryGenerator.hpp
    )

add_executable(${PROJECT_NAME}
    ${ARCIMBOLDO_SOURCES}
    "qml.qrc"
    ${ARCIMBOLDO_HEADERS}
    )

target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Quick Qt5::Widgets)

#FILE(GLOB_RECURSE LibFiles "${CMAKE_SOURCE_DIR}/*.hpp")
#add_custom_target(headers SOURCES ${LibFiles})
