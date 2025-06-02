# I don't know the real minimum version. I only have 3.22 installed and it works with that
cmake_minimum_required(VERSION 3.22)

set(
    CMAKE_C_STANDARD 90
)

set(
    CMAKE_C_STANDARD_REQUIRED TRUE
)

project(
    libfec
    DESCRIPTION "A FEC library."
    VERSION 0.0.1
    LANGUAGES C
)

add_library(libfec_libfec STATIC)
add_library(libfec::libfec ALIAS libfec_libfec)

target_sources(libfec_libfec PRIVATE encode_rs_8.c decode_rs_8.c encode_rs_ccsds.c decode_rs_ccsds.c)
set_target_properties(libfec_libfec PROPERTIES OUTPUT_NAME libfec EXPORT_NAME libfec)


# Install with CMake:
# cmake [--toolchain <toolchain file>] [-DLFS_THREADSAFE] [other options] -S . -B build
# cmake --build build
# sudo cmake --install build [--prefix <prefix of install directory>]

# Use in other project with CMake:
# find_package(littlefs [<version>] REQUIRED)
# target_link_libraries(<target> (PUBLIC|INTERFACE|PRIVATE) littlefs::littlefs)

# Install rules

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

set(package libfec)
set(libfec_INSTALL_CMAKEDIR ${CMAKE_INSTALL_LIBDIR}/cmake/${package})

install(FILES
    ${CMAKE_SOURCE_DIR}/ccsds.h
    ${CMAKE_SOURCE_DIR}/fec.h
    ${CMAKE_SOURCE_DIR}/fixed.h
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${package})
# install(FILES lfs.h lfs_util.h DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${package})
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