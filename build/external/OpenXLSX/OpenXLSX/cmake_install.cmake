# Install script for directory: /home/ivankurnikov/Vault/Personal/ProgAndCode/cpp-cource2026/phys_laba/obrabotka_lab_2026/external/OpenXLSX/OpenXLSX

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

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/OpenXLSX/headers" TYPE FILE FILES "/home/ivankurnikov/Vault/Personal/ProgAndCode/cpp-cource2026/phys_laba/obrabotka_lab_2026/build/external/OpenXLSX/OpenXLSX/OpenXLSX-Exports.hpp")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/OpenXLSX/headers" TYPE FILE FILES
    "/home/ivankurnikov/Vault/Personal/ProgAndCode/cpp-cource2026/phys_laba/obrabotka_lab_2026/external/OpenXLSX/OpenXLSX/headers/XLCell.hpp"
    "/home/ivankurnikov/Vault/Personal/ProgAndCode/cpp-cource2026/phys_laba/obrabotka_lab_2026/external/OpenXLSX/OpenXLSX/headers/XLCellIterator.hpp"
    "/home/ivankurnikov/Vault/Personal/ProgAndCode/cpp-cource2026/phys_laba/obrabotka_lab_2026/external/OpenXLSX/OpenXLSX/headers/XLCellRange.hpp"
    "/home/ivankurnikov/Vault/Personal/ProgAndCode/cpp-cource2026/phys_laba/obrabotka_lab_2026/external/OpenXLSX/OpenXLSX/headers/XLCellReference.hpp"
    "/home/ivankurnikov/Vault/Personal/ProgAndCode/cpp-cource2026/phys_laba/obrabotka_lab_2026/external/OpenXLSX/OpenXLSX/headers/XLCellValue.hpp"
    "/home/ivankurnikov/Vault/Personal/ProgAndCode/cpp-cource2026/phys_laba/obrabotka_lab_2026/external/OpenXLSX/OpenXLSX/headers/XLColor.hpp"
    "/home/ivankurnikov/Vault/Personal/ProgAndCode/cpp-cource2026/phys_laba/obrabotka_lab_2026/external/OpenXLSX/OpenXLSX/headers/XLColumn.hpp"
    "/home/ivankurnikov/Vault/Personal/ProgAndCode/cpp-cource2026/phys_laba/obrabotka_lab_2026/external/OpenXLSX/OpenXLSX/headers/XLCommandQuery.hpp"
    "/home/ivankurnikov/Vault/Personal/ProgAndCode/cpp-cource2026/phys_laba/obrabotka_lab_2026/external/OpenXLSX/OpenXLSX/headers/XLConstants.hpp"
    "/home/ivankurnikov/Vault/Personal/ProgAndCode/cpp-cource2026/phys_laba/obrabotka_lab_2026/external/OpenXLSX/OpenXLSX/headers/XLContentTypes.hpp"
    "/home/ivankurnikov/Vault/Personal/ProgAndCode/cpp-cource2026/phys_laba/obrabotka_lab_2026/external/OpenXLSX/OpenXLSX/headers/XLDateTime.hpp"
    "/home/ivankurnikov/Vault/Personal/ProgAndCode/cpp-cource2026/phys_laba/obrabotka_lab_2026/external/OpenXLSX/OpenXLSX/headers/XLDocument.hpp"
    "/home/ivankurnikov/Vault/Personal/ProgAndCode/cpp-cource2026/phys_laba/obrabotka_lab_2026/external/OpenXLSX/OpenXLSX/headers/XLException.hpp"
    "/home/ivankurnikov/Vault/Personal/ProgAndCode/cpp-cource2026/phys_laba/obrabotka_lab_2026/external/OpenXLSX/OpenXLSX/headers/XLFormula.hpp"
    "/home/ivankurnikov/Vault/Personal/ProgAndCode/cpp-cource2026/phys_laba/obrabotka_lab_2026/external/OpenXLSX/OpenXLSX/headers/XLIterator.hpp"
    "/home/ivankurnikov/Vault/Personal/ProgAndCode/cpp-cource2026/phys_laba/obrabotka_lab_2026/external/OpenXLSX/OpenXLSX/headers/XLProperties.hpp"
    "/home/ivankurnikov/Vault/Personal/ProgAndCode/cpp-cource2026/phys_laba/obrabotka_lab_2026/external/OpenXLSX/OpenXLSX/headers/XLRelationships.hpp"
    "/home/ivankurnikov/Vault/Personal/ProgAndCode/cpp-cource2026/phys_laba/obrabotka_lab_2026/external/OpenXLSX/OpenXLSX/headers/XLRow.hpp"
    "/home/ivankurnikov/Vault/Personal/ProgAndCode/cpp-cource2026/phys_laba/obrabotka_lab_2026/external/OpenXLSX/OpenXLSX/headers/XLRowData.hpp"
    "/home/ivankurnikov/Vault/Personal/ProgAndCode/cpp-cource2026/phys_laba/obrabotka_lab_2026/external/OpenXLSX/OpenXLSX/headers/XLSharedStrings.hpp"
    "/home/ivankurnikov/Vault/Personal/ProgAndCode/cpp-cource2026/phys_laba/obrabotka_lab_2026/external/OpenXLSX/OpenXLSX/headers/XLSheet.hpp"
    "/home/ivankurnikov/Vault/Personal/ProgAndCode/cpp-cource2026/phys_laba/obrabotka_lab_2026/external/OpenXLSX/OpenXLSX/headers/XLWorkbook.hpp"
    "/home/ivankurnikov/Vault/Personal/ProgAndCode/cpp-cource2026/phys_laba/obrabotka_lab_2026/external/OpenXLSX/OpenXLSX/headers/XLXmlData.hpp"
    "/home/ivankurnikov/Vault/Personal/ProgAndCode/cpp-cource2026/phys_laba/obrabotka_lab_2026/external/OpenXLSX/OpenXLSX/headers/XLXmlFile.hpp"
    "/home/ivankurnikov/Vault/Personal/ProgAndCode/cpp-cource2026/phys_laba/obrabotka_lab_2026/external/OpenXLSX/OpenXLSX/headers/XLXmlParser.hpp"
    "/home/ivankurnikov/Vault/Personal/ProgAndCode/cpp-cource2026/phys_laba/obrabotka_lab_2026/external/OpenXLSX/OpenXLSX/headers/XLZipArchive.hpp"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/OpenXLSX" TYPE FILE FILES "/home/ivankurnikov/Vault/Personal/ProgAndCode/cpp-cource2026/phys_laba/obrabotka_lab_2026/external/OpenXLSX/OpenXLSX/OpenXLSX.hpp")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "lib" OR NOT CMAKE_INSTALL_COMPONENT)
  foreach(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libOpenXLSXd.so.0.3.1"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libOpenXLSXd.so.0"
      )
    if(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      file(RPATH_CHECK
           FILE "${file}"
           RPATH "")
    endif()
  endforeach()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES
    "/home/ivankurnikov/Vault/Personal/ProgAndCode/cpp-cource2026/phys_laba/obrabotka_lab_2026/build/output/libOpenXLSXd.so.0.3.1"
    "/home/ivankurnikov/Vault/Personal/ProgAndCode/cpp-cource2026/phys_laba/obrabotka_lab_2026/build/output/libOpenXLSXd.so.0"
    )
  foreach(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libOpenXLSXd.so.0.3.1"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libOpenXLSXd.so.0"
      )
    if(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      if(CMAKE_INSTALL_DO_STRIP)
        execute_process(COMMAND "/usr/bin/llvm-strip-21" "${file}")
      endif()
    endif()
  endforeach()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "lib" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES "/home/ivankurnikov/Vault/Personal/ProgAndCode/cpp-cource2026/phys_laba/obrabotka_lab_2026/build/output/libOpenXLSXd.so")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/OpenXLSX" TYPE FILE FILES
    "/home/ivankurnikov/Vault/Personal/ProgAndCode/cpp-cource2026/phys_laba/obrabotka_lab_2026/external/OpenXLSX/OpenXLSX/OpenXLSXConfig.cmake"
    "/home/ivankurnikov/Vault/Personal/ProgAndCode/cpp-cource2026/phys_laba/obrabotka_lab_2026/build/external/OpenXLSX/OpenXLSX/OpenXLSX/OpenXLSXConfigVersion.cmake"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/OpenXLSX/OpenXLSXTargets.cmake")
    file(DIFFERENT _cmake_export_file_changed FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/OpenXLSX/OpenXLSXTargets.cmake"
         "/home/ivankurnikov/Vault/Personal/ProgAndCode/cpp-cource2026/phys_laba/obrabotka_lab_2026/build/external/OpenXLSX/OpenXLSX/CMakeFiles/Export/c72cc94553a1a0c9b05f75dae42fb1d7/OpenXLSXTargets.cmake")
    if(_cmake_export_file_changed)
      file(GLOB _cmake_old_config_files "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/OpenXLSX/OpenXLSXTargets-*.cmake")
      if(_cmake_old_config_files)
        string(REPLACE ";" ", " _cmake_old_config_files_text "${_cmake_old_config_files}")
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/OpenXLSX/OpenXLSXTargets.cmake\" will be replaced.  Removing files [${_cmake_old_config_files_text}].")
        unset(_cmake_old_config_files_text)
        file(REMOVE ${_cmake_old_config_files})
      endif()
      unset(_cmake_old_config_files)
    endif()
    unset(_cmake_export_file_changed)
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/OpenXLSX" TYPE FILE FILES "/home/ivankurnikov/Vault/Personal/ProgAndCode/cpp-cource2026/phys_laba/obrabotka_lab_2026/build/external/OpenXLSX/OpenXLSX/CMakeFiles/Export/c72cc94553a1a0c9b05f75dae42fb1d7/OpenXLSXTargets.cmake")
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/OpenXLSX" TYPE FILE FILES "/home/ivankurnikov/Vault/Personal/ProgAndCode/cpp-cource2026/phys_laba/obrabotka_lab_2026/build/external/OpenXLSX/OpenXLSX/CMakeFiles/Export/c72cc94553a1a0c9b05f75dae42fb1d7/OpenXLSXTargets-debug.cmake")
  endif()
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
if(CMAKE_INSTALL_LOCAL_ONLY)
  file(WRITE "/home/ivankurnikov/Vault/Personal/ProgAndCode/cpp-cource2026/phys_laba/obrabotka_lab_2026/build/external/OpenXLSX/OpenXLSX/install_local_manifest.txt"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
endif()
