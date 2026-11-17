cmake_minimum_required(VERSION 3.15)
project(MyProject LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# --- Настройки OpenXLSX ДО add_subdirectory ---
set(OPENXLSX_CREATE_DOCS   OFF CACHE BOOL "" FORCE)
set(OPENXLSX_BUILD_SAMPLES OFF CACHE BOOL "" FORCE)
set(OPENXLSX_BUILD_TESTS   OFF CACHE BOOL "" FORCE)
set(OPENXLSX_BUILD_BENCHMARKS OFF CACHE BOOL "" FORCE)
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)

# --- Подключаем библиотеку как подпроект ---
add_subdirectory(external/OpenXLSX)

# --- Ваша программа ---
# 1. СНАЧАЛА создаем исполняемый файл (цель)
add_executable(MyProject main.cpp Excel.cpp)

# 2. ТЕПЕРЬ настраиваем её свойства
# Явно указываем компилятору, где искать заголовочные файлы OpenXLSX
target_include_directories(MyProject PRIVATE external/OpenXLSX/include)

# 3. Линкуем библиотеку
target_link_libraries(MyProject PRIVATE OpenXLSX::OpenXLSX)