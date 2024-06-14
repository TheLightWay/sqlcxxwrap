#ifndef __SQLQUERYPREREQ_HXX
#define __SQLQUERYPREREQ_HXX

template<class TString>
class DefaultDebugOutput
{
public:
    DefaultDebugOutput& operator <<( const TString& instr ) 
    { 
        return *this; 
    }
};


#endif // __SQLQUERYPREREQ_HXX