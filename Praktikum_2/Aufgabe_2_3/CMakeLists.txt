# Collect all source files
CollectSourceFiles(
    ${CMAKE_CURRENT_SOURCE_DIR}
    PRIVATE_SOURCES
)

add_executable(Aufgabe_2_3 
    ${PRIVATE_SOURCES}
)