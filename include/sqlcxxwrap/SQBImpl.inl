template <class TString, template <class> class TList>
TString SqlQueryBuilder<TString, TList>::join( const TStringList& list, const TString& separator )
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

template <class TString, template <class> class TList>
TString SqlQueryBuilder<TString, TList>::concateWord( TString& instr, const TString& word )
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

template <class TString, template <class> class TList>
TString SqlQueryBuilder<TString, TList>::query() const
{
    TString ret;
    ret = concateWord( ret, SELECT_KEYWQORD );

    ret = concateWord( ret, join( mSelect.columnsList(  mTableName ), COMMA_KEYWQORD ) );
    ret = concateWord( ret, FROM_KEYWQORD );
    ret = concateWord( ret, mTableName );
        
    return ret;
}
