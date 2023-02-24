cmake_minimum_required(VERSION 3.1)
PROJECT(clip2png CXX)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} -pedantic")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} -O2")

find_path(SPNG_C_INCLUDES
  NAMES spng.h
  DOC "SPNG C header"
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
  pic2dataurl.cpp
  base64.cpp
  convert.cpp
)

add_executable(pic2stdout
  pic2stdout.cpp
  convert.cpp
)

target_include_directories(pic2dataurl
	PRIVATE ${PROJECT_INCLUDE_DIRS}
)

target_include_directories(pic2stdout
	PRIVATE ${PROJECT_INCLUDE_DIRS}
)

set(CLIP_EXAMPLES OFF CACHE BOOL "Compile clip examples")
set(CLIP_TESTS OFF CACHE BOOL "Compile clip tests")

add_custom_command(TARGET pic2dataurl 
  POST_BUILD
  COMMAND strip pic2dataurl)

add_custom_command(TARGET pic2stdout 
  POST_BUILD
  COMMAND strip pic2stdout)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/clip)
target_link_libraries(pic2dataurl clip spng)
target_link_libraries(pic2stdout clip spng)

install(TARGETS pic2dataurl pic2stdout
  CONFIGURATIONS Release
  RUNTIME DESTINATION "$ENV{HOME}/bin")
