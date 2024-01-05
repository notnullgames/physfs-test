cmake_minimum_required(VERSION 3.18)
project(physfs-test
  DESCRIPTION "null0 game engine fs tester"
  HOMEPAGE_URL "https://github.com/notnullgames/physfs-test"
  VERSION 0.0.1
  LANGUAGES C
)

include(FetchContent)
set(FETCHCONTENT_QUIET FALSE)

FetchContent_Declare(
  physfs
  GIT_REPOSITORY https://github.com/icculus/physfs.git
  GIT_TAG main
  GIT_PROGRESS TRUE
  GIT_SHALLOW 1
)

FetchContent_MakeAvailable(physfs)
include_directories(${physfs_SOURCE_DIR}/src)

add_executable(${PROJECT_NAME} main.c)
target_link_libraries(${PROJECT_NAME} physfs)