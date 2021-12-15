set("CPACK_COMPONENT_LIBRARY_DESCRIPTION" "lib${PROJECT_NAME} is a library for replacing emoji slug codes with actual emoji.")

buildAndPackageLib(${PROJECT_NAME}
	TARGET_NAME_WITH_LIB_PREFIX
	COMPONENT "library"
	DESCRIPTION "A library for ${DESCRIPTION_SHARED}."
	PUBLIC_INCLUDES ${Include_dir}
	PRIVATE_LIBS mo::libmo
)

if(WITH_CTRE)
	target_compile_definitions(lib${PROJECT_NAME} PRIVATE "-DWITH_CTRE")
	target_link_libraries(lib${PROJECT_NAME} PRIVATE ctre::ctre)
endif()
