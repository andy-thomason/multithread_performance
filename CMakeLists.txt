cmake_minimum_required (VERSION 2.6)

project(multithread_performance)


IF(WIN32)
ELSE(WIN32)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
ENDIF(WIN32)

find_package (Threads)

# include_directories(${PROJECT_SOURCE_DIR}/include/ ${PROJECT_SOURCE_DIR}/external/minizip/include/ ${PROJECT_SOURCE_DIR}/external/glm/)

add_executable(mutex mutex.cpp)
target_link_libraries (mutex ${CMAKE_THREAD_LIBS_INIT})
