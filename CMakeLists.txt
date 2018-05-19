cmake_minimum_required(VERSION 3.1)

project(photo-selector LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Core Quick Widgets REQUIRED)

add_executable(${PROJECT_NAME} "main.cpp" "qml.qrc"
    PhotoDirModel.cpp)

target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Quick Qt5::Widgets stdc++fs)
