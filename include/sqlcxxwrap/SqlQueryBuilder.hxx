#ifndef __SQLQUERYBUILDER_HXX
#define __SQLQUERYBUILDER_HXX

#include <type_traits>
#include <variant>
#include "sqlcxxwrap/SqlQueryPrereq.hxx"

template<
    class TString,
    template <class> class TList
>
class SqlQueryBuilder final  
{
public:
    SqlQueryBuilder() = default;

    ~SqlQueryBuilder() = default;

    using TStringList = TList<TString>;
    using SelfBuilderClass = SqlQueryBuilder<TString,TList>;

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
            Column column = { ctRegular, RegularColumn{ columnName, "" } };
            
            mColumns.push_back( column );
            return *this;
        }

    private:

        
        
        struct RegularColumn final 
        {
            TString name;
            TString aliasName;
        };

        struct JoinColumn final
        {
            TString name;
            TString table;
            TString aliasName;
        };

        using ColumnVariant = std::variant<RegularColumn, JoinColumn>;

        enum ColumnType
        {
            ctRegular,
            ctJoin
        };

        struct Column
        {
            ColumnType type;
            ColumnVariant data;
        };

        TList<Column> mColumns;

        TStringList columnsList( const TString& tableName ) const
        {
            TStringList columns;

            for( auto& item : mColumns )
            {
                switch( item.type )
                {
                    case ctRegular:
                    {
                        auto regColumn = std::get<RegularColumn>( item.data );
                        TString push_name = tableName + "." + regColumn.name;

                        if( regColumn.aliasName.length() > 0 )
                        {
                            push_name += " AS " + regColumn.aliasName;
                        }

                        columns.push_back( push_name );
                        break;
                    }
                    case ctJoin:
                    {
                        auto jointColumn = std::get<JoinColumn>( item.data );
                        TString push_name = jointColumn.table + "." + jointColumn.name;

                        if( jointColumn.aliasName.length() > 0 )
                        {
                            push_name += " AS " + jointColumn.aliasName;
                        }

                        columns.push_back( push_name );
                        break;
                    }
                    default:
                    {
                        continue;
                    }
                }
            }

            return columns;
        }

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
        TString ret;
        ret = concateWord( ret, SELECT_KEYWQORD );

        ret = concateWord( ret, join( mSelect.columnsList(  mTableName ), "," ) );
        ret = concateWord( ret, FROM_KEYWQORD );
        ret = concateWord( ret, mTableName );
        
        return ret;
    }

private:
    const TString SELECT_KEYWQORD = "SELECT";
    const TString FROM_KEYWQORD = "FROM";
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

    TString concateWord( TString& instr, const TString& word ) const
    {
        TString ret;
        
        if( instr.length() > 0 )
        {
            ret += instr;
            ret += " ";
        }

        ret += word;
        
        return ret;
    }

    friend class SelectStatement;
    friend class FromStatement;

    SelectStatement mSelect;
    TString mTableName;
};

#endif // __SQLQUERYBUILDER_HXX