include(cmake/cmake_env.cmake)

cmake_minimum_required(VERSION 3.15)
project(cvAutoTrack.Depends)

set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR}/install)

set(USED_PROXY OFF CACHE BOOL "是否使用代理")
set(USED_MRIRROR OFF CACHE BOOL "是否使用国内镜像")
set(USED_MRIRROR ON)
if(USED_PROXY)
    message(STATUS "设置代理 127.0.0.1:1080")
    set(ENV{http_proxy} "http://127.0.0.1:1080")
    set(ENV{https_proxy} "http://127.0.0.1:1080")
endif()

set(GIT_HOST "github.com")
if(USED_MRIRROR)
    set(GIT_HOST "gitee.com")
endif()

include(FetchContent)

message(STATUS "安装opencv")
FetchContent_Populate(opencv_contrib GIT_REPOSITORY https://${GIT_HOST}/opencv/opencv_contrib.git GIT_TAG 4.8.0 GIT_SHALLOW 1)
# # 手动下载opencv编译安装
# # https://github.com/opencv/opencv.git 4.8.0
FetchContent_Declare(opencv GIT_REPOSITORY https://${GIT_HOST}/opencv/opencv.git GIT_TAG 4.8.0 GIT_SHALLOW 1)
set(BUILD_SHARED_LIBS ON)
set(OPENCV_CONFIG_FILE_INCLUDE_DIR ${CMAKE_BINARY_DIR}/opencv_gen_include)
# extra modules
set(OPENCV_EXTRA_MODULES_PATH ${opencv_contrib_SOURCE_DIR}/modules)
set(OPENCV_ENABLE_NONFREE ON)
# disable modules
set(BUILD_opencv_apps OFF)
set(BUILD_opencv_aruco OFF)
set(BUILD_opencv_bgsegm OFF)
set(BUILD_opencv_bioinspired OFF)
set(BUILD_opencv_calib3d ON)
set(BUILD_opencv_ccalib OFF)
set(BUILD_opencv_core ON)
set(BUILD_opencv_datasets OFF)
set(BUILD_opencv_dnn OFF)
set(BUILD_opencv_dnn_objdetect OFF)
set(BUILD_opencv_dnn_superres OFF)
set(BUILD_opencv_dpm OFF)
set(BUILD_opencv_face OFF)
set(BUILD_opencv_flann ON)
set(BUILD_opencv_features2d ON)
set(BUILD_opencv_fuzzy OFF)
set(BUILD_opencv_gapi OFF)
set(BUILD_opencv_hfs OFF)
set(BUILD_opencv_highgui ON)
set(BUILD_opencv_imgcodecs ON)
set(BUILD_opencv_imgproc ON)
set(BUILD_opencv_intensity_transform OFF)
set(BUILD_opencv_line_descriptor OFF)
set(BUILD_opencv_mcc OFF)
set(BUILD_opencv_ml OFF)
set(BUILD_opencv_objdetect OFF)
set(BUILD_opencv_optflow OFF)
set(BUILD_opencv_phase_unwrapping OFF)
set(BUILD_opencv_photo OFF)
set(BUILD_opencv_plot OFF)
set(BUILD_opencv_quality OFF)
set(BUILD_opencv_rapid OFF)
set(BUILD_opencv_reg OFF)
set(BUILD_opencv_rgbd OFF)
set(BUILD_opencv_saliency OFF)
set(BUILD_opencv_shape OFF)
set(BUILD_opencv_stereo OFF)
set(BUILD_opencv_stitching OFF)
set(BUILD_opencv_structured_light OFF)
set(BUILD_opencv_superres OFF)
set(BUILD_opencv_surface_matching OFF)
set(BUILD_opencv_text OFF)
set(BUILD_opencv_tracking OFF)
set(BUILD_opencv_ts OFF)
set(BUILD_opencv_video OFF)
set(BUILD_opencv_videoio OFF)
set(BUILD_opencv_videostab OFF)
set(BUILD_opencv_world ON)
set(BUILD_opencv_wechat_qrcode OFF)
set(BUILD_opencv_xfeatures2d ON)
set(BUILD_opencv_ximgproc OFF)
set(BUILD_opencv_xobjdetect OFF)
set(BUILD_opencv_xphoto OFF)
# disable python
set(BUILD_opencv_python_bindings_generator OFF)
set(BUILD_opencv_python_tests OFF)
# disable java
set(BUILD_JAVA OFF)
set(BUILD_opencv_java_bindings_generator OFF)
# disable js
set(BUILD_opencv_js OFF)
set(BUILD_opencv_js_bindings_generator OFF)
# disable objc
set(BUILD_opencv_objc_bindings_generator OFF)
# not test
set(BUILD_TESTS OFF)
set(BUILD_PERF_TESTS OFF)
set(BUILD_EXAMPLES OFF)
set(BUILD_DOCS OFF)
set(BUILD_WITH_DEBUG_INFO OFF)
# no itt
set(WITH_ITT OFF)
set(BUILD_ITT OFF)
set(ccitt OFF)
# pic
set(BUILD_SHARED_LIBS OFF)
set(BUILD_WITH_STATIC_CRT ON)
# 启用位置无关代码
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

FetchContent_MakeAvailable(opencv)

message(STATUS "opencv编译目录：${opencv_BINARY_DIR}")

# check download cache
# fils : ${opencv_BINARY_DIR}/download/xfeatures2d/vgg_generated_120.i
if (NOT EXISTS ${opencv_BINARY_DIR}/3rdparty/ippicv/ippicv_win/icv/lib/intel64/ippicvmt.lib)
    message(FAIAL_ERROR "缺少ippicvmt.lib, 请启用代理（set(USED_PROXY ON)）重新编译")
endif()




message(STATUS "安装 fmt")
FetchContent_Populate(fmt GIT_REPOSITORY https://github.com/fmtlib/fmt GIT_TAG 10.2.0 GIT_SHALLOW 1)
set(BUILD_SHARED_LIBS OFF)

message(STATUS "安装 spdlog")
FetchContent_Populate(spdlog GIT_REPOSITORY https://github.com/gabime/spdlog.git GIT_TAG v1.12.0 GIT_SHALLOW 1)
set(BUILD_SHARED_LIBS OFF)

message(STATUS "安装 cereal")
FetchContent_Populate(cereal GIT_REPOSITORY https://github.com/USCiLab/cereal.git GIT_TAG v1.3.0 GIT_SHALLOW 1)
set(JUST_INSTALL_CEREAL ON)
set(BUILD_SANDBOX OFF)

set(dep_opencv_include ${opencv_SOURCE_DIR}/include)
set(dep_opencv_modules_include ${opencv_SOURCE_DIR}/modules)
set(dep_opencv_extra_modules_include ${opencv_contrib_SOURCE_DIR}/modules)
set(dep_opencv_3rdparty_include ${opencv_SOURCE_DIR}/3rdparty/include)
list(APPEND dep_opencv_3rdparty_include 
${opencv_SOURCE_DIR}/3rdparty/include/opencl/1.2
${opencv_SOURCE_DIR}/3rdparty/include/vulkan
${opencv_SOURCE_DIR}/3rdparty/zlib
# ${opencv_SOURCE_DIR}/3rdparty/libjpeg
${opencv_SOURCE_DIR}/3rdparty/libjpeg-turbo/src
${opencv_BINARY_DIR}/3rdparty/libjpeg-turbo
${opencv_SOURCE_DIR}/3rdparty/libpng
${opencv_SOURCE_DIR}/3rdparty/libtiff
${opencv_BINARY_DIR}/3rdparty/libtiff
${opencv_SOURCE_DIR}/3rdparty/libwebp/src
${opencv_SOURCE_DIR}/3rdparty/openexr/Half
${opencv_SOURCE_DIR}/3rdparty/openexr/Iex
${opencv_SOURCE_DIR}/3rdparty/openexr/IlmImf
${opencv_SOURCE_DIR}/3rdparty/openexr/IlmThread
${opencv_SOURCE_DIR}/3rdparty/openexr/Imath
${opencv_BINARY_DIR}/3rdparty/openexr
${opencv_SOURCE_DIR}/3rdparty/openjpeg/openjp2
${opencv_BINARY_DIR}/3rdparty/openjpeg/openjp2


${opencv_BINARY_DIR}/3rdparty/ippicv/ippicv_win/icv/include
${opencv_BINARY_DIR}/3rdparty/ippicv/ippicv_win/iw/include
${opencv_BINARY_DIR}/3rdparty/ippiw/ippicv_win/iw/include
)

list(APPEND dep_opencv_libs ${opencv_BINARY_DIR}/3rdparty/ippicv/ippicv_win/icv/lib/intel64/ippicvmt.lib)

set(dep_fmt_include ${fmt_SOURCE_DIR}/include)
set(dep_spdlog_include ${spdlog_SOURCE_DIR}/include)
set(dep_cereal_include ${cereal_SOURCE_DIR}/include)

file(GLOB dep_opencv_build_world_include ${opencv_BINARY_DIR}/modules/world/*.h ${opencv_BINARY_DIR}/modules/world/*.hpp)

file(GLOB_RECURSE dep_opencv_h
${dep_opencv_include}/*.h*
${dep_opencv_modules_include}/calib3d/include/*.h*
${dep_opencv_modules_include}/core/include/*.h*
${dep_opencv_modules_include}/flann/include/*.h*
${dep_opencv_modules_include}/features2d/include/*.h*
#${dep_opencv_modules_include}/highgui/include/*.h*
${dep_opencv_modules_include}/imgcodecs/include/*.h*
${dep_opencv_modules_include}/imgproc/include/*.h*
${dep_opencv_modules_include}/world/include/*.h*
${dep_opencv_extra_modules_include}/xfeatures2d/include/*.h*
${dep_opencv_modules_include}/calib3d/src/*.h*
${dep_opencv_modules_include}/core/src/*.h*
${dep_opencv_modules_include}/flann/src/*.h*
${dep_opencv_modules_include}/features2d/src/*.h*
#${dep_opencv_modules_include}/highgui/src/*.h*
${dep_opencv_modules_include}/imgcodecs/src/*.h*
${dep_opencv_modules_include}/imgproc/src/*.h*
${dep_opencv_modules_include}/world/src/*.h*
${dep_opencv_extra_modules_include}/xfeatures2d/src/*.h*
${opencv_BINARY_DIR}/3rdparty/libjpeg-turbo/*.h*
)
list(APPEND dep_opencv_h ${dep_opencv_build_world_include})
file(GLOB_RECURSE dep_fmt_h ${dep_fmt_include}/*.h*)
file(GLOB_RECURSE dep_spdlog_h ${dep_spdlog_include}/*.h*)
file(GLOB_RECURSE dep_cereal_h ${dep_cereal_include}/*.h*)

file(GLOB_RECURSE dep_opencv_src 
${dep_opencv_modules_include}/calib3d/src/*.cpp
${dep_opencv_modules_include}/core/src/*.cpp
${dep_opencv_modules_include}/flann/src/*.cpp
${dep_opencv_modules_include}/features2d/src/*.cpp
#${dep_opencv_modules_include}/highgui/src/*.cpp
${dep_opencv_modules_include}/imgcodecs/src/*.cpp
${dep_opencv_modules_include}/imgproc/src/*.cpp
${dep_opencv_extra_modules_include}/xfeatures2d/src/*.cpp
${opencv_BINARY_DIR}/modules/world/opencl_kernels_*.cpp
)
#
# ${dep_opencv_modules_include}/world/src/*.cpp

# delete imgproc/src/resize.lasx.cpp
list(REMOVE_ITEM dep_opencv_src ${dep_opencv_modules_include}/features2d/src/fast.avx2.cpp)
list(REMOVE_ITEM dep_opencv_src ${dep_opencv_modules_include}/imgproc/src/resize.lasx.cpp)
list(REMOVE_ITEM dep_opencv_src ${dep_opencv_modules_include}/imgproc/src/corner.avx.cpp)
list(REMOVE_ITEM dep_opencv_src ${dep_opencv_modules_include}/imgproc/src/imgwarp.avx2.cpp)
list(REMOVE_ITEM dep_opencv_src ${dep_opencv_modules_include}/imgproc/src/imgwarp.lasx.cpp)
list(REMOVE_ITEM dep_opencv_src ${dep_opencv_modules_include}/imgproc/src/imgwarp.sse4_1.cpp)
list(REMOVE_ITEM dep_opencv_src ${dep_opencv_modules_include}/imgproc/src/resize.avx2.cpp)
list(REMOVE_ITEM dep_opencv_src ${dep_opencv_modules_include}/imgproc/src/resize.sse4_1.cpp)

file(GLOB_RECURSE dep_fmt_src ${dep_fmt_include}/../src/*.cpp)
file(GLOB_RECURSE dep_spdlog_src ${dep_spdlog_include}/../src/*.cpp)


list(APPEND deps_include ${dep_fmt_include} ${dep_spdlog_include} ${dep_cereal_include} ${dep_opencv_include} ${dep_opencv_3rdparty_include} ${OPENCV_CONFIG_FILE_INCLUDE_DIR}
${dep_opencv_modules_include}/calib3d/include
${dep_opencv_modules_include}/core/include
${dep_opencv_modules_include}/flann/include
${dep_opencv_modules_include}/features2d/include
${dep_opencv_modules_include}/highgui/include
${dep_opencv_modules_include}/imgcodecs/include
${dep_opencv_modules_include}/imgproc/include
${dep_opencv_modules_include}/world/include
${dep_opencv_extra_modules_include}/xfeatures2d/include
${opencv_BINARY_DIR}/modules/world
${opencv_BINARY_DIR}/downloads/xfeatures2d
) 
list(APPEND deps_h ${dep_fmt_h} ${dep_spdlog_h} ${dep_cereal_h} ${dep_opencv_h})
list(APPEND deps_src ${dep_fmt_src} ${dep_spdlog_src} ${dep_opencv_src})

message(STATUS "目录：${opencv_BINARY_DIR}")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

add_library(cvAutoTrack.Depends SHARED ${deps_src} ${deps_h})

target_compile_definitions(cvAutoTrack.Depends
PUBLIC 
-D_SILENCE_ALL_MS_EXT_DEPRECATION_WARNINGS
PRIVATE 
-DFMT_EXPORT 
-DSPDLOG_COMPILED_LIB -DSPDLOG_SHARED_LIB -Dspdlog_EXPORTS
-DOPENCV_EXPORTS -DCVAPI_EXPORTS
-D_CRT_SECURE_NO_DEPRECATE
-D_CRT_NONSTDC_NO_DEPRECATE
-D_SCL_SECURE_NO_WARNINGS
-DENABLE_PLUGINS
-DOPENCV_MODULE_IS_PART_OF_WORLD=1
-D_VARIADIC_MAX=10
-D_WIN32_WINNT=0x0601
-DHAVE_WEBP
-DHAVE_IMGCODEC_HDR
-DHAVE_IMGCODEC_SUNRASTER
-DHAVE_IMGCODEC_PXM
-DHAVE_IMGCODEC_PFM
-D_USE_MATH_DEFINES
-D__STDC_CONSTANT_MACROS
-D__STDC_LIMIT_MACROS
-D__STDC_FORMAT_MACROS
-D__OPENCV_BUILD=1
-DOPJ_STATIC
-DHAVE_WIN32UI
-DOPENCV_XFEATURES2D_HAS_VGG_DATA=1
-DCOMPRESS
)
set(cvAutoTrack.Depends PROPERTIES OPENCV_ALLOCATOR_STATS_COUNTER_TYPE "long long")
target_compile_options(cvAutoTrack.Depends PRIVATE /MP)
target_include_directories(cvAutoTrack.Depends PRIVATE ${deps_include})
target_link_directories(cvAutoTrack.Depends PRIVATE ${CMAKE_BINARY_DIR})
target_link_libraries(cvAutoTrack.Depends PRIVATE ${dep_opencv_libs} 
    $<TARGET_OBJECTS:opencv_world_AVX>
    $<TARGET_OBJECTS:opencv_world_AVX2>
    $<TARGET_OBJECTS:opencv_world_AVX512_SKX>
    $<TARGET_OBJECTS:opencv_world_SSE4_1>
    $<TARGET_OBJECTS:opencv_world_SSE4_2>
    $<TARGET_OBJECTS:jsimd>
    $<TARGET_FILE:ippiw>
    $<TARGET_FILE:IlmImf>
    $<TARGET_FILE:libjpeg-turbo>
    $<TARGET_FILE:libpng>
    $<TARGET_FILE:libtiff>
    $<TARGET_FILE:libwebp>
    $<TARGET_FILE:libopenjp2>
    PUBLIC
    $<TARGET_FILE:zlib>
    )

set_target_properties(cvAutoTrack.Depends PROPERTIES DEBUG_POSTFIX "d")

install(TARGETS cvAutoTrack.Depends DESTINATION ${CMAKE_INSTALL_PREFIX}
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
    INCLUDES DESTINATION include)
install(DIRECTORY ${deps_include} DESTINATION ${CMAKE_INSTALL_PREFIX}/include)

add_executable(test main.cpp)
target_include_directories(test PRIVATE ${deps_include})
target_link_libraries(test PRIVATE cvAutoTrack.Depends)
