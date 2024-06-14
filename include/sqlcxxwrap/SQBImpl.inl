template <class TString, template <class> class TList, class DebugOut>
TString SqlQueryBuilder<TString, TList, DebugOut>::join( const TStringList& list, const TString& separator )
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

template <class TString, template <class> class TList, class DebugOut>
TString SqlQueryBuilder<TString, TList, DebugOut>::concateWord( TString& instr, const TString& word, bool bNoSpace )
{
    TString ret;
        
    if( instr.length() > 0 )
    {
        ret += instr;

        if( !bNoSpace )
        {
            ret += " ";
        }
    }

    ret += word;
    
    return ret;
}

template <class TString, template <class> class TList, class DebugOut>
TString SqlQueryBuilder<TString, TList, DebugOut>::query() const
{
    TString ret;
    ret = concateWord( ret, SELECT_KEYWQORD );

    ret = concateWord( ret, join( mSelect.columnsList(  mTableName ), COMMA_KEYWQORD ) );
    ret = concateWord( ret, FROM_KEYWQORD );
    ret = concateWord( ret, mTableName );
        
    return ret;
}
