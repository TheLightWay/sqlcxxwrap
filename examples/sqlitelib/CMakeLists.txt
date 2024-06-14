
set( SQL_HEADER_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/sqlite3.h
    ${CMAKE_CURRENT_SOURCE_DIR}/sqlite3ext.h )

set( SQL_SOURCE_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/sqlite3.c
)

set( SQL_ALL_FILES
    ${SQL_HEADER_FILES}
    ${SQL_SOURCE_FILES} )

add_library( sqlitelib STATIC ${SQL_ALL_FILES} )

target_include_directories( sqlitelib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} )