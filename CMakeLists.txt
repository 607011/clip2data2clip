cmake_minimum_required(VERSION 3.1)
PROJECT(clip2dataurl CXX)

set(CMAKE_CXX_STANDARD 17)

if (UNIX)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} -pedantic")
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} -O2")
endif (UNIX)

if (MSVC)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Wall /wd4710 /wd4711 /wd4625 /wd4820")
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} /Od")
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} /O2")
endif (MSVC)

#find_path(SPNG_C_INCLUDES
#  NAMES spng.h
#  DOC "SPNG C header"
#)
#message(STATUS "SPNG include dir: ${SPNG_C_INCLUDES}")
#find_library(SPNG_C_LIBRARIES
#  NAMES spng
#  DOC "SPNG C libraries"
#)
#cmake_path(GET SPNG_C_LIBRARIES PARENT_PATH SPNG_LIB_DIR)
#message(STATUS "SPNG lib dir: ${SNG_LIB_DIR}")

include_directories(${SPNG_C_INCLUDES})
link_directories(${SPNG_LIB_DIR})

add_executable(clip2dataurl 
  clip2dataurl.cpp
  base64.cpp
  convert.cpp
)

add_executable(clip2stdout
  clip2stdout.cpp
  convert.cpp
)

target_include_directories(clip2dataurl
	PRIVATE ${PROJECT_INCLUDE_DIRS}
)

target_include_directories(clip2stdout
	PRIVATE ${PROJECT_INCLUDE_DIRS}
)

set(CLIP_EXAMPLES OFF CACHE BOOL "Compile clip examples")
set(CLIP_TESTS OFF CACHE BOOL "Compile clip tests")

if (UNIX)
add_custom_command(TARGET clip2dataurl 
  POST_BUILD
  COMMAND strip clip2dataurl)

add_custom_command(TARGET clip2stdout 
  POST_BUILD
  COMMAND strip clip2stdout)
endif (UNIX)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/clip)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/libspng)
target_link_libraries(clip2dataurl clip spng)
target_link_libraries(clip2stdout clip spng)

install(TARGETS clip2dataurl clip2stdout
  CONFIGURATIONS Release
  RUNTIME DESTINATION "$ENV{HOME}/bin")
