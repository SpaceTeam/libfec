# I don't know the real minimum version. I only have 3.22 installed and it works with that
cmake_minimum_required(VERSION 3.22)
project(
    libfec
    DESCRIPTION "A FEC library."
    VERSION 0.0.1
    LANGUAGES C
)

add_library(libfec_libfec STATIC)
add_library(libfec::libfec ALIAS libfec_libfec)
set_target_properties(libfec_libfec PROPERTIES OUTPUT_NAME fec EXPORT_NAME libfec)
target_include_directories(libfec_libfec PUBLIC "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}>")
add_subdirectory(libfec)

include(CTest)
if(BUILD_TESTING)
    add_subdirectory(tests)
endif()

# Install with CMake:
# cmake [--toolchain <toolchain file>] [other options] -S . -B build
# cmake --build build
# sudo cmake --install build [--prefix <prefix of install directory>]

# Use in other project with CMake:
# find_package(libfec [<version>] REQUIRED)
# target_link_libraries(<target> (PUBLIC|INTERFACE|PRIVATE) libfec::libfec)

# Install rules

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

set(package libfec)
set(libfec_INSTALL_CMAKEDIR ${CMAKE_INSTALL_LIBDIR}/cmake/${package})

install(FILES
    ${CMAKE_SOURCE_DIR}/libfec/fec.h
    ${CMAKE_SOURCE_DIR}/libfec/fixed.h
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${package})
target_include_directories(
    libfec_libfec SYSTEM INTERFACE $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

write_basic_package_version_file(
    "${package}ConfigVersion.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)

install(
    FILES install-config.cmake
    DESTINATION ${libfec_INSTALL_CMAKEDIR}
    RENAME "${package}Config.cmake"
)
install(FILES "${PROJECT_BINARY_DIR}/${package}ConfigVersion.cmake"
        DESTINATION ${libfec_INSTALL_CMAKEDIR}
)

install(
    TARGETS libfec_libfec
    EXPORT libfecTargets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}/${package}
)
install(
    EXPORT libfecTargets
    NAMESPACE libfec::
    DESTINATION ${libfec_INSTALL_CMAKEDIR}
)