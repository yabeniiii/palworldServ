cmake_minimum_required(VERSION 3.15)

#
# Project details
#

project(
  "palWorldServ"
  VERSION 0.1.0
  LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED On)

include(cmake/Config.cmake)
include(cmake/ClangTidy.cmake)
include(cmake/Sources.cmake)
include(cmake/Doxygen.cmake)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Debug")
endif()

include(CheckIPOSupported)
check_ipo_supported(RESULT result OUTPUT output)
if(result)
  set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)
endif()

find_package(BOOST REQUIRED)

add_executable(${PROJECT_NAME} ${sources})
target_link_libraries(${PROJECT_NAME} boost::boost)
target_include_directories(${PROJECT_NAME} PRIVATE ${includes})
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_23)

set_target_properties(
  ${PROJECT_NAME}
  PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/${CMAKE_BUILD_TYPE}"
)
