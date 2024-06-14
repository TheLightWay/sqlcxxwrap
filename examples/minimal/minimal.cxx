#include <cstdlib>
#include <cstdio>

#include <string>

#include "sqlcxxwrap/SqlQueryBuilder.hxx"

using StlSqlQueryBuilder = SqlQueryBuilder<std::string,std::string::value_type>;

int main( int argc, char* argv[] )
{
    printf( "Hello World!\n" );
    return EXIT_SUCCESS;
}