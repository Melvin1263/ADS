# Collect all source files
CollectSourceFiles(
    ${CMAKE_CURRENT_SOURCE_DIR}
    PRIVATE_SOURCES
)

add_executable(Aufgabe_2_4
    ${PRIVATE_SOURCES}
)

set_target_properties (Aufgabe_2_4 PROPERTIES
    FOLDER ${NAMED_FOLDER}
)
