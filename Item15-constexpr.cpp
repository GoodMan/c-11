#include "BHSTimeUtil.h"

#include <iostream>

namespace
{

constexpr uint32_t gaussConstExpr( const uint32_t num )
{
    return ( num == 0 ? 0 : num + gaussConstExpr( num - 1 ) );
}

uint32_t gauss( const uint32_t num )
{
    return ( num == 0 ? 0 : num + gauss( num - 1 ) );
}

}	//	anoymous namesapce

int main( int argc, char* argv[] )
{
	//
	//	The result varies, and don't forget to set '-fconstexpr-depth=xxx' where xxx is depth
	//
    //	r1 = 1250025000
    //	Elapsed time : 3.68e-07 seconds.
    //	               0 m secs.
    //	               0 u secs.
    //	               368 n secs.
    //
    //	r2 = 1250025000
    //	Elapsed time : 0.00602588 seconds.
    //	               6 m secs.
    //	               6025 u secs.
    //	               6025876 n secs.

    BHSTimeUtil::BHSClock clock;

    //	Rember!!!
    //	If you call only gaussConstExpr without taking return value with constexpr qualifier,
    //	then it will not be constexpr and it takes more time than non-constexpr function
    //
    //		gaussConstExpr( 50000 );	            //	it won't be constexpr
    //		uint32_t r1 = gaussConstExpr( 50000 );	//	it won't be constexpr
    //
    clock.on();
    constexpr uint32_t r1 = gaussConstExpr( 50000 );
    clock.off();
    std::cout << "r1 = " << r1 << '\n';
    std::cout << clock << '\n';

    clock.on();
    uint32_t r2 = gauss( 50000 );
    clock.off();
    std::cout << "r2 = " << r2 << '\n';
    std::cout << clock << '\n';

    return 0;
}

