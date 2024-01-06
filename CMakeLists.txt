include(cmake/cmake_env.cmake)

cmake_minimum_required(VERSION 3.15)
project(Demo)



include(FetchContent)

message(STATUS "安装opencv")
# 手动下载opencv编译安装
# https://github.com/opencv/opencv.git 4.8.0
FetchContent_Declare(opencv GIT_REPOSITORY https://github.com/opencv/opencv.git GIT_TAG 4.8.0 )
set(BUILD_SHARED_LIBS ON)
set(BUILD_opencv_apps OFF)
set(BUILD_opencv_calib3d OFF)
set(BUILD_opencv_dnn OFF)
set(BUILD_opencv_features2d ON)
set(BUILD_opencv_flann OFF)
set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/deps/opencv)

FetchContent_MakeAvailable(opencv)


