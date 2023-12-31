add_library("${PROJECT_NAME}" "")
add_library(rti::rti ALIAS "${PROJECT_NAME}")

set(RTI_EXPORT_FILE "Rti-Exports")
install(TARGETS "${PROJECT_NAME}" EXPORT "${RTI_EXPORT_FILE}")

target_include_directories("${PROJECT_NAME}" PUBLIC
	"$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
	"$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>" #foo_export.h
	"$<INSTALL_INTERFACE:include>" #${CMAKE_INSTALL_PREFIX}/include
)

if(NOT BUILD_SHARED_LIBS)
	set(STATIC_POSTFIX "-s")
	set_target_properties("${PROJECT_NAME}" PROPERTIES 
	COMPILE_FLAGS -DRTI_STATIC_DEFINE)
endif()

#Rename target Rti
set_target_properties("${PROJECT_NAME}" PROPERTIES
	DEBUG_POSTFIX "${STATIC_POSTFIX}-d" 
	RELEASE_POSTFIX "${STATIC_POSTFIX}"
	MINSIZEREL_POSTFIX "${STATIC_POSTFIX}-mr"
	RELWITHDEBINFO_POSTFIX "${STATIC_POSTFIX}-rd"
)
set_target_properties("${PROJECT_NAME}" PROPERTIES LINK_FLAGS " /MANIFESTUAC:\"level='requireAdministrator' uiAccess='false'\" ")
add_definitions(-DUNICODE -D_UNICODE)

include("GenerateExportHeader")
generate_export_header("${PROJECT_NAME}")
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/rti_export.h" DESTINATION "include")

add_subdirectory("include")
add_subdirectory("src")

set(RTI_CONFIG_DIR "lib/cmake/${PROJECT_NAME}")
configure_file("${rti_SOURCE_DIR}/cmake/RtiConfig.cmake.in" "${rti_BINARY_DIR}/${RTI_CONFIG_DIR}/RtiConfig.cmake")
install(FILES "${rti_BINARY_DIR}/${RTI_CONFIG_DIR}/RtiConfig.cmake" DESTINATION "${RTI_CONFIG_DIR}")
install(EXPORT "${RTI_EXPORT_FILE}" DESTINATION "${RTI_CONFIG_DIR}" NAMESPACE "rti::")