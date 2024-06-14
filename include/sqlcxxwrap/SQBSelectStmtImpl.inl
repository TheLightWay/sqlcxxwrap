template <class TString, template <class> class TList>
typename SqlQueryBuilder<TString, TList>::TStringList 
SqlQueryBuilder<TString, TList>::SelectStatement::columnsList( const TString& tableName ) const
{
    TStringList columns;

    for( auto& item : mColumns )
    {
        TString push_name;
        switch( item.type )
        {
            case ctRegular:
            {
                push_name = tableName + "." + item.name;
                break;
            }
            case ctJoin:
            {
                push_name = item.joinName + "." + item.name;
                break;
            }
            default:
            {
                continue;
            }
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

template <class TString, template <class> class TList>
inline typename SqlQueryBuilder<TString, TList>::SelectStatement& 
SqlQueryBuilder<TString, TList>::SelectStatement::column( const TString& columnName )
{   
    Column column = { ctRegular, columnName, "", "", 
    this->mbAfterDistinct, this->mbAfterCount };

    this->mbAfterDistinct = false;
    this->mbAfterCount = false;
    
    mColumns.push_back( column );
    return *this;
}

template <class TString, template <class> class TList>
inline typename SqlQueryBuilder<TString, TList>::SelectStatement& 
SqlQueryBuilder<TString, TList>::SelectStatement::joinColumn( const TString& tableName, const TString& columnName )
{   
    Column column = { ctJoin, columnName, "", tableName, 
    this->mbAfterDistinct, this->mbAfterCount };

    this->mbAfterDistinct = false;
    this->mbAfterCount = false;
    
    mColumns.push_back( column );
    return *this;
}

template <class TString, template <class> class TList>
typename SqlQueryBuilder<TString, TList>::SelectStatement& 
SqlQueryBuilder<TString, TList>::SelectStatement::as( const TString& aliasName )
{
    if( mColumns.empty() )
    {
        return *this;
    }

    auto& column = mColumns.back();

    column.aliasName = aliasName;

    return *this;
}

template <class TString, template <class> class TList>
inline typename SqlQueryBuilder<TString, TList>::SelectStatement& 
SqlQueryBuilder<TString, TList>::SelectStatement::distinct()
{   
    this->mbAfterDistinct = true;
    return *this;
}

template <class TString, template <class> class TList>
inline typename SqlQueryBuilder<TString, TList>::SelectStatement& 
SqlQueryBuilder<TString, TList>::SelectStatement::count()
{   
    this->mbAfterCount = true;
    return *this;
}

template <class TString, template <class> class TList>
void
SqlQueryBuilder<TString, TList>::SelectStatement::reset()
{
    mColumns.clear();
    mbAfterDistinct = false;
    mbAfterCount = false;
}

