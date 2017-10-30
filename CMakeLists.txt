cmake_minimum_required(VERSION 3.9)
project(thumbnailer VERSION 0.0.1)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

add_subdirectory(ffmpegthumbnailer)
add_subdirectory(librestd)
set(CMAKE_CXX_STANDARD 17)

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/librestd/include")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/ffmpegthumbnailer/libffmpegthumbnailer")

file(GLOB_RECURSE SOURCE_LIST "src/*.cpp" "src/*.h")
add_executable(thumbnailer ${SOURCE_LIST})
target_link_libraries(thumbnailer restd Threads::Threads)