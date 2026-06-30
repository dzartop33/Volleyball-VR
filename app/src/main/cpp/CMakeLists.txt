cmake_minimum_required(VERSION 3.22.1)
project(volleyball_logic)

add_library(volleyball_logic SHARED main.cpp)

find_library(log-lib log)
find_library(android-lib android)
find_library(gles-lib GLESv3)
find_library(egl-lib EGL)

# Подключаем OpenXR напрямую из префаба, который скачал Gradle
target_link_libraries(volleyball_logic
    ${log-lib}
    ${android-lib}
    ${gles-lib}
    ${egl-lib}
)
