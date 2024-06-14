#include <cstdlib>
#include <cstdio>

#include <iostream>
#include <string>
#include <list>

#include "sqlcxxwrap/SqlQueryBuilder.hxx"

using StlSqlQueryBuilder = SqlQueryBuilder<std::string,
                           std::list,
                           DefaultDebugOutput<std::string>>;

int main( int argc, char* argv[] )
{
    StlSqlQueryBuilder qb;

    qb.select( ).column( "col1" ).column( "col2" 
        ).as( "mycol" ).count().column( "col3" ).as( "mycount" ).distinct().column( "col4" ).as( "mydistinct" );

    qb.from( "table1" );

    auto ret = qb.query();

    std::cout << ret << std::endl;

    (void)std::cin.get();
    return EXIT_SUCCESS;
}