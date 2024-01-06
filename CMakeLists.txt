include(cmake/cmake_env.cmake)

cmake_minimum_required(VERSION 3.15)
project(cvAutoTrack.Depends)

set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/install)


include(FetchContent)
# message(STATUS "安装opencv")
# 
# FetchContent_Declare(opencv_contrib GIT_REPOSITORY https://github.com/opencv/opencv_contrib.git GIT_TAG 4.8.0)
# FetchContent_MakeAvailable(opencv_contrib)
# message(STATUS "opencv_contrib_SOURCE_DIR:${opencv_contrib_SOURCE_DIR}")
# # 手动下载opencv编译安装
# # https://github.com/opencv/opencv.git 4.8.0
# FetchContent_Declare(opencv GIT_REPOSITORY https://github.com/opencv/opencv.git GIT_TAG 4.8.0)
# # output static lib
# set(BUILD_SHARED_LIBS OFF)
# # extra modules
# set(OPENCV_EXTRA_MODULES_PATH ${opencv_contrib_SOURCE_DIR}/modules)
# set(OPENCV_ENABLE_NONFREE ON)
# # disable modules
# set(BUILD_opencv_apps OFF)
# set(BUILD_opencv_aruco OFF)
# set(BUILD_opencv_bgsegm OFF)
# set(BUILD_opencv_bioinspired OFF)
# set(BUILD_opencv_calib3d ON)
# set(BUILD_opencv_ccalib OFF)
# set(BUILD_opencv_core ON)
# set(BUILD_opencv_datasets OFF)
# set(BUILD_opencv_dnn OFF)
# set(BUILD_opencv_dnn_objdetect OFF)
# set(BUILD_opencv_dnn_superres OFF)
# set(BUILD_opencv_dpm OFF)
# set(BUILD_opencv_face OFF)
# set(BUILD_opencv_flann ON)
# set(BUILD_opencv_features2d ON)
# set(BUILD_opencv_fuzzy OFF)
# set(BUILD_opencv_gapi OFF)
# set(BUILD_opencv_hfs OFF)
# set(BUILD_opencv_highgui ON)
# set(BUILD_opencv_imgcodecs ON)
# set(BUILD_opencv_imgproc ON)
# set(BUILD_opencv_intensity_transform OFF)
# set(BUILD_opencv_line_descriptor OFF)
# set(BUILD_opencv_mcc OFF)
# set(BUILD_opencv_ml OFF)
# set(BUILD_opencv_objdetect OFF)
# set(BUILD_opencv_optflow OFF)
# set(BUILD_opencv_phase_unwrapping OFF)
# set(BUILD_opencv_photo OFF)
# set(BUILD_opencv_plot OFF)
# set(BUILD_opencv_quality OFF)
# set(BUILD_opencv_rapid OFF)
# set(BUILD_opencv_reg OFF)
# set(BUILD_opencv_rgbd OFF)
# set(BUILD_opencv_saliency OFF)
# set(BUILD_opencv_shape OFF)
# set(BUILD_opencv_stereo OFF)
# set(BUILD_opencv_stitching OFF)
# set(BUILD_opencv_structured_light OFF)
# set(BUILD_opencv_superres OFF)
# set(BUILD_opencv_surface_matching OFF)
# set(BUILD_opencv_text OFF)
# set(BUILD_opencv_tracking OFF)
# set(BUILD_opencv_ts OFF)
# set(BUILD_opencv_video OFF)
# set(BUILD_opencv_videoio OFF)
# set(BUILD_opencv_videostab OFF)
# set(BUILD_opencv_world ON)
# set(BUILD_opencv_wechat_qrcode OFF)
# set(BUILD_opencv_xfeatures2d ON)
# set(BUILD_opencv_ximgproc OFF)
# set(BUILD_opencv_xobjdetect OFF)
# set(BUILD_opencv_xphoto OFF)
# # disable python
# set(BUILD_opencv_python2 OFF)
# set(BUILD_opencv_python3 OFF)
# set(BUILD_opencv_python_bindings_generator OFF)
# set(BUILD_opencv_python_tests OFF)
# # disable java
# set(BUILD_JAVA OFF)
# set(BUILD_opencv_java_bindings_generator OFF)
# # disable js
# set(BUILD_opencv_js OFF)
# set(BUILD_opencv_js_bindings_generator OFF)
# # not test
# set(BUILD_TESTS OFF)
# set(BUILD_PERF_TESTS OFF)
# set(BUILD_EXAMPLES OFF)
# set(BUILD_DOCS OFF)
# set(BUILD_WITH_DEBUG_INFO OFF)
# # no itt
# set(WITH_ITT OFF)
# set(BUILD_ITT OFF)
# set(ccitt OFF)
# # pic
# set(BUILD_SHARED_LIBS OFF)
# set(BUILD_WITH_STATIC_CRT ON)
# # 启用位置无关代码
# set(CMAKE_POSITION_INDEPENDENT_CODE ON)
# 
# set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/deps/opencv)
# 
# FetchContent_MakeAvailable(opencv)
# # install opencv
# install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/deps/opencv DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/build/_deps/opencv-src)



# 将opencv的静态库链接到my_opencv dynamic库
# set(OpenCV_DIR  ${CMAKE_CURRENT_SOURCE_DIR}/deps/opencv/x64/vc17/staticlib)
# find_package(OpenCV REQUIRED)
# 
# file(GLOB_RECURSE opencv_src ${CMAKE_CURRENT_SOURCE_DIR}/deps/opencv/include/*.h)
# add_library(my_opencv SHARED ${opencv_src} main.cpp)
# target_include_directories(my_opencv PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/deps/opencv/include)
# target_compile_definitions(my_opencv PRIVATE -DOPENCV_EXPORTS -DCVAPI_EXPORTS)
# target_link_libraries(my_opencv PRIVATE opencv_world opencv_img_hash)
# 
# add_executable(Demo main.cpp)
# target_include_directories(Demo PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/deps/opencv/include)
# target_link_libraries(Demo my_opencv)

message(STATUS "安装 fmt")
FetchContent_Populate(fmt GIT_REPOSITORY https://github.com/fmtlib/fmt GIT_TAG 10.2.0)
set(BUILD_SHARED_LIBS OFF)

message(STATUS "安装 spdlog")
FetchContent_Populate(spdlog GIT_REPOSITORY https://github.com/gabime/spdlog.git GIT_TAG v1.12.0)
set(BUILD_SHARED_LIBS OFF)

message(STATUS "安装 cereal")
FetchContent_Populate(cereal GIT_REPOSITORY https://github.com/USCiLab/cereal.git GIT_TAG v1.3.0)
set(JUST_INSTALL_CEREAL ON)
set(BUILD_SANDBOX OFF)

set(dep_fmt_include ${fmt_SOURCE_DIR}/include)
set(dep_spdlog_include ${spdlog_SOURCE_DIR}/include)
set(dep_cereal_include ${cereal_SOURCE_DIR}/include)

file(GLOB_RECURSE dep_fmt_h ${dep_fmt_include}/*.h )
file(GLOB_RECURSE dep_spdlog_h ${dep_spdlog_include}/*.h)
file(GLOB_RECURSE dep_cereal_h ${dep_cereal_include}/*.h)
file(GLOB_RECURSE dep_fmt_src ${dep_fmt_include}/../src/*.cpp)
file(GLOB_RECURSE dep_spdlog_src ${dep_spdlog_include}/../src/*.cpp)

list(APPEND deps_include ${dep_fmt_include} ${dep_spdlog_include} ${dep_cereal_include})
list(APPEND deps_h ${dep_fmt_h} ${dep_spdlog_h} ${dep_cereal_h})
list(APPEND deps_src ${dep_fmt_src} ${dep_spdlog_src})

message(STATUS "目录：${deps_include}")

add_library(cvAutoTrack.Depends SHARED ${deps_src} ${deps_h})
target_compile_definitions(cvAutoTrack.Depends PRIVATE -DFMT_EXPORT -DSPDLOG_COMPILED_LIB -DSPDLOG_SHARED_LIB -Dspdlog_EXPORTS)
target_include_directories(cvAutoTrack.Depends PRIVATE ${deps_include})

set_target_properties(cvAutoTrack.Depends PROPERTIES DEBUG_POSTFIX "d")

install(TARGETS cvAutoTrack.Depends DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/install
    LIBRARY DESTINATION  ${CMAKE_BINARY_DIR}/install/lib
    ARCHIVE DESTINATION  ${CMAKE_BINARY_DIR}/install/lib
    RUNTIME DESTINATION  ${CMAKE_BINARY_DIR}/install/bin
    INCLUDES DESTINATION ${CMAKE_BINARY_DIR}/install/include
 )
install(DIRECTORY ${deps_include} DESTINATION ${CMAKE_BINARY_DIR}/install/include)

add_executable(test main.cpp)
target_include_directories(test PRIVATE ${deps_include})
target_link_libraries(test PRIVATE cvAutoTrack.Depends)
