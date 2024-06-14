

add_executable( minimal minimal.cxx )

target_link_libraries( minimal PRIVATE sqlitelib sqlcxxwrap )