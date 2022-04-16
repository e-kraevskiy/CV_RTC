cmake_minimum_required(VERSION 3.5)

project(create_board_charuco LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# OpenCV:
FIND_PACKAGE(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
link_directories(${OpenCV_LIBRARY_DIR})

# Сюда добавляем .h-ки
set(PROJECT_HEADERS
    aruco_samples_utility.hpp
)
# Сюда добавляем .cpp-ки
set(PROJECT_SOURCES
    create_board_charuco.cpp
    #calibrate_camera_charuco.cpp
    #detect_board_charuco.cpp
)

add_executable(${PROJECT_NAME}
  ${PROJECT_SOURCES}
  ${PROJECT_HEADERS}
)

target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBRARIES})
