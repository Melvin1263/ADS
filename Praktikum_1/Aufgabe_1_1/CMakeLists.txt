# Collect all source files
CollectSourceFiles(
    ${CMAKE_CURRENT_SOURCE_DIR}
    PRIVATE_SOURCES
)

add_executable(Aufgabe_1_1 
    ${PRIVATE_SOURCES}
)