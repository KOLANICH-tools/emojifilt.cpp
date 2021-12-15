find_package(whereami)

if(whereami_FOUND)
	option(WITH_DB_PATH_RELATIVE_TO_BINARY "Allows emoji db be found relative to location of the binary" ON)
endif()
if(UNIX)
	option(WITH_DB_PATH_ACCORDING_TO_FHS "Allows emoji db be found in hardcoded dirs" ON)
endif()

if(NOT WITH_DB_PATH_RELATIVE_TO_BINARY AND NOT WITH_DB_PATH_ACCORDING_TO_FHS)
	message(FATAL_ERROR "At least one way to discover the emoji database must be present.")
endif()

set(EMOJIFILT_RESOURCES_SUBDIR_NAME "emojifilt" CACHE STRING "The name of the subdir in config dirs")
set(EMOJIFILT_DB_FILE_NAME "emoji" CACHE STRING "The name of DB file")

configure_file("${CMAKE_CURRENT_SOURCE_DIR}/searchPathsConfig.hpp.in" "${CMAKE_CURRENT_SOURCE_DIR}/searchPathsConfig.hpp")

file(GLOB_RECURSE SRCFILES "${CMAKE_CURRENT_SOURCE_DIR}/*.c" "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

add_executable(emojifilt "${SRCFILES}")
target_include_directories(emojifilt PRIVATE "${Include_dir}")
set_target_properties(emojifilt PROPERTIES OUTPUT_NAME "emojifilt")

message(STATUS "CMAKE_INSTALL_FULL_DATAROOTDIR ${CMAKE_INSTALL_FULL_DATAROOTDIR}")
message(STATUS "CMAKE_INSTALL_FULL_SYSCONFDIR ${CMAKE_INSTALL_FULL_SYSCONFDIR}")

if(WITH_DB_PATH_RELATIVE_TO_BINARY)
	target_link_libraries(emojifilt PRIVATE whereami::whereami)
endif()

harden(emojifilt)
add_sanitizers(emojifilt)

target_link_libraries(emojifilt PRIVATE libemojifilt mo::libmo)

cpack_add_component(bin
	DISPLAY_NAME "binary"
	DESCRIPTION "The CLI tool converting :text_codes: into real emoji"
)

install(TARGETS "emojifilt"
	RUNTIME
	COMPONENT "bin"
)

set("CPACK_COMPONENT_BIN_DESCRIPTION" "A tool for ${DESCRIPTION_SHARED}.")
set("CPACK_DEBIAN_BIN_PACKAGE_NAME" "emojifilt")
set("CPACK_RPM_BIN_PACKAGE_NAME" "emojifilt")
set("CPACK_DEBIAN_BIN_PACKAGE_DEPENDS" "${CPACK_DEBIAN_LIBRARY_PACKAGE_NAME} (>= ${CPACK_PACKAGE_VERSION})")
set("CPACK_RPM_BIN_PACKAGE_DEPENDS" "${CPACK_RPM_LIBRARY_PACKAGE_NAME}")


list(APPEND CPACK_COMPONENTS_ALL "bin")  # strangely, not populated automatically correctly

pass_through_cpack_vars()
