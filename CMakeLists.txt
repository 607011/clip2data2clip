cmake_minimum_required(VERSION 3.25)
PROJECT(pic2dataurl CXX)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} -O2")

find_path(SPNG_C_INCLUDES
  NAMES spng.h
  DOC "PNG C header"
)
message(STATUS "SPNG include dir: ${SPNG_C_INCLUDES}")
find_library(SPNG_C_LIBRARIES
  NAMES spng
  DOC "SPNG C libraries"
)
cmake_path(GET SPNG_C_LIBRARIES PARENT_PATH SPNG_LIB_DIR)
message(STATUS "SPNG lib dir: ${SNG_LIB_DIR}")

include_directories(${SPNG_C_INCLUDES})
link_directories(${SPNG_LIB_DIR})

add_executable(pic2dataurl 
    main.cpp
    base64.cpp
) 

target_include_directories(pic2dataurl
	PRIVATE ${PROJECT_INCLUDE_DIRS}
	PUBLIC ${Boost_INCLUDE_DIRS}
)

set(CLIP_EXAMPLES OFF CACHE BOOL "Compile clip examples")
set(CLIP_TESTS OFF CACHE BOOL "Compile clip tests")

add_custom_command(TARGET pic2dataurl 
  POST_BUILD
  COMMAND strip pic2dataurl)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/clip)
target_link_libraries(pic2dataurl clip spng)
