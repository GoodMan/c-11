#ifndef WIDGET_H
#define WIDGET_H

class Widget
{
	//
	//	Atrributes
	//
	private:
		int id_;

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
};

#endif //	WIDGET_H
