cmake_minimum_required(VERSION 3.14)

include(cmake/prelude.cmake)

# macOS: ensure libc++ headers are visible to clang++
if(APPLE AND NOT CMAKE_OSX_SYSROOT)
  execute_process(COMMAND xcrun --show-sdk-path
                  OUTPUT_VARIABLE SDK_PATH
                  OUTPUT_STRIP_TRAILING_WHITESPACE)
  if(SDK_PATH AND EXISTS "${SDK_PATH}")
    set(CMAKE_OSX_SYSROOT "${SDK_PATH}" CACHE PATH "macOS SDK" FORCE)
  endif()
endif()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(
    algorithms
    VERSION 0.1.0
    DESCRIPTION "Short description"
    HOMEPAGE_URL "https://example.com/"
    LANGUAGES CXX
)

include(cmake/project-is-top-level.cmake)
include(cmake/variables.cmake)

# ---- Declare library ----

# add_library(
#     algorithms_lib OBJECT
#     source/lib.cpp
# )

# target_include_directories(
#     # algorithms_lib ${warning_guard}
#     PUBLIC
#     "\$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/source>"
# )

# target_compile_features(algorithms_lib PUBLIC cxx_std_20)

# ---- Declare executable ----

add_executable(algorithms_exe source/main.cpp)
add_executable(algorithms::exe ALIAS algorithms_exe)

set_property(TARGET algorithms_exe PROPERTY OUTPUT_NAME algorithms)

target_compile_features(algorithms_exe PRIVATE cxx_std_20)

# target_link_libraries(algorithms_exe PRIVATE algorithms_lib)

# ---- Install rules ----

if(NOT CMAKE_SKIP_INSTALL_RULES)
  include(cmake/install-rules.cmake)
endif()

# ---- Developer mode ----

if(NOT algorithms_DEVELOPER_MODE)
  return()
elseif(NOT PROJECT_IS_TOP_LEVEL)
  message(
      AUTHOR_WARNING
      "Developer mode is intended for developers of algorithms"
  )
endif()

include(cmake/dev-mode.cmake)
