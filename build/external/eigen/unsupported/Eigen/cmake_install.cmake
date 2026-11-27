# Install script for directory: /home/ivankurnikov/Vault/Personal/ProgAndCode/cpp-cource2026/phys_laba/obrabotka_lab_2026/external/eigen/unsupported/Eigen

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set path to fallback-tool for dependency-resolution.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/usr/bin/llvm-objdump-21")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Devel" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/eigen3/unsupported/Eigen" TYPE FILE FILES
    "/home/ivankurnikov/Vault/Personal/ProgAndCode/cpp-cource2026/phys_laba/obrabotka_lab_2026/external/eigen/unsupported/Eigen/AdolcForward"
    "/home/ivankurnikov/Vault/Personal/ProgAndCode/cpp-cource2026/phys_laba/obrabotka_lab_2026/external/eigen/unsupported/Eigen/AlignedVector3"
    "/home/ivankurnikov/Vault/Personal/ProgAndCode/cpp-cource2026/phys_laba/obrabotka_lab_2026/external/eigen/unsupported/Eigen/ArpackSupport"
    "/home/ivankurnikov/Vault/Personal/ProgAndCode/cpp-cource2026/phys_laba/obrabotka_lab_2026/external/eigen/unsupported/Eigen/AutoDiff"
    "/home/ivankurnikov/Vault/Personal/ProgAndCode/cpp-cource2026/phys_laba/obrabotka_lab_2026/external/eigen/unsupported/Eigen/BVH"
    "/home/ivankurnikov/Vault/Personal/ProgAndCode/cpp-cource2026/phys_laba/obrabotka_lab_2026/external/eigen/unsupported/Eigen/EulerAngles"
    "/home/ivankurnikov/Vault/Personal/ProgAndCode/cpp-cource2026/phys_laba/obrabotka_lab_2026/external/eigen/unsupported/Eigen/FFT"
    "/home/ivankurnikov/Vault/Personal/ProgAndCode/cpp-cource2026/phys_laba/obrabotka_lab_2026/external/eigen/unsupported/Eigen/IterativeSolvers"
    "/home/ivankurnikov/Vault/Personal/ProgAndCode/cpp-cource2026/phys_laba/obrabotka_lab_2026/external/eigen/unsupported/Eigen/KroneckerProduct"
    "/home/ivankurnikov/Vault/Personal/ProgAndCode/cpp-cource2026/phys_laba/obrabotka_lab_2026/external/eigen/unsupported/Eigen/LevenbergMarquardt"
    "/home/ivankurnikov/Vault/Personal/ProgAndCode/cpp-cource2026/phys_laba/obrabotka_lab_2026/external/eigen/unsupported/Eigen/MatrixFunctions"
    "/home/ivankurnikov/Vault/Personal/ProgAndCode/cpp-cource2026/phys_laba/obrabotka_lab_2026/external/eigen/unsupported/Eigen/MoreVectorization"
    "/home/ivankurnikov/Vault/Personal/ProgAndCode/cpp-cource2026/phys_laba/obrabotka_lab_2026/external/eigen/unsupported/Eigen/MPRealSupport"
    "/home/ivankurnikov/Vault/Personal/ProgAndCode/cpp-cource2026/phys_laba/obrabotka_lab_2026/external/eigen/unsupported/Eigen/NonLinearOptimization"
    "/home/ivankurnikov/Vault/Personal/ProgAndCode/cpp-cource2026/phys_laba/obrabotka_lab_2026/external/eigen/unsupported/Eigen/NumericalDiff"
    "/home/ivankurnikov/Vault/Personal/ProgAndCode/cpp-cource2026/phys_laba/obrabotka_lab_2026/external/eigen/unsupported/Eigen/OpenGLSupport"
    "/home/ivankurnikov/Vault/Personal/ProgAndCode/cpp-cource2026/phys_laba/obrabotka_lab_2026/external/eigen/unsupported/Eigen/Polynomials"
    "/home/ivankurnikov/Vault/Personal/ProgAndCode/cpp-cource2026/phys_laba/obrabotka_lab_2026/external/eigen/unsupported/Eigen/Skyline"
    "/home/ivankurnikov/Vault/Personal/ProgAndCode/cpp-cource2026/phys_laba/obrabotka_lab_2026/external/eigen/unsupported/Eigen/SparseExtra"
    "/home/ivankurnikov/Vault/Personal/ProgAndCode/cpp-cource2026/phys_laba/obrabotka_lab_2026/external/eigen/unsupported/Eigen/SpecialFunctions"
    "/home/ivankurnikov/Vault/Personal/ProgAndCode/cpp-cource2026/phys_laba/obrabotka_lab_2026/external/eigen/unsupported/Eigen/Splines"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Devel" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/eigen3/unsupported/Eigen" TYPE DIRECTORY FILES "/home/ivankurnikov/Vault/Personal/ProgAndCode/cpp-cource2026/phys_laba/obrabotka_lab_2026/external/eigen/unsupported/Eigen/src" FILES_MATCHING REGEX "/[^/]*\\.h$")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/home/ivankurnikov/Vault/Personal/ProgAndCode/cpp-cource2026/phys_laba/obrabotka_lab_2026/build/external/eigen/unsupported/Eigen/CXX11/cmake_install.cmake")

endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
if(CMAKE_INSTALL_LOCAL_ONLY)
  file(WRITE "/home/ivankurnikov/Vault/Personal/ProgAndCode/cpp-cource2026/phys_laba/obrabotka_lab_2026/build/external/eigen/unsupported/Eigen/install_local_manifest.txt"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
endif()
