#include <iostream>
#include <vector>
#include <typeinfo>

template< typename T >
void f(const T& param)
{
	std::cout << "T=    " << typeid( T ).name() << '\n';
	std::cout << "param=" << typeid( param ).name() << '\n';

}


std::vector< Widget > createVec()
{
	return std::vector< Widget >( 1, Widget() );
}

int main( int argc, char* argv[] )
{

const auto vw = createVec();

if ( not vw.empty() )
{
	f( &vw[ 0 ] );	//	const Widget* const&
}

return 0;
}


