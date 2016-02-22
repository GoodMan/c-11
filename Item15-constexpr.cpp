#include <iostream>
#include <iomanip>
#include <chrono>

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

}

class BHSClock
{
    private:
        std::chrono::steady_clock::time_point start;
        std::chrono::steady_clock::time_point end;

    public:
        void on()
        {
            start = std::chrono::steady_clock::now();
        }

        void off()
        {
            end = std::chrono::steady_clock::now();
        }

        std::ostream& report( std::ostream& os ) const
        {
            std::chrono::duration< double > timeSpanInSecs
                = std::chrono::duration_cast< std::chrono::duration< double > >( end - start );

            std::chrono::milliseconds timeSpanInMilliSecs
                = std::chrono::duration_cast< std::chrono::milliseconds >( end - start );
            std::chrono::microseconds timeSpanInMicroSecs
                = std::chrono::duration_cast< std::chrono::microseconds >( end - start );
            std::chrono::nanoseconds timeSpanInNanoSecs
                = std::chrono::duration_cast< std::chrono::nanoseconds >( end - start );

            return os << "Elapsed time : " << timeSpanInSecs.count()      << " seconds.\n"
                   << "               " << timeSpanInMilliSecs.count() << " m secs.\n"
                   << "               " << timeSpanInMicroSecs.count() << " u secs.\n"
                   << "               " << timeSpanInNanoSecs.count()  << " n secs.\n"
                   ;
        }
};

std::ostream& operator<<( std::ostream& os, const BHSClock& clock )
{
    return clock.report( os );
}


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

    BHSClock clock;

    //	Rember!!!
    //	If you call only gaussConstExpr without taking return value,
    //	then it will not be constexprt and it takes more time than non-constexpr function
    //
    //		gaussConstExpr( 50000 );	            //	it won't be constexprt
    //		uint32_t r1 = gaussConstExpr( 50000 );	//	it won't be constexprt
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

