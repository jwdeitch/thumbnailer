cmake_minimum_required(VERSION 3.9)
project(thumbnailer)


add_subdirectory(ffmpegthumbnailer)
add_subdirectory(librestd)
set(CMAKE_CXX_STANDARD 17)

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/librestd/include")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/ffmpegthumbnailer/libffmpegthumbnailer")

add_executable(thumbnailer main.cpp videos.cpp videos.h)