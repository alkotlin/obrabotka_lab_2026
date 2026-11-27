cmake_minimum_required(VERSION 3.15)
project(MyProject LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON) # Для работы IntelliSense в VS Code

# ==============================================================================
# 1. ПОДКЛЮЧАЕМ EIGEN (из external/eigen)
# ==============================================================================
# Отключаем тесты, чтобы не было спама в консоли
set(EIGEN_BUILD_TESTING OFF CACHE BOOL "Disable Eigen tests" FORCE)
set(EIGEN_BUILD_DOC OFF CACHE BOOL "Disable Eigen docs" FORCE)

add_subdirectory(external/eigen)

# ==============================================================================
# 2. ПОДКЛЮЧАЕМ OPENXLSX (из external/OpenXLSX)
# ==============================================================================
set(OPENXLSX_CREATE_DOCS   OFF CACHE BOOL "" FORCE)
set(OPENXLSX_BUILD_SAMPLES OFF CACHE BOOL "" FORCE)
set(OPENXLSX_BUILD_TESTS   OFF CACHE BOOL "" FORCE)
set(OPENXLSX_BUILD_BENCHMARKS OFF CACHE BOOL "" FORCE)
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)

add_subdirectory(external/OpenXLSX)
# Принудительно подключаем <cstdint> для OpenXLSX, чтобы починить ошибку с uint32_t
target_compile_options(OpenXLSX PRIVATE -include cstdint)
# ==============================================================================
# 3. ПОДКЛЮЧАЕМ LEAST-SQUARES-CPP (из external/least-squares-cpp)
# ==============================================================================
add_subdirectory(external/least-squares-cpp)

# ==============================================================================
# 4. ТВОЙ ИСПОЛНЯЕМЫЙ ФАЙЛ
# ==============================================================================
# Оставляем только ОДИН add_executable (MyProject)
add_executable(MyProject main.cpp Excel.cpp)

# Явно указываем заголовочные файлы (на всякий случай)
target_include_directories(MyProject PRIVATE external/OpenXLSX/include)

# Линкуем все три библиотеки
target_link_libraries(MyProject PRIVATE 
    OpenXLSX::OpenXLSX 
    lsqcpp::lsqcpp 
    Eigen3::Eigen
)