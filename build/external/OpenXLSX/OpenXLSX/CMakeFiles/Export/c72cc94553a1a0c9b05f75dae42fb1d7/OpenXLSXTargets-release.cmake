#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "OpenXLSX::static" for configuration "Release"
set_property(TARGET OpenXLSX::static APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(OpenXLSX::static PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/OpenXLSX/libpugixml.a"
  )

list(APPEND _cmake_import_check_targets OpenXLSX::static )
list(APPEND _cmake_import_check_files_for_OpenXLSX::static "${_IMPORT_PREFIX}/lib/OpenXLSX/libpugixml.a" )

# Import target "OpenXLSX::miniz" for configuration "Release"
set_property(TARGET OpenXLSX::miniz APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(OpenXLSX::miniz PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "C"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/OpenXLSX/libminiz.a"
  )

list(APPEND _cmake_import_check_targets OpenXLSX::miniz )
list(APPEND _cmake_import_check_files_for_OpenXLSX::miniz "${_IMPORT_PREFIX}/lib/OpenXLSX/libminiz.a" )

# Import target "OpenXLSX::nowide" for configuration "Release"
set_property(TARGET OpenXLSX::nowide APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(OpenXLSX::nowide PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/OpenXLSX/libnowide.a"
  )

list(APPEND _cmake_import_check_targets OpenXLSX::nowide )
list(APPEND _cmake_import_check_files_for_OpenXLSX::nowide "${_IMPORT_PREFIX}/lib/OpenXLSX/libnowide.a" )

# Import target "OpenXLSX::OpenXLSX" for configuration "Release"
set_property(TARGET OpenXLSX::OpenXLSX APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(OpenXLSX::OpenXLSX PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libOpenXLSX.a"
  )

list(APPEND _cmake_import_check_targets OpenXLSX::OpenXLSX )
list(APPEND _cmake_import_check_files_for_OpenXLSX::OpenXLSX "${_IMPORT_PREFIX}/lib/libOpenXLSX.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
