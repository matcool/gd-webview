add_library(webview webview.cc)

target_include_directories(webview PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    webview2/build/native/include
)