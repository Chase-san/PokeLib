FILE(GLOB pokelib_headers RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "*.h")

FOREACH(header ${pokelib_headers})
    INSTALL(FILES ${header} DESTINATION ${INCLUDE_DIR}/pokelib COMPONENT Headers)
ENDFOREACH(header)
