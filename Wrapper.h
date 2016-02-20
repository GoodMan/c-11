#ifndef WRAPPER_H
#define WRAPPER_H

#include "Widget.h"

class Wrapper
{
    public:
        using DataType = std::vector< Widget >;

    private:
        DataType data_;

    public:
        Warpper();

    public:
        ~Warpper();

    public:
        DataType& data()&;		//	for lvalue Wrapper
        DataType data()&&;		//	for rvalue Wrapper

        void push_back( const Widget& w );
};

#endif	//	 WRAPPER_H
