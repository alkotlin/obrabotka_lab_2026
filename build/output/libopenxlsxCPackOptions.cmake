# #=======================================================================================================================
# # Transfer project variables to local constants needed for CPack
# #=======================================================================================================================
# set(GIT_COMMIT_ID "98684fc4")
# set(GIT_COMMIT_ID_TIME "2026-11-17 16:23:50 +0300")

#=======================================================================================================================
# Set CPack options for debian package generation
#=======================================================================================================================
set(CPACK_PACKAGE_NAME "libopenxlsx")
set(CPACK_PACKAGE_CONTACT "coding23@uffmann.name")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Lars Uffmann <coding23@uffmann.name>")

set(CPACK_DEBIAN_PACKAGE_DEPENDS "") # TODO: set project dependencies here
set(CPACK_BINARY_DEB "ON") # TEST

set(CPACK_PACKAGE_VERSION_MAJOR ${OPENXLSX_MAJOR_VERSION})
set(CPACK_PACKAGE_VERSION_MINOR ${OPENXLSX_MINOR_VERSION})
set(CPACK_VERSION_PATCH "${OPENXLSX_MICRO_VERSION}-${GIT_COMMIT_ID}")
set(CPACK_PACKAGE_VERSION "${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}.${CPACK_VERSION_PATCH}")
