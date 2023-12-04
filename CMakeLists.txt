cmake_minimum_required(VERSION 3.15)

#
# Project details
#

project(
  "Project"
  VERSION 0.1.0
  LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED On)
message("standard set 23")

include(cmake/Config.cmake)
include(cmake/ClangTidy.cmake)
include(cmake/Sources.cmake)
include(cmake/Doxygen.cmake)

message("files included")

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Debug")
endif()
message("build type set") 

include(CheckIPOSupported)
check_ipo_supported(RESULT result OUTPUT output)
if(result)
  set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)
endif()
message("ipo set up")

add_executable(${PROJECT_NAME} ${sources})
target_include_directories(${PROJECT_NAME} PRIVATE ${includes})
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_23)
message("exe set up")

set_target_properties(
  ${PROJECT_NAME}
  PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/${CMAKE_BUILD_TYPE}"
)
message("properties set up")
