cmake_minimum_required(VERSION 3.22.1)
project(volleyball_logic)

set(OPENXR_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(GLM_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include/glm)
set(OPENXR_LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libs/${ANDROID_ABI})

add_library(volleyball_logic SHARED main.cpp)

target_include_directories(volleyball_logic PRIVATE ${OPENXR_INCLUDE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_library(openxr_loader SHARED IMPORTED)
set_target_properties(openxr_loader PROPERTIES IMPORTED_LOCATION ${OPENXR_LIB_DIR}/libopenxr_loader.so)

find_library(log-lib log)
target_link_libraries(volleyball_logic openxr_loader ${log-lib} android GLESv3 EGL)
