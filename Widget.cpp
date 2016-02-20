#include "Widget.h"

#include <iostream>

bool Widget::LOG( true );

Widget::Widget()
	: id_( 0 )
{
	if ( Widget::LOG )
	{
		std::cout << " -> Widget: default ctor\n";
	}
}

Widget::Widget( const Widget& other )
	: id_( other.id_ )
{
	if ( Widget::LOG )
	{
		std::cout << " -> Widget: copy ctor\n";
	}
}

Widget::Widget( Widget&& other )
	: id_( other.id_ )
{
	other.id_ = -1;	//	invalidate
	if ( Widget::LOG )
	{
		std::cout << " -> Widget: move ctor\n";
	}
}

Widget::~Widget()
{
	//std::cout << "Widget: dtor\n";
}

Widget& Widget::operator=( const Widget& rhs )
{
	this->id_ = rhs.id_;
	if ( Widget::LOG )
	{
		std::cout << " -> Widget: assign operator\n";
	}

	return *this;
}

Widget& Widget::operator=( Widget&& rhs )
{
	this->id_ = rhs.id_;
	rhs.id_ = -1;	//	invalidate

	if ( Widget::LOG )
	{
		std::cout << " -> Widget: move operator\n";
	}

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
