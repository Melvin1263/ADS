# Collect all source files
CollectSourceFiles(
    ${CMAKE_CURRENT_SOURCE_DIR}
    PRIVATE_SOURCES
)

if(WIN32)
    add_definitions("/openmp")
elseif(UNIX)
    add_definitions("−fopenmp −lgomp")
endif()

add_executable(Aufgabe_3_1
    ${PRIVATE_SOURCES}
)

set_target_properties (Aufgabe_3_1 PROPERTIES
    FOLDER ${NAMED_FOLDER}
)
