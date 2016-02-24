////////////////////////////////////////////////////////////////////////////////
#include "Widget.h"

#include <iomanip>
#include <iostream>
#include <sstream>
#include <utility>
#include <stdexcept>

////////////////////////////////////////////////////////////////////////////////

int limit_ = 0;

bool Widget::LOG( true );
uint32_t Widget::counter_ = 0;

namespace
{

void nameIt( std::string& name, uint32_t id )
{
    std::ostringstream ostrm;

    ostrm << name << " " << std::setw( 4 ) << std::setfill( '0' ) << id ;

    name = ostrm.str();	//	move assignment ;)
}

}

Widget::Widget()
    : id_( ++ Widget::counter_ ),
      name_( "I am Widget" )
{
    nameIt( name_, id_ );
    //++ Widget::counter_;

    if( Widget::LOG )
    {
        std::cout << " -> Widget: default ctor\n";
    }
}


Widget::Widget( const Widget& other )
    : id_( other.id_ ),
      name_( other.name_ )
{
    if( Widget::LOG )
    {
        std::cout << " -> Widget: copy ctor\n";
    }
}


Widget::Widget( Widget&& other )
    : id_( other.id_ ),
      name_( std::move( other.name_ ) )
{
    if( Widget::LOG )
    {
        std::cout << " -> Widget: move ctor\n";
    }

    if( ++limit_ > 5 )
    {
        throw std::runtime_error( "---" );
    }
}


Widget::~Widget()
{
    //std::cout << "Widget: dtor\n";
}


Widget& Widget::operator=( const Widget& rhs )
{
    if( Widget::LOG )
    {
        std::cout << " -> Widget: assign operator\n";
    }

    if( this != &rhs )
    {
        //	Widget: copy ctor
        Widget temp( rhs );
		//	std::swap
        //	-> Widget: move ctor
        //	-> Widget: move operator
        //	-> Widget: move operator
        //	bacuase, std::swap does as below
        //	  	T c(std::move(a));
        //		a=std::move(b);
        //		b=std::move(c);
        std::swap( *this, temp );
    }

    return *this;
}


Widget& Widget::operator=( Widget&& rhs )
{
    if( Widget::LOG )
    {
        std::cout << " -> Widget: move operator\n";
    }

    //	call base class' move assign operator if any
    //	Base::operator=( rhs )
    //	then move member variables
    this->id_ = std::move( rhs.id_ );
    //rhs.id_ = -1;	//	invalidate
    name_ = std::move( rhs.name_ );
    // 	don't use std::swap for move assign operator
	//	see comments in copy assign operator

    return *this;
}


void Widget::id( int id )
{
    id_ = id;
}


int Widget::id()
{
    return id_;
}


void Widget::whoami()
{
    std::cout << "  Widget::id_=(" << id_ << ")\n";
    std::cout << "  Widget::name_=(" << name_ << ")\n";
}


void Widget::name( const std::string& name )
{
    name_ = name;
}

const std::string& Widget::name()
{
    return name_;
}
////////////////////////////////////////////////////////////////////////////////
