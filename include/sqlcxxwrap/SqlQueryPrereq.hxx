#ifndef __SQLQUERYPREREQ_HXX
#define __SQLQUERYPREREQ_HXX

class SqlNoCopyAssignment
{
private:
    SqlNoCopyAssignment( const SqlNoCopyAssignment& ) = delete;
    SqlNoCopyAssignment( SqlNoCopyAssignment&& ) = delete;
    SqlNoCopyAssignment& operator=( const SqlNoCopyAssignment& ) = delete;
    SqlNoCopyAssignment& operator=( SqlNoCopyAssignment&& ) = delete;
};

#endif // __SQLQUERYPREREQ_HXX