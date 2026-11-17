# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file LICENSE.rst or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 4.4.4)

# Reject any attempt to use a toolchain file. We must not use one because
# we could be downloading it here. If the CMAKE_TOOLCHAIN_FILE environment
# variable is set, the cache variable will have been initialized from it.
unset(CMAKE_TOOLCHAIN_FILE CACHE)
unset(ENV{CMAKE_TOOLCHAIN_FILE})

# We name the project and the target for the ExternalProject_Add() call
# to something that will highlight to the user what we are working on if
# something goes wrong and an error message is produced.

project(nowide_fetch-populate NONE)



include(ExternalProject)
ExternalProject_Add(nowide_fetch-populate
                     "UPDATE_DISCONNECTED" "False" "DOWNLOAD_EXTRACT_TIMESTAMP" "OFF" "EXTERNALPROJECT_INTERNAL_ARGUMENT_SEPARATOR" "URL" "https://github.com/boostorg/nowide/releases/download/v11.3.1/nowide_standalone_v11.3.1.tar.gz" "URL_HASH" "SHA256=eaec4d331e3961f5eeb10c46a11691d62047900a7a40765b0f23cdd3181e6ca6"
                    SOURCE_DIR          "C:/Users/AlKotlin/Desktop/laba/build/_deps/nowide_fetch-src"
                    BINARY_DIR          "C:/Users/AlKotlin/Desktop/laba/build/_deps/nowide_fetch-build"
                    CONFIGURE_COMMAND   ""
                    BUILD_COMMAND       ""
                    INSTALL_COMMAND     ""
                    TEST_COMMAND        ""
                    USES_TERMINAL_DOWNLOAD  YES
                    USES_TERMINAL_UPDATE    YES
                    USES_TERMINAL_PATCH     YES
)


