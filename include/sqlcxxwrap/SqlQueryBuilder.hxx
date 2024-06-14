#ifndef __SQLQUERYBUILDER_HXX
#define __SQLQUERYBUILDER_HXX

#include <type_traits>
#include <variant>
#include "sqlcxxwrap/SqlQueryPrereq.hxx"

template<
    class TString,
    template <class> class TList,
    class DebugOut
>
class SqlQueryBuilder final  
{
public:
    SqlQueryBuilder() = default;

    ~SqlQueryBuilder() = default;

    using TStringList = TList<TString>;
    using SelfBuilderClass = SqlQueryBuilder<TString,TList,DebugOut>;

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

        SelectStatement& column( const TString& columnName );
        

        SelectStatement& joinColumn( const TString& tableName, const TString& columnName );
       
        SelectStatement& as( const TString& aliasName );

        SelectStatement& distinct();

        SelectStatement& count();

        void reset();

    private:      
        enum ColumnType
        {
            ctRegular,
            ctJoin
        };

        struct Column
        {
            ColumnType type;
            TString name;
            TString aliasName;
            TString joinName;
            bool distinct;
            bool count;
        };

        bool mbAfterDistinct = false;
        bool mbAfterCount = false;

        TList<Column> mColumns;

        TStringList columnsList( const TString& tableName ) const;
    };

    SelectStatement& select() 
    {
        return mSelect;
    }

    void from( const TString& tableName )
    {
        mTableName = tableName;
    }

    TString query() const;

private:
    static const TString SELECT_KEYWQORD;
    static const TString FROM_KEYWQORD;
    static const TString COMMA_KEYWQORD;
    static const TString AS_KEYWQORD;
    static const TString WHERE_KEYWQORD;
    static const TString JOIN_KEYWQORD;
    static const TString ON_KEYWQORD;
    static const TString DISTINCT_KEYWQORD;
    static const TString COUNT_KEYWQORD;
    static const TString OPEN_BRACE_KEYWQORD;
    static const TString CLOSE_BRACE_KEYWQORD;

    static TString join( const TStringList& list, const TString& separator );

    static TString concateWord( TString& instr, const TString& word, bool bNoSpace = false );

    friend class SelectStatement;
    friend class FromStatement;

    SelectStatement mSelect;
    TString mTableName;
};

#include "sqlcxxwrap/SQBConsts.inl"

#include "sqlcxxwrap/SQBSelectStmtImpl.inl"

#include "sqlcxxwrap/SQBImpl.inl"

#endif // __SQLQUERYBUILDER_HXX

