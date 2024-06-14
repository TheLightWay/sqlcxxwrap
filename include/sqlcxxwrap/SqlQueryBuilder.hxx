#ifndef __SQLQUERYBUILDER_HXX
#define __SQLQUERYBUILDER_HXX

#include "sqlcxxwrap/SqlQueryPrereq.hxx"

template<
    class TString,
    class TChar
>
class SqlQueryBuilder final : public SqlNoCopyAssignment 
{
public:
    SqlQueryBuilder() = default;
    ~SqlQueryBuilder() = default;
private:
    TString mQuery;
};

#endif // __SQLQUERYBUILDER_HXX