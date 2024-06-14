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

include( CTest )


include( Functions )

DisallowIntreeBuilds( )

MakeOutputDirectories( )


set( PUB_INCLUDE_DIR "${TOP_LEVEL_SOURCE_DIR}/include" )

set( SQWRP_HEADER_FILES 
    ${PUB_INCLUDE_DIR}/sqlcxxwrap/SqlQueryPrereq.hxx
    ${PUB_INCLUDE_DIR}/sqlcxxwrap/SqlQueryBuilder.hxx 
)


add_library( sqlcxxwrap INTERFACE  ${SQWRP_HEADER_FILES} )
target_include_directories( sqlcxxwrap INTERFACE ${PUB_INCLUDE_DIR} )


add_subdirectory( examples )
