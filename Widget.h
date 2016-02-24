////////////////////////////////////////////////////////////////////////////////
#ifndef WIDGET_H
#define WIDGET_H

#include <string>

////////////////////////////////////////////////////////////////////////////////

class Widget
{
	//
	//	Atrributes
	//
	private:
		static uint32_t counter_;
		int id_;
		std::string name_;

	public:
		static bool LOG;

	//
	//	ctor
	//
	public:
		Widget();						// default ctor
		Widget( const Widget& other );	//	copy ctor
		Widget( Widget&& other );		//	move ctor

	//
	//	dtor
	//
	public:
		~Widget();

	//
	//	operators
	//
	public:
		Widget& operator=( const Widget& rhs );
		Widget& operator=( Widget&& rhs );

		void id( int id );
		int  id();

        void whoami();

        void name( const std::string& name );
        const std::string& name();
};

////////////////////////////////////////////////////////////////////////////////

#endif //	WIDGET_H

////////////////////////////////////////////////////////////////////////////////
