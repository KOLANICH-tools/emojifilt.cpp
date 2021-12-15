cmake_minimum_required(VERSION 3.13)

set(CMAKE_USE_RELATIVE_PATHS TRUE)
project("emojifilt")
set("DESCRIPTION_SHARED" "to replace emoji slugs with actual emoji within text files.")
set("PROJECT_DESCRIPTION" "A tool ${DESCRIPTION_SHARED}")
set("PROJECT_HOMEPAGE_URL" "https://codeberg.org/KOLANICH-tools/emojifilt.cpp")
set(CPACK_PACKAGE_VENDOR "KOLANICH")

set(CPACK_PACKAGE_VERSION_MAJOR "0")
set(CPACK_PACKAGE_VERSION_MINOR "0")
set(CPACK_PACKAGE_VERSION_PATCH "1")
set(CPACK_PACKAGE_VERSION "${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}.${CPACK_PACKAGE_VERSION_PATCH}")

set(OUR_CMAKE_MODULES_DIR "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
set(OUR_CMAKE_3PARTY_MODULES_DIR "${OUR_CMAKE_MODULES_DIR}/thirdParty")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${OUR_CMAKE_MODULES_DIR}" "${OUR_CMAKE_MODULES_DIR}/Boilerplate" "${OUR_CMAKE_MODULES_DIR}/DoxygenUtils" "${OUR_CMAKE_3PARTY_MODULES_DIR}")

include(Boilerplate)

find_package(mo REQUIRED)

set(Include_dir "${CMAKE_CURRENT_SOURCE_DIR}/include")
file(GLOB_RECURSE HDRFILES "${Include_dir}/*.h" "${Include_dir}/*.hpp")

set(BinSource_dir "${CMAKE_CURRENT_SOURCE_DIR}/bin")
set(Library_dir "${CMAKE_CURRENT_SOURCE_DIR}/lib")

set(kaitai_dir "${CMAKE_CURRENT_SOURCE_DIR}/kaitai")
set(kaitai_include_dir "${kaitai_dir}")
set(kaitai_source_dir "${kaitai_dir}/kaitai")


set(CPACK_PACKAGE_MAINTAINER "${CPACK_PACKAGE_VENDOR}")
set(CPACK_DEBIAN_PACKAGE_NAME "${CPACK_PACKAGE_NAME}")
set(CPACK_RPM_PACKAGE_NAME "${CPACK_PACKAGE_NAME}")


find_package(ctre)
if(ctre_FOUND)
	option(WITH_CTRE "Use CTRE for parsing, not runtime regular expressions" ON)
endif()

add_subdirectory("${Library_dir}")
add_subdirectory("${BinSource_dir}")

set(CPACK_DEB_COMPONENT_INSTALL ON)
set(CPACK_RPM_COMPONENT_INSTALL ON)
set(CPACK_NSIS_COMPONENT_INSTALL ON)
#set(CPACK_DEBIAN_ENABLE_COMPONENT_DEPENDS ON)
#set(CPACK_RPM_ENABLE_COMPONENT_DEPENDS ON)
set(CPACK_DEBIAN_COMPRESSION_TYPE "xz")

include(CPack)
