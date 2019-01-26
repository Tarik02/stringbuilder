cmake_minimum_required(VERSION 3.5)
project(stringbuilder VERSION 1.0.0 LANGUAGES C)

##############################################
# Create target and set properties

add_library(stringbuilder
  src/stringbuilder.c
)

#Add an alias so that library can be used inside the build tree, e.g. when testing
add_library(StringBuilder::stringbuilder ALIAS stringbuilder)

#Set target properties
target_include_directories(stringbuilder
  PUBLIC
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_compile_options(stringbuilder PRIVATE $<$<CXX_COMPILER_ID:GNU>:-Wall>)

##############################################
# Installation instructions

include(GNUInstallDirs)
set(INSTALL_CONFIGDIR ${CMAKE_INSTALL_LIBDIR}/cmake/StringBuilder)

install(TARGETS stringbuilder
  EXPORT stringbuilder-targets
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

#This is required so that the exported target has the name StringBuilder and not stringbuilder
set_target_properties(stringbuilder PROPERTIES EXPORT_NAME StringBuilder)

install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

#Export the targets to a script
install(EXPORT stringbuilder-targets
  FILE
    StringBuilderTargets.cmake
  NAMESPACE
    StringBuilder::
  DESTINATION
    ${INSTALL_CONFIGDIR}
)

#Create a ConfigVersion.cmake file
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
  ${CMAKE_CURRENT_BINARY_DIR}/StringBuilderConfigVersion.cmake
  VERSION ${PROJECT_VERSION}
  COMPATIBILITY AnyNewerVersion
)

configure_package_config_file(${CMAKE_CURRENT_LIST_DIR}/cmake/StringBuilderConfig.cmake.in
  ${CMAKE_CURRENT_BINARY_DIR}/StringBuilderConfig.cmake
  INSTALL_DESTINATION ${INSTALL_CONFIGDIR}
)

#Install the config, configversion and custom find modules
install(FILES
  ${CMAKE_CURRENT_BINARY_DIR}/StringBuilderConfig.cmake
  ${CMAKE_CURRENT_BINARY_DIR}/StringBuilderConfigVersion.cmake
  DESTINATION ${INSTALL_CONFIGDIR}
)

##############################################
## Exporting from the build tree
export(EXPORT stringbuilder-targets FILE ${CMAKE_CURRENT_BINARY_DIR}/StringBuilderTargets.cmake NAMESPACE StringBuilder::)

#Register package in user's package registry
export(PACKAGE StringBuilder)
