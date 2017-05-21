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
    plots.gnu
    make_matrixplots.mlab
    make_plots.mlab
)

set_source_files_properties(make_matrixplots.m PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties(make_plots.m PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties(plots.gnu PROPERTIES HEADER_FILE_ONLY TRUE)

set_target_properties (Aufgabe_3_1 PROPERTIES
    FOLDER ${NAMED_FOLDER}
)


add_custom_command(
        TARGET Aufgabe_3_1 PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_SOURCE_DIR}/Praktikum_3/Aufgabe_3_1/plots.gnu
        ${CMAKE_BINARY_DIR}/bin/plots.gnu)
        
add_custom_command(
        TARGET Aufgabe_3_1 PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_SOURCE_DIR}/Praktikum_3/Aufgabe_3_1/matrixplots.gnu
        ${CMAKE_BINARY_DIR}/bin/matrixplots.gnu)


add_custom_command(
        TARGET Aufgabe_3_1 PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_SOURCE_DIR}/Praktikum_3/Aufgabe_3_1/make_matrixplots.mlab
        ${CMAKE_BINARY_DIR}/bin/make_matrixplots.m)

add_custom_command(
        TARGET Aufgabe_3_1 PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_SOURCE_DIR}/Praktikum_3/Aufgabe_3_1/make_plots.mlab
        ${CMAKE_BINARY_DIR}/bin/make_plots.m)
