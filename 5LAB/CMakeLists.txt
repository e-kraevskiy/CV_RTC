cmake_minimum_required(VERSION 3.5)

project(5LAB LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# OpenCV:
FIND_PACKAGE(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
link_directories(${OpenCV_LIBRARY_DIR})

# Сюда добавляем .h-ки
set(PROJECT_HEADERS
    src/cube.h
)
# Сюда добавляем .cpp-ки
set(PROJECT_SOURCES
    src/main.cpp
    src/cube.cpp
)


add_executable(${PROJECT_NAME}
  ${PROJECT_SOURCES}
  ${PROJECT_HEADERS}
)

target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBRARIES})
