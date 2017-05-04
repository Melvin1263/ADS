# Collect all source files
CollectSourceFiles(
    ${CMAKE_CURRENT_SOURCE_DIR}
    PRIVATE_SOURCES
)

add_executable(Aufgabe_2_3 
    ${PRIVATE_SOURCES}
	ExportZielanalyse.csv
)

add_custom_command(
        TARGET Aufgabe_2_3 PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
                ${CMAKE_SOURCE_DIR}/Praktikum_2/Aufgabe_2_3/ExportZielanalyse.csv
                ${CMAKE_CURRENT_BINARY_DIR}/ExportZielanalyse.csv)
				
set_target_properties (Aufgabe_2_3 PROPERTIES
    FOLDER ${NAMED_FOLDER}
)
