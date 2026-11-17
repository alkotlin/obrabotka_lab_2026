# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file LICENSE.rst or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION ${CMAKE_VERSION}) # this file comes with cmake

# If CMAKE_DISABLE_SOURCE_CHANGES is set to true and the source directory is an
# existing directory in our source tree, calling file(MAKE_DIRECTORY) on it
# would cause a fatal error, even though it would be a no-op.
if(NOT EXISTS "C:/Users/AlKotlin/Desktop/laba/build/_deps/pugixml_fetch-src")
  file(MAKE_DIRECTORY "C:/Users/AlKotlin/Desktop/laba/build/_deps/pugixml_fetch-src")
endif()
file(MAKE_DIRECTORY
  "C:/Users/AlKotlin/Desktop/laba/build/_deps/pugixml_fetch-build"
  "C:/Users/AlKotlin/Desktop/laba/build/_deps/pugixml_fetch-subbuild/pugixml_fetch-populate-prefix"
  "C:/Users/AlKotlin/Desktop/laba/build/_deps/pugixml_fetch-subbuild/pugixml_fetch-populate-prefix/tmp"
  "C:/Users/AlKotlin/Desktop/laba/build/_deps/pugixml_fetch-subbuild/pugixml_fetch-populate-prefix/src/pugixml_fetch-populate-stamp"
  "C:/Users/AlKotlin/Desktop/laba/build/_deps/pugixml_fetch-subbuild/pugixml_fetch-populate-prefix/src"
  "C:/Users/AlKotlin/Desktop/laba/build/_deps/pugixml_fetch-subbuild/pugixml_fetch-populate-prefix/src/pugixml_fetch-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "C:/Users/AlKotlin/Desktop/laba/build/_deps/pugixml_fetch-subbuild/pugixml_fetch-populate-prefix/src/pugixml_fetch-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "C:/Users/AlKotlin/Desktop/laba/build/_deps/pugixml_fetch-subbuild/pugixml_fetch-populate-prefix/src/pugixml_fetch-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
