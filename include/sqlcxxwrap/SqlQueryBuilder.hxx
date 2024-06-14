#ifndef __SQLQUERYBUILDER_HXX
#define __SQLQUERYBUILDER_HXX

#include <type_traits>
#include "sqlcxxwrap/SqlQueryPrereq.hxx"

template<
    class TString,
    class TChar,
    template<class> class TList
>
class SqlQueryBuilder final  
{
public:
    SqlQueryBuilder() = default;

    ~SqlQueryBuilder() = default;

    using TStringList = TList<TString>;
    using SelfBuilderClass = SqlQueryBuilder<TString,TChar,TList>;

    enum sqDataType
    {
        dtText,
        dtInt,
        dtDouble,
        dtDateTime
    };

    class SelectStatement final 
    {
    private:
        friend class SqlQueryBuilder;
        SelectStatement() = default;
        ~SelectStatement() = default;
    public:

        SelectStatement& column( const TString& columnName )
        {
            mColumns.push_back( columnName );
            return *this;
        }
    private:
        TStringList mColumns;
    };

    SelectStatement& select() 
    {
        return mSelect;
    }

    void from( const TString& tableName )
    {
        mTableName = tableName;
    }

    TString query() const
    {
        TString ret = "SELECT ";
        
        ret += join( mSelect.mColumns, "," );
        ret += " FROM ";
        ret += mTableName;
        
        return ret;
    }

private:

    TString join( const TStringList& list, const TString& separator ) const
    {
        TString ret;
    
        for( auto& item : list )
        {
            if( ret.length() > 0 )
            {
                ret += separator;
            }

            ret += item;
        }

        return ret;
    }

    friend class SelectStatement;
    friend class FromStatement;

    SelectStatement mSelect;
    TString mTableName;
};

#endif // __SQLQUERYBUILDER_HXX