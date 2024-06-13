cmake_minimum_required(VERSION 3.22)

project( sqlcxxwrap VERSION 0.1.0 LANGUAGES C CXX )

enable_language( C )
enable_language( CXX )
# Force C++17 support requirement
set( CMAKE_CXX_STANDARD 17 )
set( CMAKE_CXX_STANDARD_REQUIRED ON )


set( TOP_LEVEL_SOURCE_DIR "${CMAKE_CURRENT_LIST_DIR}" )

list( APPEND CMAKE_MODULE_PATH "${TOP_LEVEL_SOURCE_DIR}/cmake" )
list( APPEND CMAKE_MODULE_PATH "${TOP_LEVEL_SOURCE_DIR}/cmake/modules" )

include(CTest)


include( Functions )

DisallowIntreeBuilds( )

MakeOutputDirectories( )


add_compile_definitions(  $<$<CXX_COMPILER_ID:MSVC>:_CRT_SECURE_NO_DEPRECATE> )
add_compile_definitions(  $<$<CXX_COMPILER_ID:MSVC>:_CRT_SECURE_NO_WARNINGS> )
add_compile_definitions(  $<$<CONFIG:DEBUG>:_DEBUG> )


add_subdirectory( src )
