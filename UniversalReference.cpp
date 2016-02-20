#include "Widget.h"

#include <iostream>
#include <typeinfo>
#include <utility>


template< typename T >
void foo( T&& param )	//	Universal reference
{
	std::cout << "T=    " << typeid( T ).name() << '\n';
	std::cout << "param=" << typeid( param ).name() << '\n';
}

void f( Widget & w )
{
	std::cout << "lvaue reference\n";
}

void f( const Widget & w )
{
	std::cout << "const lvaue reference\n";
}

void f( Widget && w )
{
	std::cout << "rvalue reference\n";
}

int main( int argc, char* argv[] )
{

	Widget w;
	Widget w2;

	std::cout << "----------------\n";
	std::cout << "Widget wr1 = Widget();\n";
	Widget&& wr1 = Widget();

	std::cout << "----------------\n";
	std::cout << "auto wa1 = w;\n";
	auto wa1 = w;

	std::cout << "----------------\n";
	std::cout << "auto wa2 = Widget();\n";
	auto wa2 = Widget();

	std::cout << "----------------\n";
	std::cout << "auto&& war1 = Widget();\n";
	auto&& war1 = Widget();

	std::cout << "----------------\n";
	std::cout << "auto&& war2 = w;\n";
	auto&& war2 = w;

	std::cout << "----------------\n";
	std::cout << "war1 = war2\n";
	war1 = war2;

	std::cout << "----------------\n";
	std::cout << "war1 = wa2\n";
	war1 = wa2;

	std::cout << "----------------\n";
	std::cout << "war2 = Widget()\n";
	war2 = Widget();

	std::cout << "----------------\n";
	std::cout << "auto wa3 = wa1;\n";
	auto wa3 = wa1;

	std::cout << "----------------\n";
	std::cout << "auto wa4 = wa2;\n";
	auto wa4 = wa2;

	std::cout << "----------------\n";
	std::cout << "f( Widget() );\n";
	f( Widget() );

	std::cout << "----------------\n";
	std::cout << "f( wa2 );\n";
	f( wa2 );

	return 0;
}
