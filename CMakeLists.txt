cmake_minimum_required(VERSION 2.8.11)
project(DaedalusMaze)

find_package(Qt5Widgets REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(DMAZE_SRC
  src/main.cpp
  src/window.cpp
  src/cell.cpp
  src/mazeWidget.cpp
)

add_executable(${PROJECT_NAME} ${DMAZE_SRC})
target_link_libraries(${PROJECT_NAME} Qt5::Widgets)
