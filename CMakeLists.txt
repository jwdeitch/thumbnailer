cmake_minimum_required(VERSION 3.7)
project(thumbnailer VERSION 0.0.1)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

add_subdirectory(ffmpegthumbnailer)
add_subdirectory(librestd)
set(CMAKE_CXX_STANDARD 14)

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/librestd/include")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/ffmpegthumbnailer/libffmpegthumbnailer")

set(CURL_LIBRARY "-lcurl")
find_package(CURL REQUIRED)

include_directories(${CURL_INCLUDE_DIR})

file(GLOB_RECURSE SOURCE_LIST "src/*.cpp" "src/*.h")
add_executable(thumbnailer ${SOURCE_LIST} src/string_utils.cpp)
target_link_libraries(thumbnailer libffmpegthumbnailer restd Threads::Threads ${CURL_LIBRARIES})
set_target_properties(thumbnailer PROPERTIES LINKER_LANGUAGE CXX)