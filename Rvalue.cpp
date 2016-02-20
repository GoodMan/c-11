#include "Widget.h"

#include <iostream>
#include <typeinfo>


void bar( Widget & param )
{
	std::cout << " -> lvaue reference\n";
	//std::cout << "  param=" << typeid( param ).name() << '\n';
}

void bar( const Widget & param )
{
	std::cout << " -> const lvaue reference\n";
	//std::cout << "  param=" << typeid( param ).name() << '\n';
}

void bar( Widget && param )
{
	std::cout << " -> rvalue reference\n";
	//std::cout << "  param=" << typeid( param ).name() << '\n';
}

template< typename T >
void foo( T&& param )	//	Universal reference
{
	//	however, param is lvalue now

	//std::cout << "  T=    " << typeid( T ).name() << '\n';
	//std::cout << "  param=" << typeid( param ).name() << '\n';
	std::cout << "  bar( param );\n";
	bar( param );
}

void f( Widget & param )
{
	std::cout << " -> lvaue reference\n";
	//std::cout << "  param=" << typeid( param ).name() << '\n';
}

void f( const Widget & param )
{
	std::cout << " -> const lvaue reference\n";
	//std::cout << "  param=" << typeid( param ).name() << '\n';
}

void f( Widget && param )
{
	std::cout << " -> rvalue reference\n";
	//std::cout << "  param=" << typeid( param ).name() << '\n';
}

//	return value is temporary so that it's rvalue
Widget getWidget()
{
	return Widget();
}

void letsCheck()
{
	Widget::LOG = true;

	std::cout << "Let's check move ctor and move operator\n";
	std::cout << "=======================================\n";

	std::cout << "----------------\n";
	std::cout << "Widget wd;\n";
	Widget wd;

	std::cout << "----------------\n";
	std::cout << "Widget wc{ Widget() };\n";
	std::cout << "  thanks to compiler ;)\n";
	//	Widget() is rvalue
	//	There is no difference between pre c++11 and c++11
	Widget wc{ Widget() };

	std::cout << "----------------\n";
	std::cout << "wc = Widget();\n";
	//	Widget() is rvalue
	//	prior to c++11, assign operator will be called
	//	since c++11, however, move operator will be called
	wc = Widget();
	std::cout << "wc = getWidget();\n";
	wc = getWidget();

	std::cout << "----------------\n";
	std::cout << "Widget w;\n";
	Widget w;
	std::cout << "w = wc;	//	wc is lvalue\n";
	//	wc ls lvalue
	//	There is no difference between pre c++11 and c++11
	std::cout << "wc.id( 100 ); // set 100 to id of wc\n";
	wc.id( 100 );
	std::cout << "wc.id() = " << wc.id() << "\n";
	std::cout << "w = wc;\n";
	w = wc;
	std::cout << "w.id() = " << w.id() << "\n";
	w.id( 10 );
	std::cout << "w.id( 10 ); // set 10 to id of w\n";
	std::cout << "w.id() = " << w.id() << "\n";

	std::cout << "----------------\n";
	std::cout << "Widget& wr{ w };\n";
	Widget& wr{ w };
	std::cout << "wr.id() = " << wr.id() << "\n";
	std::cout << "w.id() = " << w.id() << "\n";
	std::cout << "wr = wc;	//	wc is lvalue, however wr is reference. Can you imagine what we have done?;)\n";
	//	wc ls lvalue
	//	There is no difference between pre c++11 and c++11
	wr = wc;	//	we updated 'w';).  See below
	std::cout << "wc.id() = " << wc.id() << "\n";
	std::cout << "wr.id() = " << wr.id() << "\n";
	std::cout << "w.id() = " << w.id() << "\n";

	std::cout << "----------------\n";
	std::cout << "Widget&& wrr = Widget();\n";
	std::cout << "  thanks to compiler ;)\n";
	//	Widget() is rvalue
	//	wrr is rvalue reference
	Widget&& wrr{ Widget() };

	std::cout << "----------------\n";
	std::cout << "wrr = Widget();\n";
	//	It's valid because Widget() is rvalue
	wrr = Widget();
	std::cout << "wrr = getWidget();\n";
	wrr = getWidget();

	std::cout << "----------------\n";
	std::cout << "wrr = wc;	//	wc is lvalue\n";
	//	It's valid because wrr is lvalue
	wrr = wc;

	std::cout << "----------------\n";
	std::cout << "Widget&& wrr2{ wrr }; // compile error\n";
	//	It's invalid, because wrr is lvalue.
	//Widget&& wrr2{ wrr };	//	compile error

	std::cout << "----------------\n";
	std::cout << "Widget&& wmc3{ Widget() };\n";
	Widget&& wrr3{ Widget() };
	std::cout << "wrr3 = wrr;	//	wrr is lvalue\n";
	//	It's invalid, because wrr is lvalue.
	wrr3 = wrr;

	std::cout << "----------------\n";
	std::cout << "Widget&& w( getWidget() );\n";
	const Widget&& cwrr{ getWidget() };
	std::cout << "cwrr = getWidget();	//	compile error\n";
	//	because cwrr is const rvalue reference
	//cwrr = getWidget();

	std::cout << "=======================================\n";
}

void functionParameter()
{
	Widget::LOG = false;

	std::cout << "function parameter\n";
	std::cout << "=======================================\n";

	std::cout << "----------------\n";
	std::cout << "const Widget cw;\n";
	const Widget cw;
	std::cout << "----------------\n";
	std::cout << "f( cw );\n";
	std::cout << " -> expected const lvaue reference\n";
	f( cw );	//	if we don't have f( const Widget& ), then f( Widget&& ) will be invoked

	std::cout << "----------------\n";
	std::cout << "Widget w;\n";
	Widget w;
	std::cout << "----------------\n";
	std::cout << "f( w );\n";
	std::cout << " -> expected lvaue reference\n";
	f( w );

	std::cout << "----------------\n";
	std::cout << "Widget&& wrr{ Widget() };\n";
	Widget&& wrr{ Widget() };	//	wrr itself is lvalue ;)
	std::cout << "----------------\n";
	std::cout << "f( wrr );\n";
	std::cout << " -> expected lvaue reference\n";
	f( wrr );

	std::cout << "----------------\n";
	std::cout << "f( Widget() );\n";
	std::cout << " -> expected rvalue reference\n";
	f( Widget() );

	std::cout << "----------------\n";
	std::cout << "const Widget& cwr{ getWidget() };\n";
	const Widget& cwr{ getWidget() };
	std::cout << "f( cwr );\n";
	std::cout << " -> expected const lvaue reference\n";
	f( cwr );

	std::cout << "----------------\n";
	std::cout << "Widget w2{ getWidget() };\n";
	Widget w2{ getWidget() };
	std::cout << "f( w2 );\n";
	std::cout << " -> expected lvaue reference\n";
	f( w2 );

	std::cout << "----------------\n";
	std::cout << "const Widget&& cwrr{ getWidget() };\n";
	const Widget&& cwrr{ getWidget() };
	std::cout << "f( cwrr );\n";
	std::cout << " -> expected const lvaue reference\n";
	f( cwrr );

	std::cout << "=======================================\n";
}

void templateFunctionParameter()
{
	Widget::LOG = false;

	std::cout << "template function parameter\n";
	std::cout << "=======================================\n";

	std::cout << "----------------\n";
	std::cout << "const Widget cw;\n";
	const Widget cw;

	std::cout << "----------------\n";
	std::cout << "foo( cw );\n";
	std::cout << " -> expected const lvaue reference\n";
	foo( cw );	//	if we don't have f( const Widget& ), then f( Widget&& ) will be invoked

	std::cout << "----------------\n";
	std::cout << "Widget w;\n";
	Widget w;

	std::cout << "----------------\n";
	std::cout << "foo( w );\n";
	std::cout << " -> expected lvaue reference\n";
	foo( w );

	std::cout << "----------------\n";
	std::cout << "Widget&& wrr{ Widget() };\n";
	Widget&& wrr{ Widget() };	//	wrr itself is lvalue ;)

	std::cout << "----------------\n";
	std::cout << "foo( wrr );\n";
	std::cout << " -> expected lvaue reference\n";
	foo( wrr );

	std::cout << "----------------\n";
	std::cout << "foo( Widget() );\n";
	std::cout << " -> expected rvalue reference\n";
	foo( Widget() );

	std::cout << "----------------\n";
	std::cout << "const Widget& cwr{ getWidget() };\n";
	const Widget& cwr{ getWidget() };
	std::cout << "foo( cwr );\n";
	std::cout << " -> expected const lvaue reference\n";
	foo( cwr );

	std::cout << "----------------\n";
	std::cout << "Widget w2{ getWidget() };\n";
	Widget w2{ getWidget() };
	std::cout << "foo( w2 );\n";
	std::cout << " -> expected lvaue reference\n";
	foo( w2 );

	std::cout << "----------------\n";
	std::cout << "const Widget&& cwrr{ getWidget() };\n";
	const Widget&& cwrr{ getWidget() };
	std::cout << "foo( cwrr );\n";
	std::cout << " -> expected const lvaue reference\n";
	foo( cwrr );

	std::cout << "=======================================\n";
}

int main( int argc, char* argv[] )
{
	letsCheck();

	functionParameter();

	templateFunctionParameter();

	return 0;
}
