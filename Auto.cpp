#include "Widget.h"

#include <iostream>
#include <typeinfo>
#include <utility>


#ifdef CHAP1
void foo( Widget & w )
{
	std::cout << " -> lvaue reference\n";
}

void foo( const Widget & w )
{
	std::cout << " -> const lvaue reference\n";
}

void foo( Widget && w )
{
	std::cout << " -> rvalue reference\n";
}

template< typename T >
void f( T&& param )	//	Universal reference
{
	std::cout << "T=    " << typeid( T ).name() << '\n';
	std::cout << "param=" << typeid( param ).name() << '\n';
	foo( param );
}
#else

void f( Widget & w )
{
	std::cout << " -> lvaue reference\n";
}

void f( const Widget & w )
{
	std::cout << " -> const lvaue reference\n";
}

void f( Widget && w )
{
	std::cout << " -> rvalue reference\n";
}

#ifdef CPP14
void fa( auto w )
{
	std::cout << " -> ??? reference\n";
}
#endif
#endif

int main( int argc, char* argv[] )
{

	std::cout << "----------------\n";
	std::cout << "Widget wd;\n";
	Widget wd;

	std::cout << "----------------\n";
	std::cout << "auto wc = Widget();\n";
	auto wc = Widget();

	std::cout << "----------------\n";
	std::cout << "wc = Widget();\n";
	wc = Widget();

	std::cout << "----------------\n";
	std::cout << "Widget wa;\n";
	Widget wa;
	std::cout << "wa = wc;\n";
	wa = wc;

	std::cout << "----------------\n";
	std::cout << "auto&& wmc = Widget();\n";
	auto&& wmc = Widget();

	std::cout << "----------------\n";
	std::cout << "wmc = Widget();\n";
	wmc = Widget();

	std::cout << "----------------\n";
	std::cout << "wmc = wc;\n";
	wmc = wc;

	std::cout << "----------------\n";
	std::cout << "auto&& wmc2 = wmc; // compile error\n";
	//auto&& wmc2 = wmc;	// compile error

	std::cout << "----------------\n";
	std::cout << "const Widget cw;\n";
	const Widget cw;

	std::cout << "----------------\n";
	std::cout << "f( cw );\n";
	std::cout << " -> expected const lvaue reference\n";
	f( cw );

	std::cout << "----------------\n";
	std::cout << "f( wd );\n";
	std::cout << " -> expected lvaue reference\n";
	f( wd );

	std::cout << "----------------\n";
	std::cout << "f( wmc );\n";
	std::cout << " -> expected const lvaue reference\n";
	f( wmc );

	std::cout << "----------------\n";
	std::cout << "f( Widget() );\n";
	std::cout << " -> expected rvalue reference\n";
	f( Widget() );

	return 0;
}
