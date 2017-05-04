# Collect all source files
CollectSourceFiles(
    ${CMAKE_CURRENT_SOURCE_DIR}
    PRIVATE_SOURCES
)

add_executable(Aufgabe_1_2 
    ${PRIVATE_SOURCES}
)

set_target_properties (Aufgabe_1_2 PROPERTIES
    FOLDER ${NAMED_FOLDER}
)
