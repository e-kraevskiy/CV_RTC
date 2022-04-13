cmake_minimum_required(VERSION 3.5)

project(3LAB LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# OpenCV:
FIND_PACKAGE(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
link_directories(${OpenCV_LIBRARY_DIR})

# Сюда добавляем .h-ки
set(PROJECT_HEADERS
    task_1.h
    task_3.h
    task_4.h
)
# Сюда добавляем .cpp-ки
set(PROJECT_SOURCES
    main.cpp
    task_1.cpp
    task_3.cpp
    task_4.cpp
)


add_executable(${PROJECT_NAME}
  ${PROJECT_SOURCES}
  ${PROJECT_HEADERS}
)

target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBRARIES})
