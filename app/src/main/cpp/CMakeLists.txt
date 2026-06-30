cmake_minimum_required(VERSION 3.22.1)
project(volleyball_logic)

# Находим пакет OpenXR, который добавил Gradle
find_package(openxr_loader REQUIRED CONFIG)

add_library(volleyball_logic SHARED main.cpp)

find_library(log-lib log)
find_library(android-lib android)

target_link_libraries(volleyball_logic
    openxr_loader::openxr_loader
    ${log-lib}
    ${android-lib}
    GLESv3
    EGL
)
