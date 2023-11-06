cmake_minimum_required(VERSION 3.21)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_OSX_ARCHITECTURES "x86_64")
set(CMAKE_CXX_VISIBILITY_PRESET hidden)

project(webview-api VERSION 1.0.0)

add_library(${PROJECT_NAME} SHARED
    src/main.cpp
    src/render.cpp
)

if (NOT DEFINED ENV{GEODE_SDK})
    message(FATAL_ERROR "Unable to find Geode SDK! Please define GEODE_SDK environment variable to point to Geode")
else()
    message(STATUS "Found Geode: $ENV{GEODE_SDK}")
endif()

add_subdirectory($ENV{GEODE_SDK} ${CMAKE_CURRENT_BINARY_DIR}/geode)

setup_geode_mod(${PROJECT_NAME})

add_subdirectory(cef)

# ADD_LOGICAL_TARGET("libcef_lib" "${CEF_LIB_DEBUG}" "${CEF_LIB_RELEASE}")

# SET_CEF_TARGET_OUT_DIR()

# include_directories(${_CEF_ROOT})

target_link_libraries(${PROJECT_NAME} libcef_dll_wrapper ${CMAKE_CURRENT_SOURCE_DIR}/cef/Release/libcef.lib)
target_include_directories(${PROJECT_NAME} PRIVATE cef)

# target_link_libraries(${PROJECT_NAME} webview)

add_executable(stupidprocess src/subprocess.cpp)
target_link_libraries(stupidprocess libcef_dll_wrapper ${CMAKE_CURRENT_SOURCE_DIR}/cef/Release/libcef.lib)
target_include_directories(stupidprocess PRIVATE cef)