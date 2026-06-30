cmake_minimum_required(VERSION 3.22.1)
project(volleyball_logic)

# Пути к OpenXR
set(OPENXR_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(OPENXR_LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libs/${ANDROID_ABI})

add_library(volleyball_logic SHARED main.cpp)

target_include_directories(volleyball_logic PRIVATE ${OPENXR_INCLUDE_DIR})

# Подключаем библиотеку OpenXR лоадера
add_library(openxr_loader SHARED IMPORTED)
set_target_properties(openxr_loader PROPERTIES IMPORTED_LOCATION ${OPENXR_LIB_DIR}/libopenxr_loader.so)

find_library(log-lib log)
find_library(android-lib android)

target_link_libraries(volleyball_logic
    openxr_loader
    ${log-lib}
    ${android-lib}
    GLESv3
    EGL
)
