template <class TString, template <class> class TList, class DebugOut>
typename SqlQueryBuilder<TString, TList, DebugOut>::TStringList 
SqlQueryBuilder<TString, TList, DebugOut>::SelectStatement::columnsList( const TString& tableName ) const
{
    TStringList columns;

    for( auto& item : mColumns )
    {
        TString push_name;

        if( item.distinct )
        {
            push_name = SelfBuilderClass::concateWord( push_name, SelfBuilderClass::DISTINCT_KEYWQORD );
        }
        if( item.count )
        {
            push_name = SelfBuilderClass::concateWord( push_name, SelfBuilderClass::COUNT_KEYWQORD, true );
            push_name = SelfBuilderClass::concateWord( push_name, SelfBuilderClass::OPEN_BRACE_KEYWQORD, true );
        }


        TString colName;
        switch( item.type )
        {
            case ctRegular:
            {
                colName = ( tableName + "." + item.name );
                break;
            }
            case ctJoin:
            {
                colName = ( item.joinName + "." + item.name );
                break;
            }
            default:
            {
                continue;
            }
        }

        push_name = SelfBuilderClass::concateWord( push_name, colName );

        if( item.count )
        {
            push_name = SelfBuilderClass::concateWord( push_name, SelfBuilderClass::CLOSE_BRACE_KEYWQORD );
        }

        if( item.aliasName.length() > 0 )
        {
            push_name = SelfBuilderClass::concateWord( push_name, SelfBuilderClass::AS_KEYWQORD );
            push_name = SelfBuilderClass::concateWord( push_name, item.aliasName );
        }
        
        if( push_name.length() > 0 ) 
        {
            columns.push_back( push_name );
        } 
    }

    return columns;
}

template <class TString, template <class> class TList, class DebugOut>
inline typename SqlQueryBuilder<TString, TList, DebugOut>::SelectStatement& 
SqlQueryBuilder<TString, TList, DebugOut>::SelectStatement::column( const TString& columnName )
{   
    Column column = { ctRegular, columnName, "", "", 
    this->mbAfterDistinct, this->mbAfterCount };

    this->mbAfterDistinct = false;
    this->mbAfterCount = false;
    
    mColumns.push_back( column );
    return *this;
}

template <class TString, template <class> class TList, class DebugOut>
inline typename SqlQueryBuilder<TString, TList, DebugOut>::SelectStatement& 
SqlQueryBuilder<TString, TList, DebugOut>::SelectStatement::joinColumn( const TString& tableName, const TString& columnName )
{   
    Column column = { ctJoin, columnName, "", tableName, 
    this->mbAfterDistinct, this->mbAfterCount };

    this->mbAfterDistinct = false;
    this->mbAfterCount = false;
    
    mColumns.push_back( column );
    return *this;
}

template <class TString, template <class> class TList, class DebugOut>
typename SqlQueryBuilder<TString, TList, DebugOut>::SelectStatement& 
SqlQueryBuilder<TString, TList, DebugOut>::SelectStatement::as( const TString& aliasName )
{
    if( mColumns.empty() )
    {
        return *this;
    }

    auto& column = mColumns.back();

    column.aliasName = aliasName;

    return *this;
}

template <class TString, template <class> class TList, class DebugOut>
inline typename SqlQueryBuilder<TString, TList, DebugOut>::SelectStatement& 
SqlQueryBuilder<TString, TList, DebugOut>::SelectStatement::distinct()
{   
    this->mbAfterDistinct = true;
    return *this;
}

template <class TString, template <class> class TList, class DebugOut>
inline typename SqlQueryBuilder<TString, TList, DebugOut>::SelectStatement& 
SqlQueryBuilder<TString, TList, DebugOut>::SelectStatement::count()
{   
    this->mbAfterCount = true;
    return *this;
}

template <class TString, template <class> class TList, class DebugOut>
void
SqlQueryBuilder<TString, TList, DebugOut>::SelectStatement::reset()
{
    mColumns.clear();
    mbAfterDistinct = false;
    mbAfterCount = false;
}

