#include <cstdlib>
#include <cstdio>

#include <iostream>
#include <string>
#include <list>

#include "sqlcxxwrap/SqlQueryBuilder.hxx"

using StlSqlQueryBuilder = SqlQueryBuilder<std::string,
                           std::list>;

int main( int argc, char* argv[] )
{
    StlSqlQueryBuilder qb;

    qb.select( ).column( "col1" ).column( "col2" ).as( "mycol" ).column( "col3" );

    qb.from( "table1" );

    auto ret = qb.query();

    std::cout << ret << std::endl;

    (void)std::cin.get();
    return EXIT_SUCCESS;
}